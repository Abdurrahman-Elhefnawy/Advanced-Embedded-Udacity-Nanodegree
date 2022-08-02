/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  GPT.h
 *       Module:  GPT
 *
 *  Description:  header file for General Purpose Timer Module    
 *  
 *********************************************************************************************************************/
#ifndef GPT_H
#define GPT_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Gpt_Types.h"
#include "Bit_Math.h"
#include "Gpt_cfg.h"
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : void Gpt_Init ( const Gpt_ConfigType* ConfigPtr )                                      
* \Description     : initialize General Purpose Timers Module by parsing the Configuration 
*                    into System registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : ConfigPtr: user configuration                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/

void Gpt_Init (Gpt_ConfigType* Gpt_channelConfigSet );		

/******************************************************************************
* \Syntax          :  void Gpt_DisableNotification ( Gpt_ChannelType Channel )                                      
* \Description     : Disable Timers Notification                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Channel: timer channel                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/ 
void Gpt_DisableNotification(Gpt_ChannelType Channel);

/******************************************************************************
* \Syntax          :  void Gpt_EnableNotification ( Gpt_ChannelType Channel )                                      
* \Description     : Enable Timers Notification                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Channel: timer channel                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Gpt_EnableNotification(Gpt_ChannelType Channel);

/******************************************************************************
* \Syntax          : void Gpt_StartTimer ( Gpt_ChannelType Channel, Gpt_ValueType Value )                                      
* \Description     : Starts selected timer cahnnel with defined target time                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : Channel: timer channel                     
* \Parameters (in) : Value: target counter value                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Gpt_StartTimer(Gpt_ChannelType Channel , Gpt_ValueType Value);

/******************************************************************************
* \Syntax          : void Gpt_StopTimer ( Gpt_ChannelType Channel )                                      
* \Description     : Stops selected timer cahnnel             
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : Channel: timer channel                                          
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Gpt_StopTimer(Gpt_ChannelType Channel);

/******************************************************************************
* \Syntax          : Gpt_ValueType Gpt_GetTimeElapsed ( Gpt_ChannelType Channel )                                      
* \Description     : Gets the Elapsed time of a specific channel                                                                        
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : Channel: timer channel
* \Parameters (out): None                                                      
* \Return value:   : Time Elapsed
*******************************************************************************/
Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType Channel);
/******************************************************************************
* \Syntax          : Gpt_ValueType Gpt_GetTimeElapsed ( Gpt_ChannelType Channel )                                      
* \Description     : Gets the Elapsed time of a specific channel                                                                        
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : Channel: timer channel
* \Parameters (out): None                                                      
* \Return value:   : Time Elapsed
*******************************************************************************/
Gpt_ValueType Gpt_GetTimeRemaining(Gpt_ChannelType Channel);



#endif  /* GPT_H */

/**********************************************************************************************************************
 *  END OF FILE: GPT.h
 *********************************************************************************************************************/
