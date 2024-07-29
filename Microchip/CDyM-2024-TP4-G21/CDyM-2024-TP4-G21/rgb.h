#ifndef RGB_H_
	#define RGB_H_

	// ------------------- Includes ----------------------------
	
	// Archivo de cabecera del Microcontrolador
	#include <avr/io.h>
	
	// Interrupciones del Microcontrolador
	#include <avr/interrupt.h>
	
	// Funciones matemáticas
	#include <math.h>
	
	// Tipos de datos enteros estandarizados
	#include <stdint.h>
	
	// Utilidades con Strings
	#include <string.h>

	// -------- Prototipos de funciones Publicas ---------------
	
	// Inicialización del LED RGB
	void RGB_Init(uint8_t redAux, uint8_t greenAux, uint8_t blueAux);
	
	// Funciones de control para el funcionamiento del LED RGB
	void RGB_setRed(uint8_t redAux);
	void RGB_setGreen(uint8_t greenAux);
	void RGB_setBlue(uint8_t blueAux);
	void RGB_setBrillo(uint8_t brillo, uint8_t redAux, uint8_t greenAux, uint8_t blueAux);

#endif /* RGB_H_ */