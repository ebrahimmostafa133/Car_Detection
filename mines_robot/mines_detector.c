/*
 * mines_detector.c
 *
 *  Created on: march 16, 2024
 *      Author: Ebrahim Mostafa
 */


#include "StdTypes.h"
#include "Delay.h"
#include "Dio.h"
#include "Gie.h"
#include "Gpt.h"
#include "Interrupts.h"
#include "Pwm.h"
#include "mines_detector.h"


/* This function is the interrupt handler for the timer.
 It is called whenever the timer overflows.
 It increments the Timer_Counter variable and sets flags based on specific counter values.*/
void Timer_Handler(void)
{
    Gpt_SetCounterValue(GPT_INT_SOURCE_TIM0_OVF, 6);
    Timer_Counter++;

    if (Timer_Counter == 2000)
    {
        flag1 = 1;
    }
    if (Timer_Counter == 2000)
    {
        flag2 = 1;
    }
    if (Timer_Counter == 3500)
    {
        flag3 = 1;
    }
}

/* This function initializes the car.
 It sets up the PWM, timer, interrupts, and pin modes.*/
void Car_Init(void)
{
    Pwm_Init(&Pwm_Configuration);
    Gpt_Init(&Gpt_Configuration);
    Gpt_EnableInterrupt(GPT_INT_SOURCE_TIM0_OVF);
    Gpt_SetCallback(GPT_INT_SOURCE_TIM0_OVF, Timer_Handler);
    Gpt_SetCounterValue(GPT_INT_SOURCE_TIM0_OVF, 6);
    Pwm_SetICR1(20000);
    Gie_Enable();

    // Set pin modes for the car's inputs and outputs
    Dio_SetPinMode(IN1, DIO_MODE_OUTPUT);
    Dio_SetPinMode(IN2, DIO_MODE_OUTPUT);
    Dio_SetPinMode(IN3, DIO_MODE_OUTPUT);
    Dio_SetPinMode(IN4, DIO_MODE_OUTPUT);
    Dio_SetPinMode(BUZZ, DIO_MODE_OUTPUT);
    Dio_SetPinMode(IR, DIO_MODE_INPUT_PULLUP);
    // Dio_SetPinMode(LED, DIO_MODE_INPUT_PULLUP); // Commented out, not used in the code
}


/* This function sets the car's direction based on the input direction parameter.
It controls the IN1, IN2, IN3, and IN4 pins to control the car's movement.*/
void Car_direction(Car_direction_type direction)
{

    switch (direction)
    {
    case STOP:
        Dio_SetPinLevel(IN1, DIO_LOW);
        Dio_SetPinLevel(IN2, DIO_LOW);
        Dio_SetPinLevel(IN3, DIO_LOW);
        Dio_SetPinLevel(IN4, DIO_LOW);
        break;
    case FORWORD:
        Dio_SetPinLevel(IN1, DIO_HIGH);
        Dio_SetPinLevel(IN2, DIO_LOW);
        Dio_SetPinLevel(IN3, DIO_LOW);
        Dio_SetPinLevel(IN4, DIO_HIGH);
        break;
    case BACKWORD:
        Dio_SetPinLevel(IN1, DIO_LOW);
        Dio_SetPinLevel(IN2, DIO_HIGH);
        Dio_SetPinLevel(IN3, DIO_HIGH);
        Dio_SetPinLevel(IN4, DIO_LOW);
        break;
    case RIGHT:
        Dio_SetPinLevel(IN1, DIO_HIGH);
        Dio_SetPinLevel(IN2, DIO_LOW);
        Dio_SetPinLevel(IN3, DIO_LOW);
        Dio_SetPinLevel(IN4, DIO_LOW);
        break;
    case LEFT:
        Dio_SetPinLevel(IN1, DIO_LOW);
        Dio_SetPinLevel(IN2, DIO_LOW);
        Dio_SetPinLevel(IN3, DIO_LOW);
        Dio_SetPinLevel(IN4, DIO_HIGH);
        break;
    default:
        Dio_SetPinLevel(IN1, DIO_HIGH);
        Dio_SetPinLevel(IN2, DIO_LOW);
        Dio_SetPinLevel(IN3, DIO_LOW);
        Dio_SetPinLevel(IN4, DIO_HIGH);
        break;
    }
}


/* This function detects a mine using an IR sensor.
 It gradually increases the PWM duty cycle to rotate the sensor and checks for a mine.
 If a mine is detected, it sets the Detected_Mine flag and activates the buzzer.
 It also resets the timer-related variables and flags.*/
void Car_Detected(void)
{
    for (i = 300; i <= 2000; i += 200)
    {
        Pwm_SetTimeOn(PWM_OUT_OC1A, i);
        _delay_ms(250);
        if (Dio_ReadPinLevel(IR) == 1)
        {
            Detected_Mine = 1;
            Dio_SetPinLevel(BUZZ, DIO_HIGH);
            _delay_ms(2000);
            Dio_SetPinLevel(BUZZ, DIO_LOW);
            break;
        }
    }

    Timer_Counter = 0;
    flag1 = 0;
    flag2 = 0;
    flag3 = 0;
}


/* This function performs a round maneuver.
 It sets the flag3 toindicate the start of the round and continuously 
rotates the car in the specified direction until the flag3 is set.
 Finally, it stops the car.*/
void Car_Round(Round_type Round)
{
    flag3 = 0;
    Timer_Counter = 0;
    if (Round == ROUND_RIGHT)
    {
        while (!flag3)
        {
            Car_direction(RIGHT);
        }
        Car_direction(STOP);
    }
    else if (Round == ROUND_LEFT)
    {
        while (!flag3)
        {
            Car_direction(LEFT);
        }
        Car_direction(STOP);
    }
}


/* This function performs a draft maneuver.
 It sets the flag2 to indicate the start of the draft and continuously moves the car backward until the flag2 is set.
 Then it stops the car for a short delay.
 After that, it performs a right turn until the flag3 is set.
 Then it stops the car for another short delay.
 Finally, it performs a left turn until the flag3 is set and stops the car.*/
void Car_Draft(void)
{
    flag2 = 0;
    Timer_Counter = 0;
    while (!flag2)
    {
        Car_direction(BACKWORD);
    }
    Car_direction(STOP);

    _delay_ms(50);
    flag3 = 0;
    Timer_Counter = 0;
    while (!flag3)
    {
        Car_direction(RIGHT);
    }
    Car_direction(STOP);

    _delay_ms(50);
    flag3 = 0;
    Timer_Counter = 0;
    while (!flag3)
    {
        Car_direction(LEFT);
    }
    Car_direction(STOP);
}


/* This function continues the car's movement forward until the flag1 is set.
 It increments the steps counter to keep track of the number of steps taken.*/
void Car_Continue(void)
{

    flag1 = 0;
    Timer_Counter = 0;

    while (!flag1)
    {
        Car_direction(FORWORD);
    }
    Car_direction(STOP);
    steps++;
}
