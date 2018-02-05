#include "joueur.h"

player_t * joueur_creer(void) {
	int i;
	player_t * joueur = malloc(sizeof(player_t));
	joueur->name = malloc(sizeof(char *));
	joueur->token = 0;
	for(i = 0; i < 5; i++)
	 joueur->cartePlayer[i] = carte_creer();
}

void joueur_detruire(player_t ** joueur) {
	int i;
	for(i = 0; i < 5; i++)
		carte_detruire(&(*joueur)->cartePlayer[i]);
	free((*joueur)->name);
	(*joueur)->name = NULL;
	free(*joueur);
	*joueur = NULL;
}
