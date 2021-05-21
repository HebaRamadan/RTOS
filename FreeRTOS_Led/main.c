/*
 * main.c
 *
 *  Created on: Aug 6, 2020
 *      Author: zas
 */
#include "../Lib/Std_types.h"
#include "../Lib/Bit_math.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Led_int.h"

void Task_1_Func( void *pvParameter );
void Task_2_Func( void *pvParameter );

int main(void)
{
	Led_vidInit(LED_1);
	Led_vidInit(LED_2);

	/* Create Tasks */
	xTaskCreate(Task_1_Func , "TASK_1" , 200 , NULL , 2 , NULL );
	xTaskCreate(Task_2_Func , "TASK_2" , 200 , NULL , 1 , NULL );

	/* Start Scheduler */
	vTaskStartScheduler();

	return 0;
}

void Task_1_Func( void *pvParameter )
{
	/* To remain in stack */
	while(1)
	{
		static u8 Flag = 0;

		if(Flag == 0)
		{
			Led_vidTurnOn(LED_1);
			Flag = 1;
		}
		else
		{
			Led_vidTurnOff(LED_1);
			Flag = 0;
		}

		vTaskDelay(500);
	}

}

void Task_2_Func( void *pvParameter )
{

	/* To remain in stack */
	while(1)
	{
		static u8 Flag = 0;

		if(Flag == 0)
		{
			Led_vidTurnOn(LED_2);
			Flag = 1;
		}
		else
		{
			Led_vidTurnOff(LED_2);
			Flag = 0;
		}

		vTaskDelay(500);
	}
}
