#ifndef UART_H_
#define UART_H_

	#include <avr/io.h>
	#include <avr/interrupt.h>
	
	// Inicialización de la UART
	void UART_Init();
	
	void UART_mensajeInicio();
	void UART_mensajeModificarRed();
	void UART_mensajeModificarGreen();
	void UART_mensajeModificarBlue();
	void UART_mensajeError();
	char UART_getRXflag();
	void UART_clearRXflag();
	char* UART_getRXBuffer();
	void UART_verificarNumero(char *entrada);
	uint8_t UART_verificarEntrada(char *entrada);

#endif /* UART_H_ */