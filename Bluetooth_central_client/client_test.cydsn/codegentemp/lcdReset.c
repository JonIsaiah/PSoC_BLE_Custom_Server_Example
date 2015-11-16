/*******************************************************************************
* File Name: lcdReset.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "lcdReset.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        lcdReset_PC =   (lcdReset_PC & \
                                (uint32)(~(uint32)(lcdReset_DRIVE_MODE_IND_MASK << (lcdReset_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (lcdReset_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: lcdReset_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void lcdReset_Write(uint8 value) 
{
    uint8 drVal = (uint8)(lcdReset_DR & (uint8)(~lcdReset_MASK));
    drVal = (drVal | ((uint8)(value << lcdReset_SHIFT) & lcdReset_MASK));
    lcdReset_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: lcdReset_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  lcdReset_DM_STRONG     Strong Drive 
*  lcdReset_DM_OD_HI      Open Drain, Drives High 
*  lcdReset_DM_OD_LO      Open Drain, Drives Low 
*  lcdReset_DM_RES_UP     Resistive Pull Up 
*  lcdReset_DM_RES_DWN    Resistive Pull Down 
*  lcdReset_DM_RES_UPDWN  Resistive Pull Up/Down 
*  lcdReset_DM_DIG_HIZ    High Impedance Digital 
*  lcdReset_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void lcdReset_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(lcdReset__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: lcdReset_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro lcdReset_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 lcdReset_Read(void) 
{
    return (uint8)((lcdReset_PS & lcdReset_MASK) >> lcdReset_SHIFT);
}


/*******************************************************************************
* Function Name: lcdReset_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 lcdReset_ReadDataReg(void) 
{
    return (uint8)((lcdReset_DR & lcdReset_MASK) >> lcdReset_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(lcdReset_INTSTAT) 

    /*******************************************************************************
    * Function Name: lcdReset_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 lcdReset_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(lcdReset_INTSTAT & lcdReset_MASK);
		lcdReset_INTSTAT = maskedStatus;
        return maskedStatus >> lcdReset_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
