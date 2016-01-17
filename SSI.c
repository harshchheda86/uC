/*
 * SSI.c
 *
 *  Created on: Jan 16, 2016
 *      Author: harsh
 */

#include "device.h"

void SSI_Init()
{
	RCGCSSI_REG	RcgcSsiReg = {0};
	SSICR0_REG  SsiCr0Reg  = {0};
	SSICR1_REG	SsiCr1Reg  = {0};
	SSICC_REG	SsiCcReg   = {0};
	SSICPSR_REG	SsiCpsrReg = {0};

	// Enable clock to SSI2 module
	RcgcSsiReg.SSI2ClockEn = 1;
	REG_WRITE(SYSCTL_RCGCSSI_R, RcgcSsiReg.Value);

	// Clearing SSE bit for SSI configuration. 
	SsiCr1Reg.SSI_PortEnable = FALSE;
	REG_WRITE(SSI2_CR1_R, SsiCr1Reg.Value); // Defaults to SSI as Master

	// Selecting Clock Source to be PIOSC
	SsiCcReg.ClockSource = 0x5;
	REG_WRITE(SSI2_CC_R, SsiCcReg.Value);

	// For 2 Mbps program the Pre Scale Divisor
	SsiCpsrReg.ClockPreScaleDivisor = 4; // CPSDVSR = 4 and SCR = 0
	REG_WRITE(SSI2_CPSR_R,SsiCpsrReg.Value);

	// Configure the SSI2 Module
	SsiCr0Reg.DataSizeSelect	= 0x7; // 8 Bits data
	SsiCr0Reg.FrameFormatSelect = 0;   // Freescale format
	SsiCr0Reg.ClockPolarity		= 1;   // Clock is held high
	SsiCr0Reg.SerialClockRate 	= 0;   // SCR = 0
	SsiCr0Reg.SerialClockPhase 	= 0;   // Data captured on First Clock edge transition.

	REG_WRITE(SSI2_CR0_R, SsiCr0Reg.Value);

	// Enable the SSI Module now
	SsiCr1Reg.Value = REG_READ(SSI2_CR1_R);
	SsiCr1Reg.SSI_PortEnable = ENABLE;
	REG_WRITE(SSI2_CR1_R, SsiCr1Reg.Value);
	
}
