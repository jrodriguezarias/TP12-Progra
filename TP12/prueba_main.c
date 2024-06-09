#include "constants.h"
#include "gpio_manage.h"
#include <stdio.h>

int main()
{
	
	pin_t led = {"23"};

	if(init_gpio_out_module() < 0) {
		printf("ERROR DE INIT MODULE\n");
		return 0;
	}
	int result =  init_gpio_out_pin(1, &led);
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

	if (result < 0) return 1;

	int value = 0;
	while(1) {
		while(getchar() != '\n');
		set_pin(led, value);
		value = !value;
	}

	return 0;
}