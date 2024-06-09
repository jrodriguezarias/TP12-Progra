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

	if( init_gpio_out_pin(1, &led) < 0) {
		printf("ERROR DE INIT DE PIN\n");
		return 0;
	}

	int value = 0;
	while(1) {
		while(getchar() != '\n');
		set_pin(led, value);
		value = !value;
	}

	return 0;
}