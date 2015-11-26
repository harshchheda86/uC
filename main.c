/*
 * main.c
 */

#include "device.h"

#define RED_LED (*(volatile uint8_t	*)GET_BIT_BAND_ALIAS(GPIO_PORTF_DATA_REG_OFFSET,1))
int main(void)
{
	//volatile uint8_t	*p = (volatile uint8_t	*)GET_BIT_BAND_ALIAS(0x400253FC,1); // Get the bit band alias for PORT F1

	// Setup the device.
	
	//Setup GPIO
	SetupGPIO();

	RED_LED = 1;
	
	PwmInit();
	
	while(TRUE)
	{
		// Processor Infinite loop here
	}
	
	return 0;
}
