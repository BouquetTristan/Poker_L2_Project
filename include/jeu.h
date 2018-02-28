#ifndef _JEU_H_
#define _JEU_H_
#include "commun.h"
#include "joueur.h"

/* jeu de cartes */
typedef struct jeu_s {
	int nb;
	carte_t * liste[N];
} jeu_t;

jeu_t * jeu_creer(void);
void jeu_detruire(jeu_t ** jeu);
void jeu_initialiser(jeu_t * jeu);
int init(int cpt);
void jeu_afficher(jeu_t * jeu);
void jeu_melanger(jeu_t * jeu);
void echanger_2cartes(carte_t * carte1, carte_t * carte2);
int pioche2main(jeu_t * jeu, player_t * joueur, int i);
int debarasser_carte(jeu_t * jeu, player_t * joueur, int i);
int handValue(int value, int card);
int combiner_jeu();

#endif
