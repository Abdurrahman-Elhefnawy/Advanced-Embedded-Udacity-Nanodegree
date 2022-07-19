/*
 * bit_math.h
 *
 *  Created on: Oct 2, 2021
 *      Author: Abdurrahman Mohamed
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_


#define SET_BIT(PORT,BIT_NUMBER) (PORT) |= (1<<BIT_NUMBER)

#define CLR_BIT(PORT,BIT_NUMBER) (PORT) &= ~(1<<BIT_NUMBER)

#define TOGGLE_BIT(PORT,BIT_NUMBER) (PORT) ^= (1<<BIT_NUMBER)

#define BIT_IS_SET(REG,BIT_NUMBER) ((REG) & (1<<BIT_NUMBER))

// #define BIT_IS_CLR(REG,BIT_NUMBER) !BIT_IS_SET(REG,BIT_NUMBER)
#define BIT_IS_CLR(REG,BIT_NUMBER) (!((REG) & (1<<BIT_NUMBER)))

#define SET_PORT_VALUE(PORT,VALUE) (PORT) = (VALUE)

#define CLR_PORT(PORT) (PORT) = (0x00)


#endif /* BIT_MATH_H_ */
