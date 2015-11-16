/******************************************************************************
* Project Name		: AN91162
* File Name			: main.h
* Version 			: 1.0
* Device Used		: CY8C4247LQI-BL483
* Software Used		: PSoC Creator 3.2
* Compiler    		: ARM GCC 4.8.4, ARM MDK Generic
* Related Hardware	: CY8CKIT-042-BLE Bluetooth Low Energy Pioneer Kit 
* Owner             : ROIT
*
********************************************************************************
* Copyright (2014), Cypress Semiconductor Corporation. All Rights Reserved.
********************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress)
* and is protected by and subject to worldwide patent protection (United
* States and foreign), United States copyright laws and international treaty
* provisions. Cypress hereby grants to licensee a personal, non-exclusive,
* non-transferable license to copy, use, modify, create derivative works of,
* and compile the Cypress Source Code and derivative works for the sole
* purpose of creating custom software in support of licensee product to be
* used only in conjunction with a Cypress integrated circuit as specified in
* the applicable agreement. Any reproduction, modification, translation,
* compilation, or representation of this software except as specified above 
* is prohibited without the express written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH 
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the 
* materials described herein. Cypress does not assume any liability arising out 
* of the application or use of any product or circuit described herein. Cypress 
* does not authorize its products for use as critical components in life-support 
* systems where a malfunction or failure may reasonably be expected to result in 
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of 
* such use and in doing so indemnifies Cypress against all charges. 
*
* Use of this Software may be limited by and subject to the applicable Cypress
* software license agreement. 
*******************************************************************************/
/*******************************************************************************
* Contains function declarations and macros used in the main file
*******************************************************************************/
#if !defined(MAIN_H)
#define MAIN_H
#include <project.h>
#include "led.h"
#include "BLEProcess.h"
#include <stdlib.h>
#include <stdio.h>
#include <mpu6050.h>
#include <math.h>
    
	
/********************************** Macors ******************************************/
/* General Macros*/
#define TRUE							0x01
#define FALSE							0x00
/******************************************************************************************/
    
//********************************Type Defs & Unions****************************************
union FloatBytes{               //stores float and byte array in same memory location
  float floats[2];                      //
  uint8 bytes[8]; 
};  

struct Vector{
  float x;
  float y;
  float z;
  float mag;
};



/******************************* Function Declaration *************************************/
void InitializeSystem(void);
void calibrateMPU(void);
struct Vector normalizeVector(struct Vector);
/********************************************************************************************/

#endif

/* [] END OF FILE */
