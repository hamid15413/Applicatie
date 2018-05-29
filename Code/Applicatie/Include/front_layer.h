#ifndef front_layer_h
#define front_layer_h

#define MAX_AANTAL_WOORDEN 	30
#define COMMAND				0

enum commandos{
	LIJN,
	ELLIPS,
	RECHTHOEK,
	DRIEHOEK,
	TEKST,
	BITMAP,
	CLEARSCHERM,
	WACHT
};

enum stijls{
	NORM,
	VET,
	CURSIEF
};

struct {
	uint8_t		command,
				kleur,
				nr,
				stijl,
				dikte;

	uint16_t	x_mp,
				y_mp,
				radius_x,
				radius_y,
				x_lo,
				y_lo,
				x_rb,
				y_rb,
				x1,
				x2,
				x3,
				y1,
				y2,
				y3;

	volatile unsigned int msecs;

	char		tekst[255];

} gebruiker_input;

struct gebruiker_input;

char gebruiker_arr [255];

void user_input_init();
void lees_buffer();
void gebruiker_input_herkennen(char** input_string);

uint8_t commando_herkennen(char* commando_string);
uint8_t kleur_herkennen(char* kleur);
uint8_t tekst_stijl_herkennen(char* stijl_string);


#endif /* front_layer_h */
