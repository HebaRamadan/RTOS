/*
  * Stepper_prg.c
 *
 *  Created on: Feb 17, 2020
 *      Author: zas
 */
#include "../Lib/Std_types.h"
#include "../Lib/Bit_math.h"
#include "Dio_int.h"
#include "Stepper_cfg.h"
#include "Stepper_int.h"

void Stepper_vidInit(void)
{
	Dio_vidSetPinDir(STEPPER_ORANGE_COIL , DIO_u8OUTPUT);
	Dio_vidSetPinDir(STEPPER_YELLOW_COIL , DIO_u8OUTPUT);
	Dio_vidSetPinDir(STEPPER_PINK_COIL   , DIO_u8OUTPUT);
	Dio_vidSetPinDir(STEPPER_BLUE_COIL   , DIO_u8OUTPUT);
}


void Stepper_vidPattern_1(void)
{
	Dio_vidSetPinVal(STEPPER_ORANGE_COIL , DIO_u8HIGH);
	Dio_vidSetPinVal(STEPPER_YELLOW_COIL , DIO_u8LOW );
	Dio_vidSetPinVal(STEPPER_PINK_COIL   , DIO_u8LOW );
	Dio_vidSetPinVal(STEPPER_BLUE_COIL   , DIO_u8LOW );
}


void Stepper_vidPattern_2(void)
{
	Dio_vidSetPinVal(STEPPER_ORANGE_COIL , DIO_u8LOW );
	Dio_vidSetPinVal(STEPPER_YELLOW_COIL , DIO_u8HIGH);
	Dio_vidSetPinVal(STEPPER_PINK_COIL   , DIO_u8LOW );
	Dio_vidSetPinVal(STEPPER_BLUE_COIL   , DIO_u8LOW );
}


void Stepper_vidPattern_3(void)
{
	Dio_vidSetPinVal(STEPPER_ORANGE_COIL , DIO_u8LOW );
	Dio_vidSetPinVal(STEPPER_YELLOW_COIL , DIO_u8LOW );
	Dio_vidSetPinVal(STEPPER_PINK_COIL   , DIO_u8HIGH);
	Dio_vidSetPinVal(STEPPER_BLUE_COIL   , DIO_u8LOW );
}


void Stepper_vidPattern_4(void)
{
	Dio_vidSetPinVal(STEPPER_ORANGE_COIL , DIO_u8LOW );
	Dio_vidSetPinVal(STEPPER_YELLOW_COIL , DIO_u8LOW );
	Dio_vidSetPinVal(STEPPER_PINK_COIL   , DIO_u8LOW );
	Dio_vidSetPinVal(STEPPER_BLUE_COIL   , DIO_u8HIGH);
}

void Stepper_vidStopMotor(void)
{
	Dio_vidSetPinVal(STEPPER_ORANGE_COIL , DIO_u8LOW );
	Dio_vidSetPinVal(STEPPER_YELLOW_COIL , DIO_u8LOW );
	Dio_vidSetPinVal(STEPPER_PINK_COIL   , DIO_u8LOW );
	Dio_vidSetPinVal(STEPPER_BLUE_COIL   , DIO_u8LOW );
}
