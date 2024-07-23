#include "main.h"

uint8_t red=0, redAux=0;
uint8_t green=0, greenAux=0;
uint8_t blue=0, blueAux=0;
uint8_t brillo=0, brilloAnterior=0;

uint8_t entrada = 0;
uint8_t inicio = 1;

int main(void)
{
	DDRB |= (1<<PORTB5) | (1<<PORTB2) | (1<<PORTB1); // Configuración de los puertos PB1, PB2 y PB5 como salida
	RGB_Init(red, green, blue);
	UART_Init();
	ADC_Init();
	sei();
	
	// UART_mensajeBienvenida();
	
    while (1) 
    {
		if (UART_getRXflag()) {
			if (inicio) {
				// UART_ingresarProporciones();
				inicio = 0;
			} else {
				entrada = UART_verificarEntrada(UART_getRXBuffer());
				switch (entrada) {
					case 1: {
						// UART_mensajeModificarRed();
						// RGB_setRed(redAux);
						break;
					}
					case 2: {
						// UART_mensajeModificarGreen();
						// RGB_setGreen(greenAux);
						break;
					}
					case 3: {
						// UART_mensajeModificarBlue();
						// RGB_setBlue(blueAux);
						break;
					}
					default: {
						// UART_mensajeError();
						break;
					}
			}
		} 
		
		brillo = ADC_Read();
		if (brillo != brilloAnterior) {
			brilloAnterior = brillo;
			RGB_setBrillo(brillo, redAux, greenAux, blueAux);
		}
    }
}