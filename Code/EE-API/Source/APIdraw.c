/**
 * @file APIdraw.c
 */

/** Includes */
#include "APIdraw.h"

/**
 * @brief 	Gebruik deze functie bij het teken van een lijn
 * @Note	TODO: code netter maken
 * @param 	x1 			x-coördinaat van het beginpunt
 * @param 	y1 			y-coördinaat van het beginpunt
 * @param 	x2 			x-coördinaat van het eindpunt
 * @param 	y2 			y-coördinaat van het eindpunt
 * @param 	lijn_dikte 	dikte van de lijn
 * @param 	kleur 		kleur van de lijn
 * @retval	Geen
 */
void lijn(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t lijn_dikte, uint8_t kleur)
{
	/* Nodig bij schuine lijn, dit is het stuk die netter gemaakt moet worden */
	uint16_t x_cor_1 = x1;
	uint16_t y_cor_1 = y1;

	if (x2 < x1)
	{
		x1 = x2;
		x2 = x_cor_1;

		y1 = y2;
		y2 = y_cor_1;
	}

	/* Variabelen: */
	float dy = abs(y2 - y1);
	float dx = abs(x2 - x1);

	/* Variabelen voor Bresenham's line algoritme */
	float error = 0.0;
	float delta_error = (dy / dx);

	/* rechte verticale lijn */
	if (x1 == x2)
	{
		int x, direction;
		for(x = x1; x < (x1 + lijn_dikte); x++)
		{
			if (y2 < y1) direction = -1;
			else direction =  1;

			for(int y = y1; y != y2; y += direction)
			{
				VGA_set_pixel(x,y,kleur);
			}
		}
	}


	else
	{
		/* rechte horizontale lijn en schuine lijn */
		int b, xp, xp2, yp = y1, yp2 = y2;
		for (xp = x1, xp2 = x2; (xp <= x2) || (xp2 <= x1); xp++, xp2++)
		{
			if (((xp == x2) || (xp2 == x1))  && ((yp == y2) || (yp2 == y1))) break; /* loop verlaten na tekenen van lijn */

			/* bij iedere stap van x-as, y-as pixel bepalen */
			if (delta_error >= RC_GRENSWAARDE)
			{
				if (xp < x2)
				{
					for(b = xp; b < (xp + lijn_dikte); b++)
						VGA_set_pixel(b,yp,kleur);
				}

				else if (xp2 <= x1)
				{
					for(b = xp; b < (xp + lijn_dikte); b++)
						VGA_set_pixel(b,yp2,kleur);
				}
			}

			/* bij iedere stap van y-as, x-as pixel bepalen */
			else if (delta_error < RC_GRENSWAARDE)
			{
				if (xp <= xp2)
				{
					for(b = yp; b < (yp + lijn_dikte); b++)
						VGA_set_pixel(xp,b,kleur);
				}

				else if(xp2 <= xp)
				{
					for(b = yp; b < (yp + lijn_dikte); b++)
						VGA_set_pixel(xp2,b,kleur);
				}
			}


			/* Bresenham's lijn algoritme */
			error += delta_error;
			while (error >= 0.5)
			{
				if (y2 > y1) yp  += 1;
				else if (y2 < y1) yp  -= 1;

				error -= 1;
			}
		}
	}
}

/**
 * @brief 	Gebruik deze functie bij het tekenen van een ellips
 * @param 	x_mp 		x-coördinaat van het middelpunt
 * @param 	y_mp 		y-coördinaat van het middelpunt
 * @param 	radius_x 	radius in de x-richting
 * @param 	radius_y 	radius in de y-richting
 * @param 	kleur 		kleur van de ellips
 */
void ellips(uint16_t x_mp, uint16_t y_mp, uint16_t radius_x, uint16_t radius_y, uint8_t kleur)
{
	int ry2 = pow(radius_y, 2);
	int rx2 = pow(radius_x, 2);
	int ry2rx2 = ry2 * rx2;
	int x0 = radius_x;
	int x1 = 0;
	int dx = 0;

	for (int x = -radius_x; x <= radius_x; x++)
		VGA_set_pixel( x_mp + x, y_mp, kleur);

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
	    	VGA_set_pixel( x_mp + x, y_mp - y, kleur);
	    	VGA_set_pixel( x_mp + x, y_mp + y, kleur);
	    }
	}
}

/**
 * @brief 	Gebruik deze functie om een rechthoek te tekenen
 * @param 	x_lo 	x-coördinaat van linksonder
 * @param 	y_lo 	y-coördinaat van linksonder
 * @param 	x_rb 	x-coördinaat van rechtsonder
 * @param 	y_rb 	y-coördinaat van rechtsonder
 * @param 	kleur 	kleur van de rechthoek
 */
void rechthoek(uint16_t x_lo, uint8_t y_lo, uint16_t x_rb, uint8_t y_rb, uint8_t kleur)
{
	/* 4 lijnen naar elkaar toe tekenen */
	lijn(x_lo, y_lo, x_lo, y_rb, 1, kleur);
	lijn(x_rb, y_lo, x_rb, y_rb, 1, kleur);
	lijn(x_lo, y_lo, x_rb, y_lo, 1, kleur);
	lijn(x_lo, y_rb, x_rb, y_rb, 1, kleur);
}

/**
 * @brief 	Gebruik deze functie om een driehoek te tekenen
 * @param 	x1 		x-coördinaat van eerste hoek
 * @param 	y1 		y-coördinaat van eerste hoek
 * @param 	x2 		x-coördinaat van tweede hoek
 * @param 	y2 		y-coördinaat van tweede hoek
 * @param 	x3 		x-coördinaat van derde hoek
 * @param 	y3 		y-coördinaat van derde hoek
 * @param 	kleur 	kleur van de driehoek
 * @retval	Geen
 */
void driehoek(uint16_t x1, uint8_t y1, uint16_t x2, uint8_t y2, uint16_t x3, uint8_t y3, uint8_t kleur)
{
	/* 3 lijnen naar elkaar toe tekenen */
	lijn(x1, y1, x2, y2, 1, kleur);
	lijn(x2, y2, x3, y3, 1, kleur);
	lijn(x1, y1, x3, y3, 1, kleur);
}

void letter(uint8_t x_loc, uint8_t y_loc, unsigned char letter, uint8_t kleur, uint8_t stijl)
{
	/* lokale variabelen */
	uint8_t byte, y_counter = 0;

	for (int y =0; y < FONT_WIDTH; y++)
	{
		for(int x =0; x < FONT_WIDTH; x++)
		{
			byte = font8x8_normaal[letter][y];

			if ((stijl == NORM) &&  (byte >> x & 0x01)) 	VGA_set_pixel(x_loc + x ,y_loc + y, kleur);

			else if ((stijl == VET) &&  (byte >> x & 0x01))
			{
				VGA_set_pixel(x_loc + x ,y_loc + y, kleur);
				VGA_set_pixel(x_loc + x + 1 ,y_loc + y, kleur);
			}

			else if ((stijl == CURS) &&  (byte >> x & 0x01)) VGA_set_pixel(x_loc + x - y_counter,y_loc + y, kleur);
		}
		y_counter++; /* deze counter is enkel nodig bij cursief stijl */
	}
}

/**
 * @brief	Gebruik deze functie om een stuk tekst te weergeven
 * @param	x_loc	Het x-coördinaat
 * @param	y_loc	Het y-coördinaat
 * @param	tekst	De Tekst (string)
 * @param	kleur	De kleur
 * @param	stijl	De stijl (normaal, vet gedrukt, cursief)
 * @retval	Geen
 */
void tekst (uint8_t x_loc, uint8_t y_loc, char *tekst, uint8_t kleur, uint8_t stijl)
{
	/* lokale variabelen */
	int i, xp = 0, ascii_nr;

	/* De lengte van de string achterhalen*/
	uint8_t tekst_lentgh = strlen(tekst);

	for(i = 0; i < tekst_lentgh; i++)
	{
		/* zie vanaf 32e ascii waarde*/
		ascii_nr = (int)tekst[i]; - START_ASCII_NR;

		/* letter weergeven */
		letter(x_loc + xp, y_loc, ascii_nr, kleur, stijl);

		/* afstand tussen letters */
		xp += FONT_WIDTH-2;
	}
}

/**
 * @brief 	Gebruik deze functie om een bitmap te kiezen en geef de x_lo en y_lo
 * @param	nr 		nummer van de gewenste bitmap
 * @param 	x_lo 	x-coordinaat linksonder
 * @param 	y_lo 	y-coordinaat linksonder
 * @retval	Geen
 */
void bitmap(uint8_t nr, uint16_t x_lo, uint16_t y_lo)
{
	unsigned char *gekozen_bitmap;

	/* wordt aan de hand van gebruikersinput een bitmap gekozen*/
	switch(nr)
	{
		case 0: gekozen_bitmap = pijl_omhoog; break; 	/* pijl omloog bitmap */
		case 1: gekozen_bitmap = pijl_omlaag; break; 	/* pijl omlaag bitmap */
		case 2: gekozen_bitmap = pijl_rechts; break; 	/* pijl naar rechts bitmap */
		case 3: gekozen_bitmap = smiley_blij; break; 	/* smiley blij bitmap */
		case 4: gekozen_bitmap = pijl_links;  break; 	/* pijl naar links bitmap */
		case 5: gekozen_bitmap = smiley_boos; break; 	/* smiley boos bitmap */
	}

	/* gekozen bitmap weergeven */
	bitmap_generator(gekozen_bitmap, x_lo, y_lo);
}

/**
 * @brief 	Een functie om een bitmap te weergeven, Dit wordt gebruikt door de functie bitmap()
 * @param 	gekozen_arr	Gekozen array meegegeven array
 * @param	x_lo 		Het x-coordinaat linksonder
 * @param	y_lo 		Het y-coordinaat linksonder
 * @retval	Geen
 */
void bitmap_generator(unsigned char gekozen_arr[BITMAP_ARRAY_GROOTTE][BITMAP_ARRAY_GROOTTE], uint16_t x_lo, uint16_t y_lo)
{
	uint8_t kleur = 0;

	for (int i = 0; i < BITMAP_ARRAY_GROOTTE; i++)
	{
		for (int j = 0; j < BITMAP_ARRAY_GROOTTE; j++)
		{
			/* de kleur van de bitmap op een bepaalde pixel achterhalen */
			kleur = gekozen_arr[i][j];

			/* zet een pixel met de kleur van de bitmap */
			VGA_set_pixel((x_lo + j), (y_lo + i), kleur);
		}
	}
}

/**
 * @brief 	Gebruik deze functie om het hele scherm te vullen met een kleur
 * @param 	kleur 	kleur van de pixels
 * @retval	Geen
 */
void clearscherm(uint8_t kleur)
{
	/* Het hele scherm vullen met een kleur */
	UB_VGA_FillScreen(kleur);
}

/**
 * @brief	Wacht een aantal milli secondes
 * @param	msecs 	Het aantal milli secondes
 * @retval	Geen
 */
void wacht(volatile unsigned int msecs)
{
	volatile unsigned int i;

	/* Globale variable (ms) */
	uint32_t D_mS = 0;

	/* Run x times 1 millisecond */
    while(msecs > 0)
    {
        for(i = 0 ;i < D_mS; i++);
        msecs--;
    }
}

/**
 * @brief	Zet een pixel op VGA scherm met een kleur
 * @param	xp		x-coördinaat
 * @param	yp		y-coördinaat
 * @param	kleur	kleur van de pixel
 * @retval	Geen
 */
void VGA_set_pixel(uint16_t xp, uint16_t yp, uint8_t kleur)
{
	/* als xp en xy binnen is */
	if ((xp <= VGA_DISPLAY_X) && (xp >= 0) && (yp <= VGA_DISPLAY_Y) && (yp >= 0))
	{
		/* set pixel functie afkomstig uit stm32_ub_vga_screen */
		UB_VGA_SetPixel(xp, yp, kleur);
	}

//	else
//	{
//		/* Print WARNING CODE*/
//		UART_puts(WARNING01); UART_puts("\r");
//	}
}
