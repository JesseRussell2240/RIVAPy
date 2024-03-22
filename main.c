//main to test Servo PWM signal genoration
//Code is part of lab 3 for embeded software systems
//Jesse Russell 25 jan 2024

#include "stm32f303xe.h"
#include "SysClock.h"
#include "UART.h"
#include "Utility.h"
#include "Stepper.h"
#include "Servo.h"
#include "UltraSonic.h"




int main(void){

	//initilie and update core clocks to ensure frequency
	System_Clock_Init();
	SystemCoreClockUpdate();
	
	UltraSonic_Init();
	
	//calls initiliations of helper files
	UART2_Init();
	//Stepper_init();
	Servo_Init();
//	SET_BITS(TIM16->CR1, TIM_CR1_CEN);
	// Set all servos to 0 deg  before loop
    for (int16_t i = 0; i < NUM_SERVOS; ++i) {
        Servo_SetAngle(i, 0);
    }
	
	
	  //  int degrees[NUM_SERVOS];
	for(;;){
 
       // Get user input for servo number
        UARTprintf("Enter servo number (0-5): ");
		//UARTprintf("Distance: %d", ReadSensor());
		
        int servoNumber = UARTgetc() - '0';  // Convert char to integer
       

        // Get user input for degree
        UARTprintf("Enter degree (-90 to 90): ");
        int degree = UARTgetc()  - '0';  // Convert string to integer
       // degree

        // Set the angle of the specified servo
        Servo_SetAngle(servoNumber, (degree * 10));
		
			//	Servo_SetAngle(servoNumber, ((degree * 10)));
		
		//this is for RIVA
 // Get user input for degrees
		/*
		
		
        char inputBuffer[MAX_UART_BUFSIZ];
        UARTprintf("Enter degrees for servos (comma-separated, e.g., 0,45,90,-45,-90,100): ");
        UARTgets(inputBuffer, MAX_UART_BUFSIZ);

        // Parse the comma-separated values and store them in the degrees array
        int num = sscanf(inputBuffer, "%d,%d,%d,%d,%d,%d",
                           &degrees[0], &degrees[1], &degrees[2],
                           &degrees[3], &degrees[4], &degrees[5]);

        if (num != NUM_SERVOS) {
            UARTprintf("Invalid input. Please enter values for all %d servos.\n", NUM_SERVOS);
            continue;  // Skip the rest of the loop and start over
        }

        // Set the angles of the servos
        for (int i = 0; i < NUM_SERVOS; ++i) {
            Servo_SetAngle(i, degrees[i]);
        }
				
				*/
		//end of for RIVA
			
	
}
}
