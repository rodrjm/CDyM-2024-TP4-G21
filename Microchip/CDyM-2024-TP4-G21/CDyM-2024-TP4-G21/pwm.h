#ifndef PWM_H_
#define PWM_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdint.h>

void PWM_Init(uint8_t redAux, uint8_t greenAux, uint8_t blueAux);
void setRed(uint8_t redAux);
void setGreen(uint8_t greenAux);
void setBlue(uint8_t blueAux);

#endif /* PWM_H_ */