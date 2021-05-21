/*
 * Lcd_prg.c
 *
 *  Created on: Jul 18, 2020
 *      Author: zas
 */
#include "../Lib/Std_types.h"
#include "../Lib/Bit_math.h"
#include "Dio_int.h"
#include "Lcd_cfg.h"
#include "Lcd_int.h"

u8  arr_Queue[MAXIMUM_ELEMENT_IN_QUEUE] ;
u8  arr_State[MAXIMUM_ELEMENT_IN_QUEUE] ;
u8 Queue_Write_Counter = 0;
u8 Queue_Read_Counter  = 0;

void Lcd_vidSendCommand(u8 Cmd)
{
	//Start to change in LCD control Reg to indicate it that you will receive command
	Dio_vidSetPinVal(LCD_u8RS_PIN , DIO_u8LOW);  //make RS->0 to indicate LCD "you will receive command not data"
	Dio_vidSetPinVal(LCD_u8RW_PIN , DIO_u8LOW);  //make RW->0 to indicate LCD "you will write in command Register"
	Dio_vidSetPinVal(LCD_u8EN_PIN , DIO_u8HIGH); //make EN->1 to indicate LCD "Please LCD don't save any thing in your buffer until be sure all data sent "

	//Make Data Ready To Sent
	Dio_vidSetPinVal(LCD_u8D0_PIN , GET_BIT(Cmd,0));
	Dio_vidSetPinVal(LCD_u8D1_PIN , GET_BIT(Cmd,1));
	Dio_vidSetPinVal(LCD_u8D2_PIN , GET_BIT(Cmd,2));
	Dio_vidSetPinVal(LCD_u8D3_PIN , GET_BIT(Cmd,3));
	Dio_vidSetPinVal(LCD_u8D4_PIN , GET_BIT(Cmd,4));
	Dio_vidSetPinVal(LCD_u8D5_PIN , GET_BIT(Cmd,5));
	Dio_vidSetPinVal(LCD_u8D6_PIN , GET_BIT(Cmd,6));
	Dio_vidSetPinVal(LCD_u8D7_PIN , GET_BIT(Cmd,7));

}


void Lcd_vidInit(void)
{
	 Dio_vidSetPinDir(LCD_u8RS_PIN , DIO_u8OUTPUT);
	 Dio_vidSetPinDir(LCD_u8RW_PIN , DIO_u8OUTPUT);
	 Dio_vidSetPinDir(LCD_u8EN_PIN , DIO_u8OUTPUT);

	 Dio_vidSetPinDir(LCD_u8D0_PIN , DIO_u8OUTPUT);
	 Dio_vidSetPinDir(LCD_u8D1_PIN , DIO_u8OUTPUT);
	 Dio_vidSetPinDir(LCD_u8D2_PIN , DIO_u8OUTPUT);
	 Dio_vidSetPinDir(LCD_u8D3_PIN , DIO_u8OUTPUT);
	 Dio_vidSetPinDir(LCD_u8D4_PIN , DIO_u8OUTPUT);
	 Dio_vidSetPinDir(LCD_u8D5_PIN , DIO_u8OUTPUT);
	 Dio_vidSetPinDir(LCD_u8D6_PIN , DIO_u8OUTPUT);
	 Dio_vidSetPinDir(LCD_u8D7_PIN , DIO_u8OUTPUT);


	 arr_Queue[Queue_Write_Counter]  = LCD_u8CMD_8_BIT_2x16_5x7;
	 arr_State[Queue_Write_Counter]  = COMMAND;
	 Queue_Write_Counter++;

	 arr_Queue[Queue_Write_Counter]  = LCD_u8CMD_DISP_ON_CURS_OFF;
	 arr_State[Queue_Write_Counter]  = COMMAND;
	 Queue_Write_Counter++;

	 arr_Queue[Queue_Write_Counter]  = LCD_u8CMD_CLR_Display;
	 arr_State[Queue_Write_Counter]  = COMMAND;
	 Queue_Write_Counter++;

	 u8 i;

	 for( i=3; i<MAXIMUM_ELEMENT_IN_QUEUE; i++ )
	 {
		 arr_Queue[i]  = LCD_QUEUE_NULL;
		 arr_State[i]  = LCD_QUEUE_NULL;
	 }

}


void Lcd_vidWriteChar(u8 Char)

{
	Dio_vidSetPinVal(LCD_u8RS_PIN , DIO_u8HIGH);  //RS
	Dio_vidSetPinVal(LCD_u8RW_PIN , DIO_u8LOW);   //RW
	Dio_vidSetPinVal(LCD_u8EN_PIN , DIO_u8HIGH);  //EN


	//Make Data Ready To Sent
	Dio_vidSetPinVal(LCD_u8D0_PIN , GET_BIT(Char,0));
	Dio_vidSetPinVal(LCD_u8D1_PIN , GET_BIT(Char,1));
	Dio_vidSetPinVal(LCD_u8D2_PIN , GET_BIT(Char,2));
	Dio_vidSetPinVal(LCD_u8D3_PIN , GET_BIT(Char,3));
	Dio_vidSetPinVal(LCD_u8D4_PIN , GET_BIT(Char,4));
	Dio_vidSetPinVal(LCD_u8D5_PIN , GET_BIT(Char,5));
	Dio_vidSetPinVal(LCD_u8D6_PIN , GET_BIT(Char,6));
	Dio_vidSetPinVal(LCD_u8D7_PIN , GET_BIT(Char,7));

}


void Lcd_vidEnableTrigger(void)
{

	//make EN->0 to indicate LCD "NOW you can save bits in your buffer all data sent"
	Dio_vidSetPinVal(LCD_u8EN_PIN , DIO_u8LOW);

}


void Lcd_vidDisableTrigger(void)
{
	Dio_vidSetPinVal(LCD_u8EN_PIN , DIO_u8HIGH);
}


void Lcd_vidQueueChar(u8 Char)
{
	arr_Queue[Queue_Write_Counter] = Char;
	arr_State[Queue_Write_Counter] = CHAR;
	Queue_Write_Counter++;
}


void Lcd_vidQueueCommand(u8 Command)
{
	arr_Queue[Queue_Write_Counter] = Command;
	arr_State[Queue_Write_Counter] = COMMAND;
	Queue_Write_Counter++;
}


void Lcd_vidQueueString(u8 *Str)
{
	u8 Index = 0 ;

	while( Str[Index] != '\0' )
	{
		arr_Queue[Queue_Write_Counter] = Str[Index];
		arr_State[Queue_Write_Counter] = CHAR;
		Index++;
		Queue_Write_Counter++;
	}
}


void Lcd_vidClearQueue(void)
{
	 u8 i;

	 for( i=0; i<MAXIMUM_ELEMENT_IN_QUEUE; i++ )
	 {
		 arr_Queue[i]  = LCD_QUEUE_NULL;
		 arr_State[i]  = LCD_QUEUE_NULL;
	 }
	 Queue_Write_Counter = 0;
}


u8 Lcd_u8ReadQueue(void)
{
	u8 State_Value;
	u8 Byte;

	State_Value = arr_State[Queue_Read_Counter];


	if( State_Value != LCD_QUEUE_NULL )
	{
		switch(State_Value)
		{
		case CHAR:
			Byte = arr_Queue[Queue_Read_Counter];
			Lcd_vidWriteChar( Byte );
			Queue_Read_Counter++;
			break;

		case COMMAND:
			Byte = arr_Queue[Queue_Read_Counter];
			Lcd_vidSendCommand( Byte );
			Queue_Read_Counter++;
			break;
		}
		return 1;
	}
	else
	{
		 u8 i;

		 for( i=0; i<MAXIMUM_ELEMENT_IN_QUEUE; i++ )
		 {
			 arr_Queue[i]  = LCD_QUEUE_NULL;
			 arr_State[i]  = LCD_QUEUE_NULL;
		 }
		 Queue_Write_Counter = 0;
		 Queue_Read_Counter  = 0;

		 return LCD_QUEUE_NULL;
	}

}
