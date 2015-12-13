/*
 * ISR.c
 *
 *  Created on: Dec 12, 2015
 *      Author: harsh
 *      File for writing interrupt handlers.
 */

#include "device.h"
 #include "ISR.h"

void GPIO_PortFInterruptHandler(void)
{
	GPIOCONFIG_REG	GpioRis = {0};

	GpioRis.Value = REG_READ(GPIO_PORTF_RIS_R);

	if(GpioRis.PortBit4Cfg)
	{
		RED_LED = 1;
	}

    // Set Bits in ICR for the bits which were set in RIS register. 
	REG_WRITE(GPIO_PORTF_ICR_R,GpioRis.Value);
}
