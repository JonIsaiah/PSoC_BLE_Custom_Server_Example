/*******************************************************************************
* File Name: lcdReset.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_lcdReset_H) /* Pins lcdReset_H */
#define CY_PINS_lcdReset_H

#include "cytypes.h"
#include "cyfitter.h"
#include "lcdReset_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    lcdReset_Write(uint8 value) ;
void    lcdReset_SetDriveMode(uint8 mode) ;
uint8   lcdReset_ReadDataReg(void) ;
uint8   lcdReset_Read(void) ;
uint8   lcdReset_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define lcdReset_DRIVE_MODE_BITS        (3)
#define lcdReset_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - lcdReset_DRIVE_MODE_BITS))

#define lcdReset_DM_ALG_HIZ         (0x00u)
#define lcdReset_DM_DIG_HIZ         (0x01u)
#define lcdReset_DM_RES_UP          (0x02u)
#define lcdReset_DM_RES_DWN         (0x03u)
#define lcdReset_DM_OD_LO           (0x04u)
#define lcdReset_DM_OD_HI           (0x05u)
#define lcdReset_DM_STRONG          (0x06u)
#define lcdReset_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define lcdReset_MASK               lcdReset__MASK
#define lcdReset_SHIFT              lcdReset__SHIFT
#define lcdReset_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define lcdReset_PS                     (* (reg32 *) lcdReset__PS)
/* Port Configuration */
#define lcdReset_PC                     (* (reg32 *) lcdReset__PC)
/* Data Register */
#define lcdReset_DR                     (* (reg32 *) lcdReset__DR)
/* Input Buffer Disable Override */
#define lcdReset_INP_DIS                (* (reg32 *) lcdReset__PC2)


#if defined(lcdReset__INTSTAT)  /* Interrupt Registers */

    #define lcdReset_INTSTAT                (* (reg32 *) lcdReset__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define lcdReset_DRIVE_MODE_SHIFT       (0x00u)
#define lcdReset_DRIVE_MODE_MASK        (0x07u << lcdReset_DRIVE_MODE_SHIFT)


#endif /* End Pins lcdReset_H */


/* [] END OF FILE */
