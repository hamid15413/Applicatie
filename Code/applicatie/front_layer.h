#ifndef front_layer_h
#define front_layer_h

#include "APIdraw.h"

typedef enum{
	LIJN,
	ELLIPS,
	RECHTHOEK,
	DRIEHOEK,
	TEKST,
	BITMAP,
	CLEARSCHERM,
	WACHT
} type_commando;

struct gebruiker_input;
struct {

	type_commando commando;
	uint16_t coordinaten;
	uint8_t kleur;

} gebruiker_input;





#endif /* front_layer_h */
