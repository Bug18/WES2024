/**
 * @file gui_app.c
 *
 * @brief See the source file.
 *
 * COPYRIGHT NOTICE: (c) 2023 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

#ifndef __GUI_APP_C__
#define __GUI_APP_C__

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------- INCLUDES ----------------------------------

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------
/**
 * @brief Enums hold gui app events.
 *
 */
typedef enum
{
    GUI_APP_EVENT_BUTTON_LED_ON_PRESSED,
    GUI_APP_EVENT_BUTTON_LED_OFF_PRESSED,

    GUI_APP_EVENT_COUNT
} gui_app_event_t;

//---------------------- PUBLIC FUNCTION PROTOTYPES --------------------------
/**
 * @brief The function initialized first screen.
 *
 */
void gui_app_init(void);

#ifdef __cplusplus
}
#endif

#endif // __GUI_APP_C__
