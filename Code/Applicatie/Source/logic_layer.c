/* includes */
#include "main.h"

/**
 * @brief	Aanroepen van de juiste functie a.d.h.v. de input van de gebruiker
 * @param	Geen
 * @Note	Functies zijn afkomstig uit de EE-API library
 * @retval	Geen
 */
void gebruiker_input_verwerking()
{
	switch (gebruiker_input.command)
	{
		case LIJN:

			/* DEBUG voor gebruikersinput, kan worden aangezet in main.h */
			#ifdef DEBUG_USER_INPUT
				UART_putint(gebruiker_input.command); 	UART_puts("\r");
				UART_putint(gebruiker_input.x1); 		UART_puts("\r");
				UART_putint(gebruiker_input.y1); 		UART_puts("\r");
				UART_putint(gebruiker_input.x2); 		UART_puts("\r");
				UART_putint(gebruiker_input.y2); 		UART_puts("\r");
				UART_putint(gebruiker_input.dikte); 	UART_puts("\r");
				UART_putint(gebruiker_input.kleur); 	UART_puts("\r");
			#endif

			/* Teken een lijn */
			lijn(gebruiker_input.x1,
					gebruiker_input.y1,
					gebruiker_input.x2,
					gebruiker_input.y2,
					gebruiker_input.dikte,
					gebruiker_input.kleur);
			break;

		case ELLIPS:

			/* DEBUG voor gebruikersinput, kan worden aangezet in main.h */
			#ifdef DEBUG_USER_INPUT
				UART_putint(gebruiker_input.command); 	UART_puts("\r");
				UART_putint(gebruiker_input.x_mp); 		UART_puts("\r");
				UART_putint(gebruiker_input.y_mp); 		UART_puts("\r");
				UART_putint(gebruiker_input.radius_x); 	UART_puts("\r");
				UART_putint(gebruiker_input.radius_y); 	UART_puts("\r");
				UART_putint(gebruiker_input.kleur); 	UART_puts("\r");
			#endif

			/* Teken een ellips */
			ellips(gebruiker_input.x_mp,
					gebruiker_input.y_mp,
					gebruiker_input.radius_x,
					gebruiker_input.radius_y,
					gebruiker_input.kleur);
			break;

		case RECHTHOEK:

			/* DEBUG voor gebruikersinput, kan worden aangezet in main.h */
			#ifdef DEBUG_USER_INPUT
				UART_putint(gebruiker_input.command); 	UART_puts("\r");
				UART_putint(gebruiker_input.x_lo); 		UART_puts("\r");
				UART_putint(gebruiker_input.y_lo); 		UART_puts("\r");
				UART_putint(gebruiker_input.x_rb); 		UART_puts("\r");
				UART_putint(gebruiker_input.y_rb); 		UART_puts("\r");
				UART_putint(gebruiker_input.kleur); 	UART_puts("\r");
			#endif

			/* Teken een rechthoek */
			rechthoek(gebruiker_input.x_lo,
						gebruiker_input.y_lo,
						gebruiker_input.x_rb,
						gebruiker_input.y_rb,
						gebruiker_input.kleur);
			break;

		case DRIEHOEK:

			/* DEBUG voor gebruikersinput, kan worden aangezet in main.h */
			#ifdef DEBUG_USER_INPUT
				UART_putint(gebruiker_input.command); 	UART_puts("\r");
				UART_putint(gebruiker_input.x1); 		UART_puts("\r");
				UART_putint(gebruiker_input.y1); 		UART_puts("\r");
				UART_putint(gebruiker_input.x2); 		UART_puts("\r");
				UART_putint(gebruiker_input.y2); 		UART_puts("\r");
				UART_putint(gebruiker_input.x3); 		UART_puts("\r");
				UART_putint(gebruiker_input.y3); 		UART_puts("\r");
				UART_putint(gebruiker_input.kleur); 	UART_puts("\r");
			#endif

			/* Teken een driehoek */
			driehoek( gebruiker_input.x1,
						gebruiker_input.y1,
						gebruiker_input.x2,
						gebruiker_input.y2,
						gebruiker_input.x3,
						gebruiker_input.y3,
						gebruiker_input.kleur);
			break;

		case TEKST:

			/* DEBUG voor gebruikersinput, kan worden aangezet in main.h */
			#ifdef DEBUG_USER_INPUT
				UART_putint(gebruiker_input.command); 	UART_puts("\r");
				UART_putint(gebruiker_input.x_lo); 		UART_puts("\r");
				UART_putint(gebruiker_input.y_lo); 		UART_puts("\r");
				UART_puts(gebruiker_input.tekst); 		UART_puts("\r");
				UART_putint(gebruiker_input.kleur); 	UART_puts("\r");
				UART_putint(gebruiker_input.stijl); 	UART_puts("\r");
			#endif

			/* Schrijf een tekst */
			tekst(gebruiker_input.x_lo,
					gebruiker_input.y_lo,
					gebruiker_input.tekst,
					gebruiker_input.kleur,
					gebruiker_input.stijl);
			break;

		case BITMAP:

			/* DEBUG voor gebruikersinput, kan worden aangezet in main.h */
			#ifdef DEBUG_USER_INPUT
				UART_putint(gebruiker_input.command); 	UART_puts("\r");
				UART_putint(gebruiker_input.nr); 		UART_puts("\r");
				UART_putint(gebruiker_input.x_lo); 		UART_puts("\r");
				UART_puts(gebruiker_input.y_lo); 		UART_puts("\r");
			#endif

			/* Een bitmap weergeven */
			bitmap(gebruiker_input.nr,
					gebruiker_input.x_lo,
					gebruiker_input.y_lo);
			break;

		case CLEARSCHERM:

			/* DEBUG voor gebruikersinput, kan worden aangezet in main.h */
			#ifdef DEBUG_USER_INPUT
				UART_putint(gebruiker_input.command); 	UART_puts("\r");
				UART_putint(gebruiker_input.kleur); 	UART_puts("\r");
			#endif

			/* scherm vullen met een kleur */
			clearscherm(gebruiker_input.kleur);
			break;

		case WACHT:

			/* DEBUG voor gebruikersinput, kan worden aangezet in main.h */
			#ifdef DEBUG_USER_INPUT
				UART_putint(gebruiker_input.command); 	UART_puts("\r");
				UART_putint(gebruiker_input.msecs); 	UART_puts("\r");
			#endif

			/* wacht een aantal ms */
			wacht(gebruiker_input.msecs);
			break;

		default:
			/* print ERROR CODE */
			UART_puts(ERROR02); UART_puts("\r");
	}
}
