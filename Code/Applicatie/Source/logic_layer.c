#include "main.h"

void gebruiker_input_verwerkeing()
{

	switch (gebruiker_input.command)
	{
		case LIJN:

			#ifdef DEBUG_USER_INPUT
				UART_putint(gebruiker_input.command); 	UART_puts("\r");
				UART_putint(gebruiker_input.x1); 		UART_puts("\r");
				UART_putint(gebruiker_input.y1); 		UART_puts("\r");
				UART_putint(gebruiker_input.x2); 		UART_puts("\r");
				UART_putint(gebruiker_input.y2); 		UART_puts("\r");
				UART_putint(gebruiker_input.dikte); 	UART_puts("\r");
				UART_putint(gebruiker_input.kleur); 	UART_puts("\r");
			#endif

			lijn(gebruiker_input.x1,
					gebruiker_input.y1,
					gebruiker_input.x2,
					gebruiker_input.y2,
					gebruiker_input.dikte,
					gebruiker_input.kleur);
			break;


		case ELLIPS:

			#ifdef DEBUG_USER_INPUT
				UART_putint(gebruiker_input.command); 	UART_puts("\r");
				UART_putint(gebruiker_input.x_mp); 		UART_puts("\r");
				UART_putint(gebruiker_input.y_mp); 		UART_puts("\r");
				UART_putint(gebruiker_input.radius_x); 	UART_puts("\r");
				UART_putint(gebruiker_input.radius_y); 	UART_puts("\r");
				UART_putint(gebruiker_input.kleur); 	UART_puts("\r");
			#endif

			ellips(gebruiker_input.x_mp,
					gebruiker_input.y_mp,
					gebruiker_input.radius_x,
					gebruiker_input.radius_y,
					gebruiker_input.kleur);
			break;


		case RECHTHOEK:

			#ifdef DEBUG_USER_INPUT
				UART_putint(gebruiker_input.command); 	UART_puts("\r");
				UART_putint(gebruiker_input.x_lo); 		UART_puts("\r");
				UART_putint(gebruiker_input.y_lo); 		UART_puts("\r");
				UART_putint(gebruiker_input.x_rb); 		UART_puts("\r");
				UART_putint(gebruiker_input.y_rb); 		UART_puts("\r");
				UART_putint(gebruiker_input.kleur); 	UART_puts("\r");
			#endif

			rechthoek(gebruiker_input.x_lo,
						gebruiker_input.y_lo,
						gebruiker_input.x_rb,
						gebruiker_input.y_rb,
						gebruiker_input.kleur);
			break;

		case DRIEHOEK:

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

			driehoek( gebruiker_input.x1,
						gebruiker_input.y1,
						gebruiker_input.x2,
						gebruiker_input.y2,
						gebruiker_input.x3,
						gebruiker_input.y3,
						gebruiker_input.kleur);
			break;

		case TEKST:

			#ifdef DEBUG_USER_INPUT
				UART_putint(gebruiker_input.command); 	UART_puts("\r");
				UART_putint(gebruiker_input.x_lo); 		UART_puts("\r");
				UART_putint(gebruiker_input.y_lo); 		UART_puts("\r");
				UART_puts(gebruiker_input.tekst); 		UART_puts("\r");
				UART_putint(gebruiker_input.kleur); 	UART_puts("\r");
				UART_putint(gebruiker_input.stijl); 	UART_puts("\r");
			#endif

			tekst(gebruiker_input.x_lo,
					gebruiker_input.y_lo,
					gebruiker_input.tekst[255],
					gebruiker_input.kleur,
					gebruiker_input.stijl);
			break;


		case BITMAP:

			#ifdef DEBUG_USER_INPUT
				UART_putint(gebruiker_input.command); 	UART_puts("\r");
				UART_putint(gebruiker_input.nr); 		UART_puts("\r");
				UART_putint(gebruiker_input.x_lo); 		UART_puts("\r");
				UART_puts(gebruiker_input.y_lo); 		UART_puts("\r");
			#endif

			bitmap(gebruiker_input.nr,
					gebruiker_input.x_lo,
					gebruiker_input.y_lo);
			break;

		case CLEARSCHERM:

			#ifdef DEBUG_USER_INPUT
				UART_putint(gebruiker_input.command); 	UART_puts("\r");
				UART_putint(gebruiker_input.kleur); 	UART_puts("\r");
			#endif

			clearscherm(gebruiker_input.kleur);
			break;

		case WACHT:

			#ifdef DEBUG_USER_INPUT
				UART_putint(gebruiker_input.command); 	UART_puts("\r");
				UART_putint(gebruiker_input.msecs); 	UART_puts("\r");
			#endif

			wacht(gebruiker_input.msecs);
			break;

		//default:
			// print error :TODO warning code			 */

	}
}
