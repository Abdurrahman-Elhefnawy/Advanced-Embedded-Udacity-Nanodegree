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
uint32 PortBaseAddresses[6] = {
    0x40004000,
    0x40005000,
    0x40006000,
    0x40007000,
    0x40024000,
    0x40025000,
};

/******************************************************************************
* \Syntax          : DIO_LevelType DIO_ReadChannel(channel_id)                                      
* \Description     : Read Level from a specific Pin                          
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Channel Id                     
* \Parameters (out): None                                                      
* \Return value:   : Channel Level
*******************************************************************************/
DIO_LevelType DIO_ReadChannel(DIO_ChannelType channel_id){
    DIO_PortType portNumber =   channel_id / 8;
    DIO_ChannelType pinNumber = channel_id % 8;
    DIO_LevelType pinLevel;

    /*handle the case that Port E has only 6 pins and Port F has 5 pins*/
    if(channel_id>31){
        portNumber = DIO_PORTE;
        pinNumber = channel_id - 32; 
    }
    if(channel_id>37){
        portNumber = DIO_PORTF;
        pinNumber = channel_id - 38; 
    }

    /***set pin as input***/
    CLR_BIT(GET_GPIODIRx_ADDRESS(PortBaseAddresses[portNumber]) ,pinNumber);
    pinLevel = (DIO_LevelType)BIT_IS_SET(GET_GPIODATAx_ADDRESS(PortBaseAddresses[portNumber]) , pinNumber); 

    return pinLevel;
}


/******************************************************************************
* \Syntax          : void DIO_WriteChannel(DIO_ChannelType channel_id,DIO_LevelType channel_level)                                      
* \Description     : Writes a level to a specific Pin                          
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Channel Id  , Channel Level                  
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void DIO_WriteChannel(DIO_ChannelType channel_id,DIO_LevelType channel_level){
    DIO_PortType portNumber =   channel_id / 8;
    DIO_ChannelType pinNumber = channel_id % 8;
    /*handle the case that Port E has only 6 pins and Port F has 5 pins*/
    if(channel_id>31){
        portNumber = DIO_PORTE;
        pinNumber = channel_id - 32; 
    }
    if(channel_id>37){
        portNumber = DIO_PORTF;
        pinNumber = channel_id - 38; 
    }


    /***set pin as output***/
    SET_BIT(GET_GPIODIRx_ADDRESS(PortBaseAddresses[portNumber]) ,pinNumber);
    if (channel_level) 
        SET_BIT(GET_GPIODATAx_ADDRESS(PortBaseAddresses[portNumber]) , pinNumber); 
    else 
        CLR_BIT(GET_GPIODATAx_ADDRESS(PortBaseAddresses[portNumber]) , pinNumber);   
}


/******************************************************************************
* \Syntax          : DIO_PortLevelType DIO_ReadPort(DIO_PortType port_id)                                      
* \Description     : Reads Level from a specific Port                          
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Port Id                    
* \Parameters (out): None                                                      
* \Return value:   : Port Level
*******************************************************************************/
DIO_PortLevelType DIO_ReadPort(DIO_PortType port_id){
    DIO_PortLevelType portLevel;
    portLevel = GET_GPIODIRx_ADDRESS(PortBaseAddresses[port_id]);
    return (DIO_PortLevelType)portLevel; 
}

/******************************************************************************
* \Syntax          : void DIO_WritePort(DIO_PortType port_id,DIO_PortLevelType port_level)                                      
* \Description     : Writes a level to a specific Port                          
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Port Id  , Port Level                  
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void DIO_WritePort(DIO_PortType port_id,DIO_PortLevelType port_level){
    SET_PORT_VALUE(GET_GPIODIRx_ADDRESS(PortBaseAddresses[port_id]),port_level);
}

/******************************************************************************
* \Syntax          : void DIO_FlipChannel(DIO_ChannelType channel_id)                                      
* \Description     : Flips the level of a specific Pin                          
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Channel Id                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void DIO_FlipChannel(DIO_ChannelType channel_id){
    DIO_PortType portNumber =   channel_id / 8;
    DIO_ChannelType pinNumber = channel_id % 8;
    DIO_LevelType pinLevel;

    /***set pin as input***/
    CLR_BIT(GET_GPIODIRx_ADDRESS(PortBaseAddresses[portNumber]) ,pinNumber);
    pinLevel = BIT_IS_SET(GET_GPIODATAx_ADDRESS(PortBaseAddresses[portNumber]) , pinNumber); 
    if (!pinLevel) 
        SET_BIT(GET_GPIODATAx_ADDRESS(PortBaseAddresses[portNumber]) , pinNumber); 
    else 
        CLR_BIT(GET_GPIODATAx_ADDRESS(PortBaseAddresses[portNumber]) , pinNumber);   
}


/**********************************************************************************************************************
 *  END OF FILE: DIO.c
 *********************************************************************************************************************/
