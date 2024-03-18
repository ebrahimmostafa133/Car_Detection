/*
 * mines_detector.h
 *
 *  Created on: march 16, 2024
 *      Author: Ebrahim Mostafa
 */

#ifndef INC_MINES_DETECTOR_H
#define INC_MINES_DETECTOR_H

#include "StdTypes.h"
#include "Delay.h"
#include "Dio.h"
#include "Fcpu.h"




extern u16 Timer_Counter;
extern u8  Detected_Mine;

extern u16 i;

extern u8 flag1;
extern u8 flag2;
extern u8 flag3;

typedef enum
{
	STOP,
	FORWORD,
	BACKWORD,
	RIGHT,
	LEFT,
}Car_direction_type;

typedef enum
{
	ROUND_RIGHT,
	ROUND_LEFT
}Round_type;


void Car_direction(Car_direction_type direction);
void Car_Detected(void);
void Car_Round (Round_type Round);




#define IN1    DIO_PORTD,DIO_PIN0
#define IN2    DIO_PORTD,DIO_PIN1
#define IN3    DIO_PORTD,DIO_PIN2
#define IN4    DIO_PORTD,DIO_PIN3

#define IR	   DIO_PORTC,DIO_PIN0
#define BUZZ   DIO_PORTD,DIO_PIN7


#endif /* INC_MINES_DETECTOR_H */
