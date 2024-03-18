/*
 * mines_detector.c
 *
 *  Created on: march 16, 2024
 *      Author: Ebrahim Mostafa
 */


#include "Registers.h"
#include "Gie.h"
#include "Gpt.h"
#include "Interrupts.h"
#include "Pwm.h"
#include "mines_detector.h"


void Car_direction(Car_direction_type direction)
{
    switch (direction)
    {
               case STOP :
           		    Dio_SetPinLevel(IN1 , DIO_LOW);
           		    Dio_SetPinLevel(IN2 , DIO_LOW);
           		    Dio_SetPinLevel(IN3 , DIO_LOW);
           	    	Dio_SetPinLevel(IN4 , DIO_LOW);
            	   break;
               case FORWORD :
           		    Dio_SetPinLevel(IN1 , DIO_HIGH);
           	     	Dio_SetPinLevel(IN2 , DIO_LOW);
           	    	Dio_SetPinLevel(IN3 , DIO_LOW);
           	    	Dio_SetPinLevel(IN4 , DIO_HIGH);
            	   break;
               case BACKWORD :
              		Dio_SetPinLevel(IN1 , DIO_LOW);
              		Dio_SetPinLevel(IN2 , DIO_HIGH);
              		Dio_SetPinLevel(IN3 , DIO_HIGH);
              		Dio_SetPinLevel(IN4 , DIO_LOW);
            	   break;
               case RIGHT :
          		    Dio_SetPinLevel(IN1 , DIO_HIGH);
          	     	Dio_SetPinLevel(IN2 , DIO_LOW);
             		Dio_SetPinLevel(IN3 , DIO_LOW);
             		Dio_SetPinLevel(IN4 , DIO_LOW);
            	   break;
               case LEFT :
            		Dio_SetPinLevel(IN1 , DIO_LOW);
            		Dio_SetPinLevel(IN2 , DIO_LOW);
            		Dio_SetPinLevel(IN3 , DIO_LOW);
            		Dio_SetPinLevel(IN4 , DIO_HIGH);
            	   break;
               default :
          		    Dio_SetPinLevel(IN1 , DIO_HIGH);
          	     	Dio_SetPinLevel(IN2 , DIO_LOW);
          	    	Dio_SetPinLevel(IN3 , DIO_LOW);
          	    	Dio_SetPinLevel(IN4 , DIO_HIGH);
			   break;
    }
}



void Car_Detected(void)
{
	for (i=300; i<=2000; i+=200)
			      {
				             Pwm_SetTimeOn(PWM_OUT_OC1A, i);
					         _delay_ms(250);
					       if (Dio_ReadPinLevel(IR) == 1)
					       {
					    	   Detected_Mine = 1;
					    	   Dio_SetPinLevel(BUZZ , DIO_HIGH);
					    	   _delay_ms(2000);
					    	   Dio_SetPinLevel(BUZZ , DIO_LOW);
					    	   break;
					       }

			      }

    Timer_Counter = 0;
     flag1 = 0;
     flag2 = 0;
     flag3 = 0;
}



void Car_Round (Round_type Round)
{
    flag3 = 0;
	Timer_Counter = 0;
	if (Round == ROUND_RIGHT)
	{
	    while(!flag3)
		{
			Car_direction(RIGHT);
		}
		Car_direction(STOP);
	}
	else if (Round == ROUND_LEFT)
	{
	    while(!flag3)
		{
			Car_direction(LEFT);
		}
		Car_direction(STOP);
	}
}
