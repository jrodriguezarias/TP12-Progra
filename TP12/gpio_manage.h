#ifndef GPIO_MANAGE_H
#define GPIO_MANAGE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	char name[4];
	int value;
	FILE* direction_file;
	FILE* value_file;
} pin_t;


int init_gpio_out_module();

int init_gpio_out_pin(int numPins, pin_t pins[]);

int set_pin(pin_t pin, int value);

#endif