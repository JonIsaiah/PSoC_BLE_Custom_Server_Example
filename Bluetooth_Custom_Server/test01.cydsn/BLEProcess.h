/*******************************************************************************
File Name: BLEProcess.h

Description:
 This file contains the macros and declaration of BLE related functions.

********************************************************************************
Copyright 2014-15, Cypress Semiconductor Corporation.  All rights reserved.
You may use this file only in accordance with the license, terms, conditions,
disclaimers, and limitations in the end user license agreement accompanying
the software package with which this file was provided.
*******************************************************************************/
#if !defined (BLEPROCESS_H)
#define BLEPROCESS_H
#include <project.h>

/********************************** Macors ******************************************/
/* RGB LED Characteristic data length*/
#define RGB_CHAR_DATA_LEN				4
/******************************************************************************************/

/******************************* Function Declaration *************************************/
void GeneralEventHandler(uint32 , void*);
void UpdateRGBcharacteristic(uint8* , uint8, uint16);
/********************************************************************************************/
#endif
/* [] END OF FILE */
