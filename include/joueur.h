#ifndef _JOUEUR_H_
#define _JOUEUR_H_
#include "carte.h"

typedef struct player_s {
	carte_t * main[5];
	int jetons_stock;
	int jetons_mise;
	char * pseudo;
} player_t;

player_t * joueur_creer(void);
void joueur_detruire(player_t ** joueur);
void main_afficher(player_t * joueur);
void main_trier_desc(player_t * joueur);
int main_analyser(player_t * joueur);
int handValue(int value, int card);

#endif
