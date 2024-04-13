# LVGL project for ESP32

This is an ESP32 demo project showcasing LVGL v8.3.x with support for several display controllers and touch controllers.

- Version of ESP-IDF required 5.0.x
- Version of LVGL used: 8.3.x

## Get started

### How is the training structured?
This training contains the following submodules:
- [lvgl](https://github.com/lvgl/lvgl)
- [lvgl_esp32_drivers](https://github.com/lvgl/lvgl_esp32_drivers) (this does not have a support for lvgl 8.3. so we provided a patch for this)

#### [LVGL](https://github.com/lvgl/lvgl)

This submodule we are using is an embedded graphics library used to create beautiful UIs for any MCU, MPU and display types. It provides us with APIs for creating buttons, switches, labels, etc. But, for displaying those objects on our display (model ILI9341) and using the touch screen (XPT2046 touch controller) we are using an additional submodule called lvgl_esp32_drivers.

#### [LVGL_ESP32_DRIVERS](https://github.com/lvgl/lvgl_esp32_drivers)

This submodule enables us to use already implemented functions for displaying objects on different displays and receiving touch information (including our ILI9341 display and XPT2046 touch controller) on ESP32. In `gui.c` we pass those implemented functions as callbacks (for flushing the screen and reading touch input) to the LVGL library.

Those two submodules together make lives easier for creating embedded graphics on ESP32.

### Configuration

The project is already set up for Byte Lab Development Kit. If you want to use it on your custom board, you will have to make a few changes.
1. Open SDK configuration editor (menuconfig) and navigate to **LVGL TFT Display controller**.
1. Select a display model you are using. Make sure to choose appropriate communication bus, transfer modes and then assign pins in **Display Pin Assignments** section.
1. Navigate to **LVGL Touch controller** and select a touch panel you are using. Find your model in **Touchpanel Pin Assignment** and assign pins accordingly.
1. Be careful to change the horizontal and vertical screen resolution, if necessary.
