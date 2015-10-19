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

Note: When programming a register make sure to write all register bits in GPIOCONFIG_REG for that Port
and program the register.
*/
void SetupGPIO()
{
    GPIOCONFIG_REG      GpioConfigReg       = {0}; // Common register structure for various GPIO config registers.
    RCGCGPIO_REG        RcgcGpioReg         = {0}; // To enable clock to GPIO port
    
    // temporary code. Remove after testing.
    static int exp_temp = 1;
    while(exp_temp);
    
    // Code below is to light an LED on Port PF1 
    
    // Enable clocks on all ports to be configured  
    RcgcGpioReg.PortF_Clock_En = ENABLE;
    REG_WRITE(SYSCTL_RCGCGPIO_R, RcgcGpioReg.Value);
    REG_READ(SYSCTL_RCGCGPIO_R); // Read back the register for delay
    RcgcGpioReg.Value = 0;
    
    // Set direction for all bits of Port F
    GpioConfigReg.PortBit0Cfg = DIR_OUTPUT;
    
    // Write the directions in DIR register
    REG_WRITE(GPIO_PORTF_DIR_R, GpioConfigReg.Value); // WRITE_REG() should be last after setting all bits for a given register.
    GpioConfigReg.Value = 0;
    
    // Disable Alternate function for all GPIO pins of PORT F
    GpioConfigReg.PortBit0Cfg = DISABLE;
    
    // Write the AFSEL bits in register
    REG_WRITE(GPIO_PORTF_AFSEL_R, GpioConfigReg.Value);
    GpioConfigReg.Value = 0;
    
    // Disable Analog function
    GpioConfigReg.PortBit0Cfg = DISABLE;
    
    // Write the analog mode register
    REG_WRITE(GPIO_PORTF_AMSEL_R, GpioConfigReg.Value);
    GpioConfigReg.Value = 0;
    
    // Enable Digital Port via DEN
    GpioConfigReg.PortBit0Cfg = ENABLE;
    
    // Enable DEN bits
    REG_WRITE(GPIO_PORTF_DEN_R, GpioConfigReg.Value);
    GpioConfigReg.Value = 0;
}

