// Modulo de manejo de gpio_out
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include <stdint.h>

typedef uint8_t pin_t;

// Variables globales


static const char export_path[] = "/sys/class/gpio/export";
static const char gpio_dir_path[] = "/sys/class/gpio/gpio";
static char string_buffer[ sizeof(gpio_dir_path) + 20 ]; // esto para tener espacio para copiar los strings

static FILE* gpio_pins[NUM_OF_PINS]; // como arrancan en NULL, el programa puede ver si estan inicializados o no
static FILE* export_handle = NULL;

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

int init_gpio_out_pin(pin_t pin) {
	
	// Valido q pueda arrancar
	if(pin > NUM_OF_PINS || pin < 0) return INVALID_INPUT;
	if(export_handle == NULL) return GPIO_UNINITIATED;
	
	/*int result;
	result = fputs( itoa(pin, string_buffer, 10), export_handle); // pone "17", "23" o lo q sea en el export.
	if(result == -1) return ERR_UNACCESIBLE;
	*/
	//comentado pq itoa aparentemente no esta en stdlib xd

	// Habria q hacer un strcpy del gpio_dir_path al buffer, dsps sprintf("%s%d/value") de  itoa del pin al buffer, despues value

	return 0;
}
