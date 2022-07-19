/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  DIO.c
 *        \brief  DIO Driver
 *
 *      \details  The Driver implements basic DIO functions to read/write from any DIO pin or port
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "DIO.h"
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

DIO_LevelType DIO_ReadChannel(DIO_ChannelType channel_id){
    DIO_PortType portNumber =   channel_id / 8;
    DIO_ChannelType pinNumber = channel_id % 8;
    DIO_LevelType pinLevel;

    /***set pin as input***/
    CLR_BIT(GET_GPIODIRx_ADDRESS(PortsBaseAddresses[portNumber]) ,pinNumber);
    pinLevel = (DIO_LevelType)BIT_IS_SET(GET_GPIODATAx_ADDRESS(PortsBaseAddresses[portNumber]) , pinNumber); 

    return pinLevel;
}

void DIO_WriteChannel(DIO_ChannelType channel_id,DIO_LevelType channel_level){
    DIO_PortType portNumber =   channel_id / 8;
    DIO_ChannelType pinNumber = channel_id % 8;

    /***set pin as output***/
    SET_BIT(GET_GPIODIRx_ADDRESS(PortsBaseAddresses[portNumber]) ,pinNumber);
    if (channel_level) 
        SET_BIT(GET_GPIODATAx_ADDRESS(PortsBaseAddresses[portNumber]) , pinNumber); 
    else 
        CLR_BIT(GET_GPIODATAx_ADDRESS(PortsBaseAddresses[portNumber]) , pinNumber);   
}

DIO_PortLevelType DIO_ReadPort(DIO_PortType port_id){
    DIO_PortLevelType portLevel;
    portLevel = GET_GPIODIRx_ADDRESS(PortsBaseAddresses[port_id]);
    return portLevel; 
}

void DIO_WritePort(DIO_PortType port_id,DIO_PortLevelType port_level){
    SET_PORT_VALUE(GET_GPIODIRx_ADDRESS(PortsBaseAddresses[port_id]),port_level);
}

void DIO_FlipChannel(DIO_ChannelType channel_id){
    DIO_PortType portNumber =   channel_id / 8;
    DIO_ChannelType pinNumber = channel_id % 8;
    DIO_LevelType pinLevel;

    /***set pin as input***/
    CLR_BIT(GET_GPIODIRx_ADDRESS(PortsBaseAddresses[portNumber]) ,pinNumber);
    pinLevel = BIT_IS_SET(GET_GPIODATAx_ADDRESS(PortsBaseAddresses[portNumber]) , pinNumber); 
    if (!pinLevel) 
        SET_BIT(GET_GPIODATAx_ADDRESS(PortsBaseAddresses[portNumber]) , pinNumber); 
    else 
        CLR_BIT(GET_GPIODATAx_ADDRESS(PortsBaseAddresses[portNumber]) , pinNumber);   
}


/**********************************************************************************************************************
 *  END OF FILE: DIO.c
 *********************************************************************************************************************/
