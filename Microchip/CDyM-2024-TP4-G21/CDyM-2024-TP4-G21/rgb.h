#ifndef RGB_H_
	#define RGB_H_

	#include <avr/io.h>
	#include <avr/interrupt.h>
	
	#include <math.h>
	#include <stdint.h>
	#include <string.h>

	void RGB_Init(uint8_t redAux, uint8_t greenAux, uint8_t blueAux);
	void RGB_setRed(uint8_t redAux);
	void RGB_setGreen(uint8_t greenAux);
	void RGB_setBlue(uint8_t blueAux);
	void RGB_setBrillo(uint8_t brillo, uint8_t redAux, uint8_t greenAux, uint8_t blueAux);

#endif /* RGB_H_ */