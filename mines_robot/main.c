/*
 * main.c
 *
 *  Created on: Mar 15, 2024
 *      Author: Ebrahim Mostafa
 */

#include "StdTypes.h"
#include "Delay.h"
#include "Dio.h"
#include "Fcpu.h"
#include "Gie.h"
#include "Gpt.h"
#include "Interrupts.h"
#include "Pwm.h"
#include "mines_detector.h"

 u16 Timer_Counter = 0;
 u8  Detected_Mine = 0;
 u16 i = 0;
 u8 flag1 = 0;
 u8 flag2 = 0;
 u8 flag3 = 0;

 u8 steps = 0;
 u8 Total_Steps= 0;


void Timer_Handler (void)
{
	Gpt_SetCounterValue (GPT_INT_SOURCE_TIM0_OVF, 6);
	Timer_Counter++;

	if (Timer_Counter == 2000)
	{
		flag1 = 1;
	}
	if (Timer_Counter == 2000)
	{
        flag2 = 1;
	}
	if (Timer_Counter == 4000)
	{
		flag3 = 1;
	}
}


int main (void)
{
	Pwm_Init(&Pwm_Configuration);

	Gpt_Init(&Gpt_Configuration);
    Gpt_EnableInterrupt(GPT_INT_SOURCE_TIM0_OVF);
    Gpt_SetCallback(GPT_INT_SOURCE_TIM0_OVF, Timer_Handler);
    Gpt_SetCounterValue (GPT_INT_SOURCE_TIM0_OVF, 6);


	Dio_SetPinMode (IN1,DIO_MODE_OUTPUT);
	Dio_SetPinMode (IN2,DIO_MODE_OUTPUT);
	Dio_SetPinMode (IN3,DIO_MODE_OUTPUT);
	Dio_SetPinMode (IN4,DIO_MODE_OUTPUT);

	Dio_SetPinMode (BUZZ,DIO_MODE_OUTPUT);
	Dio_SetPinMode(IR,DIO_MODE_INPUT_PULLUP);
	// Dio_SetPinMode (LED,DIO_MODE_INPUT_PULLUP);


	Pwm_SetICR1(20000);

	Gie_Enable();
	while(1)
	{

	  while(steps<4)
	  {
	    flag1 = 0;
	    flag2 = 0;
	    flag3 = 0;
		Car_Detected();

		if(Detected_Mine == 1)
		{
			Detected_Mine=0;

		     flag2 = 0;
			Timer_Counter = 0;
			while(!flag2)
			{
				Car_direction(BACKWORD);
			}
			Car_direction(STOP);

            _delay_ms(50);
		     flag3 = 0;
			Timer_Counter = 0;
		    while(!flag3)
			{
				Car_direction(RIGHT);
			}
			Car_direction(STOP);

            _delay_ms(50);
		     flag3 = 0;
			Timer_Counter = 0;
		    while(!flag3)
			{
				Car_direction(LEFT);
			}
			Car_direction(STOP);


		}
		else
		{
		    flag1 = 0;
			Timer_Counter = 0;

			while(!flag1)
			{
				Car_direction(FORWORD);
			}
			Car_direction(STOP);
			steps++;
		}

	  } // end of first part

	  Total_Steps += steps;
	  if(Total_Steps == 4)
	  {
		    Car_Round(ROUND_RIGHT);
			Car_Detected();
		    Car_Round(ROUND_RIGHT);
	  }
	  else if (Total_Steps == 8)
	  {
		    Car_Round(ROUND_LEFT);
			Car_Detected();
		    Car_Round(ROUND_LEFT);
		    Total_Steps = 0;
	  }

	  steps = 0;
	}  // end of while

}  // end of main
