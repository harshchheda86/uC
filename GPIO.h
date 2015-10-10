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

/*
*****************************************************************************************
********* NEVER PROGRAM PD4 AND PD5 PINS AS GPIO AS THEY ARE USED FOR DEBUGGING *********
*****************************************************************************************
*/

#define DIR_INPUT 0
#define DIR_OUTPUT 1
#define ANALOG 0
#define DIGITAL 1
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
			uint32_t Reserved        :BIT_RANGE(31,6);
			uint32_t PortF_Clock_En  :BIT(5);
			uint32_t PortE_Clock_En  :BIT(4);
			uint32_t PortD_Clock_En  :BIT(3);
			uint32_t PortC_Clock_En  :BIT(2);
			uint32_t PortB_Clock_En  :BIT(1);
			uint32_t PortA_Clock_En  :BIT(0);
		};
		uint32_t Data;
	};
}RCGCGPIO_REG;

typedef struct GPIO_CONFIG_PARAMS_REC
{
	BOOL Type,		// Analog or Digital
	BOOL Direction, // Input or Output
}GPIO_CONFIG_PARAMS;

#endif /* GPIO_H_ */
