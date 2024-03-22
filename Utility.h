#ifndef UTILITY_H
#define UTILITY_H

// Macros
#define GPIOx(port) GPIO ## port

//clocks
#define CLOCKx(port) RCC_AHBENR_GPIO ## port ## EN
#define ENABLE_CLOCKx(port) (((RCC->AHBENR)) |= (CLOCKx(port)))


#define PUPDR_NP  0x0  // No Pull
#define PUPDR_PU  0x1  // Pull-up
#define PUPDR_PD  0x2  // Pull-down


// Bit manipulation macros
#define SET_BITS(port, mask) ((port) |= (mask))
#define CLEAR_BITS(port, mask) ((port) &= (~(mask)))
#define FLIP_BITS(port, mask) ((port) ^= (mask))
#define FORCE_BITS(port, mask, value) ((port) = ((port) & ~(mask)) | ((value) & (mask)))
#define IS_BIT_SET(port, bit) (((port) & (1UL << (bit))) != 0)
#define IS_BIT_CLEAR(port, bit) (((port) & (1UL << (bit))) == 0)

//AF

// GPIO mode macros
#define GPIO_MODER_SET(port, pin, mode) \
    FORCE_BITS(GPIOx(port)->MODER, (3UL << ((pin) * 2)), ((mode) << ((pin) * 2)))

#define GPIO_AFRL(port,pin,type) FORCE_BITS(GPIOx(port)-> AFR[0], (0xFUL << ((pin)*4)), ((type)<<((pin)*4)))
#define GPIO_AFRH(port,pin,type) FORCE_BITS(GPIOx(port)-> AFR[1], (0xFUL << ((pin)*4)), ((type)<<((pin)*4)))

#define GPIO_OTYPER_SET(port, pin, type) \
    FORCE_BITS(GPIOx(port)->OTYPER, (1UL << (pin)), ((type) << (pin)))


#define GPIO_PUPDR_SET(port, pin, mode) \
    FORCE_BITS(GPIOx(port)->PUPDR, (3UL << ((pin) * 2)), ((mode) << ((pin) * 2)))


#define GPIO_OSPEEDR_SET(port, pin, speed) \
    FORCE_BITS(GPIOx(port)->OSPEEDR, (3UL << ((pin) * 2)), ((speed) << ((pin) * 2)))



// Additional constants
#define OTYPER_PP 0UL
#define OTYPER_OD 1UL
#define GPIO_MODER_AF 2UL
#define GPIO_PUPD_NO 0UL

// Delay function
void Delay_ms(int msec);

// Implementation of customAtoi function
int Atoi(const char* str) ;

#endif
