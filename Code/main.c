//--------------------------------------------------------------
// File     : main.c
// Datum    : 30.03.2016
// Version  : 1.0
// Autor    : UB
// mods by	: J.F. van der Bent
// CPU      : STM32F4
// IDE      : CooCox CoIDE 1.7.x
// Module   : CMSIS_BOOT, M4_CMSIS_CORE
// Function : VGA_core DMA LIB 320x240, 8bit color
//--------------------------------------------------------------
#include "main.h"

int main(void)
{
	SystemInit(); // System speed to 168MHz
	init_VGA_API();
	init_UART_API();

	//clearscherm(255);

	//UART_puts("start VESOFTON van Ali en Hamid\n\n");

	//ellips(100, 100, 100, 50, 255);
	bitmap(3, 20, 20);

	/*
	for (int var = 0; var < 10; var++)
	{
		UART_puts("aantal secondes");
		wacht(1000000);
	}
	*/

	while(1)
	{

	}
}
