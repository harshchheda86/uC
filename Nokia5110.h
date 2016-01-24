/*
 * Nokia5110.h
 *
 *  Created on: Jan 16, 2016
 *      Author: harsh
 */

#ifndef NOKIA5110_H_
#define NOKIA5110_H_

#include "device.h"

#define BACKLIGHT_LED (*(volatile uint8_t	*)GET_BIT_BAND_ALIAS(GPIO_PORTB_DATA_REG_OFFSET,3))
#define DATA_COMMAND (*(volatile uint8_t	*)GET_BIT_BAND_ALIAS(GPIO_PORTB_DATA_REG_OFFSET,2))
#define LCD_RESET (*(volatile uint8_t	*)GET_BIT_BAND_ALIAS(GPIO_PORTB_DATA_REG_OFFSET,1))

#define DATA 1
#define COMMAND 0 

void NOKIA_LCD_Init();

#endif /* NOKIA5110_H_ */
