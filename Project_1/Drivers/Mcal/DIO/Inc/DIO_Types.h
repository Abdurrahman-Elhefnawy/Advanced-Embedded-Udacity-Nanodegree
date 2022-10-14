/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  DIO_Types.h
 *       Module:  DIO
 *
 *  Description:  Header file for DIO types    
 *  
 *********************************************************************************************************************/
#ifndef DIO_TYPES_H
#define DIO_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
typedef enum
{
    DIO_PA0=0,
    DIO_PA1,
    DIO_PA2,
    DIO_PA3,
    DIO_PA4,
    DIO_PA5,
    DIO_PA6,
    DIO_PA7,

    DIO_PB0,
    DIO_PB1,
    DIO_PB2,
    DIO_PB3,
    DIO_PB4,
    DIO_PB5,
    DIO_PB6,
    DIO_PB7,

    DIO_PC0,
    DIO_PC1,
    DIO_PC2,
    DIO_PC3,
    DIO_PC4,
    DIO_PC5,
    DIO_PC6,
    DIO_PC7,

    DIO_PD0,
    DIO_PD1,
    DIO_PD2,
    DIO_PD3,
    DIO_PD4,
    DIO_PD5,
    DIO_PD6,
    DIO_PD7,

    DIO_PE0 ,
    DIO_PE1,
    DIO_PE2,
    DIO_PE3,
    DIO_PE4,
    DIO_PE5,
    
    
    DIO_PF0,
    DIO_PF1,
    DIO_PF2,
    DIO_PF3,
    DIO_PF4
}DIO_ChannelType;

typedef enum
{
    DIO_PORTA=0,
    DIO_PORTB,
    DIO_PORTC,
    DIO_PORTD,
    DIO_PORTE,
    DIO_PORTF,    
}DIO_PortType;

typedef enum
{
    LOW = 0,
    HIGH
}DIO_LevelType;

typedef uint8 DIO_PortLevelType;


 
#endif  /* DIO_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: DIO_Types.h
 *********************************************************************************************************************/
