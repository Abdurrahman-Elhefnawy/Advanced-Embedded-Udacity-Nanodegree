#include "IntCtrl.h"
#include "Port.h"
#include "DIO.h"
#include "Gpt.h"
#include "Gpt_cfg.h"
#include "Port_cfg.h"	


#define ON_SWITCH       DIO_PF0
#define OFF_SWITCH 			DIO_PF4
#define SETTING_SWITCH  DIO_PF1
#define LED 						DIO_PF2

void GetInput(void);
void timer1A_init(void);
void timer2A_init(void);
static uint8  On_Interval = 1 ;
static uint8  OFF_Interval = 1 ;
static uint32 fs =64000;   							  /*the selected timer frequency = 64000 (prescaler = 250) */
static uint32 TimerTargetTicks =0x02111111;     /*Total number of ticks in for OFF timer*/

//0x0AAAFFFF
int main()
{	
	IntCrtl_Init();
	Port_Init();
	Gpt_Init();

	DIO_WriteChannel(LED,HIGH);

//	TimerTargetTicks = OFF_Interval * fs;   /*ticks = Interval / Time for single tick = Interval * fs */
	Gpt_StartTimer(Gpt_TIMER_0 , TimerTargetTicks);

	while(1){
	//GetInput();
}
}


void GetInput(void){
		if(!DIO_ReadChannel(ON_SWITCH) && !DIO_ReadChannel(SETTING_SWITCH) ){
		On_Interval++ ;
		while (!DIO_ReadChannel(ON_SWITCH));  /*to prevent counting more than one time each press on ON_SWITCH*/
	}	
	
	if(!DIO_ReadChannel(OFF_SWITCH) && !DIO_ReadChannel(SETTING_SWITCH) ){
		OFF_Interval ++ ;
		while (!DIO_ReadChannel(OFF_SWITCH));  /*to prevent counting more than one time each press on OFF_SWITCH*/
	}
}


void TIMER0A_Handler(void)
{  

	static uint8 state = 0;
	DIO_WriteChannel(LED,state);
	state = !state;
		
	//OnTimerTargetTicks = On_Interval * fs;
	Gpt_StartTimer(Gpt_TIMER_0 , TimerTargetTicks);
	
	
 Gpt_ClearInterruptFlag(Gpt_TIMER_0);
}
