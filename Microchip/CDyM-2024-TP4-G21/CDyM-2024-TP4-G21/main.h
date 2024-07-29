#ifndef MAIN_H_
	#define MAIN_H_

	// ------------------- Constantes ----------------------------
	
	// Frecuencia del Microcontrolador (16 MHz)
	#define F_CPU 16000000UL
	
	// ------------------- Includes ----------------------------
	
	// Archivo de cabecera del Microcontrolador
	#include <avr/io.h>
	
	// Interrupciones del Microcontrolador
	#include <avr/interrupt.h>
	
	// Delay
	#include <util/delay.h>
	
	// Bibliotecas que componen al proyecto
	#include "adc.h"
	#include "rgb.h"
	#include "serialPort.h"
	#include "uart.h"

#endif /* MAIN_H_ */