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
#include "stm32_ub_vga_screen.h"
#include "stm32f4xx_usart.h"
#include "APIdraw.h"
#include "includes.h"
#include <math.h>
#include <stdio.h>
#include <string.h>



int main(void)
{
	SystemInit(); // System speed to 168MHz

	UB_VGA_Screen_Init(); // Init VGA-Screen
	UB_VGA_FillScreen(VGA_COL_BLACK);
	//UB_VGA_SetPixel(0,0,255);

	UART_init();
	UART_puts("start VESOFTON van Ali en Hamid\n\n");

	lijn(0, 0, 100, 150, 255); //x1,y1,x2,y2,kleur

	while(1)
	{
		// put the code here

	}
}
