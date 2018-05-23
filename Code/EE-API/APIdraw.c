/**
 * @file APIdraw.c
 */

/** Includes */
#include "APIdraw.h"

/**
 * @brief lijn tekenen
 */
void lijn(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t kleur) //momenteel zonder , uint8_t lijn_dikte
{
	clearscherm(WIT);
}

/**
 * @brief ellips tekenen
 */
void ellips(uint16_t x_mp, uint16_t y_mp, uint16_t radius_x, uint16_t radius_y, uint8_t kleur)
{
	int ry2 = pow(radius_y, 2);
	int rx2 = pow(radius_x, 2);
	int ry2rx2 = ry2 * rx2;
	int x0 = radius_x;
	int x1 = 0;
	int dx = 0;

	clearscherm(WIT);

	for (int x = -radius_x; x <= radius_x; x++)
		UB_VGA_SetPixel( x_mp + x, y_mp, kleur);

	for (int y = 1; y <= radius_y; y++)
	{
		x1 = x0 - (dx - 1);

		for ( ; x1 > 0; x1--)
			if (x1*x1*ry2 + y*y*rx2 <= ry2rx2)
				break;

	    dx = x0 - x1;
	    x0 = x1;

	    for (int x = -x0; x <= x0; x++)
	    {
	    	UB_VGA_SetPixel( x_mp + x, y_mp - y, kleur);
	    	UB_VGA_SetPixel( x_mp + x, y_mp + y, kleur);
	    }
	}
}

/**
 * @brief kies het nummer van de gewenste bitmap en geeft de x_lo en y_lo
 * @param nr het nummer van de gewenste bitmap
 * @param x_lo de x-coordinaat
 * @para, y_lo de y-c00rdinaat
 */
void bitmap(uint8_t nr, uint16_t x_lo, uint16_t y_lo)
{
	clearscherm(WIT);

	switch(nr)
	{
	case 1: bitmap_generator(pijl_naar_benden, x_lo, y_lo); break;
	case 2: bitmap_generator(pijl_naar_benden, x_lo, y_lo); break;
	case 3: bitmap_generator(pijl_naar_benden, x_lo, y_lo); break;
	case 4: bitmap_generator(pijl_naar_benden, x_lo, y_lo); break;
	case 5: bitmap_generator(pijl_naar_benden, x_lo, y_lo); break;
	}
}

void bitmap_generator(unsigned int arr[BITMAP_ARRAY_GROOTTE][BITMAP_ARRAY_GROOTTE], uint16_t x_lo, uint16_t y_lo)
{
	uint8_t kleur = 0;
	uint8_t kleur_controle = 0;

	for (int i = 0; i < BITMAP_ARRAY_GROOTTE; i++)
	{
		for (int j = 0; j < BITMAP_ARRAY_GROOTTE; j++)
		{
			kleur_controle = arr[i][j];

			if (kleur_controle != 0x00)
				kleur = ZWART;

			else
				kleur = WIT;

			UB_VGA_SetPixel((x_lo + i), (y_lo + j), kleur);
		}
	}
}

/**
 * @brief vull het scherm met een kleur
 * @param kleur de kleur
 */
void clearscherm(uint8_t kleur)
{
	UB_VGA_FillScreen(kleur);
}

/**
 * @brief wacht een aantal milli secondes
 * @param msecs het aantal milli secondes
 */
void wacht(volatile unsigned int msecs)
{
	volatile unsigned int i;

	// Globale variable (ms)
	uint32_t D_mS;

	// Run x times 1 millisecond
    while(msecs > 0)
    {
        for(i = 0 ;i < D_mS; i++);
        msecs--;
    }
}
