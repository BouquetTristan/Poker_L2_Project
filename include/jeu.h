#ifndef _JEU_H_
#define _JEU_H_
#include "commun.h"

/* jeu de cartes */
typedef struct jeu_s {
	int nb;
	carte_t * liste[N];
} jeu_t;

jeu_t * jeu_creer(void);
void jeu_detruire(jeu_t ** jeu);
void jeu_initialiser(jeu_t * jeu);
void jeu_afficher(jeu_t * jeu);
void jeu_melanger(jeu_t * jeu);
void echanger_2cartes(carte_t * carte1, carte_t * carte2);

#endif
