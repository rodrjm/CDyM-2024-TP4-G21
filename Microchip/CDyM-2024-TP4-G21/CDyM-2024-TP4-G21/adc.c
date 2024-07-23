#include "adc.h"

uint8_t ADC_Read() {
	ADCSRA |= (1<<ADSC); // Comienza la conversión
	while((ADCSRA&(1<<ADIF))==0); // Espera a que finalice la conversión
	ADCSRA |= (1<<ADIF); // Borra el flag
	return ADCH;
}

void ADC_Init() {
	DIDR0 = (1<<ADC3D); // Pin ADC3 como entrada
	ADCSRA= 0x87; // Habilita ADC y selecciona ck/128
	ADMUX= (1 << REFS0) | (1 << ADLAR) | (1 << MUX1) | (1 << MUX0); // Vref=AVCC, left-justified, ADC3 pin
}