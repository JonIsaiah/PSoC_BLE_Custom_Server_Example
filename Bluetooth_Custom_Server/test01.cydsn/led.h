/*******************************************************************************
File Name: led.h

Description:
 This file contains the macros and declaration of LED control related functions.

********************************************************************************
Copyright 2014-15, Cypress Semiconductor Corporation.  All rights reserved.
You may use this file only in accordance with the license, terms, conditions,
disclaimers, and limitations in the end user license agreement accompanying
the software package with which this file was provided.
*******************************************************************************/
#if !defined (LED_H)
#define LED_H
#include <project.h>

/********************************** Macors ******************************************/
/* LED Color and status related Macros */
#define RGB_LED_MAX_VAL					0xFF
#define RGB_LED_OFF						0xFF
#define RGB_LED_ON						0x00

/* Index values in array where respective color coordiantes
* are saved */
#define RED_INDEX						0x00
#define GREEN_INDEX						0x01
#define BLUE_INDEX						0x02
#define INTENSITY_INDEX					0x03
/***************************************************************************************/

/******************************* Function Declaration **********************************/
void UpdateRGBLED(uint8* , uint8);
/***************************************************************************************/

#endif
/* [] END OF FILE */
