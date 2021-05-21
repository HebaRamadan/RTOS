/*
 * main.c
 *
 *  Created on: Aug 7, 2020
 *      Author: zas
 */
#include "../Lib/Std_types.h"
#include "../Lib/Bit_math.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Lcd_int.h"

/* Define Priority For Tasks */
#define  TASK1_PRIORITY    2
#define  TASK2_PRIORITY    1

/* Prototype Tasks */
void LCD_Task1_Func( void *pvParameter );
void LCD_Task2_Func( void *pvParameter );


int main(void)
{
	/* Initialize LCD */
	Lcd_vidInit();

	/* Create Tasks */
	xTaskCreate( LCD_Task1_Func , "TASK_1" , 200 , NULL , TASK1_PRIORITY , NULL );
	xTaskCreate( LCD_Task2_Func , "TASK_2" , 200 , NULL , TASK2_PRIORITY , NULL );


	/* Start Scheduler */
	vTaskStartScheduler();

	while(1);

	return 0;
}

void LCD_Task1_Func( void *pvParameter )
{
	while(1)
	{
		Lcd_vidSendCommand(0x01);
		Lcd_vidWriteStr("FreeRTOS Task 1");

		vTaskDelay(2000);

	}
}

void LCD_Task2_Func( void *pvParameter )
{
	while(1)
	{
		vTaskDelay(1000);

		Lcd_vidSendCommand(0x01);
		Lcd_vidWriteStr("FreeRTOS Task 2");

		vTaskDelay(1000);

	}
}
