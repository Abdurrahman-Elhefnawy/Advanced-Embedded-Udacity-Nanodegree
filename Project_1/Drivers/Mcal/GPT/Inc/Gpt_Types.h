/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  GPT_Types.h
 *       Module:  GPT
 *
 *  Description:  Header file for GPT types    
 *  
 *********************************************************************************************************************/
#ifndef GPT_TYPES_H
#define GPT_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/



typedef void (*Gpt_NotifyType(void));
typedef uint32 Gpt_ValueType;


typedef enum
{
    Gpt_TIMER_0 = 0 ,
    Gpt_TIMER_1,
    Gpt_TIMER_2,
    Gpt_TIMER_3,
    Gpt_TIMER_4,
    Gpt_TIMER_5,
    Gpt_TIMER_6,
    Gpt_TIMER_7,
    Gpt_TIMER_8,
    Gpt_TIMER_9,
    Gpt_TIMER_10,
    Gpt_TIMER_11,
}Gpt_ChannelType;

typedef enum
{
    Gpt_ONESHOT_MODE,
    Gpt_CONTINUOUS_MODE   
}Gpt_ModeType;

typedef enum
{
    Gpt_PREDEF_TIMER_1US_16BIT,
    Gpt_PREDEF_TIMER_1US_24BIT,
    Gpt_PREDEF_TIMER_1US_32BIT,
    Gpt_PREDEF_TIMER_100US_32BIT,
    
}Gpt_PredefTimerType;

typedef struct 
{
    Gpt_ChannelType    Channel_Id;
    Gpt_ModeType       Channel_Mode;
    uint32             Channel_TickFrequency;
    uint32             Channel_TickMaxValue;
 
}Gpt_ConfigType;


#endif  /* GPT_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: GPT_Types.h
 *********************************************************************************************************************/
