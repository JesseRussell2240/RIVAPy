//main to test Servo PWM signal genoration
//Code is part of lab 3 for embeded software systems
//Jesse Russell 25 jan 2024

#include "Servo.h"
// RC Servo Skeleton


//array to hold current angles of all servos.
int16_t servoAngles[NUM_SERVOS] = {0};


void Servo_Init(void)
{

				// Set up PB15 to Output, AF1, PP, no Pull
	// 1. Enable clock to Port B
	SET_BITS(RCC->AHBENR, RCC_AHBENR_GPIOBEN);
	// 2. Set the MODER to AF
	GPIO_MODER_SET(B, 15, 2);
	// 3. Set the AFR..([0] or [1]?) to AF1 for PB15
	FORCE_BITS(GPIOB->AFR[1], (0xFUL << 28), (1UL << 28));
	// 4. Set the OTYPER to Push-Pull
	GPIO_OTYPER_SET(B, 15, OTYPER_PP);
	// 5. Set the PUPDR to no pull
	GPIO_PUPDR_SET(B, 15, 0);

	// Configure TIM15
	// 1. Turn on TIM15 by feeding in the APB clock. (set RCC_APB2ENR_TIM15EN in RCC->APB2ENR)
	SET_BITS(RCC->APB2ENR, RCC_APB2ENR_TIM15EN);
	// 2. Program the prescaler (PSC) to ensure TIM15 counts at 1us
	TIM15->PSC = TIM15_PRESCALER_VALUE;
	// 4. Set TIM15 to Upcounting (no need to do it, because TIM15 only knows upcounting...) ***OPTIONAL***
	// 5. Set the ARR to 20000 us period
	TIM15->ARR = 20000 - 1;
	// 6. Enable TIM15 ARR Preload (ARPE flag on CR1)
	SET_BITS(TIM15->CR1, TIM_CR1_ARPE);
	// 7. Enable TIM15 main output, so to make it available to the PWM OC (MOE flag on BDTR)
	SET_BITS(TIM15->BDTR, TIM_BDTR_MOE);

	// Configure CH2 of TIM15 for PWM OC mode
	// 1. Select PWM mode 1 (low-count mode) for TIM15 CH2 (OC2M flags - 2 bits - on CCMR1)
	FORCE_BITS(TIM15->CCMR1, TIM_CCMR1_OC2M, (6UL << TIM_CCMR1_OC2M_Pos));
	// 2. Enable the Output Compare Preload on CH2 (OC2PE flag on CCMR1)
	SET_BITS(TIM15->CCMR1, TIM_CCMR1_OC2PE);
	// 3. Enable output channel 2 (CH2 with no negate) - (CC2E flag on CCER)
	SET_BITS(TIM15->CCER, TIM_CCER_CC2E);
	// 4. Make CH2 Active Hi (no negate) - (CC2P flag on CCER)
	CLEAR_BITS(TIM15->CCER, TIM_CCER_CC2P);
	// 5. Set CH2 PWM initial on-time to 0, so PWM will not output anything before preload is done (writing 0 into CCR2)
	TIM15->CCR2 = 0;

	// Set TIM15 off!
	// 1. Force and Update Event to ensure all preload operations are done in sync! (UG flag on EGR)
	SET_BITS(TIM15->EGR, TIM_EGR_UG);
	// 2. Enable TIM15 Counting! (CEN flag on CR1)
	SET_BITS(TIM15->CR1, TIM_CR1_CEN);
	
	    // Set up PC0 to PC3 to Output, AF1, PP, no Pull
    // 1. Enable clock to Port C
    SET_BITS(RCC->AHBENR, RCC_AHBENR_GPIOCEN);
    // 2. Set the MODER to AF
    GPIO_MODER_SET(C, 0, 2);
    GPIO_MODER_SET(C, 1, 2);
    GPIO_MODER_SET(C, 2, 2);
    GPIO_MODER_SET(C, 3, 2);
    // 3. Set the AFR to AF1 for PC0 to PC3		//this needs to be AF2
    FORCE_BITS(GPIOC->AFR[0], (0xFUL << 0), (2UL << 0));
    FORCE_BITS(GPIOC->AFR[0], (0xFUL << 4), (2UL << 4));
    FORCE_BITS(GPIOC->AFR[0], (0xFUL << 8), (2UL << 8));
    FORCE_BITS(GPIOC->AFR[0], (0xFUL << 12), (2UL << 12));
    // 4. Set the OTYPER to Push-Pull
    GPIO_OTYPER_SET(C, 0, OTYPER_PP);
    GPIO_OTYPER_SET(C, 1, OTYPER_PP);
    GPIO_OTYPER_SET(C, 2, OTYPER_PP);
    GPIO_OTYPER_SET(C, 3, OTYPER_PP);
    // 5. Set the PUPDR to no pull
    GPIO_PUPDR_SET(C, 0, 0);
    GPIO_PUPDR_SET(C, 1, 0);
    GPIO_PUPDR_SET(C, 2, 0);
    GPIO_PUPDR_SET(C, 3, 0);

    // Configure TIM1
    // 1. Turn on TIM1 by feeding in the APB clock (set RCC_APB2ENR_TIM1EN in RCC->APB2ENR)
    SET_BITS(RCC->APB2ENR, RCC_APB2ENR_TIM1EN);
    // 2. Program the prescaler (PSC) to ensure TIM1 counts at 1us
    TIM1->PSC = TIM15_PRESCALER_VALUE;
    // 3. Set TIM1 to Upcounting (no need to do it, because TIM1 only knows upcounting...) ***OPTIONAL***
		//set bit 4 to 0 to ensure upcounting'
		
		CLEAR_BITS(TIM1->CR1, TIM_CR1_CMS);  // Ensure upcounting
		//set alighnment ot edge align piro to setting to upcount
    // 4. Set the ARR to 20000 us period
    TIM1->ARR = 20000 - 1;
    // 5. Enable TIM1 ARR Preload (ARPE flag on CR1)
    SET_BITS(TIM1->CR1, TIM_CR1_ARPE);
    // 6. Enable TIM1 main output, so to make it available to the PWM OC (MOE flag on BDTR)
    SET_BITS(TIM1->BDTR, TIM_BDTR_MOE);

    // Configure CH1 to CH4 of TIM1 for PWM OC mode

        
						
		// Configure CH1 to CH4 of TIM1 for PWM OC mode
		// Servo 0 (TIM1_CH1)
		
		// Configure CH1 to CH4 of TIM1 for PWM OC mode
		FORCE_BITS(TIM1->CCMR1, TIM_CCMR1_OC1M, (6UL << TIM_CCMR1_OC1M_Pos));
		// Enable the Output Compare Preload on CH1 to CH4 (OC1PE to OC4PE flags on CCMR1)
		SET_BITS(TIM1->CCMR1, TIM_CCMR1_OC1PE);
		SET_BITS(TIM1->CCER, TIM_CCER_CC1E);
		CLEAR_BITS(TIM1->CCER, TIM_CCER_CC1P);
		TIM1->CCR1 = 0;

		// Servo 1 (TIM1_CH2)
		FORCE_BITS(TIM1->CCMR1, TIM_CCMR1_OC2M, (6UL << TIM_CCMR1_OC2M_Pos));
		SET_BITS(TIM1->CCMR1, TIM_CCMR1_OC2PE);
		SET_BITS(TIM1->CCER, TIM_CCER_CC2E);
		CLEAR_BITS(TIM1->CCER, TIM_CCER_CC2P);
		TIM1->CCR2 = 0;

		// Servo 2 (TIM1_CH3)
		FORCE_BITS(TIM1->CCMR2, TIM_CCMR2_OC3M, (6UL << TIM_CCMR2_OC3M_Pos));
		SET_BITS(TIM1->CCMR2, TIM_CCMR2_OC3PE);
		SET_BITS(TIM1->CCER, TIM_CCER_CC3E);
		CLEAR_BITS(TIM1->CCER, TIM_CCER_CC3P);
		TIM1->CCR3 = 0;

		// Servo 3 (TIM1_CH4)
		FORCE_BITS(TIM1->CCMR2, TIM_CCMR2_OC4M, (6UL << TIM_CCMR2_OC4M_Pos));
		SET_BITS(TIM1->CCMR2, TIM_CCMR2_OC4PE);
		SET_BITS(TIM1->CCER, TIM_CCER_CC4E);
		CLEAR_BITS(TIM1->CCER, TIM_CCER_CC4P);
		TIM1->CCR4 = 0;
		
    // Set TIM1 off!
    // 1. Force and Update Event to ensure all preload operations are done in sync! (UG flag on EGR)
    SET_BITS(TIM1->EGR, TIM_EGR_UG);
    // 2. Enable TIM1 Counting! (CEN flag on CR1)
    SET_BITS(TIM1->CR1, TIM_CR1_CEN);
	
}


uint16_t Servo_SetAngle(int16_t servoIndex, int16_t angle){
	    // 1. Convert the target angle to the corresponding target Pulse Width (1 degree angle maps to ~ 10us step)
    uint16_t targetPW = 1500 + angle * 10;
	
	
		//if((angle - servoAngles[servoIndex]) > 10 ||( angle - servoAngles[servoIndex]) < 10){
		//	Servo_SetAngle(servoIndex, angle - 10);
		//	angle = angle - 10;
			
		//}
	
			//this loop needs limits set for each axsis and any potential collision zones as a saftey factor.
	//these limits are +/- 100 deg
    if (targetPW < 800) {
        targetPW = 800; 
    } else if (targetPW > 2100) {
        targetPW = 2100; 
    }
		
   switch (servoIndex) {
        case 4:  // Gripper
            TIM15->CCR2 = targetPW;
            servoAngles[servoIndex] = angle;
						
            break;

        case 0:  // Servo 0 using TIM1 and PC0
            TIM1->CCR1 = targetPW;
            servoAngles[servoIndex] = angle;
            break;

        case 1:  // Servo 1 using TIM1 and PC1
            TIM1->CCR2 = targetPW;
            servoAngles[servoIndex] = angle;
            break;

        case 2:  // Servo 2 using TIM1 and PC2
            TIM1->CCR3 = targetPW;
            servoAngles[servoIndex] = angle;
            break;

        case 3:  // Servo 3 using TIM1 and PC3
            TIM1->CCR4 = targetPW;
            servoAngles[servoIndex] = angle;
            break;

        default:
            // Handle invalid servoIndex or add additional cases if needed
            break;
    }

    return targetPW;
}




int16_t Servo_GetAngle(int servoIndex) {
    // Return the current angle of the specified servo
    return servoAngles[servoIndex];
}
