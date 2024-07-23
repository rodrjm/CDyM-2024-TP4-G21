#ifndef RGB_H_
#define RGB_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdint.h>

void RGB_Init(uint8_t redAux, uint8_t greenAux, uint8_t blueAux);
void RGB_setRed(uint8_t redAux);
void RGB_setGreen(uint8_t greenAux);
void RGB_setBlue(uint8_t blueAux);

#endif /* RGB_H_ */