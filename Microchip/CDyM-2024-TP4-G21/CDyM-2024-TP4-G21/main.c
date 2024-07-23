#include "main.h"

uint8_t red=0, redAux=0;
uint8_t green=0, greenAux=0;
uint8_t blue=0, blueAux=0;
uint8_t brillo=0, brilloAnterior=0;

uint8_t leerRed=0, leerGreen=0, leerBlue=0;

uint8_t listo = 1;
uint8_t entrada = 0, numero = 0;
uint8_t inicio = 1;

int main(void)
{
	DDRB |= (1<<PORTB5) | (1<<PORTB2) | (1<<PORTB1); // Configuración de los puertos PB1, PB2 y PB5 como salida
	RGB_Init(red, green, blue);
	UART_Init();
	ADC_Init();
	sei();
	UART_mensajeInicio();
	leerRed=1;
    while (1) 
    {
		if (UART_getRXflag()) {
			if (inicio) {
				if (UART_verificarNumero(UART_getRXBuffer(), &numero)) {
					if (leerRed) {
						UART_mensajeModificarRed();
						RGB_setRed(redAux);
						leerRed = 0;
						leerGreen = 1;
					} else
					if (leerGreen) {
						UART_mensajeModificarGreen();
						RGB_setGreen(greenAux);
						leerGreen = 0;
						leerBlue = 1;
					} else
					if (leerBlue) {
						UART_mensajeModificarBlue();
						RGB_setBlue(blueAux);
						leerBlue = 0;
						inicio = 0;
					}
				} else {
					UART_mensajeIngresarNumeroValido();
				}
				UART_clearRXflag();
			} else {
				if (listo) {
					entrada = UART_verificarEntrada(UART_getRXBuffer());
					listo = 0;
				}
				switch (entrada) {
					case 1: {
						UART_mensajeModificarRed();
						RGB_setRed(redAux);
						break;
					}
					case 2: {
						UART_mensajeModificarGreen();
						RGB_setGreen(greenAux);
						break;
					}
					case 3: {
						UART_mensajeModificarBlue();
						RGB_setBlue(blueAux);
						break;
					}
					case 4: {
						UART_mensajeComandoInvalido();
						break;
					}
					listo = 1;
					UART_clearRXflag();
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