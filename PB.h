#ifndef PB_H
#define PB_h

#include "stm32f303xe.h"
#include "Utility.h"


#define DEBOUNCE_LIMIT 17
#define DEBOUNCE_DELAY_MS 250


void PB_Init(void);
uint8_t PB_Pressed(void);
void debounce(void);

#endif

