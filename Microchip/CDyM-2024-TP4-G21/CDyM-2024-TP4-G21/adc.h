#ifndef ADC_H_
	#define ADC_H_
	
	// ------------------- Includes ----------------------------
	
	// Archivo de cabecera del Microcontrolador
	#include <avr/io.h>
	
	// -------- Prototipos de funciones Publicas ---------------
	
	// Inicializaci�n del potenci�metro
	void ADC_Init();
	
	// Funciones de control para el funcionamiento del potenci�metro
	void ADC_Run();
	uint8_t ADC_Read();
	uint8_t ADC_GetFlag();
	void ADC_SetFlag();
	
#endif /* ADC_H_ */