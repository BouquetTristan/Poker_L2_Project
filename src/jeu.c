#include "carte.h"
#include "jeu.h"
#include "time.h"

jeu_t * jeu_creer(void) {
	jeu_t * jeu = malloc(sizeof(jeu_t)); // alloc memoire au jeu de cartes
	for(int i = 0; i < N; i++)
		jeu->liste[i] = carte_creer(); // alloc memoire aux cartes de ce jeu
	return(jeu);
}

void jeu_detruire(jeu_t ** jeu) {
	for(int i = 0; i < N; i++)
		carte_detruire( &((*jeu)->liste[i]) );
	free(*jeu);
	*jeu = NULL;
}

void jeu_initialiser(jeu_t * jeu) {
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 13; j++) {
			strcpy(jeu->liste[i*13 + j]->couleur, tab_couleur[i]);
			strcpy(jeu->liste[i*13 + j]->hauteur, tab_hauteur[j]);
			strcpy(jeu->liste[i*13 + j]->owner, "pioche");
		}
	}
}

void jeu_afficher(jeu_t * jeu) {
	for (int i = 0; i < N; i++)
		printf("jeu[%i] : %s de %s [%s]\n", i, jeu->liste[i]->hauteur, jeu->liste[i]->couleur, jeu->liste[i]->owner);
}

void jeu_melanger(jeu_t * jeu) {
	int pos_carte1, pos_carte2;
	srand(time(NULL)); // initialisation de rand
	
	for (int i = 0; i < N; i++) {
		pos_carte1 = rand()%N;
		pos_carte2 = rand()%N;
		carte_echanger(jeu->liste[pos_carte1], jeu->liste[pos_carte2]);
	}
}

void carte_echanger(carte_t * carte1, carte_t * carte2) {
	char * hauteur_temp, * couleur_temp, * owner_temp;

	hauteur_temp = carte1->hauteur;
	couleur_temp = carte1->couleur;
	owner_temp = carte1->owner;

	carte1->hauteur = carte2->hauteur;
	carte1->couleur = carte2->couleur;
	carte1->owner = carte2->owner;

	carte2->hauteur = hauteur_temp;
	carte2->couleur = couleur_temp;
	carte2->owner = owner_temp;

	hauteur_temp = NULL; couleur_temp = NULL; owner_temp = NULL;
}

int carte_distribuer(jeu_t * jeu, player_t * joueur, int i) {
    if (!strcmp(jeu->liste[i]->owner, "pioche")) { // vérifie que la carte à distribuer est bien présente dans la pioche
        for (int j = 0; j < 5; j++) {
            if (joueur->main[j] == NULL) {
                joueur->main[j] = jeu->liste[i];
                strcpy(jeu->liste[i]->owner, joueur->pseudo);
                return 1;
            }             
        }
    }
    return 0;
}

int carte_debarasser(jeu_t * jeu, player_t * joueur, int i) {
	if (i >= 0 && i <= 4) { // verifie la valeur de l'indice i
		if (joueur->main[i] != NULL) { // verifie qu'une carte existe dans la main du joueur à l'indice i
			if (!strcmp(joueur->main[i]->owner, joueur->pseudo)) { // vérifie que la carte à jeter appartient bien au joueur
				strcpy(joueur->main[i]->owner, "poubelle"); // tag la carte comme "jetée" de la main d'un joueur
				joueur->main[i] = NULL; // défausse la carte de la main du joueur
		        return 1;	
			}
		}
	}
	return 0;
}
