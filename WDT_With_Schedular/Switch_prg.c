/*
 * Switch_prg.c
 *
 *  Created on: Jul 13, 2020
 *      Author: zas
 */
#include "../Lib/Std_types.h"
#include "../Lib/Bit_math.h"
#include "Dio_int.h"
#include "Switch_cfg.h"
#include "Switch_int.h"

void Switch_vidInit(u8 SwitchId)
{
	switch( SwitchId )
	{
	case 1:
		Dio_vidSetPinDir( SWITCH_8ID_1 , DIO_u8INPUT );
		Dio_vidSetPinVal( SWITCH_8ID_1 , DIO_u8HIGH  );
		break;

	case 2:
		Dio_vidSetPinDir( SWITCH_8ID_2 , DIO_u8INPUT );
		Dio_vidSetPinVal( SWITCH_8ID_2 , DIO_u8HIGH  );
		break;

	case 3:
		Dio_vidSetPinDir( SWITCH_8ID_3 , DIO_u8INPUT );
		Dio_vidSetPinVal( SWITCH_8ID_3 , DIO_u8HIGH  );
		break;

	case 4:
		Dio_vidSetPinDir( SWITCH_8ID_4 , DIO_u8INPUT );
		Dio_vidSetPinVal( SWITCH_8ID_4 , DIO_u8HIGH  );
		break;

	case 5:
		Dio_vidSetPinDir( SWITCH_8ID_5 , DIO_u8INPUT );
		Dio_vidSetPinVal( SWITCH_8ID_5 , DIO_u8HIGH  );
		break;

	case 6:
		Dio_vidSetPinDir( SWITCH_8ID_6 , DIO_u8INPUT );
		Dio_vidSetPinVal( SWITCH_8ID_6 , DIO_u8HIGH  );
		break;

	case 7:
		Dio_vidSetPinDir( SWITCH_8ID_7 , DIO_u8INPUT );
		Dio_vidSetPinVal( SWITCH_8ID_7 , DIO_u8HIGH  );
		break;

	case 8:
		Dio_vidSetPinDir( SWITCH_8ID_8 , DIO_u8INPUT );
		Dio_vidSetPinVal( SWITCH_8ID_8 , DIO_u8HIGH  );
		break;

	case 9:
		Dio_vidSetPinDir( SWITCH_8ID_9 , DIO_u8INPUT );
		Dio_vidSetPinVal( SWITCH_8ID_9 , DIO_u8HIGH  );
		break;

	case 10:
		Dio_vidSetPinDir( SWITCH_8ID_10 , DIO_u8INPUT );
		Dio_vidSetPinVal( SWITCH_8ID_10 , DIO_u8HIGH  );
		break;


	case 11:
		Dio_vidSetPinDir( SWITCH_8ID_11 , DIO_u8INPUT );
		Dio_vidSetPinVal( SWITCH_8ID_11 , DIO_u8HIGH  );
		break;

	case 12:
		Dio_vidSetPinDir( SWITCH_8ID_12 , DIO_u8INPUT );
		Dio_vidSetPinVal( SWITCH_8ID_12 , DIO_u8HIGH  );
		break;

	case 13:
		Dio_vidSetPinDir( SWITCH_8ID_13 , DIO_u8INPUT );
		Dio_vidSetPinVal( SWITCH_8ID_13 , DIO_u8HIGH  );
		break;

	case 14:
		Dio_vidSetPinDir( SWITCH_8ID_14 , DIO_u8INPUT );
		Dio_vidSetPinVal( SWITCH_8ID_14 , DIO_u8HIGH  );
		break;

	case 15:
		Dio_vidSetPinDir( SWITCH_8ID_15 , DIO_u8INPUT );
		Dio_vidSetPinVal( SWITCH_8ID_15 , DIO_u8HIGH  );
		break;

	case 16:
		Dio_vidSetPinDir( SWITCH_8ID_16 , DIO_u8INPUT );
		Dio_vidSetPinVal( SWITCH_8ID_16 , DIO_u8HIGH  );
		break;
	}
}



u8   Switch_u8GetVal(u8 SwitchId)
{
	u8 RetVal ;

	switch( SwitchId )
	{
	case 1:
		RetVal = Dio_u8GetPinVal( SWITCH_8ID_1 );
		break;

	case 2:
		RetVal = Dio_u8GetPinVal( SWITCH_8ID_2 );
		break;

	case 3:
		RetVal = Dio_u8GetPinVal( SWITCH_8ID_3 );
		break;

	case 4:
		RetVal = Dio_u8GetPinVal( SWITCH_8ID_4 );
		break;

	case 5:
		RetVal = Dio_u8GetPinVal( SWITCH_8ID_5 );
		break;

	case 6:
		RetVal = Dio_u8GetPinVal( SWITCH_8ID_6 );
		break;

	case 7:
		RetVal = Dio_u8GetPinVal( SWITCH_8ID_7 );
		break;

	case 8:
		RetVal = Dio_u8GetPinVal( SWITCH_8ID_8 );
		break;

	case 9:
		RetVal = Dio_u8GetPinVal( SWITCH_8ID_9 );
		break;

	case 10:
		RetVal = Dio_u8GetPinVal( SWITCH_8ID_10 );
		break;


	case 11:
		RetVal = Dio_u8GetPinVal( SWITCH_8ID_11 );
		break;

	case 12:
		RetVal = Dio_u8GetPinVal( SWITCH_8ID_12 );
		break;

	case 13:
		RetVal = Dio_u8GetPinVal( SWITCH_8ID_13 );
		break;

	case 14:
		RetVal = Dio_u8GetPinVal( SWITCH_8ID_14 );
		break;

	case 15:
		RetVal = Dio_u8GetPinVal( SWITCH_8ID_15 );
		break;

	case 16:
		RetVal = Dio_u8GetPinVal( SWITCH_8ID_16 );
		break;
	}

	return RetVal;
}
