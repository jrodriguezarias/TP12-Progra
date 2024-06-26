#include "constants.h"
#include "gpio_manage.h"
#include <time.h> // sleep (int ms)



static const char export_path[] = "/sys/class/gpio/export";
static const char unexport_path[] = "/sys/class/gpio/unexport";
static const char gpio_dir_path[] = "/sys/class/gpio/gpio";
static char string_buffer[ sizeof(gpio_dir_path) + 20 ]; // esto para tener espacio para copiar los strings

static FILE* export_handle = NULL;
static FILE* unexport_handle = NULL;


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
		if(result == EOF) return ERR_CANT_EXPORT;
	}

	delay (10); // Frena 10 ms para q el SO pueda generar todos los archivos de direction y value

	// Ponerlos en modo out
	for(i = 0 ; i < numPins ; i++) {

		// Copiar el path
		strcpy(string_buffer, gpio_dir_path);
		strcat(string_buffer, pins[i].name );
		strcat(string_buffer, "/direction");

		// Abrir y escribir en el archivo direction
		pins[i].direction_file = fopen(string_buffer, "w");
		if(pins[i].direction_file == NULL) return ERR_DIRECTION;
		
		result = fputs("out", pins[i].direction_file);
		fclose(pins[i].direction_file);
		if(result == EOF) return ERR_DIRECTION;
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
	
	return value;
}

int deinit_gpio_out_module(pin_t pins[], int size) {

	int i;

	unexport_handle = fopen(unexport_path, "w");
	if(unexport_handle == NULL) return ERR_UNACCESIBLE; 
	
	if(export_handle != NULL) fclose(export_handle);

	delay(10); // Frena x las dudas para poder usar bien el unexport_handle
	for(i = 0; i < size; i++) {
		if(pins[i].direction_file != NULL) fclose( pins[i].direction_file );
		if(pins[i].value_file != NULL) fclose( pins[i].value_file );
		fputs(pins[i].name, unexport_handle);
	}

	return 0;

}







void delay(int ms)
{
    // Storing start time
    clock_t start_time = clock();
 
    // looping till required time is not achieved
    while (clock() < start_time + ms);
}