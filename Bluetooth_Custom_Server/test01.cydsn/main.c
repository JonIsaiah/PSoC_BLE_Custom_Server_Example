/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include<main.h>



#define numberOfTests 100
int i = 0; //for loop increment variable
   

   



uint16 fiveMicroSeconds_count = 0;
CY_ISR(TIMER_ISR){
    fiveMicroSeconds_count++;
}



int main()
{
    /* Start the components */
	InitializeSystem();
    
    CYBLE_GATT_HANDLE_VALUE_PAIR_T		TransmitDataHandle;
    union FloatBytes ExampleData;
    ExampleData.floats[0] = 0.000000;
    ExampleData.floats[1] = 0.000000; 
    
    TransmitDataHandle.attrHandle = 0x000Eu; //CYBLE_CUSTOMSERVICE_TRANSMITDATA_CHAR_HANDLE in BLE_custom.h
    TransmitDataHandle.value.val = ExampleData.bytes;
	TransmitDataHandle.value.len = 8;

    float incrementUp= 0.00;    
    float incrementDown = 65000;
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {   
        CyBle_ProcessEvents();

         ExampleData.floats[0] = incrementUp;   //incrementer or something here
         ExampleData.floats[1] = incrementDown;    //incrementer or something here

         incrementUp = incrementUp + 1.00;
         incrementDown = incrementDown - 1.00;
                    
         CyBle_ProcessEvents();
         TransmitDataHandle.value.val = ExampleData.bytes;
         TransmitDataHandle.value.len = 8;
        
         CyBle_GattsWriteAttributeValue(&TransmitDataHandle, 
									FALSE, 
									&cyBle_connHandle, 
									CYBLE_GATT_DB_LOCALLY_INITIATED);
         

         CyDelay(250);
    }
}



void InitializeSystem(void)
{
	/* Enable Global Interrupt Mask */
	CyGlobalIntEnable;		
    isr_1_StartEx(TIMER_ISR);

	CyBle_Start(GeneralEventHandler);
    
    
    
    
}



/* [] END OF FILE */
