
#include "SysClock.h"
#include "Utility.h"

void Delay_ms(int msec){
    SysTick->CTRL = 0;                        		    // Disable Timer + SysTick interrupt + default AHB/8 clock + clear CountFlag (how?)
    SysTick->LOAD = ((SystemCoreClock /8) / 1000UL) * msec; 	// Set reload register (like BRR)
    SysTick->VAL = 0;             	    			// Reset the SysTick counter value
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk; 		// Start SysTick. Use AHBclock/8
    while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)); 	// Wait for timeout
    SysTick->CTRL = 0;                       		// Disable SysTick until next time
 }

 // Implementation of customAtoi function
int Atoi(const char* str) {
    int result = 0;
    int sign = 1;
    int i = 0;

    // Handle negative sign
    if (str[0] == '-') {
        sign = -1;
        i = 1;
    }

    // Process each digit in the string
    while (str[i] != '\0') {
        result = result * 10 + (str[i] - '0');
        ++i;
    }

    return sign * result;
}