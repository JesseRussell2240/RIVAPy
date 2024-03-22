#include "Stepper.h"
#include "Utility.h"
#include "stm32f303xe.h"
#include "UART.h"



void Stepper_init(void){
	RCC -> AHBENR |= RCC_AHBENR_GPIOCEN; //enable GPIO port c clock
	
	GPIOC->MODER &= ~(0x3UL << (2*0));//clear both bits
	GPIOC->MODER |= ~(0x1UL << (2*0));//set 1 as output
	GPIOC->PUPDR &= ~(0x3UL << (2*0));//no pull
	GPIOC->OTYPER &= ~(0x1UL << 3); //pushpull
	
	
	GPIOC->MODER &= ~(0x3UL << (2*2));//clear both bits
	GPIOC->MODER |= ~(0x1UL << (2*2));//set 1 as output
	GPIOC->PUPDR &= ~(0x3UL << (2*2));//no pull
	GPIOC->OTYPER &= ~(0x1UL << 2); //pushpull

	GPIOC->MODER &= ~(0x3UL << (2*3));//clear both bits
	GPIOC->MODER |= ~(0x1UL << (2*3));//set 1 as output
	GPIOC->PUPDR &= ~(0x3UL << (2*3));//no pull
	GPIOC->OTYPER &= ~(0x1UL << 3); //pushpull

	
	
	//GPIO_OTYPER_SET(C, 0, OTYPER_PP);
	//GPIO_OTYPER_SET(C, 1, OTYPER_PP);
	//GPIO_OTYPER_SET(C, 2, OTYPER_PP);
	//GPIO_OTYPER_SET(C, 3, OTYPER_PP);
}

void Update_stepper_Pattern(int stepType){
	
	
	UARTprintf("Stepping: %d ,Type: %d ,Pattern: %d\n", count, stepType, stepPatternArray[count]);
	currentStepIndex += stepType;
	
	
    
    count += stepType;

    if (count >= ARRAY_SIZE) {
        count = 0;
    } else if (count < 0) { 
        count = ARRAY_SIZE - 1;
    }

    // Update GPIO outputs based on the pattern
		
    switch (count) {
        case 0:
					
				//case8
            GPIOC->ODR |= (1UL << 0);
            GPIOC->ODR &= ~(1ul << 1);
            GPIOC->ODR &= ~(1ul << 2);
            GPIOC->ODR &= ~(1ul << 3);
            break;
        case 1:
					
            GPIOC->ODR |= (1UL << 0);
            GPIOC->ODR &= ~(1UL << 1);
            GPIOC->ODR |= (1UL << 2);
            GPIOC->ODR &= ~(1UL<< 3);
            break;
        case 2:
            GPIOC->ODR &= ~(1UL << 0);
            GPIOC->ODR &= ~(1UL << 1);
            GPIOC->ODR |= (1UL << 2);
            GPIOC->ODR &= ~(1UL << 3);
            break;
        case 3:
            GPIOC->ODR &= ~(1UL << 0);
            GPIOC->ODR |= (1UL << 1);
            GPIOC->ODR |= (1UL << 2);
            GPIOC->ODR &= ~(1UL << 3);
            break;
        case 4:
            GPIOC->ODR &= ~(1UL << 0);
            GPIOC->ODR |= (1UL << 1);
            GPIOC->ODR &= ~(1UL << 2);
            GPIOC->ODR &= ~(1UL << 3);
            break;
        case 5:
            GPIOC->ODR &= ~(1UL << 0);
            GPIOC->ODR |= (1UL << 1);
            GPIOC->ODR &= ~(1UL << 2);
            GPIOC->ODR |= (1UL << 3);
            break;
				case 6:
            GPIOC->ODR &= ~(1UL << 0);
            GPIOC->ODR &= ~(1UL << 1);
            GPIOC->ODR &= ~(1UL << 2);
            GPIOC->ODR |= (1UL << 3);
            break;
        case 7:
            GPIOC->ODR |= (1UL << 0);
            GPIOC->ODR &= ~(1UL << 1);
            GPIOC->ODR &= ~(1UL << 2);
            GPIOC->ODR |= (1UL << 3);
            break;
    }
		
		
	
}

