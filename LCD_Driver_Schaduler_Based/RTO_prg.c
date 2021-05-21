/*
 * RTO_prg.c
 *
 *  Created on: Jul 17, 2020
 *      Author: zas
 */
#include "../Lib/Std_types.h"
#include "../Lib/Bit_math.h"
#include "Timer0_int.h"
#include "RTO_int.h"

/* Declare Global Variable To Select Number Of Over Flow */
u32 Ovf_Count = 0;

/* Create Array Of Pointer To Struct To Refer For Our Tasks */
Task_Type* apstrTaskArray[MAXIMUM_TASKS];


void RTO_vidInit(void)
{
	u8 i;
	for(i=0; i<MAXIMUM_TASKS; i++)
	{
		apstrTaskArray[i] = RTO_NULL;
	}

	/* Set Overflow Call Back Function */
	OVF_vidSetCB( TimerTick );

	/* Initialize Counter Register */
	Timer0_vidSetCounterRegisterValue( 192 );

	/* Initialize Timer_0 */
	Timer0_vidInit();
}



void RTO_vidCreateQueueOfTasks( Task_Type* TaskPointer , u8 Priorty_Of_Task)
{
	apstrTaskArray[ Priorty_Of_Task ] = TaskPointer ;
}



void RTO_vidScheduler(void)
{

	u8 u8TaskCounter ;
	for( u8TaskCounter = 0; u8TaskCounter < MAXIMUM_TASKS; u8TaskCounter++)
	{
		if( apstrTaskArray[u8TaskCounter] != RTO_NULL )
		{
			if( apstrTaskArray[u8TaskCounter]->u8TaskState == TASK_RUNNING_STATE)
			{
				if( apstrTaskArray[u8TaskCounter]->u32FirstDelay == 0 )
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
		RTO_vidScheduler();
	}

}
