/**
 * @file APIdraw.c
 */

/** Includes */
#include "APIdraw.h"

/**
 * @brief Gebruik deze functie bij het teken van een lijn
 * @param x1 Het x-coördinaat van het beginpunt
 * @param y1 Het y-coördinaat van het beginpunt
 * @param x2 Het x-coördinaat van het eindpunt
 * @param y2 Het y-coördinaat van het eindpunt
 * @param lijn_dikte De dikte van de lijn
 * @param kleur De kleur van de lijn
 */
void lijn(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t lijn_dikte, uint8_t kleur)
{

	/* Warnings */
	if (((x1 || x2) > VGA_DISPLAY_X) || ((x1 || x2) < 0))
			UART_puts("\n Bij lijn is een x-waarde buiten de range!!! \n x-range is van 0 t/m 320 \n");

	if (((y1 || y2) > VGA_DISPLAY_Y) || ((y1 || y2) < 0))
			UART_puts("\n Bij lijn is een y-waarde buiten de range!!! \n y-range is van 0 t/m 240 \n");

	/* lokale variabelen */
	float dy = abs(y2 - y1);
	float dx = abs(x2 - x1);

	float error = 0.0;
	float delta_error = (dy / dx);

	/* rechte vertical lijn */
	int i, j, a;
	if (x1 == x2)
	{
		for(i = x1; i < (x1 + lijn_dikte); i++)
		{
			for(j = y1, a = y2; (j <= y2) || (a <= y1); j++, a++)
			{
				if ((j == y2) || (a == y1)) break;
				if 		(y2 > y1) UB_VGA_SetPixel(i,j,kleur);
				else if (y2 < y1) UB_VGA_SetPixel(i,a,kleur);
			}
		}
	}

	/* rechte horizontale lijn en schuine lijn */
	int b, xp, xp2, yp = y1, yp2 = y2;
	for (xp = x1, xp2 = x2; (xp <= x2) || (xp2 <= x1); xp++, xp2++)
	{
		if (((xp == x2) || (xp2 == x1))  && ((yp == y2) || (yp2 == y1))) break;

		if (delta_error >= RC_GRENSWAARDE)
		{
			if (xp <= x2)
			{
				for(b = xp; b < (xp + lijn_dikte); b++)
					UB_VGA_SetPixel(b,yp,kleur);
			}

			else if (xp2 <= x1)
			{
				for(b = xp; b < (xp + lijn_dikte); b++)
					UB_VGA_SetPixel(b,yp2,kleur);
			}
		}

		else if (delta_error < RC_GRENSWAARDE)
		{
			if (xp <= xp2)
			{
				for(b = yp; b < (yp + lijn_dikte); b++)
					UB_VGA_SetPixel(xp,b,kleur);
			}

			else if(xp2 <= xp)
			{
				for(b = yp; b < (yp + lijn_dikte); b++)
					UB_VGA_SetPixel(xp2,b,kleur);
			}
		}

		error += delta_error;

		while (error >= 0.5)
		{
			if (y2 > y1) yp  += 1;
			else if (y2 < y1) yp  -= 1;

			error -= 1;
		}
	}
}

/**
 * @brief Gebruik deze functie bij het tekenen van een ellips
 * @param x_mp Het x-coördinaat van het middelpunt
 * @param y_mp Het y-coördinaat van het middelpunt
 * @param radius_x radius in de x-richting
 * @param radius_y radius in de y-richting
 * @param kleur de kleur van de ellips
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
 * @brief Gebruik deze functie om een rechthoek te tekenen
 * @param x_lo Het x-coördinaat van linksonder
 * @param y_lo Het y-coördinaat van linksonder
 * @param x_rb Het x-coördinaat van rechtsonder
 * @param y_rb Het y-coördinaat van rechtsonder
 * @param kleur De kleur van de rechthoek
 */
void rechthoek(uint16_t x_lo, uint8_t y_lo, uint16_t x_rb, uint8_t y_rb, uint8_t kleur)
{
	/* Warnings */
	if (((x_lo || x_rb) > VGA_DISPLAY_X) || ((x_lo || x_rb) < 0))
			UART_puts("\n Bij rechthoek is een x-waarde buiten de range!!! \n x-range is van 0 t/m 320 \n");

	if (((y_lo || y_rb) > VGA_DISPLAY_Y) || ((y_lo || y_rb) < 0))
			UART_puts("\n Bij rechthoek is een y-waarde buiten de range!!! \n y-range is van 0 t/m 240 \n");

	/* y-as lijnen */
	int a, b;
	for(a = y_rb, b = y_lo; (a <= y_lo) || (b >= y_rb); a++, b--)
	{
		UB_VGA_SetPixel(x_rb, a, kleur);
		UB_VGA_SetPixel(x_lo, b, kleur);
	}

	/* x-as lijnen */
	int i, j;
	for(i = x_rb, j = x_lo; (i > x_lo) || (j < x_rb); i--, j++)
	{
		UB_VGA_SetPixel(i, y_rb, kleur);
		UB_VGA_SetPixel(j, y_lo, kleur);
	}
}

/**
 * @brief Gebruik deze functie om een driehoek te tekenen
 * @param x1 Het x-coördinaat van eerste hoek
 * @param y1 Het y-coördinaat van eerste hoek
 * @param x2 Het x-coördinaat van tweede hoek
 * @param y2 Het y-coördinaat van tweede hoek
 * @param x3 Het x-coördinaat van derde hoek
 * @param y3 Het y-coördinaat van derde hoek
 * @param kleur de kleur van de driehoek
 */
void driehoek(uint16_t x1, uint8_t y1, uint16_t x2, uint8_t y2, uint16_t x3, uint8_t y3, uint8_t kleur)
{
	/* Warnings */
	if (((x1 || x2 || x3) > VGA_DISPLAY_X) || ((x1 || x2 || x3) < 0))
			UART_puts("\n Bij driehoek is een x-waarde buiten de range!!! \n x-range is van 0 t/m 320 \n");

	if (((y1 || y2 || y3) > VGA_DISPLAY_Y) || ((y1 || y2 || y3) < 0))
			UART_puts("\n Bij driehoek is een y-waarde buiten de range!!! \n y-range is van 0 t/m 240 \n");

	/* drie lijnen tekenen */
	lijn(x1, y1, x2, y2, 1, kleur);
	lijn(x2, y2, x3, y3, 1, kleur);
	lijn(x1, y1, x3, y3, 1, kleur);
}

void letter(uint8_t x_loc, uint8_t y_loc, unsigned char letter, uint8_t kleur, uint8_t stijl)
{
	uint8_t byte, y_counter = 0;

	for (int y =0; y < FONT_WIDTH; y++)
	{
		for(int x =0; x < FONT_WIDTH; x++)
		{
			byte = font8x8_normaal[letter][y];

			if ((stijl == NORM) &&  (byte >> x & 0x01)) 	UB_VGA_SetPixel(x_loc + x ,y_loc + y, kleur);

			else if ((stijl == VET) &&  (byte >> x & 0x01))
			{
				UB_VGA_SetPixel(x_loc + x ,y_loc + y, kleur);
				UB_VGA_SetPixel(x_loc + x + 1 ,y_loc + y, kleur);
			}

			else if ((stijl == CURS) &&  (byte >> x & 0x01)) UB_VGA_SetPixel(x_loc + x - y_counter,y_loc + y, kleur);

			//if(byte >> x & 0x01) UB_VGA_SetPixel(x_loc + x ,y_loc + y, kleur);
			//if(byte >> x & 0x01) UB_VGA_SetPixel(x_loc + x - y_counter,y_loc + y, kleur);
		}
		y_counter++;
	}
}

void tekst (uint8_t x_loc, uint8_t y_loc, char *tekst, uint8_t kleur, uint8_t stijl)
{
	/* Warnings */
	if ((x_loc > VGA_DISPLAY_X) || (x_loc < 0))
		UART_puts("\n Bij tekst is de x-waarde buiten de range!!! \n x-range is van 0 t/m 320 \n");

	if ((y_loc > VGA_DISPLAY_Y) || (y_loc < 0))
		UART_puts("\n Bij tekst is de y-waarde buiten de range!!! \n y-range is van 0 t/m 240 \n");

	int i, xp = 0, ascii_nr;
	uint8_t tekst_lentgh = strlen(tekst);


	for(i = 0; i < tekst_lentgh; i++)
	{
		ascii_nr = (int)tekst[i]; - START_ASCII_NR;

		letter(x_loc + xp, y_loc, ascii_nr, kleur, stijl);


		xp += FONT_WIDTH;
	}
}

/**
 * @brief Gebruik deze functie om een bitmap te kiezen en geef de x_lo en y_lo
 * @param nr Het nummer van de gewenste bitmap
 * @param x_lo Het x-coordinaat linksonder
 * @param y_lo Het y-coordinaat linksonder
 */
void bitmap(uint8_t nr, uint16_t x_lo, uint16_t y_lo)
{
	uint8_t* gekozen_bitmap;

	switch(nr)
	{
		case 1: gekozen_bitmap = pijl_omlaag; break; 	/* pijl omloog bitmap */
		case 2: gekozen_bitmap = pijl_omlaag; break; 	/* pijl omhoog bitmap */
		case 3: gekozen_bitmap = pijl_rechts; break; 	/* pijl naar rechts bitmap */
		case 4: gekozen_bitmap = pijl_links; break; 	/* pijl naar links bitmap */
		case 5: gekozen_bitmap = smiley_blij; break; 	/* smiley blij bitmap */
		case 6: gekozen_bitmap = smiley_boos; break; 	/* smiley boos bitmap */
	}

	bitmap_generator(gekozen_bitmap, x_lo, y_lo);
}

/**
 * @brief een functie om een bitmap te tekenen, Het wordt gebruikt door de functie bitmap()
 * @param gekozen_arr meegegeven array
 * @param x_lo Het x-coordinaat linksonder
 * @param y_lo Het y-coordinaat linksonder
 */
void bitmap_generator(uint8_t gekozen_arr[BITMAP_ARRAY_GROOTTE][BITMAP_ARRAY_GROOTTE], uint16_t x_lo, uint16_t y_lo)
{
	uint8_t kleur = 0;

	for (int i = 0; i < BITMAP_ARRAY_GROOTTE; i++)
	{
		for (int j = 0; j < BITMAP_ARRAY_GROOTTE; j++)
		{
			kleur = gekozen_arr[i][j];
			UB_VGA_SetPixel((x_lo + j), (y_lo + i), kleur);
		}
	}
}

/**
 * @brief Gebruik deze functie om het hele scherm te vullen met een kleur
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
	uint32_t D_mS = 0;

	// Run x times 1 millisecond
    while(msecs > 0)
    {
        for(i = 0 ;i < D_mS; i++);
        msecs--;
    }
}
