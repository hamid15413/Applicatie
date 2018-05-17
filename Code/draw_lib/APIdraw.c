//------------------------------------------------------------------------
//  File:   APIdraw.c
//
//
//
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------
#include "APIdraw.h"

// -----------------------------------------------------------------------
// lijn
// -----------------------------------------------------------------------
void lijn(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t kleur) //momenteel zonder , uint8_t lijn_dikte
{
	typedef enum {false=0, true=1} bool;
	bool print_bool = false;
	float rc; // richtingscoefficient

	if(x1 >= VGA_DISPLAY_X) x1= VGA_DISPLAY_X - 2;
	if(x2 >= VGA_DISPLAY_X) x2= VGA_DISPLAY_X - 2;
	if(y1 >= VGA_DISPLAY_Y) y1= VGA_DISPLAY_Y - 2;
	if(y2 >= VGA_DISPLAY_Y) y2= VGA_DISPLAY_Y - 2;

	if(x1 <= 0) x1=2;
	if(x2 <= 0) x2=2;
	if(y1 <= 0) y1=2;
	if(y2 <= 0) y2=2;

	//Lijn
	rc = ((y2 - y1) / (x2 - x1));
	//int rc_int = (int)rc;

	int i, yp;
	yp = y1;

	for(i = x1; i <= x2; i++)
	{
		UB_VGA_SetPixel(i,yp,kleur);
		UART_puts("\ny = ");
		UART_putint(yp);
		UART_puts("\n");

		while (yp <= y2)
		{
			yp += rc;
			break;
		}


		UART_puts("\nx = ");
		UART_putint(i);
		UART_puts("\t");
	}
}
