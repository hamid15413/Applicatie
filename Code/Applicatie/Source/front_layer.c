#include "main.h"

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

	gebruiker_input.tekst[255] = "";

}

void lees_buffer()
{
	// alle gebruiker inputs gelijk maken aan 0.
	user_input_init();

	// string binnen halen indien de gebruiker een command geeft.
	UART_gets(gebruiker_arr, 0);

	char* woord;
	const char str[2] = ",";
	char* woorden[MAX_AANTAL_WOORDEN] = {NULL};

	/* alles splitten vóór de komma */
	woord = strtok(gebruiker_arr, str);

	// resterende woorden splitten en opslaan in woorden[]
	int i = 0;
	while (woord != NULL)
	{
		woorden[i++] = woord;
		woord = strtok (NULL, str);
	}

	gebruiker_input_herkennen(woorden);

	/* de struct naar logic layer verzenden */
	gebruiker_input_verwerkeing();
}

void gebruiker_input_herkennen(char** input_string)
{
	//char** input_string_kopie = input_string; //TODO: remove this
	char* input_command = input_string[COMMAND];

	// aanwezigheid van een command controleren
	if (input_command == NULL)
		// print errorcode (ER is geen command)
		UART_puts("er is geen command");

	if (strcasecmp(input_command, "lijn") == 0)
	{
		gebruiker_input.command = commando_herkennen(input_string[COMMAND]);
		gebruiker_input.x1 = 	atoi(input_string[1]);
		gebruiker_input.y1 = 	atoi(input_string[2]);
		gebruiker_input.x2 = 	atoi(input_string[3]);
		gebruiker_input.y2 = 	atoi(input_string[4]);
		gebruiker_input.dikte = atoi(input_string[5]);
		gebruiker_input.kleur = kleur_herkennen(input_string[6]);
	}

	else if (strcasecmp(input_command, "ellips") == 0)
	{
		gebruiker_input.command = commando_herkennen(input_string[COMMAND]);
		gebruiker_input.x_mp = 		atoi(input_string[1]);
		gebruiker_input.y_mp = 		atoi(input_string[2]);
		gebruiker_input.radius_x =	atoi(input_string[3]);
		gebruiker_input.radius_y = 	atoi(input_string[4]);
		gebruiker_input.kleur = 	kleur_herkennen(input_string[5]);
	}

	else if (strcasecmp(input_command, "rechthoek") == 0)
	{
		gebruiker_input.command = commando_herkennen(input_string[COMMAND]);
		gebruiker_input.x_lo =	atoi(input_string[1]);
		gebruiker_input.y_lo = 	atoi(input_string[2]);
		gebruiker_input.x_rb = 	atoi(input_string[3]);
		gebruiker_input.y_rb = 	atoi(input_string[4]);
		gebruiker_input.kleur = kleur_herkennen(input_string[5]);
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
	}

	else if (strcasecmp(input_command, "tekst") == 0)
	{
		gebruiker_input.command = 		commando_herkennen(input_string[COMMAND]);
		gebruiker_input.x_lo =			atoi(input_string[1]);
		gebruiker_input.y_lo =			atoi(input_string[2]);
		gebruiker_input.tekst[255] =	input_string[3];
		gebruiker_input.kleur =			kleur_herkennen(input_string[4]);
		gebruiker_input.stijl = 		tekst_stijl_herkennen(input_string[5]);
	}

	else if (strcasecmp(input_command, "bitmap") == 0)
	{
		gebruiker_input.command = commando_herkennen(input_string[COMMAND]);
		gebruiker_input.nr = 	atoi(input_string[1]);
		gebruiker_input.x_lo = 	atoi(input_string[2]);
		gebruiker_input.y_lo = 	atoi(input_string[3]);
	}

	else if (strcasecmp(input_command, "clearscherm") == 0)
	{
		gebruiker_input.command = commando_herkennen(input_string[COMMAND]);
		gebruiker_input.kleur = kleur_herkennen(input_string[1]);
	}

	else if (strcasecmp(input_command, "wacht") == 0)
	{
		gebruiker_input.command = commando_herkennen(input_string[COMMAND]);
		gebruiker_input.msecs = (volatile unsigned int)atoi(input_string[1]);
	}

	else
	{
		// geen geldige command
		// print error code (er is geen geldige command)
		UART_puts("none"); UART_puts("\r");
	}
}

uint8_t kleur_herkennen(char* kleur_string)
{
	uint8_t kleur = 0;

	if (strcasecmp(kleur_string, "zwart") == 0) 			kleur = 0;
	else if (strcasecmp(kleur_string, "wit") == 0) 			kleur = 255;
	else if (strcasecmp(kleur_string, "grijs") == 0)		kleur = 77;
	else if (strcasecmp(kleur_string, "blauw") == 0) 		kleur = 3;
	else if (strcasecmp(kleur_string, "lichtblauw") == 0) 	kleur = 115;
	else if (strcasecmp(kleur_string, "groen") == 0) 		kleur = 28;
	else if (strcasecmp(kleur_string, "lichtgroen") == 0) 	kleur = 29;
	else if (strcasecmp(kleur_string, "rood") == 0)			kleur = 224;
	else if (strcasecmp(kleur_string, "lichtrood") == 0) 	kleur = 233;
	else if (strcasecmp(kleur_string, "cyaan") == 0) 		kleur = 31;
	else if (strcasecmp(kleur_string, "lichtcyaan") == 0) 	kleur = 155;
	else if (strcasecmp(kleur_string, "magenta") == 0) 		kleur = 227;
	else if (strcasecmp(kleur_string, "lichtmagenta") == 0) kleur = 238;
	else if (strcasecmp(kleur_string, "geel") == 0) 		kleur = 252;
	else if (strcasecmp(kleur_string, "bruin") == 0) 		kleur = 104;
	else UART_puts("error: geen valide kleur meegegeven");

	return kleur;
}

uint8_t tekst_stijl_herkennen(char* stijl_string)
{
	uint8_t stijl = 0;

	if (strcasecmp(stijl_string, "norm") == 0)				stijl = NORM;
	else if (strcasecmp(stijl_string, "vet") == 0)			stijl = VET;
	else if (strcasecmp(stijl_string, "cursief") == 0)		stijl = CURSIEF;
	else UART_puts("error: geen valide stijl meegegeven");

	return stijl;
}

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



