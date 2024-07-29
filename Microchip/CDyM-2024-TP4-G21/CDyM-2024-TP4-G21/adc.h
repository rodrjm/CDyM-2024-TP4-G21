#ifndef ADC_H_
#define ADC_H_
	#include <avr/io.h>
	void ADC_Init();
	void ADC_Run();
	uint8_t ADC_Read();
	uint8_t ADC_GetFlag();
	void ADC_SetFlag();
#endif /* ADC_H_ */