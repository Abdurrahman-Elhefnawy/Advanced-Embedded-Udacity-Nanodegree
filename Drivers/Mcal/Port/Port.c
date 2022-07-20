/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Port.c
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
#include "Port.h"
#include "Mcu_Hw.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/	

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
uint32 PortsBaseAddresses[6] = {
    0x40004000,
    0x40005000,
    0x40006000,
    0x40007000,
    0x40024000,
    0x40025000,
};
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


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
void Port_Init(Port_ConfigType* portArrayOfConfigs){
    Port_PinType pinId ;
    Port_PinModeType pinMode;
    Port_PinDirectionType pinDirection;
    Port_PinInternalAttachType pinInternalAttach ;
    Port_PinType pinCurrent ;
     

    for( Port_PinType pinIdx; pinIdx < NUMBER_OF_CONFIGURED_PINS;pinIdx++){
        /*Assign Group\Subgroup priority in NVIC_PRIx Nvic and SCB_SYSPRIx Registers*/  
    	pinId          =Configured_Pins[pinIdx].pinId;
        pinMode            =Configured_Pins[pinIdx].pinMode;
        pinDirection       =Configured_Pins[pinIdx].pinDirection;
        pinInternalAttach  =Configured_Pins[pinIdx].pinInternalAttach;
        pinCurrent         =Configured_Pins[pinIdx].pinCurrent; 

        uint8 portNumber =   pinId / 8;
        uint8 pinNumber = pinId % 8;

        /**************SET DIRECTION*************/
        if(pinDirection == INPUT)
            CLR_BIT(GET_GPIODIRx_ADDRESS(PortsBaseAddresses[portNumber]) ,pinNumber);
        else if(pinDirection == OUTPUT)
            SET_BIT(GET_GPIODIRx_ADDRESS(PortsBaseAddresses[portNumber]) ,pinNumber);
        
        

        /**************SELECT MODE*************/

        //Unlock GPIOLOCK to commit in GPIOCR  
      //  GPIOLOCKx(PortsBaseAddresses[portNumber]) = (0x4C4F44B) ;
        //Commit bit in GPIOCR  
        SET_BIT(GPIOCRx(PortsBaseAddresses[portNumber]) ,pinNumber);
        
        
        if(pinMode == GPIO_MODE)
            CLR_BIT(GPIOAFSELx((PortsBaseAddresses[portNumber]) ,pinNumber));
        else {
            /*SET corresponding bit in GPIOAFSEL to switch to alternative function*/
            SET_BIT(GPIOAFSELx(PortsBaseAddresses[portNumber]) ,pinNumber);
            /*SET alternative function in GPIOPCTL*/
            SET_BITS_VALUE(GPIOPCTLx(PortsBaseAddresses[portNumber]) ,pinNumber,pinMode);  
        }


        /**************SELECT INTERNAL ATTACH*************/
        switch (pinInternalAttach)
        {
        case OPEN_DRAIN:
            SET_BIT(GPIOODRx(PortsBaseAddresses[portNumber]) ,pinNumber);
            break;
        
        case PULL_UP:
            SET_BIT(GPIOPURx(PortsBaseAddresses[portNumber]) ,pinNumber);
            break;
        
        case PULL_DOWN:
            SET_BIT(GPIOPURx(PortsBaseAddresses[portNumber]) ,pinNumber);
            break;
        default:
            break;
        } 

        
        /**************SELECT CURRENT VALUE *************/
        switch (pinCurrent)
        {
        case mA_2:
            SET_BIT(GPIODR2Rx(PortsBaseAddresses[portNumber]) ,pinNumber);
            break;
        
        case mA_4:
            SET_BIT(GPIODR4Rx(PortsBaseAddresses[portNumber]) ,pinNumber);
            break;
        
        case mA_8:
            SET_BIT(GPIODR8Rx(PortsBaseAddresses[portNumber]) ,pinNumber);
            break;
        default:
            break;
        } 
    }   

}
/**********************************************************************************************************************
 *  END OF FILE: Port.c
 ********************   *************************************************************************************************/
