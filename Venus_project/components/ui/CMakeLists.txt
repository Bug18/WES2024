SET(COMPONENT_SRCS screens/ui_MainScreen.c
    screens/ui_StartGameScreen.c
    screens/ui_InfoScreen.c
    screens/ui_TickTackToeGame.c
    screens/ui_EndGameScreen.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    images/ui_img_test_venus_320x240_png.c)

SET(
    COMPONENT_ADD_INCLUDEDIRS "."
)

set(COMPONENT_REQUIRES lvgl TicTacToe mqtt_driver)

register_component()