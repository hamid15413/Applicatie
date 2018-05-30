/* includes */
#include "main.h"

/**
 * @brief	Alle gebruikersinput gelijk maken aan 0
 * @param	Geen
 * @retval	Geen
 */
void user_input_init()
{
	gebruiker_input.kleur = 0;
	gebruiker_input.nr = 0;
	gebruiker_input.dikte = 0;
	gebruiker_input.command = 0;
	gebruiker_input.x_mp = 0;
	gebruiker_input.y_mp = 0;
	gebruiker_input.x_rb = 0;
	gebruiker_input.y_rb = 0;
	gebruiker_input.x1 = 0;
	gebruiker_input.x2 = 0;
	gebruiker_input.x3 = 0;
	gebruiker_input.y1 = 0;
	gebruiker_input.y2 = 0;
	gebruiker_input.y3 = 0;
	gebruiker_input.radius_x = 0;
	gebruiker_input.radius_y = 0;
	gebruiker_input.x_lo = 0;
	gebruiker_input.y_lo = 0;
	gebruiker_input.msecs = 0;
	gebruiker_input.stijl = 0;
	gebruiker_input.tekst = 0;

	correct_struct = false;

}

/**
 * @brief	Elementen uit een string splitten
 * @param	Geen
 * @retval	Exit in het geval van error
 */
void lees_buffer()
{
	/* lokale variabel */
	char gebruiker_arr [255];

	// alle gebruiker inputs gelijk maken aan 0.
	user_input_init();

	// string binnen halen indien de gebruiker een command geeft.
	UART_gets(gebruiker_arr, 0);

	char* woord;
	const char str[2] = ",";
	char* woorden[MAX_AANTAL_WOORDEN] = {NULL};

	/* alles splitten vóór de komma, ofwel command*/
	woord = strtok(gebruiker_arr, str);

	// resterende woorden splitten en opslaan in woorden[]
	int i = 0;
	while (woord != NULL)
	{
		woorden[i++] = woord;
		woord = strtok (NULL, str);
	}

	/* De opgesplitse elementen uit een string in een struct zetten */
	gebruiker_input_herkennen(woorden);

	/* Het geeft uitsluitend een complete struct door */
	if (correct_struct == true)
	{
		/* Het struct wordt doorgegeven aan Logic Layer */
		gebruiker_input_verwerking();
	}

	else if (correct_struct == false)
	{
		/* print error code */
		UART_puts(ERROR02); UART_puts("\r");
		return;
	}
}

/**
 * @brief 	De opgesplitse elementen uit een string in een struct zetten
 * @param	input_string	een array van strings
 * @retval	Geen
 */
void gebruiker_input_herkennen(char** input_string)
{
	char* input_command = input_string[COMMAND];

	/* controleert de aanwezigheid van een command */
	if (input_command == NULL)
	{
		/* print error code */
		UART_puts(ERROR01); UART_puts("\r");
		return;
	}


	if (strcasecmp(input_command, "lijn") == 0)
	{
		gebruiker_input.command = commando_herkennen(input_string[COMMAND]);
		gebruiker_input.x1 = 	atoi(input_string[1]);
		gebruiker_input.y1 = 	atoi(input_string[2]);
		gebruiker_input.x2 = 	atoi(input_string[3]);
		gebruiker_input.y2 = 	atoi(input_string[4]);
		gebruiker_input.dikte = atoi(input_string[5]);
		gebruiker_input.kleur = kleur_herkennen(input_string[6]);

		correct_struct = true;
	}

	else if (strcasecmp(input_command, "ellips") == 0)
	{
		gebruiker_input.command = commando_herkennen(input_string[COMMAND]);
		gebruiker_input.x_mp = 		atoi(input_string[1]);
		gebruiker_input.y_mp = 		atoi(input_string[2]);
		gebruiker_input.radius_x =	atoi(input_string[3]);
		gebruiker_input.radius_y = 	atoi(input_string[4]);
		gebruiker_input.kleur = 	kleur_herkennen(input_string[5]);

		correct_struct = true;
	}

	else if (strcasecmp(input_command, "rechthoek") == 0)
	{
		gebruiker_input.command = commando_herkennen(input_string[COMMAND]);
		gebruiker_input.x_lo =	atoi(input_string[1]);
		gebruiker_input.y_lo = 	atoi(input_string[2]);
		gebruiker_input.x_rb = 	atoi(input_string[3]);
		gebruiker_input.y_rb = 	atoi(input_string[4]);
		gebruiker_input.kleur = kleur_herkennen(input_string[5]);

		correct_struct = true;
	}

	else if (strcasecmp(input_command, "driehoek") == 0)
	{
		gebruiker_input.command = commando_herkennen(input_string[COMMAND]);
		gebruiker_input.x1 =	atoi(input_string[1]);
		gebruiker_input.y1 =	atoi(input_string[2]);
		gebruiker_input.x2 =	atoi(input_string[3]);
		gebruiker_input.y2 =	atoi(input_string[4]);
		gebruiker_input.x3 =	atoi(input_string[5]);
		gebruiker_input.y3 =	atoi(input_string[6]);
		gebruiker_input.kleur =	kleur_herkennen(input_string[7]);

		correct_struct = true;
	}

	else if (strcasecmp(input_command, "tekst") == 0)
	{
		gebruiker_input.command = 		commando_herkennen(input_string[COMMAND]);
		gebruiker_input.x_lo =			atoi(input_string[1]);
		gebruiker_input.y_lo =			atoi(input_string[2]);
		gebruiker_input.tekst =			input_string[3];
		gebruiker_input.kleur =			kleur_herkennen(input_string[4]);
		gebruiker_input.stijl = 		tekst_stijl_herkennen(input_string[5]);

		correct_struct = true;
	}

	else if (strcasecmp(input_command, "bitmap") == 0)
	{
		gebruiker_input.command = commando_herkennen(input_string[COMMAND]);
		gebruiker_input.nr = 	atoi(input_string[1]);
		gebruiker_input.x_lo = 	atoi(input_string[2]);
		gebruiker_input.y_lo = 	atoi(input_string[3]);

		correct_struct = true;
	}

	else if (strcasecmp(input_command, "clearscherm") == 0)
	{
		gebruiker_input.command = commando_herkennen(input_string[COMMAND]);
		gebruiker_input.kleur = kleur_herkennen(input_string[1]);

		correct_struct = true;
	}

	else if (strcasecmp(input_command, "wacht") == 0)
	{
		gebruiker_input.command = commando_herkennen(input_string[COMMAND]);
		gebruiker_input.msecs = (volatile unsigned int)atoi(input_string[1]);

		correct_struct = true;
	}

	else
	{
		/* geen geldige command */
		correct_struct = false;
	}
}

/**
 * @brief	kleurwaarde bepalen
 * @Note	TODO: een betere error handling
 * @param	kleur_string	Kleur string, "(een kleur)"
 * @retval	kleurwaarde
 */
uint8_t kleur_herkennen(char* kleur_string)
{
	uint8_t kleur = 0;

	if (strcasecmp(kleur_string, "zwart") == 0) 			kleur = ZWART;
	else if (strcasecmp(kleur_string, "wit") == 0) 			kleur = WIT;
	else if (strcasecmp(kleur_string, "grijs") == 0)		kleur = GRIJS;
	else if (strcasecmp(kleur_string, "blauw") == 0) 		kleur = BLAUW;
	else if (strcasecmp(kleur_string, "lichtblauw") == 0) 	kleur = LICHT_BLAUW;
	else if (strcasecmp(kleur_string, "groen") == 0) 		kleur = GROEN;
	else if (strcasecmp(kleur_string, "lichtgroen") == 0) 	kleur = LICHT_GROEN;
	else if (strcasecmp(kleur_string, "rood") == 0)			kleur = ROOD;
	else if (strcasecmp(kleur_string, "lichtrood") == 0) 	kleur = LICHT_ROOD;
	else if (strcasecmp(kleur_string, "cyaan") == 0) 		kleur = CYAAN;
	else if (strcasecmp(kleur_string, "lichtcyaan") == 0) 	kleur = LICHT_CYAAN;
	else if (strcasecmp(kleur_string, "magenta") == 0) 		kleur = MAGENTA;
	else if (strcasecmp(kleur_string, "lichtmagenta") == 0) kleur = LICHT_MAGENTA;
	else if (strcasecmp(kleur_string, "geel") == 0) 		kleur = GEEL;
	else if (strcasecmp(kleur_string, "bruin") == 0) 		kleur = BRUIN;

	else
	{
		/* print ERROR CODE */
		UART_puts(ERROR03); UART_puts("\r");

		/* indien kleur is onbekend, kleur wordt default_kleur ofwel wit */
		kleur = WIT;
	}

	return kleur;
}

/**
 * @brief	een string van tekst stijl omzetten in een int waarde
 * @Note	TODO: een betere error handling
 * @param	stijl_string		een string ("norm" of "vet" of "curs")
 * @retval	een int waarde voor de tekst stijl
 */
uint8_t tekst_stijl_herkennen(char* stijl_string)
{
	uint8_t stijl = 0;

	if (strcasecmp(stijl_string, "norm") == 0)				stijl = NORM;
	else if (strcasecmp(stijl_string, "vet") == 0)			stijl = VET;
	else if (strcasecmp(stijl_string, "cursief") == 0)		stijl = CURS;

	else
	{
		/* print ERROR CODE */
		UART_puts(ERROR04); UART_puts("\r");

		/* indien stijl is onbekend, kleur wordt default stijl ofwel norm */
		stijl = NORM;
	}

	return stijl;
}

/**
 * @brief	een string van commando omzetten in een int waarde
 * @param	commando_string		een string van verschillend commando's
 * @retval	een int waarde 		voor de commando
 */
uint8_t commando_herkennen(char* commando_string)
{
	uint8_t commando = 0;

	if (strcasecmp(commando_string, "lijn") == 0)				commando = LIJN;
	else if (strcasecmp(commando_string, "ellips") == 0)		commando = ELLIPS;
	else if (strcasecmp(commando_string, "rechthoek") == 0)		commando = RECHTHOEK;
	else if (strcasecmp(commando_string, "driehoek") == 0)		commando = DRIEHOEK;
	else if (strcasecmp(commando_string, "tekst") == 0)			commando = TEKST;
	else if (strcasecmp(commando_string, "bitmap") == 0)		commando = BITMAP;
	else if (strcasecmp(commando_string, "clearscherm") == 0)	commando = CLEARSCHERM;
	else if (strcasecmp(commando_string, "wacht") == 0)			commando = WACHT;

	return commando;
}
