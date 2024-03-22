#include "stm32f303xe.h"
#include "utility.h"
#include "UART.h"
#include "ultraSonic.h"


#include "stm32f303xe.h"
#include "utility.h"

// Global variable to store the ultrasonic pulse width
uint32_t ultrasonic_pulse_width = 0;



void UltraSonic_Init(void)
{
// Ultrasonic Sensor Interrupt Mode - Lab 5

// In this lab, we will design a complete ultrasonic sensor control module that:
//        1. Automatically trigger the Ultrasonic Sensor every 100ms - 500ms (your choice)

//  2. For every Echo detected through interrupt on falling edge, calculate and update the 
//          measured distance.

// As described in class, an Ultrasonic Sensor will require two timers:
//  1. Trigger-Generation Timer (OCM on PWM mode, 10us PW, 100ms period)
//      Recommended Pin - PA.12 TIM 16 - Output CH1
//
//  2. Echo Measurement Timer (ICM on Slave Mode - Rising Edge Reset, Falling Edge Capture)
//      Recommended Pin - PC.7 TIM 3 - Input CH2




//  Part I - Configure Timer 16 CH1 as Trigger-Generation Timer

//  I.1 Configure GPIO Pin
//                  Enable GPIOA, set PA12 to AF - TIM16 CH1, Push-Pull, and no pull-up or pull-down.
																//enable timer 16
																RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
																
																GPIO_MODER_SET(A,12,GPIO_MODER_AF);//GPIOA->MODER &= 
																FORCE_BITS(GPIOA->AFR[0], (0xFUL << 12), (2UL << 12));
																GPIO_OTYPER_SET(A, 12, OTYPER_PP);
																GPIO_PUPDR_SET(A, 12, PUPDR_NP);
//  I.2 Configure TIM16
//      a) Turn on clock for TIM16
                                 SET_BITS(RCC->APB2ENR, RCC_APB2ENR_TIM16EN);
//    **b) Set the PSC so TIM16 counts in 1us - 10us unit (your design choice)
                                 TIM16->PSC = SystemCoreClock / 1000000 - 1;
//      c) Set the TIM16 counting direction to upcounting
//ONLY UPCOUNTS
//    **d) Set the ARR to 100ms - 500ms (your choice)
                                 TIM16->ARR = 100000 - 1;
//      e) Enable ARR preload (ARPE) in CR1
                                 SET_BITS(TIM16->CR1, TIM_CR1_ARPE); 
//      f) Set main output enabled (MOE) in BDTR
                                 SET_BITS(TIM16->BDTR, TIM_BDTR_MOE);
//  I.3 Configure TIM16 Channel 1 for OCM with PWM
//                  a) Set TIM16 CH1 to be PWM mode 1 through (OC1M) in CCMR1
                                 CLEAR_BITS(TIM16->CCMR1, TIM_CCMR1_OC1M);
                                 
                                 TIM16->CCMR1 |= 1UL << 5;
                                 TIM16->CCMR1 |= 1UL << 6;
//      b) Enable the Output Compare Preload on CH1 (we will update CCR1 only upon UE) through setting (OC1PE) on CCMR1
                                 SET_BITS(TIM16->CCMR1, TIM_CCMR1_OC1PE);
//      c) Enable the Regular Ouptut Channel for CH1 by setting (CC1E) in CCER
                                 SET_BITS(TIM16->CCER, TIM_CCER_CC1E);
//      d) Make CH1 active HI through CLEARING (CC1P) in CCER
                                 CLEAR_BITS(TIM16->CCER, TIM_CCER_CC1P);
//    **e) Set CH1 CCR1 initial output waveform on-time for 10us PWM pulse width
//                      -> Calculate the CCR1 value based on your ARR value!
                                 TIM16->CCR1 = 100;
//  I.4 Configure TIM16 CH1 for PWM - **REPEATING MODE**
//                  a) Force an update event to preload all the registers by setting (UG) in EGR
//    **b) !! DO NOT !! enable TIM16 here.
//         ** We will start the timer from the mainline function call!
                                 SET_BITS(TIM16->EGR, TIM_EGR_UG); 


// Part II  Interface Function - Start Automatic Triggering
//   Main program will call this function to start periodic trigger on ultrasonic sensor
//   a) Enable the TIM16 by setting CEN in CR1
                                // 
				//CALL HELPER FUNCTION
				us_STRTRIG();


// Part III - Configure Timer 3 CH2 as Edge-Measurement Timer

//  III.1 Configure GPIO Pin
//                  Enable GPIOC, set PC7 to AF for TIM3 CH2, no pull-up / pull-down.
//      ** read the ref manual to confirm the AF selection for TIM3 Input Channel 2 (TI2 == TIM3 Input CH2)
				ENABLE_CLOCKx(C);
				GPIO_MODER_SET(C,7,GPIO_MODER_AF);
				GPIO_PUPDR_SET(C,7,GPIO_PUPD_NO);
				GPIO_AFRH(C,7,1UL);

//double check here down
//  III.2 Configure TIM3 Timer Input Channel 2 (TI2)
				
//       // a) Turn on clock for TIM3
					SET_BITS(RCC->APB1ENR, RCC_APB1ENR_TIM3EN);
					// b) Set the PSC so TIM3 counts in us
					TIM3->PSC = SystemCoreClock / 1000000 - 1;
					// c) Set TIM3 counting direction to upcounting
					CLEAR_BITS(TIM3->CR1, TIM_CR1_DIR);
					// d) Set ARR to MAXIMUM possible value (i.e., 0xFFFF)
					TIM3->ARR = 0xFFFF;
//      e) Set TIM3 TI2 with No Input Filtering to start with, by CLEARING all 4 bits of (IC2F[3:0]) in CCMR1
//                             ** read the manual!!! (you may want to increase the filtering in the future, and you need to know how to set it)
				CLEAR_BITS(TIM3->CCMR1, TIM_CCMR1_IC2F);
//      f) Set TI2 Prescaler to ZERO to capture every valid transition event.  This can be done by CLEARING both bits in
//         (IC2PSC[1:0]) in CCMR1
//          ** read the reference manual for more detail
//          Simple Ver.: Prescaler to 1 => only use EVERY OTHER event as valid event
				CLEAR_BITS(TIM3->CCMR1, TIM_CCMR1_IC2PSC);	

			// III.3 Configure TIM3 CCR1 for PW measurement on TI2
			// a) Make sure TIM3 TI2 is connected internally to CCR1, so Echo signal falling edge from PC7 can be measured
			// and captured by the timer.
			// This is done by setting (CC1S) in CCMR1 to selection 2
			FORCE_BITS(TIM3->CCMR1, TIM_CCMR1_CC1S, 0x01 << 0); 
			// b) Set TIM3 CCR1 to capture TI2 falling edge by setting (CC1P) and clearing (CC1NP) in CCER
			SET_BITS(TIM3->CCER, TIM_CCER_CC1P);
			CLEAR_BITS(TIM3->CCER, TIM_CCER_CC1NP);

			// III.4 Configure TIM3 to Slave Reset on TI2 Rising Edge
			// a) Select Filtered Input Timer 2 (TI2) as the trigger source of the Timer Reset
			// Done by setting (TS[3:0]) in SMCR to 6
			FORCE_BITS(TIM3->SMCR, TIM_SMCR_TS, 0x06 << 0); //didnt set
			// b) Select RESET slave mode on TI2 Rising Edge, done by writing 4 into (SMS[2:0]) in SMCR
			FORCE_BITS(TIM3->SMCR, TIM_SMCR_SMS, 0x04 << 0);

			// III.5 Enable Counter Capture
			// a) Enable Counter Capture by setting (CC1E and CC2E) in CCER
			SET_BITS(TIM3->CCER, TIM_CCER_CC1E);

			// III.6 ** ENABLE TIM3 INTERRUPT on TI2 Falling Edge **
			// a) Enable TIM3 TI2 to generate interrupt request by setting (CC1IE) in DIER
			SET_BITS(TIM3->DIER, TIM_DIER_CC1IE);
			// b) Set TIM3 IRQ priority to something high (somewhere smaller than 10, your choice) in NVIC
			NVIC_SetPriority(TIM3_IRQn, 5);               
			// c) Enable TIM3 IRQ in NVIC
			NVIC_EnableIRQ(TIM3_IRQn);
			// d) Enable TIM3 main counter by setting (CEN) in CR1
			SET_BITS(TIM3->CR1, TIM_CR1_CEN);

}





// Part IV - Echo Pulse Width Measurement Interface Functions
//    **a) TIM3 IRQ Handler ** KEEP IT COMPUTATIONALLY SHORT!! **
//                             Check whether (CC1IF) in SR is set
//                                        If yes, record TIM3 CCR1 value in a global variable for further processing
//                                                              ** you may optionally toggle green LED for visual ISR execution confirmation **
//                             If no, do nothing

			// a) TIM3 IRQ Handler
		void TIM3_IRQHandler(void)
		{
				if (IS_BIT_SET(TIM3->SR, TIM_SR_CC1IF))
				{
						// Record TIM3 CCR1 value in a global variable for further processing
						ultrasonic_pulse_width = TIM3->CCR1;

						// Optionally toggle a green LED for visual ISR execution confirmation
						// Assuming the green LED is connected to, for example, GPIOB pin 0
						FLIP_BITS(GPIOB->ODR, 1UL << 0);

						// Clear the CC1 interrupt flag
						CLEAR_BITS(TIM3->SR, TIM_SR_CC1IF);
				}
		}


//                  b) READ_SENSOR function - Call this from mainline to get distance measurements whenever!
//                   - read the global variable (Critical Section, put Mutual Exclusion!)
//                             - Design Choice:
//                                        1. Return the global variable value and let the main program do the calculation, OR
//                                        2. Do the count-to-distance calculation and return the calculated value back to the main program.



//  If you've configured everything above correctly, you should be able to do this in the main control loop:
//                  - Check Distance Measurement through Read Sensor function whenever needed!


int ReadSensor(void)
{
  //  TIM3_IRQHandler();
    // Return the recorded pulse width
	//ultrasonic_pulse_width;
    int USDistance = ultrasonic_pulse_width / 59;
		return USDistance;
}


void us_STRTRIG(void){
	SET_BITS(TIM16->CR1, TIM_CR1_CEN);
}


