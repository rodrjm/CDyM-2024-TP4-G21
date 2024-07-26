#include "uart.h"

#define BR9600 (0x67)	// 0x67=103 configura BAUDRATE=9600@16MHz
#define TX_BUFFER_LENGTH 64
#define RX_BUFFER_LENGTH 64

static unsigned char TX_indiceLectura = 0, TX_indiceEscritura = 0;
static unsigned char RX_indice=0;

static char TX_Buffer [TX_BUFFER_LENGTH];
static char RX_Buffer [RX_BUFFER_LENGTH];

static unsigned char TX_flag = 0;
static unsigned char RX_flag = 0;
static char dato;

// Mensajes de bienvenida y de control del LED
static char msgBienvenida[] = "Bienvenido al sistema de control de un LED RGB\n\r";
static char msgInicio[] = "Ingrese la proporción de color para cada LED (de 0 a 255) para obtener un color resultante\n\r";
static char msgRed[] = "Ingrese la proporción de color para el LED rojo\n\r";
static char msgGreen[] = "Ingrese la proporción de color para el LED verde\n\r";
static char msgBlue[] = "Ingrese la proporción de color para el LED azul\n\r";
static char msgModificar[] = "Ingrese 'R' para modificar el rojo, 'G' para el verde o 'B' para el azul\n\r";
static char msgComandoInvalido[] = "Comando inválido. Pruebe nuevamente\n\r";
static char msgIngresarNumeroValido[] = "Ingresar número válido. Pruebe nuevamente\n\r";
static char msgFueradeRango[] = "Número fuera de rango. Debe estar entre 0 y 255\n\r";

// Inicialización de la UART
void UART_Init() {
	SerialPort_Init(BR9600); 		// Inicializo formato 8N1 y BAUDRATE = 9600bps
	SerialPort_TX_Enable();			// Activo el transmisor del Puerto Serie
	SerialPort_RX_Enable();			// Activo el receptor del Puerto Serie
	SerialPort_Send_String(msgBienvenida); // Envío el mensaje de bienvenida
	SerialPort_RX_Interrupt_Enable();	// Activo Interrupción de recepcion
}

void UART_mensajeInicio() {
	SerialPort_Send_String(msgInicio);
}

void UART_mensajeModificarRed() {
	SerialPort_Send_String(msgRed);
}

void UART_mensajeModificarGreen() {
	SerialPort_Send_String(msgGreen);
}

void UART_mensajeModificarBlue() {
	SerialPort_Send_String(msgBlue);
}

void UART_mensajeModificar() {
	SerialPort_Send_String(msgModificar);
}

void UART_mensajeComandoInvalido() {
	SerialPort_Send_String(msgComandoInvalido);
}

void UART_mensajeIngresarNumeroValido() {
	SerialPort_Send_String(msgIngresarNumeroValido);
}

void UART_mensajeFueradeRango() {
	SerialPort_Send_String(msgFueradeRango);
}

char UART_getRXflag() {
	return RX_flag;
}

void UART_clearRXflag() {
	RX_flag = 0;
}

char* UART_getRXBuffer() {
	return RX_Buffer;
}

uint8_t UART_verificarNumero(char *entrada, uint8_t *numero) {
	uint8_t digito, factor = 1; *numero = 0;
	
	for (int8_t i=strlen(entrada)-1; i>=0; i--) { // Se comienza a armar el número desde la unidad
		digito = entrada[i] - '0'; // Obtener digito
		if (digito > 9) return 0; // Si el caracter no es valido, retornar que no es número 
		(*numero) += digito * factor; // Sumar al resultado 
		factor *= 10; // Actualizar factor (x10)
	}
	return 1; // Retornar conversión exitosa
}

uint8_t UART_verificarEntrada(char *entrada) {
	if (!strcmp(entrada, "R")) {
		return 1;
	} else
	if (!strcmp(entrada, "G")) {
		return 2;
	} else
	if (!strcmp(entrada, "B")) {
		return 3;
	} else {
		return 4;
	}
}

// Interrupción de transmisión
ISR(USART_UDRE_vect) {
	if (TX_flag) {
		if (TX_indiceLectura < TX_indiceEscritura) {
			SerialPort_Send_Data(TX_Buffer[TX_indiceLectura]);
			TX_indiceLectura++;
		} else {
			TX_flag = 0;
			TX_indiceLectura = 0;
			TX_indiceEscritura = 0;
			SerialPort_TX_Interrupt_Disable();
		}
	}
}

// Interrupción de recepción
ISR(USART_RX_vect){
	dato = SerialPort_Recive_Data();
	if (dato != '\r') {
		RX_Buffer[RX_indice] = dato;
		RX_indice++;
	} else {
		RX_Buffer[RX_indice] = '\0';
		RX_indice = 0;
		RX_flag = 1;
	}
}