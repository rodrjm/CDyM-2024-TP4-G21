#ifndef UART_H_
	#define UART_H_

	// ------------------- Includes ----------------------------
	
	// Archivo de cabecera del Microcontrolador
	#include <avr/io.h>
	
	// Tipos de datos enteros estandarizados
	#include <stdint.h>
	
	// Utilidades con Strings
	#include <string.h>
	
	// Biblioteca del USART
	#include "serialPort.h"
	
	// -------- Prototipos de funciones Publicas ---------------
	
	// Inicialización de la UART
	void UART_Init();
	
	// Funciones para los mensajes que se deben transmitir a través de la terminal
	void UART_mensajeInicio();
	void UART_mensajeModificarRed();
	void UART_mensajeModificarGreen();
	void UART_mensajeModificarBlue();
	void UART_mensajeModificar();
	void UART_mensajeComandoInvalido();
	void UART_mensajeIngresarNumeroValido();
	void UART_mensajeFueradeRango();
	
	// Funciones de control para el funcionamiento del receptor de la UART
	char UART_getRXflag();
	void UART_clearRXflag();
	char* UART_getRXBuffer();
	
	// Funciones para la verificación de lo que ingrese el usuario
	uint8_t UART_verificarNumero(char *entrada, uint32_t *numero);
	uint8_t UART_verificarEntrada(char *entrada);

#endif /* UART_H_ */