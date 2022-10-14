/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Port_Types.h
 *       Module:  Port
 *
 *  Description:  Header file for Port types    
 *  
 *********************************************************************************************************************/
#ifndef PORT_TYPES_H
#define PORT_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef enum
{
    Port_PA0=0,
    Port_PA1,
    Port_PA2,
    Port_PA3,
    Port_PA4,
    Port_PA5,
    Port_PA6,
    Port_PA7,

    Port_PB0,
    Port_PB1,
    Port_PB2,
    Port_PB3,
    Port_PB4,
    Port_PB5,
    Port_PB6,
    Port_PB7,

    Port_PC0,
    Port_PC1,
    Port_PC2,
    Port_PC3,
    Port_PC4,
    Port_PC5,
    Port_PC6,
    Port_PC7,

    Port_PD0,
    Port_PD1,
    Port_PD2,
    Port_PD3,
    Port_PD4,
    Port_PD5,
    Port_PD6,
    Port_PD7,

    Port_PE0 ,
    Port_PE1,
    Port_PE2,
    Port_PE3,
    Port_PE4,
    Port_PE5,
    
    
    Port_PF0,
    Port_PF1,
    Port_PF2,
    Port_PF3,
    Port_PF4
}Port_PinType;

typedef enum
{
    PORT_PORTA=0,
    PORT_PORTB,
    Port_PORTC,
    Port_PORTD,
    Port_PORTE,
    Port_PORTF,    
}Port_PortType;


typedef enum
{
    INPUT = 0,
    OUTPUT
}Port_PinDirectionType;

typedef enum
{
    PULL_DOWN = 0,
    PULL_UP,
    OPEN_DRAIN
}Port_PinInternalAttachType;

typedef enum
{
    mA_2 = 0,
    mA_4,
    mA_8 
}Port_PinOutputCurrentType;

typedef enum
{
    DISABLE_INTERRUPT = 0,
    ENABLE_INTERRUPT = 1 
}Port_PinIntEnableType;

typedef enum
{
    GPIO_MODE = -1,
    ANALOG_MODE = 0 ,
    ALTERNATE_1_MODE = 1 ,
    ALTERNATE_2_MODE,
    ALTERNATE_3_MODE,
    ALTERNATE_4_MODE,
    ALTERNATE_5_MODE,
    ALTERNATE_6_MODE,
    ALTERNATE_7_MODE,
    ALTERNATE_8_MODE,
    ALTERNATE_9_MODE,
    ALTERNATE_10_MODE,
    ALTERNATE_11_MODE,
    ALTERNATE_12_MODE,
    ALTERNATE_13_MODE,
    ALTERNATE_14_MODE,
    ALTERNATE_15_MODE,      
}Port_PinModeType;

typedef struct
{
    Port_PinType                pinId;
    Port_PinModeType            pinMode;
    Port_PinDirectionType       pinDirection;
    Port_PinInternalAttachType  pinInternalAttach;
    Port_PinOutputCurrentType   pinCurrent;
    Port_PinIntEnableType       pinInteruurp; 
}Port_ConfigType;





 
#endif  /* Port_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Port_Types.h
 *********************************************************************************************************************/
