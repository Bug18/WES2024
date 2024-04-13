/**
 * @file user_interface.h
 *
 * @brief See the source file.
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

#ifndef __USER_INTERFACE_C__
#define __USER_INTERFACE_C__

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------- INCLUDES ----------------------------------

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PUBLIC FUNCTION PROTOTYPES --------------------------
/**
 * @brief The function initialized user interface that will act as a glue code,
 * connecting GUI, buttons and LEDs.
 *
 */
void user_interface_init(void);

#ifdef __cplusplus
}
#endif

#endif // __USER_INTERFACE_C__
