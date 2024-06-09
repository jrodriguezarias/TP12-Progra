#include "constants.h"
#include "gpio_manage.h"
#include <stdio.h>

int main()
{
	printf("Inicializando leds\n");

	pin_t leds [8] = {{"17", 0, NULL, NULL}, {"4", 0, NULL, NULL}, {"18", 0, NULL, NULL}, {"23", 0, NULL, NULL}, {"24", 0, NULL, NULL}, {"25", 0, NULL, NULL}, {"22", 0, NULL, NULL}, {"27", 0, NULL, NULL} };
	
	int result;
	int c;
	int i;

	// Abrir el archivo de export
	while( (result = init_gpio_out_module()) == ERR_UNACCESIBLE) {
		
		printf("Error al abrir archivo export. Intente más tarde apretando enter o salga apretando q \n");
		//previene fallo por timeout
		c=getchar();
		if(c == 'q') {
			printf("Saliendo del programa\n");
			deinit_gpio_out_module(leds, 8);
			return 1;
		}
		while(c != '\n') c = getchar();
	
	}
	

	// Exportar los pin y abrir los archivos para ya setearlos
	while( (result =  init_gpio_out_pin(8, leds)) != 0) {
		
		printf("Error al abrir archivos de GPIO. Intente más tarde apretando enter o salga apretando q \n");
		
		//previene fallo por timeout
		c=getchar();
		if(c == 'q') {
			printf("Saliendo del programa\n");
			deinit_gpio_out_module(leds, 8);
			return 1;
		}
		while(c != '\n') c = getchar();
	}

	/*
result =  init_gpio_out_pin(8, leds);
	switch(result) {
	case GPIO_UNINITIATED:
		printf("ERROR DE INIT DE MODULO\n");
		break;
	case ERR_CANT_EXPORT:
		printf("ERROR NO PUDO EXPORTAR\n");
		break;
	case ERR_UNACCESIBLE:
		printf("ERROR NO PUDO ABRIR VALUE\n");
		break;
	case ERR_DIRECTION:
		printf("ERROR NO PUDO ABRIR ARCHIVO DIRECTION\n");
		break;
	}
	*/
	
	const char explicacion[] = "Ingrese un numero de 0 al 7 para encender el led\n"
	"Ingrese 's' para encender todos los leds\n"
	"Ingrese 'c' para apagar todos los leds\n"
	"Ingrese 't' para cambiar el estado de todos los leds\n";


	printf("%s\n", explicacion);
	c = '\0';
	while(c != 'q') {
		c = getchar();
		
		if(c >= '0' && c <= '7') {
			
			printf("Encendiendo led %c", c);
			int result = set_pin(leds[c-'0'], 1);

			if(result == ERR_UNACCESIBLE) {
				printf("Error de controlador al intentar encender led %c, intente de nuevo\n", c);
			} else {
				leds[c-'0'].value = result;
			}

		} else if(c == 's') {
			printf("Encendiendo leds\n");
			
			for(i=0; i <= 7; i++) {
				int result = set_pin(leds[i], 1);
				if(result == ERR_UNACCESIBLE) {
					printf("Error de controlador al intentar encender led %c, intente de nuevo\n", c);
				} else {
					leds[i].value = result;
				}
			}
		
		} else if(c == 'c') {
		
			printf("Apagando leds\n");
			for(i=0; i <= 7; i++) {
				int result = set_pin(leds[i], 0);
				if(result == ERR_UNACCESIBLE) {
					printf("Error de controlador al intentar apagar led %c, intente de nuevo\n", c);
				} else {
					leds[i].value = result;
				}
			}
		} else if(c == 't') {
			printf("Cambiando leds\n");
			for(i=0; i <= 7; i++) {
				int result = set_pin(leds[i], ! (leds[i].value) );
				if(result == ERR_UNACCESIBLE) {
					printf("Error de controlador al intentar cambiar led %c, intente de nuevo\n", c);
				} else {
					leds[i].value = result;
				}
			}
		} else {
			printf ("Comando desconocido\n");
			printf("%s", explicacion);
		}

		while (c != '\n') {
			c = getchar();
		}

	}

	printf("Liberando controlador de pines de led\n");
	deinit_gpio_out_module(leds, 8);
	printf("Saliendo del programa\n");

	return 0;
}