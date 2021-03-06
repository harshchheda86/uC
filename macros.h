/*
 * macros.h
 *
 *  Created on: Oct 4, 2015
 *      Author: harsh
 */

#ifndef MACROS_H_
#define MACROS_H_

#define TRUE  1
#define FALSE 0

#define BIT_RANGE(_hi,_lo) ((_hi) - (_lo) + 1)
#define BIT(_b) (1)

#define __BIT_NO(_bitNo) (0x1 << _bitNo) 

#define SET_BIT(_val,_bit) (_val =_val | (0x1 << _bit))
#define CLEAR_BIT(_val,_bit) (_val = _val & ~(0x1 << _bit))

#define REG_READ(_offset) (_offset)
#define REG_WRITE(_offset, _value) (_offset = _value)
#define REG_OR_WRITE(_offset, _value) (REG_WRITE(_offset, (REG_READ(_offset) | _value)))
#define REG_AND_WRITE(_offset, _value) (REG_WRITE(_offset, (REG_READ(_offset) & _value)))

typedef unsigned char BOOL;

#endif /* MACROS_H_ */
