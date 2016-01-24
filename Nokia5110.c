/*
 * Nokia5110.c
 *
 *  Created on: Jan 16, 2016
 *      Author: harsh
 */

#include "Nokia5110.h"

void LCD_WriteCommand(uint8_t Command)
{
	// Wait for SSI To be not busy
	while(IsSsiBusy());

	// D/Cbar = 0 for command
	DATA_COMMAND = 0;

	// Write the command
	SsiWriteData(Command);

	// Wait for SSI To be not busy
	while(IsSsiBusy());
}

void LCD_WriteData(uint8_t Data)
{
	// Check if the previous transmission is done
	while(IsSsiTransmitDone() == FALSE);

	// D/Cbar = 0 for command
	DATA_COMMAND = 1;

	// Write the command
	SsiWriteData(Data);
}

void NOKIA_LCD_Init()
{
	// Reset the LCD 
	LCD_RESET = 0;
	LCD_RESET = 1;

	// Turn on the backlight
	BACKLIGHT_LED = 1;

	// Add LCD commands to be transmitted here

	// Test code 

	LCD_WriteCommand(0x21);
	LCD_WriteCommand(0x90);
	LCD_WriteCommand(0x20);
	LCD_WriteCommand(0x0c);

	LCD_WriteData(0xff);
	LCD_WriteData(0xff);
	LCD_WriteData(0x00);
	LCD_WriteData(0xff);
	LCD_WriteData(0xff);
	LCD_WriteData(0x00);
	LCD_WriteData(0xff);
	LCD_WriteData(0xff);
	LCD_WriteData(0x00);
	LCD_WriteData(0xff);
	LCD_WriteData(0xff);
	LCD_WriteData(0x00);
	LCD_WriteData(0xff);
	LCD_WriteData(0xff);
	LCD_WriteData(0x00);
	LCD_WriteData(0xff);

	LCD_WriteCommand(0x0d);
}
