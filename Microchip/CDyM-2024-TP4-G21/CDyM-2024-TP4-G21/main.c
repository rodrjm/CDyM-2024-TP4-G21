#include "main.h"

uint8_t redAux=0;
uint8_t greenAux=0;
uint8_t blueAux=0;
uint8_t brillo=0, brilloAnterior=0;

uint8_t listo = 0;
uint8_t entrada = 0, numero = 0;
uint8_t inicio = 1;

uint8_t estado = 1; // 1=mensajeRed; 2=setRed; 3=mensajeGreen; 4=setGreen; 5=mensajeBlue; 6=setBlue; 7=mensajeModificar;

int main(void)
{
	_delay_ms(3000);
	DDRB |= (1<<PORTB5) | (1<<PORTB2) | (1<<PORTB1); // Configuración de los puertos PB1, PB2 y PB5 como salida
	RGB_Init(redAux, greenAux, blueAux);
	UART_Init();
	ADC_Init();
	sei();
	UART_mensajeInicio();
    while (1) 
    {
		switch (estado) {
			case 1: {
				UART_mensajeModificarRed();
				estado = 2;
				break;
			}
			case 3: {
				UART_mensajeModificarGreen();
				estado = 4;
				break;
			}
			case 5: {
				UART_mensajeModificarBlue();
				estado = 6;
				break;
			}
			case 7: {
				UART_mensajeModificar();
				listo = 1;
				estado = 0;
				break;
			}
		}
		if (UART_getRXflag()) {
			if (inicio) {
				if (UART_verificarNumero(UART_getRXBuffer(), &numero)) {
					switch (estado) {
						case 2: {
							redAux = numero;
							RGB_setRed(redAux);
							estado = 3;
							break;
						}
						case 4: {
							greenAux = numero;
							RGB_setGreen(greenAux);
							estado = 5;
							break;
						}
						case 6: {
							blueAux = numero;
							RGB_setBlue(blueAux);
							estado = 7;
							inicio = 0;
							break;
						}
					}
				} else {
					UART_mensajeIngresarNumeroValido();
				}
				UART_clearRXflag();
			} else {
				if (listo) {
					entrada = UART_verificarEntrada(UART_getRXBuffer());
					listo = 0;
					switch (entrada) {
						case 1: {
							estado = 1;
							entrada = 0;
							break;
						}
						case 2: {
							estado = 3;
							entrada = 0;
							break;
						}
						case 3: {
							estado = 5;
							entrada = 0;
							break;
						}
						case 4: {
							UART_mensajeComandoInvalido();
							estado = 7;
							break;
						}
					}
				} else
				if (UART_verificarNumero(UART_getRXBuffer(), &numero)) {
					switch (estado) {
						case 2: {
							redAux = numero;
							RGB_setRed(redAux);
							estado = 7;
							break;
						}
						case 4: {
							greenAux = numero;
							RGB_setGreen(greenAux);
							estado = 7;
							break;
						}
						case 6: {
							blueAux = numero;
							RGB_setBlue(blueAux);
							estado = 7;
							break;
						}
					}
				} else {
					UART_mensajeIngresarNumeroValido();
				}
				UART_clearRXflag();
			}
		}
		if (!inicio) {
			ADC_Run();
			if(ADC_GetFlag()){
				brillo = ADC_Read();
				if (brillo != brilloAnterior) {
					brilloAnterior = brillo;
					RGB_setBrillo(brillo, redAux, greenAux, blueAux);
				}
				ADC_SetFlag();
			}
		}
    }
}