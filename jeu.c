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

int init(int cpt)
{
	return(cpt = 0);
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

    strcpy(joueurTemp->cartePlayer[0]->hauteur, "six");
    strcpy(joueurTemp->cartePlayer[1]->hauteur, "cinq");
    strcpy(joueurTemp->cartePlayer[2]->hauteur, "quatre");
    strcpy(joueurTemp->cartePlayer[3]->hauteur, "trois");
    strcpy(joueurTemp->cartePlayer[4]->hauteur, "deux");
    strcpy(joueurTemp->cartePlayer[0]->couleur, "carreau");
    strcpy(joueurTemp->cartePlayer[1]->couleur, "carreau");
    strcpy(joueurTemp->cartePlayer[2]->couleur, "carreau");
    strcpy(joueurTemp->cartePlayer[3]->couleur, "carreau");
    strcpy(joueurTemp->cartePlayer[4]->couleur, "carreau");

    /*Affecter les cartes du joueur à l'autre*/
	/*trier_carte()*/

    int indCard = indice_hauteur(joueurTemp->cartePlayer[0]);
    char * topCardCouleur = joueurTemp->cartePlayer[0]->couleur;

    /* Tests */

    printf("as : %i\n", indice_hauteur(joueurTemp->cartePlayer[0]));
    printf("roi : %i\n", indice_hauteur(joueurTemp->cartePlayer[2]));

	/*Quinte Flush Royal*/
	for (int i = 0; i < 5; ++i)
	{

		if(strcmp(joueurTemp->cartePlayer[i]->hauteur, tab_hauteur[12-i]) == 0 &&
			strcmp(joueurTemp->cartePlayer[i]->couleur, topCardCouleur) == 0)
		{
			cpt++;
			if(cpt == 4)
			{
				joueur_detruire(&joueurTemp);
				return(10);
			}
		}
	}
	cpt = init(cpt);
	printf("indCard : %i\n", indCard);

	/*Quinte Flush */
	for (int i = 0; i < 5; ++i)
	{

		if(strcmp(joueurTemp->cartePlayer[i]->hauteur, tab_hauteur[indCard-i]) == 0 &&
			strcmp(joueurTemp->cartePlayer[i]->couleur, topCardCouleur) == 0)
		{
			cpt++;
			// printf("cpt = %i\n", cpt);
			if(cpt == 4)
			{
				joueur_detruire(&joueurTemp);
				return(9);
			}
		}
	}
	cpt = init(cpt);
	// printf("indCard : %i\n", indCard);

	/*Carre*/
	for (int i = 0; i < 5; ++i)
	{
		
		if(strcmp(joueurTemp->cartePlayer[i]->hauteur, tab_hauteur[indCard]) == 0 )
			cpt++;
		else
			cpt = init(cpt);
		// printf("cpt = %i\n", cpt);
		if(cpt == 0)
		{
			indCard = indice_hauteur(joueurTemp->cartePlayer[i]);
			cpt++;
		}

		if(cpt == 4)
		{
			joueur_detruire(&joueurTemp);
			return(8);
		}	
	}
	indCard = indice_hauteur(joueurTemp->cartePlayer[0]);
	cpt = init(cpt);
	// printf("indCard : %i\n", indCard);

	/*Full House*/
	for (int i = 0; i < 5; ++i)
	{
		int pair = 0, threeKind= 0;
		if(strcmp(joueurTemp->cartePlayer[i]->hauteur, tab_hauteur[indCard]) == 0 )
			cpt++;
		else
		{

			// printf("indCard b = %i\n", indCard);
			// printf("cpt b = %i\n", cpt);

			if(cpt == 2)
			{
				indCard = indice_hauteur(joueurTemp->cartePlayer[2]);
				pair = 1;
				// printf("pair b = %i\n", pair);
			}
			if(cpt == 3)
			{
				indCard = indice_hauteur(joueurTemp->cartePlayer[3]);
				threeKind = 1;
				// printf("threekind b = %i\n", threeKind);
			}
			cpt = init(cpt);
			cpt++;
		}
		// printf("indCard = %i\n", indCard);
		// printf("cpt = %i\n", cpt);

		if(cpt == 2)
		{
			indCard = indice_hauteur(joueurTemp->cartePlayer[i]);
			pair = 1;
			// printf("pair = %i\n", pair);
		}
		if(cpt == 3)
		{
			indCard = indice_hauteur(joueurTemp->cartePlayer[i]);
			threeKind = 1;
			// printf("threekind = %i\n", threeKind);
		}

		if (threeKind == 1 && pair == 1)
		{
			joueur_detruire(&joueurTemp);
			return(7);
		}


	}
	cpt = init(cpt);
	
	/*Flush*/
	for (int i = 0; i < 5; ++i)
	{

		if(strcmp(joueurTemp->cartePlayer[i]->couleur, topCardCouleur) == 0)
		{
			cpt++;
			if(cpt == 5)
			{
				joueur_detruire(&joueurTemp);
				return(6);
			}
		}
	}
	cpt = init(cpt);
	// printf("indCard : %i\n", indCard);
	/*Quinte*/
	for (int i = 0; i < 5; ++i)
	{

		if(strcmp(joueurTemp->cartePlayer[i]->hauteur, tab_hauteur[indCard-i]) == 0)
		{
			cpt++;
			if(cpt == 4)
			{
				joueur_detruire(&joueurTemp);
				return(5);
			}
		}
	}
	cpt = init(cpt);
	printf("indCard : %i\n", indCard);

	/*Brelan*/
	for (int i = 0; i < 5; ++i)
	{

		if(strcmp(joueurTemp->cartePlayer[i]->hauteur, tab_hauteur[indCard]) == 0 )
			cpt++;
		else
			cpt = init(cpt);

		if(cpt == 3)
		{
			joueur_detruire(&joueurTemp);
			return(7);
		}	
	}
	/*Double Pair*/
	/*Pair*/
	/*Top card*/

	joueur_detruire(&joueurTemp);

}