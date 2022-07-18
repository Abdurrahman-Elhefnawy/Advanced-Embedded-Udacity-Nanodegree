/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Mcu_Hw.h
 *       Module:  Mcu_Hw
 *
 *  Description:  header file for Registers definition    
 *  
 *********************************************************************************************************************/
#ifndef MCU_HW_H
#define MCU_HW_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef struct 
{
    uint32 VECACT   :8;
    uint32          :3;
    uint32 RETBASE  :1;
    uint32 VECPEND  :3;
    uint32 VECPEND  :4;
    uint32          :2;
    uint32 ISRPEND  :1;
    uint32 ISRPRE   :1;
    uint32          :1;
    uint32 PENDSTCLR:1;
    uint32 PENDSTSET:1;
    uint32 UNPENDSV :1;
    uint32 PENDSV   :1;
    uint32          :2;
    uint32 NMISET   :1; 
}INTCTRL_BF;
typedef union 
{
    uint32 R;
    INTCTRL_BF B;
}INTCTRL_Tag;



/*        SYSPRIx       */
typedef struct 
{
    uint32          :5;
    uint32 MEM      :3;
    uint32          :5;
    uint32 BUS      :3;
    uint32          :5;
    uint32 USAGE    :3;
    uint32          :8;
}SYSPRI1_BF;
typedef union
{
    uint32 VALUE;
    SYSPRI1_BF BITS;
}SYSPRI1_U;

/**************/
typedef struct 
{
    uint32       :29;
    uint32 SVC   :3;
}SYSPRI2_BF;

typedef union
{
    uint32 VALUE;
    SYSPRI2_BF BITS;
}SYSPRI2_U;

/**************/
typedef struct 
{
    uint32        :5;
    uint32 DEBUG  :3;
    uint32        :13;
    uint32 PENDSV :3;
    uint32        :5;
    uint32 TICK   :3;
    
}SYSPRI3_BF;

typedef union
{
    uint32 VALUE;
    SYSPRI3_BF BITS;
}SYSPRI3_U;

/********SYSHNDCTRL*********/
typedef struct 
{
    uint32 MEMA   :1;
    uint32 BUSA   :1;
    uint32        :1;
    uint32 USGA   :1;
    uint32        :3;
    uint32 SVCA   :1;
    uint32 MON    :1;
    uint32        :1;
    uint32 PNDSV  :1;
    uint32 TICK   :1;
    uint32 USAGEP :1;
    uint32 MEMP   :1;
    uint32 BUSP   :1;
    uint32 SVC    :1;
    uint32 MEM    :1;
    uint32 BUS    :1;
    uint32 USAGE  :1;
    uint32        :13;
}SYSHNDCTRL_BF;

typedef union
{
    uint32 VALUE;
    SYSHNDCTRL_BF BITS;
}SYSHNDCTRL_U;



/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define CORTEXM4_PERI_BASE_ADDRESS             0xE000E000
#define APINT                                  (*((volatile uint32*)(CORTEXM4_PERI_BASE_ADDRESS+0xD0C)))
#define INTCTRL                                (*((volatile INTCTRL_Tag*)(CORTEXM4_PERI_BASE_ADDRESS+0xD04)))
#define SYSPRI1                                (*((volatile SYSPRI1_U*)(CORTEXM4_PERI_BASE_ADDRESS+0xD18)))
#define SYSPRI2                                (*((volatile SYSPRI2_U*)(CORTEXM4_PERI_BASE_ADDRESS+0xD1C)))
#define SYSPRI3                                (*((volatile SYSPRI3_U*)(CORTEXM4_PERI_BASE_ADDRESS+0xD20)))
#define SYSHNDCTRL                             (*((volatile SYSHNDCTRL_U*)(CORTEXM4_PERI_BASE_ADDRESS+0xD24)))
#define ENx_BASE_ADDRESS                       0X100
#define PRIx_BASE_ADDRESS                      0X400



/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 

 
#endif  /* MCU_HW_H */

/**********************************************************************************************************************
 *  END OF FILE: Mcu_Hw.h
 *********************************************************************************************************************/
