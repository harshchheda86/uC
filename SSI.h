/*
 * SSI.h
 *
 *  Created on: Jan 16, 2016
 *      Author: harsh
 */

#ifndef SSI_H_
#define SSI_H_

typedef struct RCGCSSI_REG_STRUCT
{
    union
    {
        struct
        {
            uint32_t SSI0ClockEn     :BIT(0);
            uint32_t SSI1ClockEn     :BIT(1);
            uint32_t SSI2ClockEn     :BIT(2);
            uint32_t SSI3ClockEn     :BIT(3);
            uint32_t                 :BIT_RANGE(31,4);
        };
        uint32_t Value;
    };
}RCGCSSI_REG;

typedef struct SSICR0_REG_STRUCT
{
	union
	{
		struct
		{
			uint32_t DataSizeSelect		:BIT_RANGE(3,  0);
			uint32_t FrameFormatSelect	:BIT_RANGE(5,  4);
			uint32_t ClockPolarity		:      BIT(    6);
			uint32_t SerialClockPhase	:	   BIT(    7); // Available only in Freescale SPI format
			uint32_t SerialClockRate	:BIT_RANGE(15, 8); // SSInClk = SysClk / (CPSDVSR * (1 + SCR))
			uint32_t					:BIT_RANGE(31, 16);
		};
		uint32_t Value;
	};
}SSICR0_REG;

typedef struct SSICR1_REG_STRUCT
{
	union
	{
		struct
		{
			uint32_t LoopBackMode		:	   BIT(    0);
			uint32_t SSI_PortEnable 	:	   BIT(    1);
			uint32_t MasterSlaveSelect  :	   BIT(    2);
			uint32_t Reserved			:	   BIT(    3);
			uint32_t EndOfTransmission	:	   BIT(    4);
			uint32_t					:BIT_RANGE(31, 5);
		};
		uint32_t Value;
	};
}SSICR1_REG;

typedef struct SSISR_REG_STRUCT
{
	union
	{
		struct
		{
			uint32_t TransmitFIFOEmpty	:	   BIT(    0);
			uint32_t TransmitFIFONotFull:	   BIT(    1);
			uint32_t ReceiveFIFONotEmpty:	   BIT(    2);
			uint32_t ReceiveFIFOFull	:	   BIT(    3);
			uint32_t Busy	            :	   BIT(    4);
			uint32_t					:BIT_RANGE(31, 5);
		};
		uint32_t Value;
	};
}SSISR_REG;

typedef struct SSICPSR_REG_STRUCT
{
	union
	{
		struct
		{
			uint32_t ClockPreScaleDivisor	:BIT_RANGE(7,  0);
			uint32_t					    :BIT_RANGE(31, 8);
		};
		uint32_t Value;
	};
}SSICPSR_REG;

typedef struct SSIIM_REG_STRUCT
{
	union
	{
		struct
		{
			uint32_t ReceiveOverRunIM	:	   BIT(    0);
			uint32_t ReceiveTimeOutIM	:	   BIT(    1);
			uint32_t ReceiveFIFOIM		:	   BIT(    2);
			uint32_t TransmitFIFOIM		:	   BIT(    3);
			uint32_t					:BIT_RANGE(31, 4);
		};
		uint32_t Value;
	};
}SSIIM_REG;

typedef struct SSIICR_REG_STRUCT
{
	union
	{
		struct
		{
			uint32_t ReceiveOverRunIC	:	   BIT(    0); // IC: Interrupt Clear
			uint32_t ReceiveTimeOutIC	:	   BIT(    1);
			uint32_t					:BIT_RANGE(31, 2);
		};
		uint32_t Value;
	};
}SSIICR_REG;

typedef struct SSICC_REG_STRUCT
{
	union
	{
		struct
		{
			uint32_t ClockSource	:BIT_RANGE(3,  0); // Values Allowed: 0x0 -> SystemClock, 0x5 -> PIOSC as clock source
			uint32_t			    :BIT_RANGE(31, 4);
		};
		uint32_t Value;
	};
}SSICC_REG;

void Ssi_Init();
BOOL IsSsiBusy();
void SsiWriteData(uint8_t Data);
BOOL IsSsiTransmitDone();

#endif /* SSI_H_ */
