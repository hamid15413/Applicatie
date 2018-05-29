/*
 * @file main.c
 *
 *
 */
#include "main.h"

int main(void)
{
	/* System speed to 168MHz */
	SystemInit();

	/*  */
	init_VGA_API();
	init_UART_API();

	//UART_puts("Welkom"); UART_puts("\r");


	while(1)
	{
		lees_buffer();
	}
}
