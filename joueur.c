#include "joueur.h"

player_t * joueur_creer(void) {
	int i;
	player_t * joueur = malloc(sizeof(player_t));
	joueur->name = malloc(sizeof(char *));
	joueur->token = 0;
	for(i = 0; i < 5; i++)
	 joueur->cartePlayer[i] = NULL;
}

void joueur_detruire(player_t ** joueur) {
	int i;
	for(i = 0; i < 5; i++)
		(*joueur)->cartePlayer[i] = NULL;
	free((*joueur)->name);
	(*joueur)->name = NULL;
	free(*joueur);
	*joueur = NULL;
}

void afficher_main(player_t * joueur) {
	for (int i = 0; i < 5; i++) 
		if (joueur->cartePlayer[i] == NULL)
			printf("main[%d] : VIDE\n", i);
		else
			printf("main[%d] : %s de %s\n", i, joueur->cartePlayer[i]->hauteur, joueur->cartePlayer[i]->couleur);
}

void main_trier_desc(player_t * joueur) {
	// creer un tableau d'entiers correspondant a la hauteur des cartes (ordre décroissant)
	int cartes[5];
	for (int i = 0; i < 5; i++) {
		cartes[i] = indice_hauteur(joueur->cartePlayer[i]);
		//printf("main[%d] : %d\n", i, cartes[i]);
	}


	// tri par sélection des cartes de la main
	carte_t * c;
	int c1;
	for (int i = 0; i < 5; i++) {
	    for (int j = i+1; j < 5; j++) {
	        if (cartes[i] < cartes[j]) {
	        	c1 = cartes[i];
	            c = joueur->cartePlayer[i];

	            joueur->cartePlayer[i] = joueur->cartePlayer[j];
	            cartes[i] = cartes[j];

	            joueur->cartePlayer[j] = c;
	            cartes[j] = c1;
	        }	
	   	}
	}
}
