/*
 * main.c
 *
 *  Created on: Jul 8, 2020
 *      Author: zas
 */
#include "../Lib/Std_types.h"
#include "../Lib/Bit_math.h"
#include "Timer0_int.h"
#include "Led_int.h"
#include "Switch_int.h"

void TimerTick(void);
void Scheduler(void);

void LedTask_Func(void);
void SwitchTask_Func(void);

typedef struct
{
	u32 u32FirstDelay        ;
	u32 u32Periodicity       ;
	void ( *pfTaskCode)(void);
}Task_Type;


/* Create Array Of Pointer To Struct To Refer For Our Tasks */
Task_Type* apstrTaskArray[2];

/* Declare Global Variable To Select Number Of Over Flow */
u32 Ovf_Count = 0;
u8 SwitchOn = 0;


int main(void)
{
	/* Create Variables Of Struct Type */
	Task_Type LedTask;
	Task_Type SwitchTask;


	/* Initialize Task_1 */
	LedTask.u32FirstDelay  = 0  ;
	LedTask.u32Periodicity = 500;
	LedTask.pfTaskCode     = LedTask_Func;


	/* Initialize Task_2 */
	SwitchTask.u32FirstDelay  = 0   ;
	SwitchTask.u32Periodicity = 50;
	SwitchTask.pfTaskCode     = SwitchTask_Func;


	/* Initialize Array Of Pointer With Our Tasks  */
	apstrTaskArray[0] = &LedTask;
	apstrTaskArray[1] = &SwitchTask;


	/* Initialize Led*/
	Led_vidInit(LED_1);
	Led_vidInit(LED_2);
	Led_vidInit(LED_3);
	Led_vidInit(LED_4);
	Led_vidInit(LED_5);
	Led_vidInit(LED_6);
	Led_vidInit(LED_7);
	Led_vidInit(LED_8);

	/* Initialize Switch */
	Switch_vidInit( SWITCH_1);


	/* Set Overflow Call Back Function */
	OVF_vidSetCB( TimerTick );

	/* Initialize Counter Register */
	Timer0_vidSetCounterRegisterValue( 192 );

	/* Initialize Timer_0 */
	Timer0_vidInit();


	while(1);


	return 0;
}

void LedTask_Func(void)
{
	static u8 Counter ;

	switch( Counter )
	{
	case 0:
		Led_vidTurnOn( LED_1 );
		break;

	case 1:
		Led_vidTurnOn( LED_2 );
		break;

	case 2:
		Led_vidTurnOn( LED_3 );
		break;

	case 3:
		Led_vidTurnOn( LED_4 );
		break;

	case 4:
		Led_vidTurnOn( LED_5 );
		break;

	case 5:
		Led_vidTurnOn( LED_6 );
		break;

	case 6:
		Led_vidTurnOn( LED_7 );
		break;

	case 7:
		Led_vidTurnOn( LED_8 );
		break;

	default:
		Led_vidTurnOff( LED_1 );
		Led_vidTurnOff( LED_2 );
		Led_vidTurnOff( LED_3 );
		Led_vidTurnOff( LED_4 );
		Led_vidTurnOff( LED_5 );
		Led_vidTurnOff( LED_6 );
		Led_vidTurnOff( LED_7 );
		Led_vidTurnOff( LED_8 );
		break;
	}
	Counter++;

	if( Counter == 9)
	{
		Counter = 0;
	}
}


void SwitchTask_Func(void)
{
	static u8 SwitchVal[2] = { 1 , 1 };
	static u8 Counter = 0 ;

	SwitchVal[Counter] = Switch_u8GetVal( SWITCH_1 );

	Counter++;

	if( Counter == 2 )
	{
		Counter = 0;
		if( ( SwitchVal[0] == 0 ) && ( SwitchVal[1] == 0  ) )
		{
			SwitchOn = 1;
		}
		else
		{
			SwitchOn = 0;
		}
	}

}

void Scheduler(void)
{
	u8 u8TaskCounter ;
	for( u8TaskCounter = 0; u8TaskCounter < 2; u8TaskCounter++)
	{
		if( (apstrTaskArray[u8TaskCounter]->u32FirstDelay) == 0 )
		{
			apstrTaskArray[u8TaskCounter]->pfTaskCode();
			apstrTaskArray[u8TaskCounter]->u32FirstDelay = apstrTaskArray[u8TaskCounter]->u32Periodicity - 1;
		}
		else
		{
			apstrTaskArray[u8TaskCounter]->u32FirstDelay--;
		}
	}

}


void TimerTick(void)
{
	Ovf_Count ++;

	/* 32 overflow Mean 1msec -> (1 Tick) */

	if( Ovf_Count == 32 )
	{
		/* Reinitialize Overflow Counter */
		Ovf_Count = 0;

		/* Initialize Counter Register */
		Timer0_vidSetCounterRegisterValue( 192 );

		/* Scheduler Will Excute Every 1msec  */
		Scheduler();
	}

}
