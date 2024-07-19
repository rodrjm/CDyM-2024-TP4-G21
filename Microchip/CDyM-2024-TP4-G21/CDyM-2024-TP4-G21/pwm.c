#include "pwm.h"

static volatile uint8_t red=0;
static volatile uint8_t green=0;
static volatile uint8_t blue=0;

static void Timer0_Init();
static void Timer1_Init();

static void Timer0_Init() {
	TIMSK0 |= (1<<OCIE0A) | (1<<TOIE0); // Activación de interrupciones Output Compare Match y Overflow
	TCCR0B |= (1<<CS00) | (1<<CS02); // Prescaler 1024
}

static void Timer1_Init() {
	TCCR1A |= (1<<WGM10); // Modo Fast PWM 8-bit
	TCCR1B |= (1<<CS10)| (1<<CS12) | (1<<WGM12); // Modo Fast PWM 8-bit y Prescaler 1024
}

void PWM_Init(uint8_t redAux, uint8_t greenAux, uint8_t blueAux) {
	red = redAux;
	green = greenAux;
	blue = blueAux;
	OCR0A = redAux;
	OCR1B = greenAux;
	OCR1A = blueAux;
	Timer0_Init();
	Timer1_Init();
}

void setRed(uint8_t redAux) {
	red = redAux;
	if (red > 0) {
		Timer0_Init(); // Enciendo el timer
	} else {
		TCCR0B = 0; // Apago el timer
		PORTB |= (1<<PORTB5); // Configuración del PORTB5 en alto
	}
}

void setGreen(uint8_t greenAux) {
	green = greenAux;
	if (green > 0) {
		TCCR1A |= (1<<COM1B1) | (1<<COM1B0); // Output Compare Match en Modo invertido
		OCR1B = green;
	} else {
		TCCR1A &= ~((1<<COM1B1) & (1<<COM1B0)); // OCR1B desconectado
		PORTB |= (1<<PORTB2); // Configuración del PORTB2 en alto
	}
}

void setBlue(uint8_t blueAux) {
	blue = blueAux;
	if (blue > 0) {
		TCCR1A |= (1<<COM1A1) | (1<<COM1A0); // Output Compare Match en Modo invertido
		OCR1A = blue;
		} else {
		TCCR1A &= ~((1<<COM1A1) & (1<<COM1A0)); // OCR1A desconectado
		PORTB |= (1<<PORTB1); // Configuración del PORTB1 en alto
	}
}

// Interrupciones que controlan el LED Rojo

ISR(TIMER0_OVF_vect) {
	OCR0A = red;
	PORTB &= ~(1<<PORTB5); // Configuración del PORTB5 en bajo
}

ISR(TIMER0_COMPA_vect) {
	PORTB |= (1<<PORTB5); // Configuración del PORTB5 en alto
}