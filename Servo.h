//main to test Servo PWM signal genoration
//Code is part of lab 3 for embeded software systems
//Jesse Russell 25 jan 2024

#ifndef SERVO_H
#define SERVO_H

#include "stm32f303xe.h"
#include "Utility.h"

// Constants

#define TIM15_PRESCALER_VALUE 71   // Considering 72MHz System Clock
#define TIM1_PRESCALER_VALUE 71   // Considering 72MHz System Clock
#define TIM15_PERIOD_US 20000     // 20ms 
#define TIM15_NEUTRAL_ANGLE 1500   // Neutral position (1.5ms pulse width)
#define TIM15_MAX_ANGLE 90         // Maximum allowed angle (+90 degrees)
#define TIM15_MIN_ANGLE -90        // Minimum allowed angle (-90 degrees)
#define SWEEP_DELAY_MS 10 					// delay on each set when stepping to new angeles

#define NUM_SERVOS 6 // 

// Function prototypes
void Servo_Init(void);
void Servos_Init(void);
uint16_t Servo_SetAngle(int16_t servoIndex, int16_t angle);
int16_t Servo_GetAngle(int servoIndex);
int16_t Servo_setTarget(int16_t servoIndex, int16_t targetAngle, uint16_t steps, uint16_t delayBetweenSteps);
void Servo_SetAngles(int16_t angle1, int16_t angle2, int16_t angle3, int16_t angle4, int16_t angle5);


#endif  // RCSERVO_H
