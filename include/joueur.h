#ifndef _JOUEUR_H_
#define _JOUEUR_H_
#include "carte.h"

typedef struct player_s {
	carte_t * cartePlayer[5];
	int token;
	char * name;
} player_t;

player_t * joueur_creer(void);
void joueur_detruire(player_t ** joueur);

#endif