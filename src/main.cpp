#include <lvgl.h>
#include <TFT_eSPI.h>
#include <ui.h>
#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <SpotifyArduino.h>
#include <SpotifyArduinoCert.h>

#include "List_SPIFFS.h"
#include "Web_Fetch.h"
#include <SPIFFS.h>
#include <TJpg_Decoder.h>

// Credentials
#define WIFI_SSID ""
#define WIFI_PASS ""
#define SPOTIFY_CLIENT_ID ""
#define SPOTIFY_CLIENT_SECRET ""
#define SPOTIFY_REFRESH_TOKEN ""
#define SPOTIFY_MARKET ""

WiFiClientSecure client;
SpotifyArduino spotify(client, SPOTIFY_CLIENT_ID, SPOTIFY_CLIENT_SECRET, SPOTIFY_REFRESH_TOKEN);

unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 5000;
unsigned long lastUIUpdateTime = 0;
const unsigned long updateUIInterval = 1000;
static bool firstTimeLoad = true;
static bool needChangeAlbumImage = false;

static String currentTrackURI;
static String currentContext;
static String currentSong;
static String currentArtist;
static int currentProgress = 0;
static int currentDuration = 0;
static String currentAlbumImageURL;

#define ROTARY_SW 25
#define ROTARY_DT 26
#define ROTARY_CLK 27
unsigned long rotaryLastChangeTime = 0;
unsigned long rotaryStableTime = 500;
bool rotaryIsStable = false;

static int volumeDifference = 0;
static int playbackVolume = 50;
static int currentStateCLK;
static int lastStateCLK;

/*Don't forget to set Sketchbook location in File/Preferences to the path of your UI project (the parent foder of this INO file)*/

/*Change to your screen resolution*/
static const uint16_t screenWidth  = 480;
static const uint16_t screenHeight = 320;

enum { SCREENBUFFER_SIZE_PIXELS = screenWidth * screenHeight / 10 };
static lv_color_t buf [SCREENBUFFER_SIZE_PIXELS];

TFT_eSPI tft = TFT_eSPI( screenWidth, screenHeight ); /* TFT instance */

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char * buf)
{
    Serial.printf(buf);
    Serial.flush();
}
#endif

/* Display flushing */
void my_disp_flush (lv_display_t *disp, const lv_area_t *area, uint8_t *pixelmap) {
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    if (LV_COLOR_16_SWAP) {
        size_t len = lv_area_get_size( area );
        lv_draw_sw_rgb565_swap( pixelmap, len );
    }

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( (uint16_t*) pixelmap, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp );
}

/*Read the touchpad*/
void my_touchpad_read (lv_indev_t * indev_driver, lv_indev_data_t * data) {
    uint16_t touchX = 0, touchY = 0;
    bool touched = tft.getTouch( &touchX, &touchY, 600 );
    touchX = 480 - touchX;

    if (!touched) {
        data->state = LV_INDEV_STATE_REL;
    } else {
        data->state = LV_INDEV_STATE_PR;
        /*Set the coordinates*/
        data->point.x = touchX;
        data->point.y = touchY;
        /*
        Serial.print( "Data x " );
        Serial.println( touchX );

        Serial.print( "Data y " );
        Serial.println( touchY );
        */
    }
}

/*Set tick routine needed for LVGL internal timings*/
static uint32_t my_tick_get_cb (void) { return millis(); }

// Self-implemented event function
// Format the time string output
String formatTimeString(int timeInMs) {
    int minute = timeInMs / 60000;
    int second = (timeInMs % 60000) / 1000;
    String strSecond = String(second);
    if (second < 10) {
        strSecond = "0" +  strSecond;
    }
    String timeString = String(minute) + ":" + strSecond;
    return timeString;
}

// TJPG Output Callback
bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap) {
  // Stop further decoding as image is running off bottom of screen
  if ( y >= tft.height() ) return 0;
  // This function will clip the image block rendering automatically at the TFT boundaries
  tft.pushImage(x, y, w, h, bitmap);
  // Return 1 to decode next block
  return 1;
}

// Update player detail
void updatePlayerDetails(PlayerDetails playerDetails) {
    if (playerDetails.shuffleState) {
        _ui_state_modify(ui_mainShuffleBtn, LV_STATE_CHECKED, _UI_MODIFY_STATE_ADD);
    } else {
        _ui_state_modify(ui_mainShuffleBtn, LV_STATE_CHECKED, _UI_MODIFY_STATE_REMOVE);
    }

    if (playerDetails.repeateState == repeat_context) {
        _ui_state_modify(ui_mainRepeatBtn, LV_STATE_CHECKED, _UI_MODIFY_STATE_ADD);
    } else {
        _ui_state_modify(ui_mainRepeatBtn, LV_STATE_CHECKED, _UI_MODIFY_STATE_REMOVE);
    }

    playbackVolume = playerDetails.device.volumePercent;
}

// Update info of Currently Playing if track changed
void updateCurrentlyPlaying(CurrentlyPlaying currentlyPlaying) {
    if (currentlyPlaying.isPlaying) {
        _ui_flag_modify( ui_mainPlayBtn, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify( ui_mainPauseBtn, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    } else {
        _ui_flag_modify( ui_mainPlayBtn, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify( ui_mainPauseBtn, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }

    if (currentTrackURI != currentlyPlaying.trackUri) {
        currentTrackURI = currentlyPlaying.trackUri;
        
        // Update Context Name
        // TODO: Change album name to true context name (Context can be: artist, playlist, album, show (spotify:xxxx:xxxx))
        currentContext = currentlyPlaying.albumName;
        lv_label_set_text(ui_mainContextLbl, currentContext.c_str());

        // Update Song Name
        currentSong = currentlyPlaying.trackName;
        lv_label_set_text(ui_mainSongLbl, currentSong.c_str());
        
        // Update Artist Name
        String tempArtist;
        tempArtist = currentlyPlaying.artists[0].artistName;
        if (currentlyPlaying.numArtists > 1) {
            for (int i=1; i<currentlyPlaying.numArtists; i++) {
                tempArtist += ", ";
                tempArtist += currentlyPlaying.artists[i].artistName;
            }
        }
        currentArtist = tempArtist;
        lv_label_set_text(ui_mainArtistLbl, currentArtist.c_str());

        // Update Duration
        currentDuration = currentlyPlaying.durationMs;
        lv_label_set_text(ui_mainSongLenLbl, formatTimeString(currentDuration).c_str());
        
        // Update Album Image URL and Image on UI
        for (int i=0; i<currentlyPlaying.numImages; i++) {
            if (currentlyPlaying.albumImages[i].height == 300 || currentlyPlaying.albumImages[i].width == 300) {
                currentAlbumImageURL = currentlyPlaying.albumImages[i].url;
                break;
            }
        }

        needChangeAlbumImage = true;
        /*if (SPIFFS.exists("/albumImage.jpg") == true) {
            SPIFFS.remove("/albumImage.jpg");
        }
        bool loaded_ok = getFile(currentAlbumImageURL, "/albumImage.jpg");
        if (!firstTimeLoad) {
            TJpgDec.drawFsJpg(45, 45, "/albumImage.jpg");
        }*/
    }
    
    // Update Real Progress
    if (currentProgress != currentlyPlaying.progressMs) {
        currentProgress = currentlyPlaying.progressMs;
        lv_label_set_text(ui_mainProgressLbl, formatTimeString(currentProgress).c_str());
        unsigned int progressPercentage = (currentProgress * 100) / currentDuration;
        lv_bar_set_value(ui_mainProgressBar, progressPercentage, LV_ANIM_OFF);
    }
}

static void changeAlbumImage() {
    if (SPIFFS.exists("/albumImage.jpg") == true) {
        SPIFFS.remove("/albumImage.jpg");
    }
    bool loaded_ok = getFile(currentAlbumImageURL, "/albumImage.jpg");
    TJpgDec.drawFsJpg(45, 45, "/albumImage.jpg");
}

// Button Events & Called Functions
static void mainPlaySong(lv_event_t * event) {
    _ui_flag_modify( ui_mainPlayBtn, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_TOGGLE);
    _ui_flag_modify( ui_mainPauseBtn, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_TOGGLE);
    spotify.play();
}

static void mainPauseSong(lv_event_t * event) {
    _ui_flag_modify( ui_mainPlayBtn, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_TOGGLE);
    _ui_flag_modify( ui_mainPauseBtn, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_TOGGLE);
    spotify.pause();
}

static void mainPrevSong(lv_event_t * event) {
    if ((currentProgress * 100 / currentDuration) < 10) {
        spotify.previousTrack();
    } else {
        spotify.seek(0);
    }
    int songStatus = spotify.getCurrentlyPlaying(updateCurrentlyPlaying, "HK");
}

static void mainNextSong(lv_event_t * event) {
    spotify.nextTrack();
    int songStatus = spotify.getCurrentlyPlaying(updateCurrentlyPlaying, "HK");
}

static void mainToggleShuffle(lv_event_t * event) {
    if (lv_obj_has_state(ui_mainShuffleBtn, LV_STATE_CHECKED)) {
        spotify.toggleShuffle(true);
    } else {
        spotify.toggleShuffle(false);
    }
}

static void mainToggleRepeat(lv_event_t * event) {
    if (lv_obj_has_state(ui_mainRepeatBtn, LV_STATE_CHECKED)) {
        spotify.setRepeatMode(repeat_context);
    } else {
        spotify.setRepeatMode(repeat_off);
    }
}

// Function for rotary switch
static void changeVolumeValue() {
    currentStateCLK = digitalRead(ROTARY_CLK);
    if (currentStateCLK != lastStateCLK) {
        if (digitalRead(ROTARY_DT) != currentStateCLK) {
            volumeDifference+=5;
        } else {
            volumeDifference-=5;
        }
        if (playbackVolume + volumeDifference < 0) {
            volumeDifference = -playbackVolume;
        } else if (playbackVolume + volumeDifference > 100) {
            volumeDifference = 100 - playbackVolume;
        }
        rotaryLastChangeTime = millis();
        rotaryIsStable = false;
    }
    lastStateCLK = currentStateCLK;
    delay(1);
}

void setup() {
    Serial.begin( 115200 ); /* prepare for possible serial debug */

    pinMode(ROTARY_SW, INPUT_PULLUP);
    pinMode(ROTARY_DT, INPUT);
    pinMode(ROTARY_CLK, INPUT);
    lastStateCLK = digitalRead(ROTARY_CLK);

    // SPIFFS Setup
    if (!SPIFFS.begin()) {
        Serial.println("SPIFFS initialisation failed!");
        while (1)
            yield(); // Stay here twiddling thumbs waiting
    }
    Serial.println("\r\nInitialisation done.");

    // WiFi Setup
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println(WIFI_SSID);
    Serial.println(WiFi.localIP());
    client.setCACert(spotify_server_cert);

    // Refresh Access Token
    Serial.println("Refreshing Access Tokens");
    if (!spotify.refreshAccessToken()) {
        Serial.println("Failed to get access tokens");
    }

    String LVGL_Arduino = "LVGL: ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

    Serial.println( LVGL_Arduino );

    lv_init();

#if LV_USE_LOG != 0
    lv_log_register_print_cb( my_print ); /* register print function for debugging */
#endif

    tft.begin();          /* TFT init */
    tft.setRotation( 3 ); /* Landscape orientation, flipped */

    // TJpgDec Setup
    TJpgDec.setJpgScale(2);
    TJpgDec.setSwapBytes(true);
    TJpgDec.setCallback(tft_output);

    static lv_disp_t* disp;
    disp = lv_display_create( screenWidth, screenHeight );
    lv_display_set_buffers( disp, buf, NULL, SCREENBUFFER_SIZE_PIXELS * sizeof(lv_color_t), LV_DISPLAY_RENDER_MODE_PARTIAL );
    lv_display_set_flush_cb( disp, my_disp_flush );

    static lv_indev_t* indev;
    indev = lv_indev_create();
    lv_indev_set_type( indev, LV_INDEV_TYPE_POINTER );
    lv_indev_set_read_cb( indev, my_touchpad_read );

    lv_tick_set_cb( my_tick_get_cb );

    ui_init();

    // Self-implemented Events
    lv_obj_add_event_cb(ui_mainPlayBtn, mainPlaySong, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_mainPauseBtn, mainPauseSong, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_mainPrevBtn, mainPrevSong, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_mainNextBtn, mainNextSong, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_mainShuffleBtn, mainToggleShuffle, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_mainRepeatBtn, mainToggleRepeat, LV_EVENT_CLICKED, NULL);

    Serial.println( "Setup done" );
    Serial.println( "Starting" );
    int songStatus = spotify.getCurrentlyPlaying(updateCurrentlyPlaying, "HK");
    int playerStatus = spotify.getPlayerDetails(updatePlayerDetails, "HK");
}

void loop () {
    // Update currently playing
    if (millis() - lastUpdateTime >= updateInterval) {
        int songStatus = spotify.getCurrentlyPlaying(updateCurrentlyPlaying, "HK");
        if (songStatus == 200) {
            Serial.print("$");
        }

        int playerStatus = spotify.getPlayerDetails(updatePlayerDetails, "HK");
        if (playerStatus == 200) {
            Serial.print("^");
        } else {
            Serial.print("Error (if 204 -> Device Not Available): ");
            Serial.println(playerStatus);
        }

        lastUpdateTime = millis();
    }

    // Update Progress Bar and Label without accessing Spotify API
    if (millis() - lastUIUpdateTime >= updateUIInterval) {
        if (lv_obj_has_flag(ui_mainPlayBtn, LV_OBJ_FLAG_HIDDEN)) {
            currentProgress += 1000;
            lv_label_set_text(ui_mainProgressLbl, formatTimeString(currentProgress).c_str());
            unsigned int progressPercentage = (currentProgress * 100) / currentDuration;
            lv_bar_set_value(ui_mainProgressBar, progressPercentage, LV_ANIM_OFF);
        }
        lastUIUpdateTime = millis();
    }

    changeVolumeValue();
    if (!rotaryIsStable && (millis() - rotaryLastChangeTime >= rotaryStableTime)) {
        rotaryIsStable = true;
        spotify.setVolume(playbackVolume + volumeDifference);
        playbackVolume = playbackVolume + volumeDifference;
        volumeDifference = 0;
        Serial.print("Volume Changed to:");
        Serial.println(playbackVolume);
    }

    lv_timer_handler(); /* let the GUI do its work */
    delay(5);

    if (needChangeAlbumImage) {
        changeAlbumImage();
        needChangeAlbumImage = false;
    }
}

