/*
 * mines_detector.h
 *
 *  Created on: March 16, 2024
 *      Author: Ebrahim Mostafa
 */

#ifndef INC_MINES_DETECTOR_H
#define INC_MINES_DETECTOR_H

#include "StdTypes.h"  // Include for standard types
#include "Dio.h"       // Include for Digital I/O functionality
#include "Registers.h" // Include for register definitions

extern u16 Timer_Counter; // External variable for timer counter
extern u8 Detected_Mine;  // External variable for detected mine

extern u16 i;             // External variable for 'i'
extern u8 flag1;          // External variable for 'flag1'
extern u8 flag2;          // External variable for 'flag2'
extern u8 flag3;          // External variable for 'flag3'

extern u8 steps;          // External variable for 'steps'
extern u8 Total_Steps;    // External variable for total steps

typedef enum
{
    STOP,
    FORWORD,
    BACKWORD,
    RIGHT,
    LEFT,
} Car_direction_type; // Enumeration type for car directions

typedef enum
{
    ROUND_RIGHT,
    ROUND_LEFT
} Round_type; // Enumeration type for round movements

void Car_Init(void);                              // Function prototype for car initialization
void Car_direction(Car_direction_type direction); // Function prototype for setting car direction
void Car_Detected(void);                          // Function prototype for handling detected mine
void Car_Round(Round_type Round);                 // Function prototype for performing round movement
void Car_Continue(void);                          // Function prototype for continuing car operation
void Car_Draft(void);                             // Function prototype for car drafting

#define IN1    DIO_PORTD, DIO_PIN0                // Macro definition for IN1 pin
#define IN2    DIO_PORTD, DIO_PIN1                // Macro definition for IN2 pin
#define IN3    DIO_PORTD, DIO_PIN2                // Macro definition for IN3 pin
#define IN4    DIO_PORTD, DIO_PIN3                // Macro definition for IN4 pin

#define IR     DIO_PORTC, DIO_PIN0                // Macro definition for IR pin
#define BUZZ   DIO_PORTD, DIO_PIN7                // Macro definition for BUZZ pin

#endif /* INC_MINES_DETECTOR_H */
