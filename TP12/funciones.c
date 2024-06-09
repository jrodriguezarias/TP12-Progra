#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include "funciones.h"

void bitSet(void * pport, int bitSwitch){
	uint8_t * p = (uint8_t *) pport;
	double mask = pow(2, bitSwitch);
	(*p) = (*p) | (int)mask;
}

void bitClr(void * pport, int bitSwitch){
	uint8_t * p = (uint8_t *) pport;
	double mask = pow(2, 7) - 1 - pow(2, bitSwitch);
	(*p) = (*p) & (int)mask;
}

int bitGet(void * pport, int bit){
	uint8_t * p = (uint8_t *) pport;
	double mask = pow(2, bit);
	uint8_t temp = (*p) & (int)mask;
	if(temp == mask){
		return 1;
	}
	return 0;
}

void bitToggle(void *pport, int bit){
	uint8_t * p = (uint8_t *) pport;
	double mask = pow(2, bit);
	(*p) = (*p) ^ (int)mask;
}

void maskOn(void *pport, int mask){
	uint8_t * p = (uint8_t *) pport;
	(*p) = (*p) | mask;
}

void maskOff(void *pport, int mask){
	uint8_t * p = (uint8_t *) pport;
	(*p) = (*p) & (~mask);
}

void maskToggle(void *pport, int mask){
	uint8_t * p = (uint8_t *) pport;
	(*p) = (*p) ^ mask;
}



