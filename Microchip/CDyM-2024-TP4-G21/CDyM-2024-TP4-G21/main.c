#include "main.h"

uint8_t red=0;
uint8_t green=0;
uint8_t blue=0;

int main(void)
{
	DDRB |= (1<<PORTB5) | (1<<PORTB2) | (1<<PORTB1);
	PWM_Init(red, green, blue);
    while (1) 
    {
    }
}