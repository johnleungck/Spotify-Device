SET(SOURCES ui_playScreen.c
    ui.c
    ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    ui_img_playicon_png.c
    ui_img_pauseicon_png.c
    ui_img_previcon_png.c
    ui_img_nexticon_png.c
    ui_img_shuffleicon_png.c
    ui_img_repeaticon_png.c)

add_library(ui ${SOURCES})
