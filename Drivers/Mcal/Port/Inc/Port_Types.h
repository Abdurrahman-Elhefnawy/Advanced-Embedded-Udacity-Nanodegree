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
}Port_PinType;

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
    Port_PinType pinId;
    Port_PinModeType pinMode;
    Port_PinDirectionType pinDirection;
    Port_PinInternalAttachType pinInternalAttach;
    Port_PinOutputCurrentType pinCurrent;
}Port_ConfigType;





 
#endif  /* Port_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Port_Types.h
 *********************************************************************************************************************/
