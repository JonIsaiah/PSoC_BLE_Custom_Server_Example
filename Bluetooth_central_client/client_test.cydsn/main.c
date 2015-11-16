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
#include <project.h>
#include <main.h>

/* 'ble_state' stores the state of connection which is used for updating LEDs */
extern uint8 					ble_state ;

/* 'deviceConnected' flag tells the status of connection with BLE peripheral Device */
extern uint8 					deviceConnected;

/* 'connectPeriphDevice' is a variable of type 'CYBLE_GAP_BD_ADDR_T' (defined in 
* BLE_StackGap.h) and is used to store address of the connected device. */
extern CYBLE_GAP_BD_ADDR_T connectPeriphDevice;

extern CYBLE_CONN_HANDLE_T			connHandle;

/* 'peripheralAddress' stores the addresses of device presently connected to */
extern uint8 peripheralFound;

extern uint8 restartScanning;



union FloatBytes sensor_data[NUMBER_OF_SENSORS][NUMBER_OF_PARAMETERS];
uint8 current_sensor = 0; //number 0 - number of sensors-1, anything else is invalid
uint8 current_characteristic = 0;  //Best to not use this, instead send all data in one array to cut down on complexity
int i_init;
int j_init;
int i_loopControl;






char buf[200]; //just to hold text values in for writing to UART




int main()
{
	InitializeSystem();
    

    
    current_sensor = 0;
    i_loopControl = 0;
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /*Process Event callback to handle BLE events. The events generated and 
		* used for this application are inside the 'ApplicationEventHandler' routine */
		CyBle_ProcessEvents();
        
        if(peripheralFound){
			/* If the desired peripheral is found, then connect to that peripheral */
			CyBle_GapcConnectDevice(&connectPeriphDevice);

			/* Call CyBle_ProcessEvents() once to process the Connect request sent above. */
			CyBle_ProcessEvents();
		
			/* Reset flag to prevent resending the Connect command */
			peripheralFound = FALSE;
		}
    
        /* If rescanning flag is TRUE, the restart the scan */
		if(restartScanning)
		{
			/* Reset flag to prevent calling multiple Start Scan commands */
			restartScanning = FALSE;
			
			/* Start Fast BLE Scanning. This API will only take effect after calling
			* CyBle_ProcessEvents()*/
			CyBle_GapcStartScan(CYBLE_SCANNING_FAST);
		}   
        
        if(deviceConnected){
         CyBle_GattcReadCharacteristicValue(connHandle, 0x000Eu);   //*****Characteristic Handle From Server BLE CUSTOM.H*******
        }
        

    
      sprintf(buf, "sensor1 = %.3f\nsensor2 = %.3f\n\n", sensor_data[0][0].floats[0], sensor_data[0][0].floats[1]);
      SERIAL_UartPutString(buf);
    
   //UN-COMMENT THIS BLOCK TO ENABLE CYCLING THROUGH MULTIPLE DEVICES - NOONE SHOULD REALLY NEED THIS
   /*       
      i_loopControl = i_loopControl+1;
      if(i_loopControl >= 40){
          i_loopControl = 0;
          CyBle_GapDisconnect(connHandle.bdHandle);
          CyBle_ProcessEvents();
          current_sensor = current_sensor + 1;
          if(current_sensor >= NUMBER_OF_SENSORS){
            current_sensor = 0;  
          }
      }
     */ 
    
    
    }
}




void InitializeSystem(void)
{
	/* Enable global interrupts. */
	CyGlobalIntEnable; 
	
    CyDelay(100);
    
    /* Change SCL and SDA pins drive mode to Resistive Pull Up */
    I2C_bus_scl_SetDriveMode(I2C_bus_scl_DM_RES_UP);
    I2C_bus_sda_SetDriveMode(I2C_bus_sda_DM_RES_UP);
    I2C_bus_Start();
    CyDelay(150);
    
    SERIAL_Start();
    


    
	/* Start BLE component with appropriate Event handler function */
	CyBle_Start(ApplicationEventHandler);	
	
	/* Load the BD address of peripheral device to which we have to connect */
	LoadPeripheralDeviceData(); 
    
    
    
    //zero out recieved sensor data array
    for (i_init=0; i_init < NUMBER_OF_SENSORS; i_init++){
        for (j_init=0; j_init < NUMBER_OF_PARAMETERS; j_init++){
            sensor_data[i_init][j_init].floats[0] = 0.00000;
        }
    }
    
    for (i_init=0; i_init < NUMBER_OF_SENSORS; i_init++){
        for (j_init=0; j_init < NUMBER_OF_PARAMETERS; j_init++){
            sensor_data[i_init][j_init].floats[1] = 0.00000;
        }
    }
	
}

/* [] END OF FILE */
