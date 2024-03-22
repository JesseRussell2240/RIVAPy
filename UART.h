////////////////////
	//UART Module Header
	////////////////////
	
#ifndef _STM32F303RE_UART_E
#define _STM32F303RE_UART_E
	
		
	//this call will ensure that our ahb clock is set to 72MHz otherwise it stays at 80 and that is the wrong clock rate for the mcu core clock
	
#define MAX_UART_BUFSIZ 64	
	
#define BAUD_RATE 9600
	
void UART2_Init(void);
void UARTputc(char thisChar);
void UARTputs( char *str );
char UARTgetc( void );
void UARTprintf( char *fmt, ... );
char UARTgetcNB( void );
//void UARTgets(char *buffer, size_t maxLength);


#endif

