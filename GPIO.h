/*
 * GPIO.h
 *
 *  Created on: Oct 4, 2015
 *      Author: harsh
 */

#ifndef GPIO_H_
#define GPIO_H_

#include"macros.h"
#include"stdint.h"
#include"device.h"

/*
*****************************************************************************************
********* NEVER PROGRAM PD4 AND PD5 PINS AS GPIO AS THEY ARE USED FOR DEBUGGING *********
*****************************************************************************************
*/

/*PF4 is SW1, PF0 is SW2, PF1 is Red LED, PF2 is Blue LED, PF3 is Green LED*/

/*
On this board
*/

#define DIR_INPUT 0
#define DIR_OUTPUT 1
#define ANALOG 0
#define DIGITAL 1
#define ENABLE 1
#define DISABLE 0
#define GPIO_MAX_PORT_BITS 8

#define GPIO_PORTF_DATA_REG_OFFSET (0x400253FC)

/*
enum for listing out PORTs
*/
typedef enum GPIO_PORT_ENUM
{
	GPIO_PORT_A = 0x0,
	GPIO_PORT_B,
	GPIO_PORT_C,
	GPIO_PORT_D,
	GPIO_PORT_E,
	GPIO_PORT_F,
	
	// Keep this as last
	GPIO_PORT_MAX,
}GPIO_PORT;

/*
RCGCGPIO register to enable clock to various PORTs
*/
typedef struct RCGCGPIO_REG_STRUCT
{
	union
	{
		struct
		{			
			uint32_t PortA_Clock_En  :BIT(0); // 0 = Clock is not supplied to the PORT
			uint32_t PortB_Clock_En  :BIT(1); // 1 = Clock is supplied to the PORT
			uint32_t PortC_Clock_En  :BIT(2);
			uint32_t PortD_Clock_En  :BIT(3);
			uint32_t PortE_Clock_En  :BIT(4);
			uint32_t PortF_Clock_En  :BIT(5);
			uint32_t Reserved        :BIT_RANGE(31,6);
		};
		uint32_t Value;
	};
}RCGCGPIO_REG;

/*
SCGCGPIO register to enable clock to various PORTs in Sleep mode.
*/
typedef struct SCGCGPIO_REG_STRUCT
{
	union
	{
		struct
		{
			uint32_t PortA_SleepClock_En  :BIT(0); // 0 = GPIO port is disabled in sleep.
			uint32_t PortB_SleepClock_En  :BIT(1); // 1 = GPIO port is enabled and clock is supplied to it.
			uint32_t PortC_SleepClock_En  :BIT(2);
			uint32_t PortD_SleepClock_En  :BIT(3);
			uint32_t PortE_SleepClock_En  :BIT(4);
			uint32_t PortF_SleepClock_En  :BIT(5);
			uint32_t Reserved             :BIT_RANGE(31,6);
		};
		uint32_t Data;
	};
}SCGCGPIO_REG;

/*
DCGCGPIO register to enable clock to various PORTs in deep sleep mode.
*/
typedef struct DCGCGPIO_REG_STRUCT
{
	union
	{
		struct
		{
			uint32_t PortA_DeepSleepClock_En  :BIT(0); // 0 = GPIO port is disabled in deep sleep.
			uint32_t PortB_DeepSleepClock_En  :BIT(1); // 1 = GPIO port is enabled and clock is supplied to it.
			uint32_t PortC_DeepSleepClock_En  :BIT(2);
			uint32_t PortD_DeepSleepClock_En  :BIT(3);
			uint32_t PortE_DeepSleepClock_En  :BIT(4);
			uint32_t PortF_DeepSleepClock_En  :BIT(5);
			uint32_t Reserved        		  :BIT_RANGE(31,6);
		};
		uint32_t Data;
	};
}DCGCGPIO_REG;

/*
GPIODIR:register to give direction to various PORTs
1 = Output and 0 = Input

GPIODRxR: GPIODRxR register to give drive capacity to various ports.x = 2, 4, 8 for x milliamps drive.
1 = Drive enabled for this value, 0 = Drive is enabled by other register

GPIOAFSEL:
register to sellect GPIO vs Alternate function.
1 = Pin functions as Alternate function, 0 = Pin functions as GPIO

GPIOPUR:
register to enable weak pull-up register on the pin
1 = Pin pull-up enable, 0 = Pin pull-up disabled

GPIOPDR:
register to enable weak pull-down register on the pin.
1 = Pin pull-down enabled, 0 = Pin pull-down disabled

GPIOODR:
register to enable Open Drain Configuration on the pin.
1 = Pin configured as open drain, 0 = Pin not configured as open drain

GPIOSLR:
GPIOSLR register to enable slew rate control. Available only if 8mA drive is enabled.
1 = Pin slew rate control enabled , 0 = Pin slew rate control disabled

GPIODEN:
GPIODEN register to enable port as digital port.
1 = Pin digital function enabled, 0 = Pin digital function disabled

GPIOAMSEL:
register to enable port as analog port.
1 = Pin analog function enabled, 0 = Pin analog function disabled

GPIOIS:
register to configure the sense of Interrupts as Edge triggered vs Level triggered.
1 = level sensitive trigger, 0 = edge sensitive trigger

GPIOBE:
GPIOBE register to configure the sense of Interrupts on both edges.GPIOIS should be configured to detect edges.
1 = Both edges generated interrupt, 0 = interrupt generation controlled by GPIODEV

GPIODEV:
register to configure the sense of Interrupts on both edges.
1 = rising edge generates interrupt, 0 = falling edge generates an interrupt

GPIOIM:
register to mask Interrupts
1 = Interrupt is masked, 0 = interrupt is unmasked

GPIOCR:
register to commit chages to various registers mentioned below
1 = The corresponding GPIOAFSEL, GPIOPUR, GPIOPDR, or GPIODEN bits can be written, 0 = The corresponding GPIOAFSEL, GPIOPUR, GPIOPDR, or GPIODEN bits cannot be written
*/
typedef struct GPIOCONFIG_REG_STRUCT
{
	union
	{
		struct
		{
			uint32_t PortBit0Cfg  :BIT(0); 
			uint32_t PortBit1Cfg  :BIT(1);
			uint32_t PortBit2Cfg  :BIT(2);
			uint32_t PortBit3Cfg  :BIT(3);
			uint32_t PortBit4Cfg  :BIT(4);
			uint32_t PortBit5Cfg  :BIT(5);
			uint32_t PortBit6Cfg  :BIT(6);
			uint32_t PortBit7Cfg  :BIT(7);
			uint32_t Reserved     :BIT_RANGE(31,8);
		};
		uint32_t Value;
	};
}GPIOCONFIG_REG;

/*
GPIOLOCK register to lock the commit register.
Commit register is used to commit the configurations of the IO registers.
LOCK register can be used to prevent accidental configuration of JTAG/SWD and NMI as GPIO. 
*/
typedef struct GPIOLOCK_REG_STRUCT
{
	union
	{
		struct
		{
			uint32_t LOCK; // magic number 0x4C4F434B unlocks the GPIOCR. Writing anything else locks GPIOCR.
		};
		uint32_t Data;
	};
}GPIOLOCK_REG;

void SetupGPIO();

#endif /* GPIO_H_ */
