/*
 * GPIO.c
 *
 *  Created on: Oct 4, 2015
 *      Author: harsh
 */

#include "GPIO.h"

/*
Function: SetupGPIO

Parameters:
    
Note: Configures GPIO Ports.
Make sure to protect the JTAG/SWD and NMI PC[3-0]by locking the CR registers for those pins.
Do not use PA1 and PA0 as they are used for debug interface to PC.

*/
void SetupGPIO()
{
    GPIOCONFIG_REG GpioConfigReg; // Common register structure for various GPIO config registers.
    
    uint8_t PinNo = pGPIO_ConfigParams->PinNo;
    
    // temporary code. Remove after testing.
    static int exp_temp = 1;
    while(exp_temp);
    
    // PORT A Configuration
    if((PinNo == 0) || (PinNo == 1))
    {
        return;
    }
    
    // Setup Direction of All pins of Port A
    
    // PORT B Configuration
    
    // PORT C Configuration
    if(((PinNo == 0) || (PinNo == 1)|| (PinNo == 2) || (PinNo == 3)))
    {
        return;
    }
    
    // PORT D Configuration
    
    // PORT E Configuration
    
    // PORT F Configuration

}

