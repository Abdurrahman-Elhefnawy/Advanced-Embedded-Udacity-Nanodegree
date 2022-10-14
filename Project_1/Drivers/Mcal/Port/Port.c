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
#include "Port.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/	
#define NUMBER_OF_CONFIGURED_PINS 4
Port_ConfigType Configured_Pins[NUMBER_OF_CONFIGURED_PINS]={
    {Port_PF0 , GPIO_MODE,INPUT,  PULL_DOWN, mA_2, DISABLE_INTERRUPT},
    {Port_PF1 , GPIO_MODE,INPUT,  PULL_DOWN, mA_8 ,DISABLE_INTERRUPT},
    {Port_PF4 , GPIO_MODE,INPUT,  PULL_DOWN, mA_8 ,DISABLE_INTERRUPT},
    {Port_PF2 , GPIO_MODE,OUTPUT, PULL_DOWN, mA_8 ,DISABLE_INTERRUPT},
};
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
* \Syntax          : void Port_Init(void)                                      
* \Description     : initialize GPIO Module by parsing the Configuration 
*                    into of the selcted pins to GPIO registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Port_Init(){
    Port_PinType pinId ;
    Port_PinModeType pinMode;
    Port_PinDirectionType pinDirection;
    Port_PinInternalAttachType pinInternalAttach ;
    Port_PinOutputCurrentType pinCurrent ;
    Port_PinIntEnableType pinInterrupt;

    for( Port_PinType pinIdx = 0 ; pinIdx < NUMBER_OF_CONFIGURED_PINS;pinIdx++){
        /*Assign Group\Subgroup priority in NVIC_PRIx Nvic and SCB_SYSPRIx Registers*/  
		pinId              =Configured_Pins[pinIdx].pinId;
        pinMode            =Configured_Pins[pinIdx].pinMode;
        pinDirection       =Configured_Pins[pinIdx].pinDirection;
        pinInternalAttach  =Configured_Pins[pinIdx].pinInternalAttach;
        pinCurrent         =Configured_Pins[pinIdx].pinCurrent; 
        pinInterrupt       =Configured_Pins[pinIdx].pinInteruurp; 

        uint8 portNumber =   pinId / 8;
        uint8 pinNumber = pinId % 8;

        /*handle the case that Port E has only 6 pins and Port F has 5 pins*/
        if(pinId>31){
            portNumber = Port_PORTE;
            pinNumber = pinId - 32; 
        }
        if(pinId>37){
            portNumber = Port_PORTF;
            pinNumber = pinId - 38; 
        }


        SET_BIT(RCGCGPIO,portNumber);
        for(int i =0 ; i < 6 ; i++);
        
        /**************SET DIRECTION*************/
        if(pinDirection == INPUT)
            CLR_BIT(GET_GPIODIRx_ADDRESS(PortsBaseAddresses[portNumber]) ,pinNumber);
        else if(pinDirection == OUTPUT)
            SET_BIT(GET_GPIODIRx_ADDRESS(PortsBaseAddresses[portNumber]) ,pinNumber);
       
        /**************SELECT MODE*************/
        //Unlock GPIOLOCK to commit in GPIOCR  
        GPIOLOCKx(PortsBaseAddresses[portNumber]) = (0x4C4F434B) ;
        //Commit bit in GPIOCR  
        SET_BIT(GPIOCRx(PortsBaseAddresses[portNumber]) ,pinNumber);  

        if(pinMode == GPIO_MODE)
            CLR_BIT(GPIOAFSELx(PortsBaseAddresses[portNumber]),pinNumber  );
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
				if(pinMode == ANALOG_MODE)
					SET_BIT(GPIOAMSELx(PortsBaseAddresses[portNumber]) ,pinNumber);
        else
					SET_BIT(GPIODENx(PortsBaseAddresses[portNumber]) ,pinNumber);

        if (pinInterrupt == ENABLE_INTERRUPT){
            CLR_BIT(GPIOISx(PortsBaseAddresses[portNumber]) ,pinNumber); /* make bit edge sensitive */
            CLR_BIT(GPIOIBEx(PortsBaseAddresses[portNumber]) ,pinNumber); /* trigger is controlled by IEV */
            CLR_BIT(GPIOIEVx(PortsBaseAddresses[portNumber]) ,pinNumber); /* falling edge trigger */
            SET_BIT(GPIOICRx(PortsBaseAddresses[portNumber]) ,pinNumber); /* clear any prior interrupt */
            SET_BIT(GPIOIMx(PortsBaseAddresses[portNumber]) ,pinNumber); /* unmask interrupt */
        }
        
    }   

}
/**********************************************************************************************************************
 *  END OF FILE: Port.c
 ********************   *************************************************************************************************/
