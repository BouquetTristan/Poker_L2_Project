#include "joueur.h"

player_t * joueur_creer(void) {
	player_t * joueur = malloc(sizeof(player_t));
	joueur->pseudo = malloc(sizeof(char *));
	joueur->jetons_stock = 0;
	joueur->jetons_mise = 0;
	for(int i = 0; i < 5; i++)
		joueur->main[i] = NULL;
}

void joueur_detruire(player_t ** joueur) {
	for(int i = 0; i < 5; i++)
		(*joueur)->main[i] = NULL;
	free((*joueur)->pseudo);
	(*joueur)->pseudo = NULL;
	free(*joueur);
	*joueur = NULL;
}

void main_afficher(player_t * joueur) {
	for (int i = 0; i < 5; i++) 
		if (joueur->main[i] == NULL)
			printf("main[%d] : VIDE\n", i);
		else
			printf("main[%d] : %s de %s\n", i, joueur->main[i]->hauteur, joueur->main[i]->couleur);
}

void main_trier_desc(player_t * joueur) {
	// creer un tableau d'entiers correspondant a la hauteur des cartes (ordre décroissant)
	int cartes[5];
	for (int i = 0; i < 5; i++)
		cartes[i] = indice_hauteur(joueur->main[i]);

	// tri par sélection des cartes de la main
	carte_t * c;
	int c1;
	for (int i = 0; i < 5; i++) {
	    for (int j = i+1; j < 5; j++) {
	        if (cartes[i] < cartes[j]) {
	        	c1 = cartes[i];
	            c = joueur->main[i];

	            joueur->main[i] = joueur->main[j];
	            cartes[i] = cartes[j];

	            joueur->main[j] = c;
	            cartes[j] = c1;
	        }	
	   	}
	}
}

int main_analyser(player_t * joueur)
{
	int i;
	int cpt = 0;

	int pair = 0, threeKind= 0, indCardThreeKind;

    
    int indCard = indice_hauteur(joueur->main[0]);
    char * topCardCouleur = joueur->main[0]->couleur;


	/*Quinte Flush Royal*/
	for (i = 0; i < 5; ++i)
	{
		/*If top card is an ace and if other card follow it*/
		if(strcmp(joueur->main[i]->hauteur, tab_hauteur[12-i]) == 0 &&
			strcmp(joueur->main[i]->couleur, topCardCouleur) == 0)
		{
			
			cpt++;
			if(cpt == 5)
				return(handValue(10, indCard));
		}
	}
	cpt = 0;


	/*Quinte Flush */
	for (i = 0; i < 5; ++i)
	{

		if(strcmp(joueur->main[i]->hauteur, tab_hauteur[indCard-i]) == 0 &&
			strcmp(joueur->main[i]->couleur, topCardCouleur) == 0)
		{
			cpt++;
			// printf("cpt = %i\n", cpt);

			if(cpt == 5)
				return(handValue(9, indCard));
		}
	}
	cpt = 0;


	/*Carre*/
	for (i = 0; i < 5; ++i)
	{
		
		if(strcmp(joueur->main[i]->hauteur, tab_hauteur[indCard]) == 0 )
			cpt++;
		else
			cpt = 0;
		// printf("cpt = %i\n", cpt);
		if(cpt == 0)
		{
			indCard = indice_hauteur(joueur->main[i]);
			cpt++;
		}

		if(cpt == 4)
			return(handValue(8, indCard));	
	}

	indCard = indice_hauteur(joueur->main[0]);
	cpt = 0;


	/*Full House*/
	for (i = 0; i < 5; ++i)
	{
		if(strcmp(joueur->main[i]->hauteur, tab_hauteur[indCard]) == 0 )
			cpt++;
		else
		{
			if(cpt == 2)
			{
				indCard = indice_hauteur(joueur->main[2]);
				pair = 1;
			}
			if(cpt == 3)
			{
				indCardThreeKind = indCard;
				indCard = indice_hauteur(joueur->main[3]);
				threeKind = 1;
			}
			cpt = 0;
			cpt++;
		}

		if(cpt == 2 && threeKind == 1)
		{
			indCard = indice_hauteur(joueur->main[i]);
			pair = 1;
		}
		if(cpt == 3 && pair == 1)
		{
			indCardThreeKind = indCard;
			indCard = indice_hauteur(joueur->main[i]);
			threeKind = 1;
		}

		cpt = 0;

		if (threeKind == 1 && pair == 1)
			return(handValue(7, indCardThreeKind));

	}

	cpt = 0;
	

	/*Flush*/
	for (i = 0; i < 5; ++i)
	{

		if(strcmp(joueur->main[i]->couleur, topCardCouleur) == 0)
		{
			cpt++;
			if(cpt == 5)
				return(handValue(6, indCard));
		}
	}
	cpt = 0;


	/*Quinte*/
	for (i = 0; i < 5; ++i)
	{

		if(strcmp(joueur->main[i]->hauteur, tab_hauteur[indCard-i]) == 0)
		{
			cpt++;
			if(cpt == 5)
				return(handValue(5, indCard));
		}
	}
	cpt = 0;


	/*Brelan*/
	for (i = 0; i < 5; ++i)
	{

		if(strcmp(joueur->main[i]->hauteur, tab_hauteur[indCard]) == 0 )
			cpt++;
		else
		{
			cpt = 1;
			indCard = indice_hauteur(joueur->main[i]);
		}

		if(cpt == 3)
			return(handValue(4, indCard));
	}

	cpt = 0;


	/*Double Pair*/
	pair = 0;
	
	for (i = 0; i < 5; ++i)
	{

		if(strcmp(joueur->main[i]->hauteur, tab_hauteur[indCard]) == 0 )
			cpt++;
		else
		{
			cpt = 0;
			cpt++;
			indCard = indice_hauteur(joueur->main[i]);
		}

		if(cpt == 2)
			pair++;

		if(pair == 2)
			return(handValue(3, indCard));
	}
	cpt = 0;


	/*Pair*/
	for (i = 0; i < 5; ++i)
	{

		if(strcmp(joueur->main[i]->hauteur, tab_hauteur[indCard]) == 0 )
			cpt++;
		else
		{
			cpt = 0;
			cpt++;
			indCard = indice_hauteur(joueur->main[i]);
		}

		if(cpt == 2)
			return(handValue(2, indCard));
	}
	cpt = 0;

	/*Top card*/
	return(handValue(1, indCard));

}

int handValue(int value, int card)
{
	return(value*100+card);
}
