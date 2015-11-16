/******************************************************************************
* Project Name		: AN91162
* File Name			: BLEProcess.c
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
* Contains function definitions for Event callback handler function for BLE 
* events as well as updating RGB characteristic GATT DB
*******************************************************************************/
#include <main.h>






/*******************************************************************************
* Function Name: GeneralEventHandler
********************************************************************************
* Summary:
*        General callback event handler function for BLE component through which
* application recieves various BLE events.
*
* Parameters:
*  event:		event type. See "CYBLE_EVENT_T" structure in BLE_Stack.h
*  eventParam: 	parameter associated with the event
*
* Return:
*  void
*
*******************************************************************************/
void GeneralEventHandler(uint32 event, void * eventParam)
{
	/* Structure to store data written by Client */	
	CYBLE_GATTS_WRITE_REQ_PARAM_T *wrReqParam;
	
	/* 'RGBledData[]' is an array to store 4 bytes of RGB LED data*/
	uint8 RGBledData[RGB_CHAR_DATA_LEN];
	
	switch(event)
    {
		case CYBLE_EVT_STACK_ON:
			/* BLE stack is on. Start BLE advertisement */
			CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
		break;
		
		case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
			/* This event is generated whenever Advertisement starts or stops.
			* The exact state of advertisement is obtained by CyBle_State() */
			if(CyBle_GetState() == CYBLE_STATE_DISCONNECTED)
			{
				CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
			}
		break;
			
		case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
			/* This event is generated at GAP disconnection. 
			* Restart advertisement */
			CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
			break;

        case CYBLE_EVT_GATTS_WRITE_REQ: 
			/* This event is generated when the connected Central device sends a
			* Write request. The parameter contains the data written */
			
			/* Extract the Write data sent by Client */
            wrReqParam = (CYBLE_GATTS_WRITE_REQ_PARAM_T *) eventParam;
			
			/* If the attribute handle of the characteristic written to 
			* is equal to that of RGB_LED characteristic, then extract 
			* the RGB LED data */
			if(CYBLE_CUSTOMSERVICE_TRANSMITDATA_CHAR_HANDLE == wrReqParam->handleValPair.attrHandle)
            {
				/* Store RGB LED data in local array */
                RGBledData[RED_INDEX] = wrReqParam->handleValPair.value.val[RED_INDEX];
                RGBledData[GREEN_INDEX] = wrReqParam->handleValPair.value.val[GREEN_INDEX];
                RGBledData[BLUE_INDEX] = wrReqParam->handleValPair.value.val[BLUE_INDEX];
                RGBledData[INTENSITY_INDEX] = wrReqParam->handleValPair.value.val[INTENSITY_INDEX];
                
				/* Update the PrISM component density value to represent color */
                UpdateRGBLED(RGBledData, sizeof(RGBledData));
				
				/* Update the GATT DB for RGB LED read characteristics*/
				UpdateRGBcharacteristic(RGBledData, 
										sizeof(RGBledData), 
										CYBLE_CUSTOMSERVICE_TRANSMITDATA_CHAR_HANDLE );
            }
			
			/* Send the response to the write request. */
			CyBle_GattsWriteRsp(cyBle_connHandle);
			
			break;
			
	    case CYBLE_EVT_GATT_DISCONNECT_IND:
			/* This event is generated at GATT disconnection */
			
			/* Reset the color values*/	
			RGBledData[RED_INDEX] = FALSE;
			RGBledData[GREEN_INDEX] = FALSE;
			RGBledData[BLUE_INDEX] = FALSE;
            RGBledData[INTENSITY_INDEX] = FALSE;
			
			/* Switch off LEDs */
			UpdateRGBLED(RGBledData, sizeof(RGBledData));
			
			/* Register the new color in GATT DB*/			
			UpdateRGBcharacteristic(RGBledData, 
									sizeof(RGBledData),
									CYBLE_CUSTOMSERVICE_TRANSMITDATA_CHAR_HANDLE );
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
			break;	
			
        default:

       	break;
    }   	
}





/*******************************************************************************
* Function Name: UpdateRGBcharacteristic
********************************************************************************
* Summary:
*        Update the GATT DB with new RGB Color received to allow Client to read 
* back updated color values.
*
* Parameters:
*  ledData:		array pointer where color value is stored
*  len: 		length of the array
*  attrHandle:	attribute handle of the characteristic
*
* Return:
*  void
*
*******************************************************************************/
void UpdateRGBcharacteristic(uint8* ledData, uint8 len, uint16 attrHandle)
{
	/* 'rgbHandle' stores RGB control data parameters */
	CYBLE_GATT_HANDLE_VALUE_PAIR_T		rgbHandle;

	/* Update RGB control handle with new values */
	rgbHandle.attrHandle = attrHandle;
	rgbHandle.value.val = ledData;
	rgbHandle.value.len = len;
	
	/* Update the RGB LED attribute value. This will allow 
	* Client device to read the existing color values over 
	* RGB LED characteristic */
	CyBle_GattsWriteAttributeValue(&rgbHandle, 
									FALSE, 
									&cyBle_connHandle, 
									CYBLE_GATT_DB_LOCALLY_INITIATED);
}

/* [] END OF FILE */
