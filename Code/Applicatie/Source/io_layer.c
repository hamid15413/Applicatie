#include "main.h"

void init_VGA_API()
{
	UB_VGA_Screen_Init(); // Init VGA-Scherm
}

void init_UART_API()
{
	UART_init(); // Init UART
}
