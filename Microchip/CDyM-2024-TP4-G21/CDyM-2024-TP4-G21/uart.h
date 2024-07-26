#ifndef UART_H_
	#define UART_H_

	#include <avr/io.h>
	
	#include <stdint.h>
	#include <string.h>
	
	#include "serialPort.h"
	
	// Inicialización de la UART
	void UART_Init();
	
	void UART_mensajeInicio();
	void UART_mensajeModificarRed();
	void UART_mensajeModificarGreen();
	void UART_mensajeModificarBlue();
	void UART_mensajeModificar();
	void UART_mensajeComandoInvalido();
	void UART_mensajeIngresarNumeroValido();
	void UART_mensajeFueradeRango();
	char UART_getRXflag();
	void UART_clearRXflag();
	char* UART_getRXBuffer();
	uint8_t UART_verificarNumero(char *entrada, uint8_t *numero);
	uint8_t UART_verificarEntrada(char *entrada);

#endif /* UART_H_ */