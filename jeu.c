#include "carte.h"
#include "jeu.h"
#include "joueur.h"
#include "time.h"

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

void jeu_melanger(jeu_t * jeu) {
	int pos_carte1, pos_carte2, i;
	srand(time(NULL)); // initialisation de rand
	
	for(i = 0; i < N; i++) {
		pos_carte1 = rand()%N;
		pos_carte2 = rand()%N;
		echanger_2cartes(jeu->liste[pos_carte1], jeu->liste[pos_carte2]);
	}
}

void echanger_2cartes(carte_t * carte1, carte_t * carte2) {
	char * hauteur_temp, * couleur_temp;
	hauteur_temp = carte1->hauteur;
	couleur_temp = carte1->couleur;
	carte1->hauteur = carte2->hauteur;
	carte1->couleur = carte2->couleur;
	carte2->hauteur = hauteur_temp;
	carte2->couleur = couleur_temp;
	hauteur_temp = NULL;
	couleur_temp = NULL;
}


int combiner_jeu(player_t * joueur)
{
	int i;
	int cpt = 0;

	player_t * joueurTemp;
    joueurTemp = joueur_creer();
    /*Affecter les cartes du joueur à l'autre*/
	/*trier_carte()*/
    char indTopCard = indic_hauteur(cartePlayer[0]->hauteur);
    char topCardCouleur = joueurTemp->cartePlayer[0]->couleur;
	/*Quinte Flush Royal*/
	for (int i = 0; i < 5; ++i)
	{

		if(strcmp(joueurTemp->cartePlayer[i]->hauteur, tab_hauteur[12-i]) == 0 &&
			strcmp(joueurTemp->cartePlayer[i]->couleur, topCardCouleur) == 0)
		{
			cpt++;
			if(cpt == 4)
				return(10);
		}
	}

	/*Quinte Flush */
	for (int i = 0; i < 5; ++i)
	{

		if(strcmp(joueurTemp->cartePlayer[i], tab_hauteur[indTopCard-i]) == 0 &&
			strcmp(joueurTemp->cartePlayer[i]->couleur, topCardCouleur) == 0)
		{
			cpt++;
			if(cpt == 4)
				return(9);
		}
	}

	/*Carre*/
	for (int i = 0; i < 5; ++i)
	{

		if(strcmp(joueurTemp->cartePlayer[i], tab_hauteur[]) == 0 )
		{
			cpt++;
			if(cpt == 4)
				return(9);
		}
	}
	/*Full House*/
	/*Quinte*/
	/*Flush*/
	/*Brelan*/
	/*Double Pair*/
	/*Pair*/
	/*Top card*/

	joueur_detruire(&joueurTemp);
}