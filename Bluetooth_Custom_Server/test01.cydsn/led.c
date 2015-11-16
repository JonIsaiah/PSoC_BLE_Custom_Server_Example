/******************************************************************************
* Project Name		: AN91162
* File Name			: led.c
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
* Contains function definitions for RGB LED control application
*******************************************************************************/
#include "main.h"
/*******************************************************************************
* Function Name: UpdateRGBLED
********************************************************************************
* Summary:
*        Receive the new RGB data and modify PrISM parameters. 
*
* Parameters:
*  ledData:		array pointer where color value is stored
*  len: 		length of the array
*
* Return:
*  void
*
*******************************************************************************/
void UpdateRGBLED(uint8* ledData, uint8 len)
{
	/* Local variables to store calculated color components from 
	* received RGB data*/
	uint8 calc_red;
	uint8 calc_green;
	uint8 calc_blue;
	
	/* Check if the array has length equal to expected length for 
	* RGB LED data */
	if(len == RGB_CHAR_DATA_LEN)
	{
		/* True color to be displayed is calculated on basis of color 
		* and intensity value received */
		calc_red = (uint8)(((uint16)ledData[RED_INDEX]*ledData[INTENSITY_INDEX])/RGB_LED_MAX_VAL);
		calc_green = (uint8)(((uint16)ledData[GREEN_INDEX]*ledData[INTENSITY_INDEX])/RGB_LED_MAX_VAL);
		calc_blue = (uint8)(((uint16)ledData[BLUE_INDEX]*ledData[INTENSITY_INDEX])/RGB_LED_MAX_VAL);
		
		/* Update the density value of the PrISM module for color control. The density value is 
		* 255 minus the calculated color value as the LED pins on BLE Pioneer kit are active low. */
        
        /*
		PrISM_1_WritePulse0(RGB_LED_MAX_VAL - calc_red);
	    PrISM_1_WritePulse1(RGB_LED_MAX_VAL - calc_green);
	    PrISM_2_WritePulse0(RGB_LED_MAX_VAL - calc_blue);
        */
	}
}

/* [] END OF FILE */
