
#include "stm32f303xe.h"
#include "UART.h"
#include "PB.h"

// Declare global variables
int rowNum;
int colNum;
uint8_t debounceCounter = 0;


char charTable[4][4] = {{'1', '2', '3', 'A'},
                        {'4', '5', '6', 'B'},
                        {'7', '8', '9', 'C'},
                        {'*', '0', '#', 'D'}};


// Initialize matrix keypad
void PB_Init(void) {
    // Configure the necessary GPIO pins for rows and columns
    // For example, if using PB0-PB3 for rows and PC4-PC7 for columns
    // Configure PB0-PB3 as outputs and PC4-PC7 as inputs
	
	// Enable clock for Port B and Port C
    SET_BITS(RCC->AHBENR, RCC_AHBENR_GPIOBEN);
    SET_BITS(RCC->AHBENR, RCC_AHBENR_GPIOCEN);

    // Configure rows (PB0-PB3) as outputs
    GPIO_MODER_SET(B, 0, 1);  // Row 1
    GPIO_MODER_SET(B, 1, 1);  // Row 2
    GPIO_MODER_SET(B, 2, 1);  // Row 3
    GPIO_MODER_SET(B, 3, 1);  // Row 4

    // Configure columns (PC4-PC7) as inputs
    GPIO_MODER_SET(C, 4, 0);  // Column 1
    GPIO_MODER_SET(C, 5, 0);  // Column 2
    GPIO_MODER_SET(C, 6, 0);  // Column 3
    GPIO_MODER_SET(C, 7, 0);  // Column 4

    // Set rows to default high (inactive)
    SET_BITS(GPIOB->ODR, (0xFUL << 0));  // PB0-PB3 high
		
		GPIO_PUPDR_SET(B, 0, PUPDR_NP);
		GPIO_PUPDR_SET(B, 1, PUPDR_NP);
		GPIO_PUPDR_SET(B, 2, PUPDR_NP);
		GPIO_PUPDR_SET(B, 3, PUPDR_NP);
		GPIO_PUPDR_SET(B, 4, PUPDR_PU);
		GPIO_PUPDR_SET(B, 5, PUPDR_PU);
		GPIO_PUPDR_SET(B, 6, PUPDR_PU);
		GPIO_PUPDR_SET(B, 7, PUPDR_PU);
		
		
		GPIO_OTYPER_SET(B,0,OTYPER_PP);
		GPIO_OTYPER_SET(B,0,OTYPER_PP);
		GPIO_OTYPER_SET(B,0,OTYPER_PP);
		GPIO_OTYPER_SET(B,0,OTYPER_PP);
		GPIO_OTYPER_SET(B,0,OTYPER_PP);
		GPIO_OTYPER_SET(B,0,OTYPER_PP);
		GPIO_OTYPER_SET(B,0,OTYPER_PP);
		GPIO_OTYPER_SET(B,0,OTYPER_PP);
	
}

// Scan for key presses
uint8_t PB_Pressed(void) {
	    // 1. Set r1 - r4 to 0 (write 0x0 into pb0-pb3)
    GPIOB->ODR &= ~(0x0FUL);

    // Reset the row and column numbers
    rowNum = -1;
    colNum = -1;

    // 2. Read c1-c4 (read upper nybble of pb - read pb 4-7)
    uint8_t colStatus = GPIOB->IDR >> 4;

    // If all columns are 1 (0xF), no key pressed
    if (colStatus == 0x0F) {
        return '\0';
    }

    // If not 0xF, convert colStatus to colNum
    switch (colStatus & 0x0F) {
        case 0x0E: 
					colNum = 0; 
				break;  // 0b1110
        case 0x0D: 
					colNum = 1; 
				break;  // 0b1101
        case 0x0B: 
					colNum = 2; 
				break;  // 0b1011
        case 0x07: 
					colNum = 3; 
				break;  // 0b0111
        default: return '\0';  // Invalid state
    }

	//	;
    // 3. Debounce (call helper function debounce())
    debounce();

 
       // 4. Row scanning
    for (int i = 0; i < 4; ++i) {
       // Set pb0-3 to the corresponding row pattern (0xE, 0xD, 0xB, 0x7)
			//Esebtually mask the lower 4 bits 
			//genorates the pattern of 0b1110, 0b1101 etc
			//then and the exsisting with the mask and or with rowPattern
        GPIOB->ODR = (GPIOB->ODR & 0xFFFFFFF0U) | ((0x0EU >> i) << 0);

        // Check if the corresponding column is 0 (key pressed)
        if (((GPIOB->IDR >> (colNum + 4)) & 0x01U) == 0) {
            rowNum = i;
            break;  // Key found, exit loop
        }
    }

    // After step 4, we have rowNum and colNum locked in
		//UARTprintf("colnum: %d", colNum);
	//	UARTprintf("Row: %d", rowNum);
    // Use colNum and rowNum to return the value stored in 2D array charTable
    if (rowNum != -1 && colNum != -1) {
		//	UARTprintf("key pressed, returning value: %c", charTable[rowNum][colNum]);
			
        return charTable[rowNum][colNum];
    } else {
        return '\0';  // Invalid state or no key pressed
    }
	
}

// Debounce function
void debounce(void) {
    // Option 1 - wait out the bounce (busy waiting is bad)
   // delay_ms(10);  // from utility.c

    // Option 2 - count the bounce out
    // Preferred option needs to develop and test algorithm
	// Debounce function

    // Option 2 - count the bounce out (preferred option, needs development and testing)
    debounceCounter++;
    
    // Check if the debounce limit is reached
    if (debounceCounter >= DEBOUNCE_LIMIT) {
        // Reset the counter and continue with further actions
        debounceCounter = 0;
    } else {
        // If not, delay for a short period
        Delay_ms(DEBOUNCE_DELAY_MS);
        return;
    }

}

