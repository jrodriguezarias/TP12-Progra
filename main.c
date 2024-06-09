// Modulo de manejo de gpio_out
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include <stdint.h>
#include "funciones.h"
#include <stdarg.h>

typedef uint8_t pin_t;

// Variables globales


static const char export_path[] = "/sys/class/gpio/export";
static const char unexport_path[] = "/sys/class/gpio/unexport";
static const char gpio_dir_path[] = "/sys/class/gpio/gpio";
static char string_buffer[ sizeof(gpio_dir_path) + 20 ]; // esto para tener espacio para copiar los strings

static FILE* gpio_pins[NUM_OF_PINS]; // como arrancan en NULL, el programa puede ver si estan inicializados o no
static FILE* export_handle = NULL;
static FILE* unexport_handle = NULL;

// funciones

int init_gpio_out_module();

int init_gpio_out_pin(pin_t pin);

int main (void){
	return 0;
}


int init_gpio_out_module() {
	static int first_time = 1;

	if(first_time) {
		
		export_handle = fopen(export_path, "w");

		if(export_handle == NULL) return ERR_UNACCESIBLE;
		
		first_time = 0;
	
	}
	return 0;
}

int init_gpio_out_pin(int numPins, ...) {

	if(export_handle == NULL) return GPIO_UNINITIATED;
	va_list valist;
	int i;
	double pin;

	va_start(valist, numPins);

	for(i = 0 ; i < numPins ; i++){
		pin = va_arg(valist, int);

		// Valido q pueda arrancar
		if(pin > NUM_OF_PINS || pin < 0) return INVALID_INPUT;

		/*int result;
		result = fputs( itoa(pin, string_buffer, 10), export_handle); // pone "17", "23" o lo q sea en el export.
		if(result == -1) return ERR_UNACCESIBLE;
		*/
		//comentado pq itoa aparentemente no esta en stdlib xd

		// Habria q hacer un strcpy del gpio_dir_path al buffer, dsps sprintf("%s%d/value") de  itoa del pin al buffer, despues value
	}
	
	va_end(valist);

	fclose(export_handle);

	return 0;
}

int deinit_gpio_out_module() {
	static int first_time = 1;

	if(first_time) {

		unexport_handle = fopen(unexport_path, "w");

		if(unexport_handle == NULL) return ERR_UNACCESIBLE;

		first_time = 0;

	}
	return 0;
}

int deinit_gpio_out_pin(int numPins, ...) {

	if(unexport_handle == NULL) return GPIO_UNINITIATED;
	va_list valist;
	int i;
	double pin;

	va_start(valist, numPins);

	for(i = 0 ; i < numPins ; i++){
		pin = va_arg(valist, int);

		// Valido q pueda arrancar
		if(pin > NUM_OF_PINS || pin < 0) return INVALID_INPUT;

		/*int result;
		result = fputs( itoa(pin, string_buffer, 10), unexport_handle); // pone "17", "23" o lo q sea en el export.
		if(result == -1) return ERR_UNACCESIBLE;
		*/
		//comentado pq itoa aparentemente no esta en stdlib xd

		// Habria q hacer un strcpy del gpio_dir_path al buffer, dsps sprintf("%s%d/value") de  itoa del pin al buffer, despues value
	}

	va_end(valist);

	fclose(unexport_handle);

	return 0;
}

void update_port(led_port port, )
