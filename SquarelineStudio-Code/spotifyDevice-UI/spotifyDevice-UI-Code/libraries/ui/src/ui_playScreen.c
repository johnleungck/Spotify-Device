// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.2
// LVGL version: 9.1.0
// Project name: spotifyDevice-UI

#include "ui.h"

void ui_playScreen_screen_init(void)
{
ui_playScreen = lv_obj_create(NULL);
lv_obj_remove_flag( ui_playScreen, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_mainControlContainer = lv_obj_create(ui_playScreen);
lv_obj_remove_style_all(ui_mainControlContainer);
lv_obj_set_width( ui_mainControlContainer, 480);
lv_obj_set_height( ui_mainControlContainer, 110);
lv_obj_set_x( ui_mainControlContainer, 0 );
lv_obj_set_y( ui_mainControlContainer, 105 );
lv_obj_set_align( ui_mainControlContainer, LV_ALIGN_CENTER );
lv_obj_remove_flag( ui_mainControlContainer, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_mainPlayBtn = lv_image_create(ui_mainControlContainer);
lv_image_set_src(ui_mainPlayBtn, &ui_img_playicon_png);
lv_obj_set_width( ui_mainPlayBtn, 50);
lv_obj_set_height( ui_mainPlayBtn, 50);
lv_obj_set_x( ui_mainPlayBtn, 0 );
lv_obj_set_y( ui_mainPlayBtn, -20 );
lv_obj_set_align( ui_mainPlayBtn, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_mainPlayBtn, LV_OBJ_FLAG_CLICKABLE );   /// Flags
lv_obj_remove_flag( ui_mainPlayBtn, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_image_set_scale(ui_mainPlayBtn,128);
lv_image_set_inner_align( ui_mainPlayBtn, LV_IMAGE_ALIGN_RIGHT_MID );
lv_obj_set_style_radius(ui_mainPlayBtn, 25, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_mainPlayBtn, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_mainPlayBtn, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_radius(ui_mainPlayBtn, 25, LV_PART_MAIN| LV_STATE_PRESSED);
lv_obj_set_style_bg_color(ui_mainPlayBtn, lv_color_hex(0xE2E2E2), LV_PART_MAIN | LV_STATE_PRESSED );
lv_obj_set_style_bg_opa(ui_mainPlayBtn, 255, LV_PART_MAIN| LV_STATE_PRESSED);

ui_mainPauseBtn = lv_image_create(ui_mainControlContainer);
lv_image_set_src(ui_mainPauseBtn, &ui_img_pauseicon_png);
lv_obj_set_width( ui_mainPauseBtn, 50);
lv_obj_set_height( ui_mainPauseBtn, 50);
lv_obj_set_x( ui_mainPauseBtn, 0 );
lv_obj_set_y( ui_mainPauseBtn, -20 );
lv_obj_set_align( ui_mainPauseBtn, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_mainPauseBtn, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_CLICKABLE );   /// Flags
lv_obj_remove_flag( ui_mainPauseBtn, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_image_set_scale(ui_mainPauseBtn,128);
lv_obj_set_style_radius(ui_mainPauseBtn, 25, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_mainPauseBtn, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_mainPauseBtn, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_radius(ui_mainPauseBtn, 25, LV_PART_MAIN| LV_STATE_PRESSED);
lv_obj_set_style_bg_color(ui_mainPauseBtn, lv_color_hex(0xE2E2E2), LV_PART_MAIN | LV_STATE_PRESSED );
lv_obj_set_style_bg_opa(ui_mainPauseBtn, 255, LV_PART_MAIN| LV_STATE_PRESSED);

ui_mainPrevBtn = lv_image_create(ui_mainControlContainer);
lv_image_set_src(ui_mainPrevBtn, &ui_img_previcon_png);
lv_obj_set_width( ui_mainPrevBtn, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_mainPrevBtn, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_mainPrevBtn, -80 );
lv_obj_set_y( ui_mainPrevBtn, -20 );
lv_obj_set_align( ui_mainPrevBtn, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_mainPrevBtn, LV_OBJ_FLAG_CLICKABLE );   /// Flags
lv_obj_remove_flag( ui_mainPrevBtn, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_image_set_scale(ui_mainPrevBtn,128);
lv_obj_set_style_radius(ui_mainPrevBtn, 25, LV_PART_MAIN| LV_STATE_PRESSED);
lv_obj_set_style_bg_color(ui_mainPrevBtn, lv_color_hex(0x2E2E2E), LV_PART_MAIN | LV_STATE_PRESSED );
lv_obj_set_style_bg_opa(ui_mainPrevBtn, 255, LV_PART_MAIN| LV_STATE_PRESSED);

ui_mainNextBtn = lv_image_create(ui_mainControlContainer);
lv_image_set_src(ui_mainNextBtn, &ui_img_nexticon_png);
lv_obj_set_width( ui_mainNextBtn, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_mainNextBtn, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_mainNextBtn, 80 );
lv_obj_set_y( ui_mainNextBtn, -20 );
lv_obj_set_align( ui_mainNextBtn, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_mainNextBtn, LV_OBJ_FLAG_CLICKABLE );   /// Flags
lv_obj_remove_flag( ui_mainNextBtn, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_image_set_scale(ui_mainNextBtn,128);
lv_obj_set_style_radius(ui_mainNextBtn, 25, LV_PART_MAIN| LV_STATE_PRESSED);
lv_obj_set_style_bg_color(ui_mainNextBtn, lv_color_hex(0x2E2E2E), LV_PART_MAIN | LV_STATE_PRESSED );
lv_obj_set_style_bg_opa(ui_mainNextBtn, 255, LV_PART_MAIN| LV_STATE_PRESSED);

ui_mainShuffleBtn = lv_image_create(ui_mainControlContainer);
lv_image_set_src(ui_mainShuffleBtn, &ui_img_shuffleicon_png);
lv_obj_set_width( ui_mainShuffleBtn, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_mainShuffleBtn, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_mainShuffleBtn, -160 );
lv_obj_set_y( ui_mainShuffleBtn, -20 );
lv_obj_set_align( ui_mainShuffleBtn, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_mainShuffleBtn, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_CHECKABLE );   /// Flags
lv_obj_remove_flag( ui_mainShuffleBtn, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_image_set_scale(ui_mainShuffleBtn,128);
lv_obj_set_style_radius(ui_mainShuffleBtn, 25, LV_PART_MAIN| LV_STATE_CHECKED);
lv_obj_set_style_bg_color(ui_mainShuffleBtn, lv_color_hex(0x1DB954), LV_PART_MAIN | LV_STATE_CHECKED );
lv_obj_set_style_bg_opa(ui_mainShuffleBtn, 255, LV_PART_MAIN| LV_STATE_CHECKED);
lv_obj_set_style_radius(ui_mainShuffleBtn, 25, LV_PART_MAIN| LV_STATE_PRESSED);
lv_obj_set_style_bg_color(ui_mainShuffleBtn, lv_color_hex(0x2E2E2E), LV_PART_MAIN | LV_STATE_PRESSED );
lv_obj_set_style_bg_opa(ui_mainShuffleBtn, 255, LV_PART_MAIN| LV_STATE_PRESSED);

ui_mainRepeatBtn = lv_image_create(ui_mainControlContainer);
lv_image_set_src(ui_mainRepeatBtn, &ui_img_repeaticon_png);
lv_obj_set_width( ui_mainRepeatBtn, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_mainRepeatBtn, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_mainRepeatBtn, 160 );
lv_obj_set_y( ui_mainRepeatBtn, -20 );
lv_obj_set_align( ui_mainRepeatBtn, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_mainRepeatBtn, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_CHECKABLE );   /// Flags
lv_obj_remove_flag( ui_mainRepeatBtn, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_image_set_scale(ui_mainRepeatBtn,128);
lv_obj_set_style_radius(ui_mainRepeatBtn, 25, LV_PART_MAIN| LV_STATE_CHECKED);
lv_obj_set_style_bg_color(ui_mainRepeatBtn, lv_color_hex(0x1DB954), LV_PART_MAIN | LV_STATE_CHECKED );
lv_obj_set_style_bg_opa(ui_mainRepeatBtn, 255, LV_PART_MAIN| LV_STATE_CHECKED);
lv_obj_set_style_radius(ui_mainRepeatBtn, 25, LV_PART_MAIN| LV_STATE_PRESSED);
lv_obj_set_style_bg_color(ui_mainRepeatBtn, lv_color_hex(0x2E2E2E), LV_PART_MAIN | LV_STATE_PRESSED );
lv_obj_set_style_bg_opa(ui_mainRepeatBtn, 255, LV_PART_MAIN| LV_STATE_PRESSED);

ui_mainProgressBar = lv_bar_create(ui_mainControlContainer);
lv_bar_set_value(ui_mainProgressBar,50,LV_ANIM_OFF);
lv_bar_set_start_value(ui_mainProgressBar, 0, LV_ANIM_OFF);
lv_obj_set_width( ui_mainProgressBar, 320);
lv_obj_set_height( ui_mainProgressBar, 5);
lv_obj_set_x( ui_mainProgressBar, 0 );
lv_obj_set_y( ui_mainProgressBar, 30 );
lv_obj_set_align( ui_mainProgressBar, LV_ALIGN_CENTER );
lv_obj_set_style_bg_color(ui_mainProgressBar, lv_color_hex(0x2E2E2E), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_mainProgressBar, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_set_style_bg_color(ui_mainProgressBar, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_mainProgressBar, 255, LV_PART_INDICATOR| LV_STATE_DEFAULT);

//Compensating for LVGL9.1 draw crash with bar/slider max value when top-padding is nonzero and right-padding is 0
if (lv_obj_get_style_pad_top(ui_mainProgressBar,LV_PART_MAIN) > 0) lv_obj_set_style_pad_right( ui_mainProgressBar, lv_obj_get_style_pad_right(ui_mainProgressBar,LV_PART_MAIN) + 1, LV_PART_MAIN );
ui_mainProgressLbl = lv_label_create(ui_mainControlContainer);
lv_obj_set_width( ui_mainProgressLbl, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_mainProgressLbl, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_mainProgressLbl, -180 );
lv_obj_set_y( ui_mainProgressLbl, 30 );
lv_obj_set_align( ui_mainProgressLbl, LV_ALIGN_CENTER );
lv_label_set_text(ui_mainProgressLbl,"1:25");

ui_mainSongLenLbl = lv_label_create(ui_mainControlContainer);
lv_obj_set_width( ui_mainSongLenLbl, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_mainSongLenLbl, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_mainSongLenLbl, 180 );
lv_obj_set_y( ui_mainSongLenLbl, 30 );
lv_obj_set_align( ui_mainSongLenLbl, LV_ALIGN_CENTER );
lv_label_set_text(ui_mainSongLenLbl,"2:50");

ui_mainDisplayContainer = lv_obj_create(ui_playScreen);
lv_obj_remove_style_all(ui_mainDisplayContainer);
lv_obj_set_width( ui_mainDisplayContainer, 480);
lv_obj_set_height( ui_mainDisplayContainer, 200);
lv_obj_set_x( ui_mainDisplayContainer, 0 );
lv_obj_set_y( ui_mainDisplayContainer, -60 );
lv_obj_set_align( ui_mainDisplayContainer, LV_ALIGN_CENTER );
lv_obj_remove_flag( ui_mainDisplayContainer, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_mainCoverImg = lv_image_create(ui_mainDisplayContainer);
lv_image_set_src(ui_mainCoverImg, &ui_img_shuffleicon_png);
lv_obj_set_width( ui_mainCoverImg, 150);
lv_obj_set_height( ui_mainCoverImg, 150);
lv_obj_set_x( ui_mainCoverImg, -120 );
lv_obj_set_y( ui_mainCoverImg, 20 );
lv_obj_set_align( ui_mainCoverImg, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_mainCoverImg, LV_OBJ_FLAG_CLICKABLE );   /// Flags
lv_obj_remove_flag( ui_mainCoverImg, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_mainCoverImg, lv_color_hex(0x353535), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_mainCoverImg, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_mainSongLbl = lv_label_create(ui_mainDisplayContainer);
lv_obj_set_width( ui_mainSongLbl, 220);
lv_obj_set_height( ui_mainSongLbl, 60);
lv_obj_set_x( ui_mainSongLbl, 90 );
lv_obj_set_y( ui_mainSongLbl, 45 );
lv_obj_set_align( ui_mainSongLbl, LV_ALIGN_CENTER );
lv_label_set_long_mode(ui_mainSongLbl,LV_LABEL_LONG_DOT);
lv_label_set_text(ui_mainSongLbl,"TextTextTextTextTextTextTextTextTextText");
lv_obj_set_style_text_align(ui_mainSongLbl, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_mainSongLbl, &lv_font_montserrat_26, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_mainArtistLbl = lv_label_create(ui_mainDisplayContainer);
lv_obj_set_width( ui_mainArtistLbl, 220);
lv_obj_set_height( ui_mainArtistLbl, 25);
lv_obj_set_x( ui_mainArtistLbl, 90 );
lv_obj_set_y( ui_mainArtistLbl, 90 );
lv_obj_set_align( ui_mainArtistLbl, LV_ALIGN_CENTER );
lv_label_set_long_mode(ui_mainArtistLbl,LV_LABEL_LONG_SCROLL_CIRCULAR);
lv_label_set_text(ui_mainArtistLbl,"texttexttexttexttexttext");
lv_obj_set_style_text_font(ui_mainArtistLbl, &lv_font_montserrat_12, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_mainContextLbl = lv_label_create(ui_mainDisplayContainer);
lv_obj_set_width( ui_mainContextLbl, 220);
lv_obj_set_height( ui_mainContextLbl, 25);
lv_obj_set_x( ui_mainContextLbl, 90 );
lv_obj_set_y( ui_mainContextLbl, -20 );
lv_obj_set_align( ui_mainContextLbl, LV_ALIGN_CENTER );
lv_label_set_long_mode(ui_mainContextLbl,LV_LABEL_LONG_SCROLL_CIRCULAR);
lv_label_set_text(ui_mainContextLbl,"texttexttexttex ttexttext");
lv_obj_set_style_text_letter_space(ui_mainContextLbl, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_line_space(ui_mainContextLbl, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_align(ui_mainContextLbl, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_decor(ui_mainContextLbl, LV_TEXT_DECOR_UNDERLINE, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_mainContextLbl, &lv_font_montserrat_16, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_mainNowPlayingStr = lv_label_create(ui_mainDisplayContainer);
lv_obj_set_width( ui_mainNowPlayingStr, 220);
lv_obj_set_height( ui_mainNowPlayingStr, 25);
lv_obj_set_x( ui_mainNowPlayingStr, 90 );
lv_obj_set_y( ui_mainNowPlayingStr, -40 );
lv_obj_set_align( ui_mainNowPlayingStr, LV_ALIGN_CENTER );
lv_label_set_text(ui_mainNowPlayingStr,"Now playing:");
lv_obj_set_style_text_letter_space(ui_mainNowPlayingStr, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_line_space(ui_mainNowPlayingStr, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_align(ui_mainNowPlayingStr, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_mainNowPlayingStr, &lv_font_montserrat_16, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_add_event_cb(ui_mainPlayBtn, ui_event_mainPlayBtn, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_mainPauseBtn, ui_event_mainPauseBtn, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_mainPrevBtn, ui_event_mainPrevBtn, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_mainNextBtn, ui_event_mainNextBtn, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_mainShuffleBtn, ui_event_mainShuffleBtn, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_mainRepeatBtn, ui_event_mainRepeatBtn, LV_EVENT_ALL, NULL);

}
