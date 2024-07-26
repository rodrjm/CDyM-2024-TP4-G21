#include "adc.h"

void ADC_Init() {
	DDRC &= ~(1<<PORTC3); // Pin ADC3 como entrada
	DIDR0 |= (1<<PORTC3); // Pin ADC3 como entrada
	ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); // Habilita ADC y selecciona ck/128
	ADMUX |= (1<<REFS0) | (1<<ADLAR) | (1<<MUX1) | (1<<MUX0); // Vref=AVCC, left-justified, ADC3 pin
}

uint8_t ADC_Read() {
	ADCSRA |= (1<<ADSC); // Comienza la conversión
	while ((ADCSRA & (1<<ADIF)) == 0); // Espera a que finalice la conversión
	ADCSRA |= (1<<ADIF); // Borra el flag
	return ADCH;
}