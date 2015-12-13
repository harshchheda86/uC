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
    static int exp_temp = 0;
    while(exp_temp);
    
    // Code below is to light an LED on Port PF1 
    
    // Enable clocks on all ports to be configured  
    RcgcGpioReg.PortF_Clock_En = ENABLE;
    REG_WRITE(SYSCTL_RCGCGPIO_R, RcgcGpioReg.Value);
    REG_READ(SYSCTL_RCGCGPIO_R); // Read back the register for delay
    RcgcGpioReg.Value = 0;
    
    // Set direction for all bits of Port F. PF1 = output and PF4 is input.
    GpioConfigReg.PortBit1Cfg = DIR_OUTPUT;
    GpioConfigReg.PortBit4Cfg = DIR_INPUT;

    // Write the directions in DIR register
    REG_WRITE(GPIO_PORTF_DIR_R, GpioConfigReg.Value); // WRITE_REG() should be last after setting all bits for a given register.
    GpioConfigReg.Value = 0;
    
    // Disable Alternate function for PF1 and Enable it for PF3
    GpioConfigReg.PortBit1Cfg = DISABLE;
    GpioConfigReg.PortBit3Cfg = ENABLE;
    GpioConfigReg.PortBit4Cfg = DISABLE;

    // Write the AFSEL bits in register
    REG_WRITE(GPIO_PORTF_AFSEL_R, GpioConfigReg.Value);
    GpioConfigReg.Value = 0;
    
    // Write port mux control register to send M1PWM7 signal to PF3
    {
        GPIOPCTL_REG   GpioPctlReg = {0};
        
        GpioPctlReg.PortMuxControl3 = M1PWM7_ENCODING; // Use PortMuxCtrl(x) for xth bit in Port
        REG_WRITE(GPIO_PORTF_PCTL_R, GpioPctlReg.Value);
    }

    // Enable weak pull up on PF4
    GpioConfigReg.PortBit4Cfg = ENABLE;
    REG_WRITE(GPIO_PORTF_PUR_R, GpioConfigReg.Value);
    GpioConfigReg.Value = 0;

    // Disable Analog function
    GpioConfigReg.PortBit1Cfg = DISABLE;
    GpioConfigReg.PortBit4Cfg = DISABLE;

    // Write the analog mode register
    REG_WRITE(GPIO_PORTF_AMSEL_R, GpioConfigReg.Value);
    GpioConfigReg.Value = 0;
    
    // Enable Digital Port via DEN
    GpioConfigReg.PortBit1Cfg = ENABLE; // For RED LED PF1 digital output.
    GpioConfigReg.PortBit3Cfg = ENABLE; // For GREEN LED PF3 PWM
    GpioConfigReg.PortBit4Cfg = ENABLE; // Enable for SW1

    // Enable DEN bits
    REG_WRITE(GPIO_PORTF_DEN_R, GpioConfigReg.Value);
    GpioConfigReg.Value = 0;

    // Setting up interrupt to trigger on rising edge of PF4.
    // 1. Mask the bit in GPIOIM.
    GpioConfigReg.PortBit4Cfg = 0;
    REG_WRITE(GPIO_PORTF_IM_R, GpioConfigReg.Value);
    GpioConfigReg.Value = 0;

    // Edge triggered interrupt.
    GpioConfigReg.PortBit4Cfg = 0;
    REG_WRITE(GPIO_PORTF_IS_R, GpioConfigReg.Value);
    GpioConfigReg.Value = 0; 

    // Interrupt on single edge.
    GpioConfigReg.PortBit4Cfg = 0;
    REG_WRITE(GPIO_PORTF_IBE_R, GpioConfigReg.Value);
    GpioConfigReg.Value = 0;

    // Interrupt on rising edge.
    GpioConfigReg.PortBit4Cfg = 1;
    REG_WRITE(GPIO_PORTF_IEV_R, GpioConfigReg.Value);
    GpioConfigReg.Value = 0;

    // Clear GPIORIS register.
    REG_WRITE(GPIO_PORTF_RIS_R, 0);

    // Unmask GPIOIM.
    GpioConfigReg.PortBit4Cfg = 1;
    REG_WRITE(GPIO_PORTF_IM_R, GpioConfigReg.Value);
    GpioConfigReg.Value = 0;

    // Enable interrupt from NVIC by writing to corresponding IEx register
    REG_WRITE(NVIC_EN0_R, 0x40000000); // Generalize later for all vectors

}

