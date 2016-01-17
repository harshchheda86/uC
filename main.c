/*
 * main.c
 */

#include "device.h"

int main(void)
{
	//volatile uint8_t	*p = (volatile uint8_t	*)GET_BIT_BAND_ALIAS(0x400253FC,1); // Get the bit band alias for PORT F1

	// Setup the device.
	
	//Setup GPIO
	SetupGPIO();

	// RED_LED = 1;
	
	PwmInit();
	
	SSI_Init();

	NOKIA_LCD_Init();

	while(TRUE)
	{
		// Processor Infinite loop here

	}
	
	return 0;
}
