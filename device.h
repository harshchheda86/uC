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

#endif /* DEVICE_H_ */
