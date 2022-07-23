/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  IntCtrl_Cfg.h
 *       Module:  -
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef INTCTRL_CFG_H
#define INTCTRL_CFG_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include"IntCtrl_Types.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define PRIORITY_GROUPING               3       // 1)--->xxx  2)-->xxy  3)-->xyy    4)-->yyy

#define NUMBER_OF_ACTIVE_INTERRUPTS     3
#define NUMBER_OF_ACTIVE_SYSEXCEPTIONS  2


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef struct {
    IntCtrl_InterruptType intNumber;
    uint8 intGroup ;
    uint8 intSubGroup;
}IntCtrl_ActiveInterruptType;
 
 
typedef struct {
    IntCtrl_InterruptType excNumber;
    uint8 excGroup ;
    uint8 excSubGroup;
}IntCtrl_ActiveExceptionType;
 


extern IntCtrl_ActiveInterruptType Active_Interrupts[NUMBER_OF_ACTIVE_INTERRUPTS];
extern IntCtrl_ActiveExceptionType Active_Exceptions[NUMBER_OF_ACTIVE_SYSEXCEPTIONS];

#endif  /* INTCTRL_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: IntCtrl_Cfg.h
 *********************************************************************************************************************/
