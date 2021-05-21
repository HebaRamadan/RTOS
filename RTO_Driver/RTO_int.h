/*
 * RTO_int.h
 *
 *  Created on: Jul 17, 2020
 *      Author: zas
 */

#ifndef RTO_INT_H_
#define RTO_INT_H_

#define RTO_NULL       0
#define MAXIMUM_TASKS  30

#define TASK_RUNNING_STATE   1
#define TASK_WAITING_STATE   0

typedef struct
{
	u32 u32FirstDelay        ;
	u32 u32Periodicity       ;
	void ( *pfTaskCode)(void);
	u8  u8TaskState          ;

}Task_Type;


void RTO_vidInit(void);
void RTO_vidCreateQueueOfTasks( Task_Type* TaskPointer , u8 Priorty_Of_Task);
void RTO_vidScheduler(void);
void TimerTick(void);


#endif /* RTO_INT_H_ */
