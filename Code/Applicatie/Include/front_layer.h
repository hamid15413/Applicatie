#ifndef front_layer_h
#define front_layer_h

#define MAX_AANTAL_WOORDEN 	30
#define COMMAND				0

#define true 1
#define false 0

/* defineren van de kleurwaardes */
#define 	ZWART          	0x00
#define 	WIT          	0xFF
#define 	GRIJS			0X4D
#define 	BLAUW          	0x03
#define 	LICHT_BLAUW		0X73
#define 	GROEN          	0x1C
#define		LICHT_GROEN		0X1D
#define 	ROOD           	0xE0
#define		LICHT_ROOD		0XE9
#define 	CYAAN          	0x1F
#define		LICHT_CYAAN		0X9B
#define 	MAGENTA        	0xE3
#define		LICHT_MAGENTA	0XEE
#define 	GEEL         	0xFC
#define		BRUIN			0X68

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
	CURS
};

/* gebruikersinput struct */
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

	char		*tekst;

} gebruiker_input;

struct gebruiker_input;

/* error struct_flag is hoog wanneer struct correct gevuld is*/
uint8_t correct_struct;

/* Error codes */
static const char ERROR01[] = "ERROR01: Er is geen command meegegeven.";
static const char ERROR02[] = "ERROR02: Er is geen geldige command meegegeven.";
static const char ERROR03[] = "ERROR03: geen valide kleur meegegeven, kleur wordt default kleur (wit).";
static const char ERROR04[] = "ERROR04: geen valide stijl meegegeven, stijl wordt default stijl (norm).";


/* Warning codes */
static const char WARNING01[] = "WARNING01: de pixels bevinden zich buiten VGA range.";

/* functies initialiseren */
void user_input_init();
void lees_buffer();
void gebruiker_input_herkennen(char** input_string);
uint8_t commando_herkennen(char* commando_string);
uint8_t kleur_herkennen(char* kleur);
uint8_t tekst_stijl_herkennen(char* stijl_string);

#endif /* front_layer_h */
