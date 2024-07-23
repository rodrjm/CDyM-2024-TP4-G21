#include "uart.c"

#define BR9600 (0x67)	// 0x67=103 configura BAUDRATE=9600@16MHz
#define TX_BUFFER_LENGTH 50
#define RX_BUFFER_LENGTH 50

unsigned char TX_indiceLectura = 0, TX_indiceEscritura = 0;
unsigned char RX_indice=0;

static char TX_Buffer [TX_BUFFER_LENGTH];
static char RX_Buffer [RX_BUFFER_LENGTH];

static unsigned char TX_flag = 0;
static unsigned char RX_flag = 0;
static char dato;

// Mensajes de bienvenida y de control del LED
char msgBienvenida[] = "Bienvenido al sistema de control de un LED RGB";
char msgRed[] = "Ingrese la proporción de color para el LED rojo\n\r";
char msgGreen[] = "Ingrese la proporción de color para el LED verde\n\r";
char msgBlue[] = "Ingrese la proporción de color para el LED azul\n\r";
char msgModificar[] = "Ingrese 'R' para modificar el rojo, 'G' para el verde o 'B' para el azul\n\r"

// Inicialización de la UART
void UART_Init() {
	SerialPort_Init(BR9600); 		// Inicializo formato 8N1 y BAUDRATE = 9600bps
	SerialPort_TX_Enable();			// Activo el transmisor del Puerto Serie
	SerialPort_RX_Enable();			// Activo el receptor del Puerto Serie
	SerialPort_Send_String(msgBienvenida); // Envío el mensaje de bienvenida
	SerialPort_RX_Interrupt_Enable();	// Activo Interrupción de recepcion
}

char UART_getRXflag() {
	return RX_flag;
}

void UART_clearRXflag() {
	RX_flag = 0;
}

char* UART_getRXBuffer() {
	return RX_Buffer
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