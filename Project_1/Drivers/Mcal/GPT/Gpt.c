/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Gpt.c
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
#include "Gpt.h"
#include "Mcu_Hw.h"

#define NUMBER_OF_CONFIGURED_CHANNELS 2
Gpt_ConfigType Gpt_ChannelConfigSet[NUMBER_OF_CONFIGURED_CHANNELS] ={
    {Gpt_TIMER_0, Gpt_CONTINUOUS_MODE , 64000 , 60000},
		{Gpt_TIMER_2, Gpt_CONTINUOUS_MODE , 64000 , 60000}
};
/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static uint32 ChannelBaseAddresses[12] = {
    0x40030000,
    0x40031000,
    0x40032000,
    0x40033000,
    0x40034000,
    0x40035000,
    0x40036000,
    0x40037000,
    0x4004C000,
    0x4004D000,
    0x4004E000,
    0x4004F000,
};

static Gpt_ValueType targetTime;


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
void Gpt_Init ()
{

    Gpt_ChannelType channelId ;
    Gpt_ModeType channelMode;
    uint32 channelTickFreq;
    uint32 channelTickMaxValue ;
    uint16 prescaler = 0 ;

    for( uint8 channelIdx = 0; channelIdx < NUMBER_OF_CONFIGURED_CHANNELS;channelIdx++){
 
    	  channelId             =Gpt_ChannelConfigSet[channelIdx].Channel_Id;
        channelMode           =Gpt_ChannelConfigSet[channelIdx].Channel_Mode;
        channelTickFreq       =Gpt_ChannelConfigSet[channelIdx].Channel_TickFrequency;
        channelTickMaxValue   =Gpt_ChannelConfigSet[channelIdx].Channel_TickMaxValue;
        
        
      
        if(channelId< 6 )
            SET_BIT(RCGCTIMER , channelId);
        else
            SET_BIT(RCGCWTIMER , channelId - 6 );    
       
				/*Clear TnEN bit before configuration*/
        CLR_BIT(GPTMCTL(ChannelBaseAddresses[channelId]) , 0); 
              
				/*Select 0x1 for one-shot or 0x2 for Periodic Mode */
        // SET_BIT(GPTMTAMR(ChannelBaseAddresses[channelId]) , channelMode);  
				GPTMTAMR(ChannelBaseAddresses[channelId]) = 0x02;
				/*Clear TACDIR to count down */
        CLR_BIT(GPTMTAMR(ChannelBaseAddresses[channelId]) , 4);  
        
        /*Set TAMIE to enable Interrupt */
        SET_BIT(GPTMIMR(ChannelBaseAddresses[channelId]) , 0);
        // SET_BIT(GPTMTAMR(ChannelBaseAddresses[channelId]) , 5);
        
        
        //  prescaler = SYSYEM_CLK / channelTickFreq;

        // if(channelId< 6 )
        //     SET_BIT(RCGCTIMER , channelId);
        // else
        //     SET_BIT(RCGCWTIMER , channelId - 6 );    
       
				// /*Clear TnEN bit before configuration*/
        // CLR_BIT(GPTMCTL(ChannelBaseAddresses[channelId]) , 0); 
        
				// /*Set Prescaler*/
        // GPTMTAPR(ChannelBaseAddresses[channelId]) = prescaler;  
				
				// /*GPTMCFG = 0X0000 0004 to work in 16 and 32 bit modes */
        // SET_BIT(GPTMCFG(ChannelBaseAddresses[channelId]) , 2);  
       
				// /*Select 0x1 for one-shot or 0x2 for Periodic Mode */
        // SET_BIT(GPTMTAMR(ChannelBaseAddresses[channelId]) , channelMode);  
				
				// /*Clear TACDIR to count down */
        // CLR_BIT(GPTMTAMR(ChannelBaseAddresses[channelId]) , 4);  
        
        // /*Set TAMIE to enable Interrupt */
        // SET_BIT(GPTMTAMR(ChannelBaseAddresses[channelId]) , 5);

       }


}

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
void Gpt_StartTimer(Gpt_ChannelType Channel , Gpt_ValueType Value){
    /*Load Values*/
    GPTMTAILR(ChannelBaseAddresses[Channel]) = Value;
    GPTMICR(ChannelBaseAddresses[Channel]) = 0;
     // GPTMTAILR(ChannelBaseAddresses[Channel])  = 300; 
    // *((volatile uint32*)(0x40031028)) = 50000; 
    SET_BIT(GPTMCTL(ChannelBaseAddresses[Channel]) , 0); /*Set TnEN bit to start timer*/
    targetTime = Value;

}

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
void Gpt_StopTimer(Gpt_ChannelType Channel){
    CLR_BIT(GPTMCTL(ChannelBaseAddresses[Channel]) , 0); /*Clear TnEN bit to stop timer*/
}



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
void Gpt_DisableNotification(Gpt_ChannelType Channel){
    CLR_BIT(GPTMTAMR(ChannelBaseAddresses[Channel]) , 5);  /*Clear TAMIE to disable Interrupt */

}


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
void Gpt_EnableNotification(Gpt_ChannelType Channel){
    SET_BIT(GPTMTAMR(ChannelBaseAddresses[Channel]) , 5);  /*Set TAMIE to enable Interrupt */

}

/******************************************************************************
* \Syntax          : Gpt_ValueType Gpt_GetTimeElapsed ( Gpt_ChannelType Channel )                                      
* \Description     : Gets the Elapsed time of a specific channel                                                                        
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : Channel: timer channel
* \Parameters (out): None                                                      
* \Return value:   : Time Elapsed
*******************************************************************************/
Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType Channel){
    
    return GPTMTAV(ChannelBaseAddresses[Channel]);
}
/******************************************************************************
* \Syntax          : Gpt_ValueType Gpt_GetTimeElapsed ( Gpt_ChannelType Channel )                                      
* \Description     : Gets the Elapsed time of a specific channel                                                                        
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : Channel: timer channel
* \Parameters (out): None                                                      
* \Return value:   : Time Elapsed
*******************************************************************************/

Gpt_ValueType Gpt_GetTimeRemaining(Gpt_ChannelType Channel){

    return targetTime-GPTMTAV(ChannelBaseAddresses[Channel]);
}

void Gpt_ClearInterruptFlag(Gpt_ChannelType Channel){
    GPTMICR(ChannelBaseAddresses[Channel]) = 0x01;
}


/**********************************************************************************************************************
 *  END OF FILE: Gpt.c
 *********************************************************************************************************************/
