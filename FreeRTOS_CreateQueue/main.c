/*
 * main.c
 *
 *  Created on: Aug 14, 2020
 *      Author: zas
 */
#include "../Lib/Std_Types.h"
#include "../Lib/Bit_math.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "Lcd_int.h"
#include "Keypad_int.h"


void KeyPad_Task_Func( void * pvParamter );
void LCD_Task_Func( void * pvParamter );
void LCD_QUEU_Func( void * pvParamter );

/* Create Message Queue Handle */
xQueueHandle Buffer;

int main(void)
{
	/* Initialize LCD */
	Lcd_vidInit();

	/* Initialize LCD */
	Keypad_vidInit();

	/* Create Message Queue  */
	Buffer = xQueueCreate( 6 , sizeof(u8) );

	/* Create KeyPad Task */
	xTaskCreate( KeyPad_Task_Func , "TASK_1" , 200 , NULL , 3 , NULL);

	/* Create LCD Task */
	xTaskCreate( LCD_Task_Func    , "TASK_2" , 200 , NULL , 2 , NULL);

	/* Create Read LCD Queue Task */
	xTaskCreate( LCD_QUEU_Func    , "TASK_3" , 200 , NULL , 1 , NULL);


	/*  Start Scheduler */
	vTaskStartScheduler();

	return 0;
}



void KeyPad_Task_Func( void * pvParamter )
{
	u8 Key;

	while(1)
	{
		Key = Keypad_u8GetKey();

		if( Key != KEYPAD_u8NO_KEY )
		{
			if( (Key >= 0) && (Key <= 9) )
			{
				Key = Key + '0';
				/* Send Key To RTOS Queue */
				xQueueSend( Buffer , &Key , portMAX_DELAY );
			}
			else
			{
				/* Send Key To RTOS Queue */
				xQueueSend( Buffer , &Key , portMAX_DELAY );
			}

		}

		/* Delay to make Task Periodic Every 150msec */
		vTaskDelay(150);
	}

}


void LCD_Task_Func( void * pvParamter )
{
	u8 Ret;
	u8 Key;

	while(1)
	{
		/* Receive data From RTOS Queue and save it in Key Variable */
		Ret = xQueueReceive( Buffer , &Key , portMAX_DELAY );

		if( Ret == pdTRUE)
		{
			Lcd_vidQueueChar( Key );
		}

		/* Delay to make Task Periodic Every 50msec */
		vTaskDelay(50);

	}

}

void LCD_QUEU_Func( void * pvParamter )
{
	u8 RetVar;

	while(1)
	{
		Lcd_vidDisableTrigger();

		/* Read LCD Queue */
		RetVar = Lcd_u8ReadQueue();

		/* Check LCD Queue To Read All Element In Queue */
		if(RetVar != LCD_QUEUE_NULL)
		{
			/* Wait 2msec To Trigger */
			vTaskDelay(2);

			/* Enable Trigger */
			Lcd_vidEnableTrigger();
		}
		else
		{
			Lcd_vidDisableTrigger();
		}
	}
}
