/*
 * ISR.c
 *
 *  Created on: Dec 12, 2015
 *      Author: harsh
 *      File for writing interrupt handlers.
 */

#include "device.h"
#include "ISR.h"
#include "PWM.h"

/*
Function: GPIO_PortFInterruptHandler

Interrupt Handler for GPIO Interrupts for PORT F.
*/
void GPIO_PortFInterruptHandler(void)
{
	GPIOCONFIG_REG	GpioRis = {0};
    static uint32_t i = 0;

    // Read the RIS register to determine which interrupt is fired. 
	GpioRis.Value = REG_READ(GPIO_PORTF_RIS_R);

	if(GpioRis.PortBit4Cfg)
	{
		// RED_LED = RED_LED^1; // Toggle RED LED
		SetPwmDutyCycle(i, M1_PWM7);

        i = (i + 5) % 100;

	}

    // Set Bits in ICR for the bits which were set in RIS register to clear the interrupt. Keep this as last line. 
	REG_WRITE(GPIO_PORTF_ICR_R,GpioRis.Value);
}
