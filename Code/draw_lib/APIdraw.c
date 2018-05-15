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
void lijn(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t kleur, uint8_t lijn_dikte)
{
	if(x1>=VGA_DISPLAY_X) x1=0; //en warning!!
	if(x2>=VGA_DISPLAY_X) x2=0;
	if(y1>=VGA_DISPLAY_Y) y1=0;
	if(y2>=VGA_DISPLAY_Y) y2=0;
}