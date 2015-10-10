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

// Definition of IO Port registers. GPIO Clock must be enabled before register can be programmed.
#define GPIO_PORT_A_APB 0x40004000
#define GPIO_PORT_A_AHB 0x40058000
#define GPIO_PORT_B_APB 0x40005000
#define GPIO_PORT_B_AHB 0x40059000
#define GPIO_PORT_C_APB 0x40006000
#define GPIO_PORT_C_AHB 0x4005A000
#define GPIO_PORT_D_APB 0x40007000
#define GPIO_PORT_D_AHB 0x4005B000
#define GPIO_PORT_E_APB 0x40024000
#define GPIO_PORT_E_AHB 0x4005C000
#define GPIO_PORT_F_APB 0x40025000
#define GPIO_PORT_F_AHB 0x4005D000

#endif /* DEVICE_H_ */
