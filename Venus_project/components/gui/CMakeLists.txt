set(COMPONENT_SRCS "gui.c""gui_app.c")
set(COMPONENT_ADD_INCLUDEDIRS ".")
set(COMPONENT_PRIV_REQUIRES lvgl lvgl_esp32_drivers esp_timer)

register_component()
