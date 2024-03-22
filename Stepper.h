
#ifndef __STEPPER_H
#define __STEPPER_H

#include "stm32f303xe.h"
#define STEPPER_STEP_STOP 0
#define STEPPER_STEP_CW_HALF 1
#define STEPPER_STEP_CCW_HALF -1
#define STEPPER_STEP_CW_FULL 2
#define STEPPER_STEP_CCW_FULL -2

#define STEP_INDEX_MASK 0x07

// Define statements for stepper motor control modes
#define FULL_STEP_CW  0x01   // Full step in Clockwise direction
#define FULL_STEP_CCW 0x02   // Full step in Counter-Clockwise direction
#define HALF_STEP_CW  0x03   // Half step in Clockwise direction
#define HALF_STEP_CCW 0x04   // Half step in Counter-Clockwise direction

#define ARRAY_SIZE 8


static int currentStepIndex = 0;
static int count;
static int stepPatternArray[ARRAY_SIZE] = {1,5,4,6,2,10,8,9};



void Stepper_init(void);
void Update_stepper_Pattern(int stepType);

#endif

