# PSoC_BLE_Custom_Server_Example
Simple Example of a Custom BLE Server and BLE Client implemented on the Cypress PSoC 4 BLE


There are two seperate projects here.

1. Bluetooth_Custom_Server is a BLE peripheral server that responds to read requests from the (central) client
2. Bluetooth_central_client is a BLE client which reads data from the peripheral

The code in the server is an example.  It prepares for transmit an example array of 2 floats.

The Client program continually reads this data and outputs it to the serial port.

**You Must change the BLE MAC address to that of the PSoC you use as the server*** 

1. Use the CySmart phone app or some other means to determine the MAC address of the PSoc you use as a server
2.  in the Bluetooth_central_client project
      in the file BLEclient.c
          in the function LoadPeripheralDeviceData
              edit the peripheralAddress array to reflect the address(es) of your servers

