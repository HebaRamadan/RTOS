/*
 * main.c
 *
 *  Created on: Aug 10, 2020
 *      Author: zas
 */
#include "../Lib/Std_Types.h"
#include "../Lib/Bit_math.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "Lcd_int.h"
#include "Dio_int.h"
#include "Interr_int.h"

u8 flag = 0;
/*Task function prototype */
void Task1_Func( void *pvParameter );

/*ISR function prototype */
void INT0_Function(void);

/*define a semaphore handle*/
xSemaphoreHandle  Task_Count_Sem;

int main(void)
{
	/* Initialize INT0 PIN */
	Dio_vidSetPinDir( DIO_u8PIN_26 , DIO_u8INPUT);
	Dio_vidSetPinVal( DIO_u8PIN_26 , DIO_u8HIGH );

	/* Initialize LCD */
	Lcd_vidInit();

	/* Initialize Interrupt */
	INT_vidInit();

	/* Initialize Interrupt CallBack Function */
	INT0_vidSetCB( INT0_Function );

	/*Create Task */
	xTaskCreate( Task1_Func , "TASK_1" , 200 , NULL , 2 , NULL);

	/*Create Counting semaphore with initial value 0 because we used it for sync. between INTERRUPT and TASK*/
	Task_Count_Sem = xSemaphoreCreateCounting(1,0);

	/*Start OS "Scheduler " */
	vTaskStartScheduler();

	while(1);


	return 0;
}


void Task1_Func( void *pvParameter )
{
	u8 Ret;

	while(1)
	{
		Ret =0 ;
		/*pend for semaphore until it released from ISR */
		xSemaphoreTake( Task_Count_Sem , portMAX_DELAY );
		Ret = xSemaphoreTake( Task_Count_Sem , portMAX_DELAY );
		if( Ret == 1 )
		{
		/*print if semaphore released*/
		Lcd_vidWriteStr("Button Pressed");
		vTaskDelay(500);
		Lcd_vidSendCommand(LCD_u8CMD_CLR_Display);
		vTaskDelay(500);
		}
		/*Take semaphore to decrement it's val. To wait again until it released by Interrupt */
		//xSemaphoreTake(Task_Count_Sem , portMAX_DELAY);
		//xSemaphoreTake(Task_Count_Sem , portMAX_DELAY);


	}
}


void INT0_Function(void)
{
	if( flag == 0)
	{
		/*release semaphore */
			xSemaphoreGiveFromISR( Task_Count_Sem , NULL );
			flag = 1 ;
	}
	else if( flag == 1)
	{
		/*release semaphore */
			xSemaphoreGiveFromISR( Task_Count_Sem , NULL );
			flag = 0 ;
	}

}
