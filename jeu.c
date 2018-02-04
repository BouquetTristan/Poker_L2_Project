#include "carte.h"
#include "jeu.h"

jeu_t * jeu_creer(void) {
	int i;
	jeu_t * jeu = malloc(sizeof(jeu_t)); // alloc memoire à l'objet jeu
	for(i = 0; i < N; i++)
		jeu->liste[i] = carte_creer(); // alloc memoire aux cartes du jeu
	return(jeu);
}

void jeu_detruire(jeu_t ** jeu) {
	int i;
	for(i = 0; i < N; i++)
		carte_detruire( &((*jeu)->liste[i]) );
	free(*jeu);
	*jeu = NULL;
}

void jeu_initialiser(jeu_t * jeu) {
	int i, j;
	for(i = 0; i < 4; i++) {
		for(j = 0; j < 13; j++) {
			strcpy(jeu->liste[i*13 + j]->couleur, tab_couleur[i]);
			strcpy(jeu->liste[i*13 + j]->hauteur, tab_hauteur[j]);
		}
	}
}

void jeu_afficher(jeu_t * jeu) {
	int i;
	for(i = 0; i < N; i++)
		printf("jeu[%i] : %s de %s\n", i, jeu->liste[i]->hauteur, jeu->liste[i]->couleur);
}