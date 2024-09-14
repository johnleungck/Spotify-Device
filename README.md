# ESP32 Spotify Device (Currently just a playback controller)

It can control playback and view track details. Like this:
![Demo Image](https://i.scdn.co/image/ab67616d00001e0285e5dcc05cc216a10f141480)

### Hardware
- AZ-Delivery ESP-32 Dev Kit C V4 (ESP32-Wrover)
- 3.5" display with ILI9488 driver
- HW-040 Rotary Encoder Switch

### Library
- ArduinoJson
- TJpg_Decoder
- ArduinoHttpClient
- SPIFFS
- LVGL
- TFT_eSPI
- Spotify-API-Arduino
- Squareline Studio generated code

### Wiring
|   |Hardware|ESP32|
|-----|-----|-----|
|**ILI9488 TFT**|VCC|3V3|
||GND|GND|
||CS|15|
||RESET|4|
||DC/RS|2|
||SDI(MOSI)|23|
||SCK|18|
||LED|3V3|
||SDO(MISO)|(x)|
|**ILI9488 Touch**|T_CLK|18|
||T_CS|21|
||T_DIN|23|
||T_DO|19|
||T_IRQ|(x)|
|**Rotary Switch**|CLK|27|
||DT|26|
||SW|25|
||+|3V3|
||GND|GND|