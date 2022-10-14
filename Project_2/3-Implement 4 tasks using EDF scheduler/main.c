/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "lpc21xx.h"
#include "queue.h"

/* Peripheral includes. */
#include "serial.h"
#include "GPIO.h"


/*-----------------------------------------------------------*/

/* Constants to setup I/O and processor. */
#define mainBUS_CLK_FULL	( ( unsigned char ) 0x01 )

/* Constants for the ComTest demo application tasks. */
#define mainCOM_TEST_BAUD_RATE	( ( unsigned long ) 115200 )


/*
 * Configure the processor for use with the Keil demo board.  This is very
 * minimal as most of the setup is managed by the settings in the project
 * file.
 */
static void prvSetupHardware( void );
/*-----------------------------------------------------------*/

/*Task Handlers*/
TaskHandle_t Handler_Button_1_Monitor= NULL;
TaskHandle_t Handler_Button_2_Monitor= NULL;
TaskHandle_t Handler_Uart_Receiver= NULL;
TaskHandle_t Handler_Periodic_Transmitter= NULL;
TaskHandle_t Handler_Load_1_Simulation= NULL;
TaskHandle_t Handler_Load_2_Simulation= NULL;

/*Queue Handlers*/
QueueHandle_t xQueue1 = NULL;
/*Task Prototypes*/ 
void Button_1_Monitor(void * pvparameters);
void Button_2_Monitor(void * pvparameters);
void Periodic_Transmitter(void * pvparameters);
void temp_task(void * pvparameters);
void Uart_Receiver(void * pvparameters);
void Load_1_Simulation(void * pvparameters);
void Load_2_Simulation(void * pvparameters);

/*
 * Application entry point:
 * Starts all the other tasks, then starts the scheduler. 
 */
int main( void )
    	{
	/* Setup the hardware for use with the Keil demo board. */
	prvSetupHardware();

	/* Create The Queue For Inrer-process Communication*/
	xQueue1 = xQueueCreate( 10, sizeof(char));
	
	
    /* Create Tasks here */
	xTaskPeriodicCreate(Button_1_Monitor,
							"Button_1_Monitor",	
							100,
							(void * ) 0,
							1,
							&Handler_Button_1_Monitor,
							50);
		
	// 	/* Create Tasks here */
	xTaskPeriodicCreate(Button_2_Monitor,
							"Button_2_Monitor",	
							100,
							(void * ) 0,
							1,
							&Handler_Button_2_Monitor,
							50);

	xTaskPeriodicCreate(Periodic_Transmitter,
							"Periodic_Transmitter",	
							100,
							(void * ) 0,
							1,
							&Handler_Periodic_Transmitter,
							100);
		
	xTaskPeriodicCreate(Uart_Receiver,
							"Uart_Receiver",	
							100,
							(void * ) 0,
							1,
							&Handler_Uart_Receiver,
							20);



	xTaskPeriodicCreate(Load_1_Simulation,
							"Load_1_Simulation",	
							100,
							(void * ) 0,
							1,
							&Handler_Load_1_Simulation,
							10);

	xTaskPeriodicCreate(Load_2_Simulation,
							"Load_2_Simulation",	
							100,
							(void * ) 0,
							1,
							&Handler_Load_2_Simulation,
							50);


		
	/* Now all the tasks have been started - start the scheduler.

	NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
	The processor MUST be in supervisor mode when vTaskStartScheduler is 
	called.  The demo applications included in the FreeRTOS.org download switch
	to supervisor mode prior to main being called.  If you are not using one of
	these demo application projects then ensure Supervisor mode is used here. */
	vTaskStartScheduler();

	/* Should never reach here!  If you do then there was not enough heap
	available for the idle task to be created. */
	for( ;; );
}
/*-----------------------------------------------------------*/

/* Function to reset timer 1 */
void timer1Reset(void)
{
	T1TCR |= 0x2;
	T1TCR &= ~0x2;
}

/* Function to initialize and start timer 1 */
static void configTimer1(void)
{
	T1PR = 1000;
	T1TCR |= 0x1;
}

static void prvSetupHardware( void )
{
	/* Perform the hardware setup required.  This is minimal as most of the
	setup is managed by the settings in the project file. */

	/* Configure UART */
	xSerialPortInitMinimal(mainCOM_TEST_BAUD_RATE);

	/* Configure GPIO */
	GPIO_init();
	
	/* Config trace timer 1 and read T1TC to get current tick */
	configTimer1();

	/* Setup the peripheral bus to be the same as the PLL output. */
	VPBDIV = mainBUS_CLK_FULL;
}
/*-----------------------------------------------------------*/

void vApplicationTickHook(void){
//	
//	GPIO_write(PORT_0,PIN3,PIN_IS_HIGH);
//		
//	GPIO_write(PORT_0,PIN3,PIN_IS_LOW);

}	



void vApplicationIdleHook(void){

}	

void Button_1_Monitor(void * pvparameters){
	int lastWakeTime = xTaskGetTickCount();
	int i=0;
	
	char pin_state,last_state;
	char falling_msg = 'f';
	char rising_msg =  'r';
	char B1 =  '1';
	char B1_falling[6] = "B_1:F\n";
	char B1_rising[6] = "B_1:R\n";
	
	
	vTaskSetApplicationTaskTag(Handler_Button_1_Monitor,(void*) 1);
	
	for( ;; ){
		pin_state =GPIO_read(PORT_0, PIN7);
		if(pin_state !=last_state ){
			if(pin_state == 1){			//Rising Edge
				int temp = xQueueOverwrite(xQueue1, &rising_msg);
//				for(i = 0 ; i<6 ; i++){
//					int temp = xQueueSend(xQueue1, &B1_rising[i], portMAX_DELAY);
//					
//				}
				
			}
			else if(pin_state == 0){ //Falling Edge 
				int temp = xQueueOverwrite(xQueue1, &falling_msg);
				// for(i = 0 ; i<6 ; i++){
				// 	int temp = xQueueSend(xQueue1, &B1_falling[i], portMAX_DELAY);
				// }
				
			}
		
		}
		last_state = pin_state;
		vTaskDelayUntil(&lastWakeTime , 50);
	}
	
}




void Button_2_Monitor(void * pvparameters){
	int lastWakeTime = xTaskGetTickCount();
	int i=0,j=0;
	
	char pin_state,last_state;

	char B2_falling[11] = "B_2:F\n";
	char B2_rising[11] = "B_2:R\n";
	
	char falling_msg = 'F';
	char rising_msg =  'R';
	
	vTaskSetApplicationTaskTag(Handler_Button_2_Monitor,(void*) 2);
	
	for( ;; ){
		//for(j = 0 ;j<100;j++){
		pin_state =GPIO_read(PORT_0, PIN8);
		if(pin_state !=last_state ){
			if(pin_state == 1){			//Rising Edge
				int temp = xQueueOverwrite(xQueue1, &rising_msg);
				// for(i = 0 ; i<6 ; i++){
				// 		//int temp = xQueueSend(xQueue1, &B2_rising[i], portMAX_DELAY);
				// 		int temp = xQueueOverwrite(xQueue1, &B2_rising[i]);
				// }
				
			}
			else if(pin_state == 0){ //Falling Edge 
				int temp = xQueueOverwrite(xQueue1, &falling_msg);
				// for(i = 0 ; i<6 ; i++){
				// 	int temp = xQueueOverwrite(xQueue1, &B2_falling[i]);
				// }
				
			}
		
		}
		last_state = pin_state;
	//}
		vTaskDelayUntil(&lastWakeTime , 50);
	}
	
}
void Periodic_Transmitter(void * pvparameters){
	int lastWakeTime = xTaskGetTickCount();
	int i=0;
	char periodic_msg[6] = "task3\n";
	char t3_msg = '3';
	
	vTaskSetApplicationTaskTag(Handler_Periodic_Transmitter,(void*) 3);
	
	for( ;; ){
				// for(i = 0 ; i<6 ; i++){
				int temp = xQueueOverwrite(xQueue1, &t3_msg);
				// }
			
		
		vTaskDelayUntil(&lastWakeTime , 100);
	}
	
}

void Uart_Receiver(void * pvparameters){
	int lastWakeTime = xTaskGetTickCount();
	int i=0,j=0;
	char received=0,received2=0;
	char received_arr[6];
	
	
	vTaskSetApplicationTaskTag(Handler_Uart_Receiver,(void*) 4);
	
	for( ;; ){

		for(i = 0 ; i < 10 ; i++)
			i = i ;
		if (xQueueReceive(xQueue1, &received, portMAX_DELAY) == pdTRUE){
			if(received == 'f')
					vSerialPutString("\nB1:Falling\n",13);
			else if(received == 'r')
					vSerialPutString("\nB1:Rising\n",12);		
			
			if(received == 'F')
					vSerialPutString("\nB2:Falling\n",13);
			else if(received == 'R')
					vSerialPutString("\nB2:Rising\n",12);		
			if(received == '3')
				vSerialPutString("Task:3 ",7);
			
			
			
			
		}

		vTaskDelayUntil(&lastWakeTime , 20);
		
	}
	
}


void Load_1_Simulation(void * pvparameters){
	int lastWakeTime = xTaskGetTickCount();
	int i=0,j=0;
		
	vTaskSetApplicationTaskTag(Handler_Load_1_Simulation,(void*) 5);
	
	for( ;; ){
		for(i = 0 ; i<33500;i++){
			i = i;
		}
		vTaskDelayUntil(&lastWakeTime ,10);
	}
	
}

void Load_2_Simulation(void * pvparameters){
	int lastWakeTime = xTaskGetTickCount();
	int i=0,j=0;
		
	vTaskSetApplicationTaskTag(Handler_Load_2_Simulation,(void*) 6);
	
	for( ;; ){
		for(i = 0 ; i<80100;i++){
			i = i;
		}
		vTaskDelayUntil(&lastWakeTime , 50);
	}
	
}


