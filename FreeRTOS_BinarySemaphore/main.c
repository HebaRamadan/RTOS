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
#include "semphr.h"
#include "Lcd_int.h"

/* Define Priority For Tasks */
#define  TASK1_PRIORITY    2
#define  TASK2_PRIORITY    2

/* Prototype Tasks */
void LCD_Task1_Func( void *pvParameter );
void LCD_Task2_Func( void *pvParameter );

/* Define global Variable as Semaphore */
 xSemaphoreHandle LCD_SEM;

int main(void)
{
	/* Initialize LCD */
	Lcd_vidInit();


	/* Create Semaphore */
	vSemaphoreCreateBinary(LCD_SEM);



	/* Create Tasks */
	xTaskCreate( LCD_Task1_Func , "TASK_1" , 200 , NULL , TASK1_PRIORITY , NULL );
	xTaskCreate( LCD_Task2_Func , "TASK_2" , 200 , NULL , TASK2_PRIORITY , NULL );


	/* Start Scheduler */
	vTaskStartScheduler();

	return 0;
}

void LCD_Task1_Func( void *pvParameter )
{
	u8 Ret = 0;

	while(1)
	{
		/* task Take Semaphore (if Semaphore not available make task wait for 0xffff ticks) */
		Ret = xSemaphoreTake(LCD_SEM , portMAX_DELAY);
		if( Ret ==1 )
		{
			Lcd_vidSendCommand(0x01);
			Lcd_vidWriteStr("FreeRTOS Task 1");

			vTaskDelay(1000);
		}
		/* Release Semaphore */
		xSemaphoreGive(LCD_SEM);
		vTaskDelay(1000);
	}
}

void LCD_Task2_Func( void *pvParameter )
{
	u8 Ret = 0;
	while(1)
	{
		/* task Take Semaphore (if Semaphore not available make task wait for 0xffff ticks) */
		Ret = xSemaphoreTake(LCD_SEM , portMAX_DELAY);

		if( Ret == 1 )
		{
			Lcd_vidSendCommand(0x01);
			Lcd_vidWriteStr("FreeRTOS Task 2");
			vTaskDelay(1000);
		}

		/* Release Semaphore */
		xSemaphoreGive(LCD_SEM);
		vTaskDelay(1000);

	}
}
