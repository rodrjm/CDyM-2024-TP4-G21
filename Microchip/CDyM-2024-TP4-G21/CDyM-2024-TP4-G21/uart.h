#ifndef UART_H_
#define UART_H_

	#include <avr/io.h>
	#include <avr/interrupt.h>
	
	// Inicialización de la UART
	void UART_Init();
	char UART_getRXflag();
	void UART_clearRXflag();
	char* UART_getRXBuffer();
	uint8_t UART_verificarEntrada(char *entrada);

#endif /* UART_H_ */