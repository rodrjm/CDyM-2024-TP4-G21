#include "main.h"

uint8_t red=0;
uint8_t green=0;
uint8_t blue=0;

int main(void)
{
	DDRB |= (1<<PORTB5) | (1<<PORTB2) | (1<<PORTB1); // Configuración de los puertos PB1, PB2 y PB5 como salida
	PWM_Init(red, green, blue);
	UART_Init();
	sei();
    while (1) 
    {
    }
}