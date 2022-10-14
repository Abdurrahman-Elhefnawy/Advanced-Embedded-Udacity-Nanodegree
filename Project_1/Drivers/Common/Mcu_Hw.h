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
    uint32 VECPEND  :7;
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
#define SYSTEM_CONTROL_BASE_ADDRESS            0x400FE000
#define APINT                                  (*((volatile uint32*)(CORTEXM4_PERI_BASE_ADDRESS+0xD0C)))
#define INTCTRL                                (*((volatile INTCTRL_Tag*)(CORTEXM4_PERI_BASE_ADDRESS+0xD04)))
#define SYSPRI1                                (*((volatile SYSPRI1_U*)(CORTEXM4_PERI_BASE_ADDRESS+0xD18)))
#define SYSPRI2                                (*((volatile SYSPRI2_U*)(CORTEXM4_PERI_BASE_ADDRESS+0xD1C)))
#define SYSPRI3                                (*((volatile SYSPRI3_U*)(CORTEXM4_PERI_BASE_ADDRESS+0xD20)))
#define SYSHNDCTRL                             (*((volatile SYSHNDCTRL_U*)(CORTEXM4_PERI_BASE_ADDRESS+0xD24)))
#define ENx_BASE_ADDRESS                       0X100
#define PRIx_BASE_ADDRESS                      0X400
 

#define ENx(OFFSET)             (*((volatile uint32*)(CORTEXM4_PERI_BASE_ADDRESS+ENx_BASE_ADDRESS + OFFSET)))
#define PRIx(OFFSET)            (*((volatile uint32*)(CORTEXM4_PERI_BASE_ADDRESS+PRIx_BASE_ADDRESS+ OFFSET)))





/***********GPIO Registers***********/
#define RCGCGPIO                            (*((volatile uint32*)(SYSTEM_CONTROL_BASE_ADDRESS+0x608)))

#define GPIODATAx_OFFSET                       0X3FC
#define GET_GPIODATAx_ADDRESS(Base)            (*((volatile uint32*)(GPIODATAx_OFFSET+Base)))

#define GPIODIRx_OFFSET                        0X400
#define GET_GPIODIRx_ADDRESS(Base)             (*((volatile uint32*)(GPIODIRx_OFFSET+Base)))


#define GPIOLOCKx_OFFSET                       0x520
#define GPIOLOCKx(Base)             (*((volatile uint32*)(GPIOLOCKx_OFFSET+Base)))


#define GPIOCRx_OFFSET                         0x524
#define GPIOCRx(Base)             (*((volatile uint32*)(GPIOCRx_OFFSET+Base)))

#define GPIOAFSELx_OFFSET                      0x420
#define GPIOAFSELx(Base)             (*((volatile uint32*)(GPIOAFSELx_OFFSET+Base)))


#define GPIOPCTLx_OFFSET                       0x52C
#define GPIOPCTLx(Base)             (*((volatile uint32*)(GPIOPCTLx_OFFSET+Base)))


#define GPIODR2Rx_OFFSET                       0x500
#define GPIODR2Rx(Base)             (*((volatile uint32*)(GPIODR2Rx_OFFSET+Base)))

#define GPIODR4Rx_OFFSET                       0x504
#define GPIODR4Rx(Base)             (*((volatile uint32*)(GPIODR4Rx_OFFSET+Base)))

#define GPIODR8Rx_OFFSET                       0x508
#define GPIODR8Rx(Base)             (*((volatile uint32*)(GPIODR8Rx_OFFSET+Base)))

#define GPIOODRx_OFFSET                       0x50C
#define GPIOODRx(Base)             (*((volatile uint32*)(GPIOODRx_OFFSET+Base)))

#define GPIOODRx_OFFSET                       0x50C
#define GPIOODRx(Base)             (*((volatile uint32*)(GPIOODRx_OFFSET+Base)))

#define GPIOPURx_OFFSET                       0x510
#define GPIOPURx(Base)             (*((volatile uint32*)(GPIOPURx_OFFSET+Base)))

#define GPIOPDRx_OFFSET                       0x514
#define GPIOPDRx(Base)             (*((volatile uint32*)(GPIOPDRx_OFFSET+Base)))

#define GPIODENx_OFFSET                       0x51C
#define GPIODENx(Base)             (*((volatile uint32*)(GPIODENx_OFFSET+Base)))

#define GPIOAMSELx_OFFSET                       0x528
#define GPIOAMSELx(Base) 	            (*((volatile uint32*)(GPIOAMSELx_OFFSET+Base)))

/****GPIO Interrupt registers */
#define GPIOISx_OFFSET                        0x404
#define GPIOISx(Base)             (*((volatile uint32*)(GPIOISx_OFFSET+Base)))

#define GPIOIBEx_OFFSET                       0x408
#define GPIOIBEx(Base)             (*((volatile uint32*)(GPIOIBEx_OFFSET+Base)))

#define GPIOIEVx_OFFSET                       0x40C
#define GPIOIEVx(Base)             (*((volatile uint32*)(GPIOIEVx_OFFSET+Base)))

#define GPIOIMx_OFFSET                        0x410
#define GPIOIMx(Base)             (*((volatile uint32*)(GPIOIMx_OFFSET+Base)))

#define GPIOICRx_OFFSET                       0x41C
#define GPIOICRx(Base)             (*((volatile uint32*)(GPIOICRx_OFFSET+Base)))




/*******************************************************
 *********************GPT Registers********************
 *******************************************************/
#define RCGCTIMER                          (*((volatile uint32*)(SYSTEM_CONTROL_BASE_ADDRESS+0x604)))
#define RCGCWTIMER                         (*((volatile uint32*)(SYSTEM_CONTROL_BASE_ADDRESS+0x65C)))

#define GPTMCFG_OFFSET                       0x000
#define GPTMCFG(Base)             (*((volatile uint32*)(GPTMCFG_OFFSET+Base)))

#define GPTMTAMR_OFFSET                       0x004
#define GPTMTAMR(Base)             (*((volatile uint32*)(GPTMTAMR_OFFSET+Base)))

#define GPTMCTL_OFFSET                       0x00C
#define GPTMCTL(Base)             (*((volatile uint32*)(GPTMCTL_OFFSET+Base)))

#define GPTMIMR_OFFSET                       0x018
#define GPTMIMR(Base)             (*((volatile uint32*)(GPTMIMR_OFFSET+Base)))

#define GPTMRIS_OFFSET                       0x01C
#define GPTMRIS(Base)             (*((volatile uint32*)(GPTMRIS_OFFSET+Base)))

#define GPTMMIS_OFFSET                       0x020
#define GPTMMIS(Base)             (*((volatile uint32*)(GPTMMIS_OFFSET+Base)))

#define GPTMTAV_OFFSET                       0x050
#define GPTMTAV(Base)             (*((volatile uint32*)(GPTMTAV_OFFSET+Base)))

#define GPTMTAILR_OFFSET                     0x028
#define GPTMTAILR(Base)             (*((volatile uint32*)(GPTMTAILR_OFFSET+Base)))

#define GPTMTAPR_OFFSET                     0x038
#define GPTMTAPR(Base)             (*((volatile uint32*)(GPTMTAPR_OFFSET+Base)))


#define GPTMICR_OFFSET                     0x024
#define GPTMICR(Base)             (*((volatile uint32*)(GPTMICR_OFFSET+Base)))



/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 

 
#endif  /* MCU_HW_H */

/**********************************************************************************************************************
 *  END OF FILE: Mcu_Hw.h
 *********************************************************************************************************************/
