/*
 * @file main.c
 */
#include "main.h"

int main(void)
{
	/* instellen van de microcontroller systeem */
	init_system_API();

	/* initialiseren van de VGA module */
	init_VGA_API();

	/* initialisatie van UART */
	init_UART_API();

	while(1)
	{
		/* Front Layer aanroepen */
		lees_buffer();
	}
}
