/*
 * device.h
 *
 *  Created on: Oct 4, 2015
 *      Author: harsh
 */

#ifndef DEVICE_H_
#define DEVICE_H_

#include "GPIO.h"
#include "macros.h"
#include "tm4c123gh6pm.h"

// Bit Band regions are useful when we want to modify one bit in peripheral register as an atomic operation.
// This protects against accidental modification of other bits in the register.
#define PERIPHERAL_BIT_BAND_START 0x40000000
#define PERIPHERAL_BIT_BAND_END   0x400FFFFF

#define PERIPHERAL_BIT_BAND_ALIAS_START 0x42000000
#define PERIPHERAL_BIT_BAND_ALIAS_END   0x43FFFFFF

#define GET_BIT_BAND_ALIAS(_addr,_bit) (PERIPHERAL_BIT_BAND_ALIAS_START + (((_addr - PERIPHERAL_BIT_BAND_START) << 5)) + (_bit << 2))

/*
RCGCx register to enable clock to various peripherals
*/
typedef struct RCGC0_REG_STRUCT
{
	uint32_t Reserved        	:BIT_RANGE(2,0  );
	uint32_t WDT0_Clock_En   	:BIT      (3    );
	uint32_t Reserved        	:BIT_RANGE(5,4  );
	uint32_t HIB_Clock_En    	:BIT      (6    );
	uint32_t Reserved		 	:BIT      (7    );
	uint32_t ADC0_Sample_speed	:BIT_RANGE(9,8  );   // 0x3 = 1M Samples/sec, 0x2 = 500K Samples/sec and so on..
	uint32_t ADC1_Sample_speed	:BIT_RANGE(11,10); // 0x3 = 1M Samples/sec, 0x2 = 500K Samples/sec and so on..
	uint32_t Reserved	        :BIT_RANGE(15,12);
	uint32_t ADC0_Clock_En		:BIT      (16   );
	uint32_t ADC1_Clock_En		:BIT      (17   );
	uint32_t Reserved	        :BIT_RANGE(19,18);
	uint32_t PWM0_Clock_En		:BIT      (20   );
	uint32_t Reserved	        :BIT_RANGE(23,21);
	uint32_t CAN0_Clock_En		:BIT      (24   );
	uint32_t CAN1_Clock_En		:BIT      (25   );
	uint32_t Reserved	        :BIT_RANGE(27,26);
	uint32_t WDT1_Clock_En		:BIT      (28   );
	uint32_t Reserved	        :BIT_RANGE(31,29);
}RCGC0_REG;

typedef struct RCGC1_REG_STRUCT
{
	uint32_t UART0_Clock_En		:BIT      (0    );
	uint32_t UART1_Clock_En		:BIT      (1    );
	uint32_t UART2_Clock_En		:BIT      (2    );
	uint32_t Reserved           :BIT      (3    );
	uint32_t SSI0_Clock_En		:BIT      (4    );
	uint32_t SSI1_Clock_En		:BIT      (5    );
	uint32_t Reserved	        :BIT_RANGE(7,6  );
	uint32_t QEI0_Clock_En		:BIT      (8    );
	uint32_t QEI1_Clock_En		:BIT      (9    );
	uint32_t Reserved	        :BIT_RANGE(11,10);
	uint32_t I2C0_Clock_En		:BIT      (12   );
	uint32_t Reserved           :BIT      (13   );
	uint32_t I2C1_Clock_En		:BIT      (14   );
	uint32_t Reserved           :BIT      (15   );
	uint32_t TIMER0_Clock_En    :BIT      (16   );
	uint32_t TIMER1_Clock_En    :BIT      (17   );
	uint32_t TIMER2_Clock_En    :BIT      (18   );
	uint32_t TIMER3_Clock_En    :BIT      (19   );
	uint32_t Reserved	        :BIT_RANGE(23,20);
	uint32_t COMP0_Clock_En     :BIT      (24   );
	uint32_t COMP1_Clock_En     :BIT      (25   );
	uint32_t Reserved	        :BIT_RANGE(31,26);
}RCGC1_REG;

typedef struct RCGC2_REG_STRUCT
{
	uint32_t GPIOA_Clock_En		:BIT      (0     );
	uint32_t GPIOB_Clock_En		:BIT      (1     );
	uint32_t GPIOC_Clock_En		:BIT      (2     );
	uint32_t GPIOD_Clock_En		:BIT      (3     );
	uint32_t GPIOE_Clock_En		:BIT      (4     );
	uint32_t GPIOF_Clock_En		:BIT      (5     );
	uint32_t Reserved	        :BIT_RANGE(12,6  );
	uint32_t UDMA_Clock_En		:BIT      (13    );
	uint32_t Reserved	        :BIT_RANGE(15, 14);
	uint32_t USB0_Clock_En		:BIT      (16    );
	uint32_t Reserved	        :BIT_RANGE(31, 17);
}RCGC2_REG;

#endif /* DEVICE_H_ */
