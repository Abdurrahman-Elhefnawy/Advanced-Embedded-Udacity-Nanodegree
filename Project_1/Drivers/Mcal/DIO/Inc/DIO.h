/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  DIO.h
 *       Module:  DIO
 *
 *  Description:  header file for DIO Module    
 *  
 *********************************************************************************************************************/
#ifndef DIO_H
#define DIO_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "DIO_Types.h"
#include "Bit_Math.h"
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
 
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
DIO_LevelType DIO_ReadChannel(DIO_ChannelType channel_id);

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
void DIO_WriteChannel(DIO_ChannelType channel_id,DIO_LevelType channel_level);

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
DIO_PortLevelType DIO_ReadPort(DIO_PortType port_id);


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
void DIO_WritePort(DIO_PortType port_id,DIO_PortLevelType port_level);

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
void DIO_FlipChannel(DIO_ChannelType channel_id);


#endif  /* DIO_H */

/**********************************************************************************************************************
 *  END OF FILE: DIO.h
 *********************************************************************************************************************/
