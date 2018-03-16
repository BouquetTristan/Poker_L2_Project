#ifndef _CARTE_H_
#define _CARTE_H_
#include "commun.h"

/* carte */
typedef struct carte_s {
	char * couleur;
	char * hauteur;
	char * owner;
} carte_t;

char * tab_couleur[4];
char * tab_hauteur[13];

carte_t * carte_creer(void);
void carte_detruire(carte_t ** carte);
int indice_hauteur(carte_t * carte);

#endif
