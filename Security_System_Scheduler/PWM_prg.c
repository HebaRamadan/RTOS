/*
 * PWM_prg.c
 *
 *  Created on: Jul 23, 2020
 *      Author: zas
 */
#include "../Lib/Std_types.h"
#include "../Lib/Bit_math.h"
#include "Dio_int.h"
#include "Timer2_int.h"
#include "PWM_cfg.h"
#include "PWM_int.h"

void PWM_vidInit(void)
{
	Dio_vidSetPinDir( PWM_u8PIN , DIO_u8OUTPUT );
	Timer2_vidInit();
}



void PWM_vidSetDutyCycle(u8 Duty_Cycle)
{
	u8 OCR2_Val;

	OCR2_Val = (u8)(Duty_Cycle * (255/100));

	Timer2_vidSetCompareRegisterValue(OCR2_Val);
}
