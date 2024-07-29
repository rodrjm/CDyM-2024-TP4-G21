#include "main.h"

// Variables para el manejo del LED RGB y el brillo del potenciómetro
uint8_t redAux=0;
uint8_t greenAux=0;
uint8_t blueAux=0;
uint8_t brillo=0, brilloAnterior=0;

// Variables de control para el flujo del programa
uint8_t listo = 0; // Variable que indica si el seteo del color de un LED fue correcto
uint8_t entrada = 0; // Variable que guarda la entrada ingresada por el usuario
uint8_t inicio = 1; // Variable que indica si el programa debe ejecutar la proporción de colores por primera vez
uint32_t numero = 0; // Variable que guarda el numero ingresado por el usuario
uint8_t estado = 1; // 1=mensajeRed; 2=setRed; 3=mensajeGreen; 4=setGreen; 5=mensajeBlue; 6=setBlue; 7=mensajeModificar;

int main(void)
{
	/* Setup */
	_delay_ms(3000);
	DDRB |= (1<<PORTB5) | (1<<PORTB2) | (1<<PORTB1); // Configuración de los puertos PB1, PB2 y PB5 como salida
	RGB_Init(redAux, greenAux, blueAux);
	UART_Init();
	ADC_Init();
	sei();
	
	UART_mensajeInicio();
	
	/* Loop */
    while (1) 
    {
		switch (estado) { // Switch que controla los mensajes que se deben imprimir a través de la terminal
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
		if (UART_getRXflag()) { // Si el buffer tiene datos para procesar
			if (inicio) { // Si el programa está en estado de inicio, se deben procesar las proporciones de color para los tres LEDs
				if (UART_verificarNumero(UART_getRXBuffer(), &numero) == 1) { // En caso de que el número haya sido ingresado correctamente
					switch (estado) { // Switch que controla qué color de LED se debe setear
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
				} else if (UART_verificarNumero(UART_getRXBuffer(), &numero) == 2) { // En caso de que el número esté fuera de rango
					UART_mensajeFueradeRango();
				} else { // En caso de que no se haya ingresado un número
					UART_mensajeIngresarNumeroValido();					
				}
				UART_clearRXflag(); // Le avisamos a la UART que ya finalizó la recepción del dato
			} else {
				if (listo) { // Si ya finalizó correctamente el seteo de un LED, debo leer nuevamente el comando que ingrese el usuario
					entrada = UART_verificarEntrada(UART_getRXBuffer());
					listo = 0;
					switch (entrada) { // Switch que controla qué se debe hacer en base a la entrada del usuario
						case 1: { // El usuario ingresó 'R'
							estado = 1; // El sistema debe mostrar el mensaje para modificar el LED Rojo
							entrada = 0;
							break;
						}
						case 2: { // El usuario ingresó 'G'
							estado = 3; // El sistema debe mostrar el mensaje para modificar el LED Green
							entrada = 0;
							break;
						}
						case 3: { // El usuario ingresó 'B'
							estado = 5; // El sistema debe mostrar el mensaje para modificar el LED Blue
							entrada = 0;
							break;
						}
						case 4: { // El usuario ingresó un comando inválido
							UART_mensajeComandoInvalido();
							estado = 7; // El sistema debe pedir nuevamente al usuario que ingrese un comando
							break;
						}
					}
				} else // Si no finalizó correctamente el seteo de un LED, debo realizar el seteo del color del LED correspondiente
				if (UART_verificarNumero(UART_getRXBuffer(), &numero) == 1) {
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
				} else if (UART_verificarNumero(UART_getRXBuffer(), &numero) == 2) {
					UART_mensajeFueradeRango();
				} else {
					UART_mensajeIngresarNumeroValido();
				}
				UART_clearRXflag();
			}
		}
		if (!inicio) { // Cuando el programa ya tiene los colores del LED RGB seteados, comienza a funcionar el potenciómetro
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