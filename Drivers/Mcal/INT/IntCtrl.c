/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  IntCrtl.c
 *        \brief  Nested Vector Interrupt Controller Driver
 *
 *      \details  The Driver Configure All MCU interrupts Priority into gorups and subgroups
 *                Enable NVIC Interrupt Gate for Peripherals
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "..\Inc\IntCtrl.h"
#include "Mcu_Hw.h"

void EnableGlobalInterrupt(void)
{

    /* Trigger exception to go to handler mode in order to go to privilege mode */
    __asm("svc #0");
    __asm("CPSIE i");
    __asm("CPSIE f");

    /* go to user mode */
    __asm("MOV R0, #0x1");
    __asm("MSR control, R0");
}

/******************************************************************************
* \Syntax          : void IntCrtl_Init(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void IntCrtl_Init(void)
{
    /* Trigger exception to go to privilege mode */
   // __asm("svc #0");
	//EnableGlobalInterrupt();
	/*TODO Configure Grouping\SubGrouping System in APINT register in SCB*/
    #if (PRIORITY_GROUPING == 1) 
        APINT = 0x05FA0400;         //xxx
        #define CALCULATE_PRIORITY(group,subgroup)   (group)
    #elif (PRIORITY_GROUPING == 2) 
        APINT = 0x05FA0500;         //xxy
        #define CALCULATE_PRIORITY(group,subgroup)   (group<<1)|(subgroup)
    #elif (PRIORITY_GROUPING == 3) 
        APINT = 0x05FA0600;         //xyy     
        #define CALCULATE_PRIORITY(group,subgroup)   (group<<2)|(subgroup)
    #elif (PRIORITY_GROUPING == 4) 
        APINT = 0x05FA0700;         //yyy
        #define CALCULATE_PRIORITY(group,subgroup)   (subgroup)
    #endif 
    IntCtrl_InterruptType interrutpIdx;
    for( interrutpIdx = 0; interrutpIdx < NUMBER_OF_ACTIVE_INTERRUPTS;interrutpIdx++){
        /*Group\Subgroup priority in NVIC_PRIx Nvic and SCB_SYSPRIx Registers*/  
    	IntCtrl_InterruptType interrutpNumber = Active_Interrupts[interrutpIdx].intNumber;
        uint8 interrutpGroup = Active_Interrupts[interrutpIdx].intGroup;
        uint8 interrutpSubGroup = Active_Interrupts[interrutpIdx].intSubGroup;

        uint8 interrutpPriority = CALCULATE_PRIORITY(interrutpGroup,interrutpSubGroup);


        uint8 interrutpBitPRIx   = 7+(interrutpNumber % 4) ;
        uint8 interrutpRegisterOffsetPRIx = interrutpNumber / 4 ;
        // SET_PRIORITY_IN_PRIx(  interrutpRegisterOffsetPRIx, interrutpBitPRIx,interrutpPriority); 
      
        
        /* Enable\Disable based on user configurations in NVIC_ENx and SCB_Sys Registers */
        uint8 interrutpBitENx   = interrutpNumber % 32 ;
        uint8 interrutpRegisterOffsetENx = interrutpNumber / 32 ;
        //SET_BIT_IN_ENx(  4*interrutpRegisterOffsetENx, interrutpBitENx); 
        SET_BIT(ENx( 4*interrutpRegisterOffsetENx) , interrutpBitENx );
        SET_BITS_VALUE(PRIx( 4*interrutpRegisterOffsetPRIx) , interrutpBitPRIx, interrutpPriority);
    }   
		uint8 exceptionIdx;
    for( exceptionIdx = 0; exceptionIdx < NUMBER_OF_ACTIVE_SYSEXCEPTIONS;exceptionIdx++){
        /*Assign Group\Subgroup priority in NVIC_PRIx Nvic and SCB_SYSPRIx Registers*/  
    	IntCtrl_ExceptionType exceptionNumber = Active_Exceptions[exceptionIdx].excNumber;
        uint8 exceptionpGroup = Active_Exceptions[exceptionIdx].excGroup;
        uint8 exceptionSubGroup = Active_Exceptions[exceptionIdx].excSubGroup;

        uint8 exceptionPriority = CALCULATE_PRIORITY(exceptionpGroup,exceptionSubGroup);

        switch (exceptionNumber)
        {
        case INTCTRL_MEM_MNGMNT_FAULT:
            SYSPRI1.BITS.MEM = exceptionPriority; 
            break;
        case INTCTRL_BUS_FAULT:
            SYSPRI1.BITS.BUS = exceptionPriority; 
            break;
        case INTCTRL_USAGE_FAULT:
            SYSPRI1.BITS.USAGE = exceptionPriority; 
            break;
        case INTCTRL_SVC:
            SYSPRI2.BITS.SVC = exceptionPriority; 
            break;
        case INTCTRL_DEBUG_MNTR:
            SYSPRI3.BITS.DEBUG = exceptionPriority; 
            break;
        case INTCTRL_PENDSV:
            SYSPRI3.BITS.PENDSV = exceptionPriority;
            break;
        case INTCTRL_SYS_TICK:
            SYSPRI3.BITS.TICK = exceptionPriority;
            break;
        //default:
            //break;
        }


             
        
        /* Enable\Disable based on user configurations in SCB_Sys Registers */
        
        switch (exceptionNumber)
        {
        case INTCTRL_MEM_MNGMNT_FAULT:
            SYSHNDCTRL.BITS.MEM =1; 
            break;
        case INTCTRL_BUS_FAULT:
            SYSHNDCTRL.BITS.BUS =1; 
            break;
        case INTCTRL_USAGE_FAULT:
            SYSHNDCTRL.BITS.USAGE =1;
            break;
        default:
            break;
        }
     
    }   


	

}


/**********************************************************************************************************************
 *  END OF FILE: IntCrtl.c
 *********************************************************************************************************************/
