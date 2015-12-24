/*
 * device.c
 *
 *  Created on: Dec 13, 2015
 *      Author: harsh

 File for device specific functions
 */

#include "device.h"
#define NVIC_EN_MAX (5)
#define MAX_BITS_IN_ENO_R (32)

/*
Function: NVIC_EnableInterrupt

Parameters:
    IRQ_No: Interrupt Request Number
Note: Enables / Disables Interrupts.
*/
void NVIC_EnableInterrupt(uint32_t IRQ_No)
{
	uint32_t BitNo = IRQ_No % MAX_BITS_IN_ENO_R;
	uint32_t Value = 0;

	volatile uint32_t *pNVIC_EnReg = &NVIC_EN0_R;

	pNVIC_EnReg = pNVIC_EnReg + (IRQ_No / MAX_BITS_IN_ENO_R);

	Value = REG_READ(*pNVIC_EnReg);

	SET_BIT(Value, BitNo);

	REG_WRITE(*pNVIC_EnReg, Value);
}
