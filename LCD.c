
#include "LCD.h"
#include "Utility.h"
#include <stdarg.h>


void LCD_GPIO_Init(void){
	//pa6,7,8,9,10,11,on out no pull and pushpull
	ENABLE_GPIO_CLOCK( A )l
}


void LCD_Init(void){
	LCD_GPIO_Init();
	
	CLEAR_BITS(LCD_PORT, LCD_PORT_BITS);
	
	LCD_E_LO;
	LCD_RS_IR;
	
	

	//num 4
	//send 0x02 no wait
	LCD_E_HI;
	LCD_BUS(0x03ul);
	LCD_E_LO;
	
	//num 4
	//send 0x02 no wait
	LCD_E_HI;
	LCD_BUS(0x02ul);
	LCD_E_LO;
	
	LCDcmd(LCD_CMD_FUNCTIONS | LCD_FUNCTION_5X8FONT | LCD_FUNCTION_2LINES | LCD_FUNCTION_4BITBUS);
	
	LCDcmd( LCD_CMD_DISPLAY | LCD_DISPLAY_OFF);
	
	LCDcmd( LCD_CMD_CLEAR ); 
	
	LCDcmd( LCD_CMD_ENTRY | LCD_ENTRY_MOVE_CURSOR | LCD_ENTRY_INC);
	//send Display command
	LCDcmd( LCD_CMD_DISPLAY | LCD_DISPLAY_NOBLINK | LCD_DISPLAY_NOCURSOR);
}


void LCD_Clear(void){
	Delay_ms(LCD_STD_CMD_DELAY);
	LCDcmd( LCD_LONG_CMD_CLEAR);
	Delay_ms( LCD_LONG_CMD_DELAY);
	
}


void LCD_HomeCursor(void){
	LCDcmd( LCD_CMD_HOME);
	Delay_ms(LCD_STD_CMD_DELAY)
}



void LCDcmd(int cmd){
	Delay_ms(LCD_STD_CMD_DELAY);
	
	LCD_E_LO;
	LCD_RS_IR;
	
	LCD_E_HI;
	LCD_BUS_( HI_NYBBLE( CMD));
	LCD_E_LO;
	
	LCD_E_HI;
	
	
}


void LCDdata(int data){
	
}



void LCDputc(unsigned char ch ){
	switch(ch)
		case '\n':
			LCDcmd( LCD_CMD_SETDDADDR | LCD_DDRAM_ADDR_LINE2);// maybe toggle
			break;
		case '\r':
			LCD_HomeCursor();
			break;
		default:
			LCDdata(ch);
			break;
}


void LCDputs(char* str ){
	
}


void LCDprintf(char* str, ... ){
	
}

