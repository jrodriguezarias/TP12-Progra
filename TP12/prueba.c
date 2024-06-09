#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "constants.h"

// Falta la funcion de unexport, igual con esto ya podemos probar

typedef struct {
	char name[4];
	int value;
	FILE* direction_file;
	FILE* value_file;
} pin_t;


static const char export_path[] = "/sys/class/gpio/export";
static const char unexport_path[] = "/sys/class/gpio/unexport";
static const char gpio_dir_path[] = "/sys/class/gpio/gpio";
static char string_buffer[ sizeof(gpio_dir_path) + 20 ]; // esto para tener espacio para copiar los strings

static FILE* export_handle = NULL;
static FILE* unexport_handle = NULL;

int init_gpio_out_module();

int init_gpio_out_pin(int numPins, pin_t pins[]);

int set_pin(pin_t pin, int value);



int init_gpio_out_module() {
	static int first_time = 1;

	if(first_time) {
		
		export_handle = fopen(export_path, "w");

		if(export_handle == NULL) return ERR_UNACCESIBLE;
		
		first_time = 0;
	
	}
	return 0;
}

// Necesito escribir el num en export_handle, abrir direction y escribir "out", y abrir "value" y escribir el num

int init_gpio_out_pin(int numPins, pin_t pins[]) {

	if(export_handle == NULL) return GPIO_UNINITIATED;
	int i, result;

	// Exportar los pines escribiendo en el archivo export
	for(i = 0 ; i < numPins ; i++) {
		result = fputs(pins[i].name, export_handle);
		fflush(export_handle);
		if(result == EOF) return ERR_UNACCESIBLE;
	}


	// Ponerlos en modo out
	for(i = 0 ; i < numPins ; i++) {

		// Copiar el path
		strcpy(string_buffer, gpio_dir_path);
		strcat(string_buffer, pins[i].name );
		strcat(string_buffer, "/direction");

		// Abrir y escribir en el archivo direction
		pins[i].direction_file = fopen(string_buffer, "w");
		if(pins[i].direction_file == NULL) return ERR_UNACCESIBLE;
		
		result = fputs("out", pins[i].direction_file);
		fclose(pins[i].direction_file);
		if(result == EOF) return ERR_UNACCESIBLE;
	}
	
	// Abrir los archivos de value para q ya despues se puedan escribir
	for(i = 0 ; i < numPins ; i++) {

		// Copiar el path
		strcpy(string_buffer, gpio_dir_path);
		strcat(string_buffer, pins[i].name );
		strcat(string_buffer, "/value");

		pins[i].value_file = fopen(string_buffer, "w");

		if(pins[i].value_file == NULL) return ERR_UNACCESIBLE;

	}

	fclose(export_handle);

	return 0;
}

int set_pin(pin_t pin, int value) {
	

	if(pin.value_file == NULL) return ERR_UNACCESIBLE;
	
	int result = fputs(value ? "1" : "0", pin.value_file);
	if(result == EOF) return ERR_UNACCESIBLE;
	
	fflush(pin.value_file);
	pin.value = value;
	
	return 0;
}