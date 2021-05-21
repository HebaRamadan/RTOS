/*
 * main.c
 *
 *  Created on: Jul 20, 2020
 *      Author: Heba Ramadan Taha
 */
#include "../Lib/Std_types.h"
#include "../Lib/Bit_math.h"
#include "RTO_int.h"
#include "Lcd_int.h"
#include "Keypad_int.h"
#include "Stepper_int.h"
#include "Servo_int.h"
#include "PWM_int.h"
#include "DC_Motor_int.h"
#include "Led_int.h"
#include "Buzzer_int.h"

void LCD_Task_Fun(void);
void KeyPad_Task_Fun(void);
void LCD_Trigger_Task_Fun(void);
void Password_Task_Func(void);
void Door_Task_Func(void);
void Control_Task_Func(void);
void Window_Task_Func(void);
void Light_Task_Func(void);
void Fan_Task_Func(void);
void Exit_Task_Func(void);
void Alarm_Task_Func(void);

Task_Type KeyPad_Task;
Task_Type LCD_Task;
Task_Type LCD_Trigger_Task;
Task_Type Password_Task;
Task_Type Door_Task;
Task_Type Control_Task;
Task_Type Window_Task;
Task_Type Light_Task;
Task_Type Fan_Task;
Task_Type Exit_Task;
Task_Type Alarm_Task;


u8 Pass_Arr[4] = { 1, 2, 3, 4};
u8 SaveVal[3] ;
u8 Save_Key    = KEYPAD_u8NO_KEY;
u8 Exit_Door_Flag = 0;

int main(void)
{
	Lcd_vidInit();
	Keypad_vidInit();
	Stepper_vidInit();
	Servo_vidInit();
	PWM_vidInit();
	DC_vidInit();
	Led_vidInit(LED_1);
	Buzzer_vidInit();
	RTO_vidInit();


	KeyPad_Task.u32FirstDelay       = 0;
	KeyPad_Task.u32Periodicity      = 50;
	KeyPad_Task.pfTaskCode          = KeyPad_Task_Fun    ;
	KeyPad_Task.u8TaskState         = TASK_RUNNING_STATE ;

	LCD_Task.u32FirstDelay          = 0;
	LCD_Task.u32Periodicity         = 10;
	LCD_Task.pfTaskCode             = LCD_Task_Fun       ;
	LCD_Task.u8TaskState            = TASK_RUNNING_STATE ;

	LCD_Trigger_Task.u32FirstDelay  = 0;
	LCD_Trigger_Task.u32Periodicity = 3;
	LCD_Trigger_Task.pfTaskCode     = LCD_Trigger_Task_Fun;
	LCD_Trigger_Task.u8TaskState    = TASK_WAITING_STATE  ;

	/* Initialize Password Task  */
	Password_Task.u32FirstDelay  = 0 ;
	Password_Task.u32Periodicity = 100;
	Password_Task.pfTaskCode     = Password_Task_Func ;
	Password_Task.u8TaskState    = TASK_RUNNING_STATE ;

	/* Initialize Door Task  */
	Door_Task.u32FirstDelay  = 0 ;
	Door_Task.u32Periodicity = 2;
	Door_Task.pfTaskCode     = Door_Task_Func         ;
	Door_Task.u8TaskState    = TASK_WAITING_STATE     ;

	/* Initialize Control Task  */
	Control_Task.u32FirstDelay  = 0 ;
	Control_Task.u32Periodicity = 100;
	Control_Task.pfTaskCode     = Control_Task_Func   ;
	Control_Task.u8TaskState    = TASK_WAITING_STATE  ;


	/* Initialize Window Task  */
	Window_Task.u32FirstDelay  = 0 ;
	Window_Task.u32Periodicity = 100;
	Window_Task.pfTaskCode     = Window_Task_Func     ;
	Window_Task.u8TaskState    = TASK_WAITING_STATE   ;


	/* Initialize Light Task  */
	Light_Task.u32FirstDelay  = 0 ;
	Light_Task.u32Periodicity = 100;
	Light_Task.pfTaskCode     = Light_Task_Func      ;
	Light_Task.u8TaskState    = TASK_WAITING_STATE   ;

	/* Initialize Fan Task  */
	Fan_Task.u32FirstDelay  = 0 ;
	Fan_Task.u32Periodicity = 100;
	Fan_Task.pfTaskCode     = Fan_Task_Func          ;
	Fan_Task.u8TaskState    = TASK_WAITING_STATE     ;

	/* Initialize Exit Task  */
	Exit_Task.u32FirstDelay  = 0 ;
	Exit_Task.u32Periodicity = 100;
	Exit_Task.pfTaskCode     = Exit_Task_Func         ;
	Exit_Task.u8TaskState    = TASK_WAITING_STATE     ;

	/* Initialize Alarm Task  */
	Alarm_Task.u32FirstDelay  = 0 ;
	Alarm_Task.u32Periodicity = 100;
	Alarm_Task.pfTaskCode     = Alarm_Task_Func        ;
	Alarm_Task.u8TaskState    = TASK_WAITING_STATE     ;


	RTO_vidCreateQueueOfTasks( &KeyPad_Task      , 0 );
	RTO_vidCreateQueueOfTasks( &LCD_Task         , 1 );
	RTO_vidCreateQueueOfTasks( &LCD_Trigger_Task , 2 );
	RTO_vidCreateQueueOfTasks( &Password_Task    , 3 );
	RTO_vidCreateQueueOfTasks( &Door_Task        , 4 );
	RTO_vidCreateQueueOfTasks( &Control_Task     , 5 );
	RTO_vidCreateQueueOfTasks( &Window_Task      , 6 );
	RTO_vidCreateQueueOfTasks( &Light_Task       , 7 );
	RTO_vidCreateQueueOfTasks( &Fan_Task         , 8 );
	RTO_vidCreateQueueOfTasks( &Exit_Task        , 9 );
	RTO_vidCreateQueueOfTasks( &Alarm_Task       , 10);

	while(1);

	return 0;
}


void KeyPad_Task_Fun(void)
{
	static u8 Key_Counter = 0;
	u8 Key;

	Key = Keypad_u8GetKey();

	if(Key != KEYPAD_u8NO_KEY)
	{
		if(Key_Counter == 2)
		{
			Save_Key = Key;
		}
	}

	Key_Counter++;

	if(Key_Counter == 3)
	{
		Key_Counter = 0;
	}
}


void Password_Task_Func(void)
{
	static u8 PassArray_Counter  = 0;
	static u8 Enter_Error_Pass   = 0;
	static u8 Error_Flag   = 0;
	static u8 flag         = 0;

	if(flag == 0)
	{
		Lcd_vidQueueCommand( 0x01 );
		Password_Task.u32Periodicity = 100;
		Lcd_vidQueueString( "Enter Password : ");
		Lcd_vidQueueCommand(0xc0);
		flag++;
	}

	if( (Save_Key != '#') && (Save_Key != KEYPAD_u8NO_KEY) )
	{
		Lcd_vidQueueChar( Save_Key + '0');

		if( Pass_Arr[PassArray_Counter] != Save_Key )
		{
			Error_Flag = 1;
		}

		Save_Key = KEYPAD_u8NO_KEY;
		PassArray_Counter++;
	}
	else if(Save_Key == '#')
	{
		Save_Key = KEYPAD_u8NO_KEY;


		if( (Error_Flag == 0)  && (PassArray_Counter == 4))
		{
			Lcd_vidQueueCommand( 0x01 );
			Lcd_vidQueueString( "Welcome Home...");

			Password_Task.u8TaskState = TASK_WAITING_STATE;
			KeyPad_Task.u8TaskState   = TASK_WAITING_STATE;
			Door_Task.u8TaskState     = TASK_RUNNING_STATE;

			flag = 0;
			Enter_Error_Pass = 0;
			PassArray_Counter   = 0;
		}

		else
		{

			if( Enter_Error_Pass == 2)
			{
				Lcd_vidQueueCommand( 0x01 );
				Lcd_vidQueueString("System Blocked");

				Password_Task.u8TaskState = TASK_WAITING_STATE;
				KeyPad_Task.u8TaskState   = TASK_WAITING_STATE;
				Alarm_Task.u8TaskState    = TASK_RUNNING_STATE;

			}
			else
			{
				Enter_Error_Pass++;
				Lcd_vidQueueCommand( 0x01 );
				flag = 0;
				Error_Flag = 0;
				Password_Task.u32Periodicity = 1500;
				Lcd_vidQueueString( "  Not Valid  ");
				PassArray_Counter   = 0;
			}
		}

	}
}


void Door_Task_Func(void)
{
	static u16 Num_Of_Iteration = 0;
	static u8  Pattern = 0;
	static u8  StepFlag    = 0;

	if( (StepFlag == 0) && (Num_Of_Iteration <= 256))
	{
		switch(Pattern)
		{
		case 0:
			Stepper_vidPattern_1();
			break;

		case 1:
			Stepper_vidPattern_2();
			break;

		case 2:
			Stepper_vidPattern_3();
			break;

		case 3:
			Stepper_vidPattern_4();
			Num_Of_Iteration++;
			break;
		}

		Pattern++;
		if(Pattern == 4)
		{
			Pattern = 0;
		}

		if( Num_Of_Iteration == 257)
		{
			Door_Task.u32Periodicity = 1000;
			Num_Of_Iteration = 0;
			StepFlag = 1;
		}
	}
	else if( (StepFlag == 1) && (Num_Of_Iteration <= 256))
	{
		Door_Task.u32Periodicity = 2;
		switch(Pattern)
		{
		case 0:
			Stepper_vidPattern_4();
			break;

		case 1:
			Stepper_vidPattern_3();
			break;

		case 2:
			Stepper_vidPattern_2();
			break;

		case 3:
			Stepper_vidPattern_1();
			Num_Of_Iteration++;
			break;
		}

		Pattern++;
		if(Pattern == 4)
		{
			Pattern = 0;
		}

		if( Num_Of_Iteration == 257)
		{
			if( Exit_Door_Flag == 1)
			{
				Exit_Task.u8TaskState = TASK_RUNNING_STATE;
			}
			else
			{
				Lcd_vidQueueCommand( 0x01);
				KeyPad_Task.u8TaskState   = TASK_RUNNING_STATE;
				Control_Task.u8TaskState  = TASK_RUNNING_STATE;
			}

			Door_Task.u8TaskState     = TASK_WAITING_STATE;
			Num_Of_Iteration = 0;
			StepFlag = 0;
		}
	}
}


void Control_Task_Func(void)
{

	static u8 ControlFlag = 0;

	if(ControlFlag == 0)
	{
		Lcd_vidQueueCommand( 0x01 );
		Lcd_vidQueueString("1-Window");
		Lcd_vidQueueCommand(0xc0);
		Lcd_vidQueueString("2-Light");
		Lcd_vidQueueCommand(0x89);
		Lcd_vidQueueString("3-Fan");
		Lcd_vidQueueCommand(0xc9);
		Lcd_vidQueueString("4-Exit");

		Control_Task.u32Periodicity = 100;
		ControlFlag++;
	}

	if( Save_Key != KEYPAD_u8NO_KEY )
	{
		switch(Save_Key)
		{
		case 1:
			Window_Task.u8TaskState   = TASK_RUNNING_STATE;
			Control_Task.u8TaskState  = TASK_WAITING_STATE;
			ControlFlag = 0;
			break;

		case 2:
			Light_Task.u8TaskState    = TASK_RUNNING_STATE;
			Control_Task.u8TaskState  = TASK_WAITING_STATE;
			ControlFlag = 0;
			break;

		case 3:
			Fan_Task.u8TaskState      = TASK_RUNNING_STATE;
			Control_Task.u8TaskState  = TASK_WAITING_STATE;
			ControlFlag = 0;
			break;

		case 4:
			Exit_Task.u8TaskState      = TASK_RUNNING_STATE;
			Control_Task.u8TaskState  = TASK_WAITING_STATE;
			ControlFlag = 0;
			break;

		default :
			Lcd_vidQueueCommand( 0x01 );
			Lcd_vidQueueString("Not Valid InPut");
			Control_Task.u32Periodicity = 1500;
			ControlFlag = 0;
			break;
		}
		Save_Key = KEYPAD_u8NO_KEY;
	}
}



void Window_Task_Func(void)
{
	static u8 ServoFlag   = 0;
	static u8 Arr_Counter = 0;

	u16 ServoAngle;

	if( ServoFlag == 0 )
	{
		Lcd_vidQueueCommand(0x01);
		Lcd_vidQueueString("Window : ");
		Lcd_vidQueueCommand(0xC0);
		Lcd_vidQueueString("Angle = ");
		Window_Task.u32Periodicity = 100;
		u8 i;

		for( i=0; i<3; i++ )
		{
			SaveVal[i] = 0;
		}
		ServoFlag++;
	}

	if( (Save_Key >= 0) && (Save_Key <=9))
	{

		Lcd_vidQueueChar( Save_Key + '0');
		SaveVal[Arr_Counter]  = Save_Key;
		Save_Key = KEYPAD_u8NO_KEY;
		Arr_Counter++;

	}
	else if( Save_Key == '#' )
	{
		Save_Key = KEYPAD_u8NO_KEY;

		if( Arr_Counter == 1 )
		{
			ServoAngle = SaveVal[0];
		}
		else if(  Arr_Counter == 2 )
		{
			ServoAngle = (SaveVal[0] * 10) + SaveVal[1];
		}
		else if(  Arr_Counter == 3 )
		{
			ServoAngle = (SaveVal[0] * 100) + (SaveVal[1] * 10) + SaveVal[2];
		}

		if( (ServoAngle >= 0) && (ServoAngle <= 180) && (Arr_Counter <=3))
		{
			Servo_vidSetDegree( (u8)ServoAngle );

			Control_Task.u8TaskState = TASK_RUNNING_STATE;
			Window_Task.u8TaskState  = TASK_WAITING_STATE;

			Arr_Counter = 0;
			ServoFlag   = 0;
		}
		else
		{
			Lcd_vidQueueCommand(0x01);
			Lcd_vidQueueString(" Not Valid Angle ");
			Window_Task.u32Periodicity = 1500;
			Arr_Counter = 0;
			ServoFlag   = 0;
		}
	}
}



void Light_Task_Func(void)
{
	static u8 LightFlag   = 0;
	static u8 Arr_Counter = 0;

	u16 LightsIntensity;

	if( LightFlag == 0 )
	{
		Lcd_vidQueueCommand(0x01);
		Lcd_vidQueueString("Light : ");
		Lcd_vidQueueCommand(0xC0);
		Lcd_vidQueueString("Intensity = ");
		Light_Task.u32Periodicity = 100;
		u8 i;

		for( i=0; i<3; i++ )
		{
			SaveVal[i] = 0;
		}
		LightFlag++;
	}

	if( (Save_Key >= 0) && (Save_Key <=9))
	{

		Lcd_vidQueueChar( Save_Key + '0');
		SaveVal[Arr_Counter]  = Save_Key;
		Save_Key = KEYPAD_u8NO_KEY;
		Arr_Counter++;

	}
	else if( Save_Key == '#' )
	{
		Save_Key = KEYPAD_u8NO_KEY;

		if( Arr_Counter == 1 )
		{
			LightsIntensity = SaveVal[0];
		}
		else if(  Arr_Counter == 2 )
		{
			LightsIntensity = (SaveVal[0] * 10) + SaveVal[1];
		}
		else if(  Arr_Counter == 3 )
		{
			LightsIntensity = (SaveVal[0] * 100) + (SaveVal[1] * 10) + SaveVal[2];
		}

		if( (LightsIntensity >= 0) && (LightsIntensity <= 100) && (Arr_Counter <=3))
		{
			PWM_vidSetDutyCycle( (u8)LightsIntensity );

			Control_Task.u8TaskState = TASK_RUNNING_STATE;
			Light_Task.u8TaskState  = TASK_WAITING_STATE;

			Arr_Counter = 0;
			LightFlag   = 0;
		}
		else
		{
			Lcd_vidQueueCommand(0x01);
			Lcd_vidQueueString(" Not Valid InPut ");
			Light_Task.u32Periodicity = 1500;
			Arr_Counter = 0;
			LightFlag   = 0;
		}
	}
}



void Fan_Task_Func(void)
{
	static u8 FanFlag   = 0;


	if( FanFlag == 0 )
	{
		Lcd_vidQueueCommand(0x01);
		Lcd_vidQueueString("Fan : ");
		Lcd_vidQueueCommand(0xC0);
		Lcd_vidQueueString("0- OFF ");
		Lcd_vidQueueCommand(0xC8);
		Lcd_vidQueueString("1- ON ");
		Fan_Task.u32Periodicity = 100;

		FanFlag++;
	}

	if(Save_Key != KEYPAD_u8NO_KEY)
	{
		switch(Save_Key)
		{
		case 0:
			DC_vidTurnOff();
			Control_Task.u8TaskState = TASK_RUNNING_STATE;
			Fan_Task.u8TaskState  = TASK_WAITING_STATE;

			FanFlag   = 0;
			break;

		case 1:
			DC_vidTurnOn();
			Control_Task.u8TaskState = TASK_RUNNING_STATE;
			Fan_Task.u8TaskState  = TASK_WAITING_STATE;

			FanFlag   = 0;
			break;

		default :
			Lcd_vidQueueCommand(0x01);
			Lcd_vidQueueString("Not Valid InPut");
			Fan_Task.u32Periodicity = 1500;

			FanFlag = 0;
			break;
		}

		Save_Key = KEYPAD_u8NO_KEY;

	}

}



void Exit_Task_Func(void)
{
	static u8 ExitFlag   = 0;

	if(ExitFlag == 0)
	{
		Lcd_vidQueueCommand(0x01);
		Lcd_vidQueueString(" GoodBye ");
		Exit_Task.u8TaskState = TASK_WAITING_STATE;
		Door_Task.u8TaskState = TASK_RUNNING_STATE;

		Exit_Door_Flag = 1;

		ExitFlag++;
	}
	else
	{
		Servo_vidSetDegree( 0  );
		PWM_vidSetDutyCycle( 0 );
		DC_vidTurnOff();

		Password_Task.u8TaskState = TASK_RUNNING_STATE;
		Door_Task.u8TaskState     = TASK_WAITING_STATE;
		Exit_Task.u8TaskState     = TASK_WAITING_STATE;

		Exit_Door_Flag = 0;
		ExitFlag = 0;
	}


}



void Alarm_Task_Func(void)
{
	Led_vidTurnOn(LED_1);
	Buzzer_vidTurnOn();
}



void LCD_Task_Fun(void)
{
	u8 RetVar;

	Lcd_vidDisableTrigger();

	RetVar = Lcd_u8ReadQueue();

	if(RetVar != LCD_QUEUE_NULL)
	{
		LCD_Trigger_Task.u8TaskState = TASK_RUNNING_STATE;
	}
	else
	{
		Lcd_vidDisableTrigger();
	}
}



void LCD_Trigger_Task_Fun(void)
{
	Lcd_vidEnableTrigger();
	LCD_Trigger_Task.u8TaskState = TASK_WAITING_STATE;
}
