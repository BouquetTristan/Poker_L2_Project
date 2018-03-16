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

	player_t * joueurTemp;
    joueurTemp = joueur;


	/* Tests */

    
    /*Affecter les cartes du joueur à l'autre*/
	/*trier_carte()*/

    int indCard = indice_hauteur(joueurTemp->main[0]);
    char * topCardCouleur = joueurTemp->main[0]->couleur;


	/*Quinte Flush Royal*/
	for (int i = 0; i < 5; ++i)
	{
		/*If top card is an ace and if other card follow it*/
		if(strcmp(joueurTemp->main[i]->hauteur, tab_hauteur[12-i]) == 0 &&
			strcmp(joueurTemp->main[i]->couleur, topCardCouleur) == 0)
		{
			/*printf("n°%s topCardCouleur : %s      main couleur : %s\n", tab_hauteur[12-i], topCardCouleur, joueurTemp->main[i]->couleur);*/
			cpt++;
			if(cpt == 5)
			{
		
				return(handValue(10, indCard));
			}
		}
	}
	cpt = init(cpt);


	/*Quinte Flush */
	for (int i = 0; i < 5; ++i)
	{

		if(strcmp(joueurTemp->main[i]->hauteur, tab_hauteur[indCard-i]) == 0 &&
			strcmp(joueurTemp->main[i]->couleur, topCardCouleur) == 0)
		{
			cpt++;
			// printf("cpt = %i\n", cpt);
			if(cpt == 5)
			{
		
				return(handValue(9, indCard));
			}
		}
	}
	cpt = init(cpt);


	/*Carre*/
	for (int i = 0; i < 5; ++i)
	{
		
		if(strcmp(joueurTemp->main[i]->hauteur, tab_hauteur[indCard]) == 0 )
			cpt++;
		else
			cpt = init(cpt);
		// printf("cpt = %i\n", cpt);
		if(cpt == 0)
		{
			indCard = indice_hauteur(joueurTemp->main[i]);
			cpt++;
		}

		if(cpt == 4)
		{
	
			return(handValue(8, indCard));
		}	
	}
	indCard = indice_hauteur(joueurTemp->main[0]);
	cpt = init(cpt);


	/*Full House*/
	for (int i = 0; i < 5; ++i)
	{
		if(strcmp(joueurTemp->main[i]->hauteur, tab_hauteur[indCard]) == 0 )
			cpt++;
		else
		{

			printf("indCard b = %i\n", indCard);
			printf("cpt b = %i\n", cpt);

			if(cpt == 2)
			{
				indCard = indice_hauteur(joueurTemp->main[2]);
				pair = 1;
				printf("pair b = %i\n", pair);
			}
			if(cpt == 3)
			{
				indCardThreeKind = indCard;
				indCard = indice_hauteur(joueurTemp->main[3]);
				threeKind = 1;
				printf("threekind b = %i\n", threeKind);
			}
			cpt = init(cpt);
			cpt++;
		}
		printf("indCard = %i\n", indCard);
		printf("cpt = %i\n", cpt);

		if(cpt == 2 && threeKind == 1)
		{
			indCard = indice_hauteur(joueurTemp->main[i]);
			pair = 1;
			printf("pair = %i\n", pair);
			cpt = init(cpt);
		}
		if(cpt == 3 && pair == 1)
		{
			indCardThreeKind = indCard;
			indCard = indice_hauteur(joueurTemp->main[i]);
			threeKind = 1;
			printf("threekind = %i\n", threeKind);
			cpt = init(cpt);
		}

		if (threeKind == 1 && pair == 1)
		{
	
			return(handValue(7, indCardThreeKind));
		}


	}
	cpt = init(cpt);
	

	/*Flush*/
	for (int i = 0; i < 5; ++i)
	{

		if(strcmp(joueurTemp->main[i]->couleur, topCardCouleur) == 0)
		{
			cpt++;
			if(cpt == 5)
			{
		
				return(handValue(6, indCard));
			}
		}
	}
	cpt = init(cpt);


	/*Quinte*/
	for (int i = 0; i < 5; ++i)
	{

		if(strcmp(joueurTemp->main[i]->hauteur, tab_hauteur[indCard-i]) == 0)
		{
			cpt++;
			if(cpt == 5)
			{
		
				return(handValue(5, indCard));
			}
		}
	}
	cpt = init(cpt);


	/*Brelan*/
	for (int i = 0; i < 5; ++i)
	{

		if(strcmp(joueurTemp->main[i]->hauteur, tab_hauteur[indCard]) == 0 )
			cpt++;
		else
		{
			cpt = init(cpt);
			cpt++;
			indCard = indice_hauteur(joueurTemp->main[i]);
		}

		if(cpt == 3)
		{
	
			return(handValue(4, indCard));
		}	
	}

	cpt = init(cpt);


	/*Double Pair*/
	pair = 0;
	
	for (int i = 0; i < 5; ++i)
	{

		if(strcmp(joueurTemp->main[i]->hauteur, tab_hauteur[indCard]) == 0 )
			cpt++;
		else
		{
			cpt = init(cpt);
			cpt++;
			indCard = indice_hauteur(joueurTemp->main[i]);
		}

		if(cpt == 2)
			pair++;
		if(pair == 2)
		{
	
			return(handValue(3, indCard));
		}
	}
	cpt = init(cpt);


	/*Pair*/
	for (int i = 0; i < 5; ++i)
	{

		if(strcmp(joueurTemp->main[i]->hauteur, tab_hauteur[indCard]) == 0 )
			cpt++;
		else
		{
			cpt = init(cpt);
			cpt++;
			indCard = indice_hauteur(joueurTemp->main[i]);
		}

		if(cpt == 2)
		{
	
			return(handValue(2, indCard));
		}	
	}
	cpt = init(cpt);

	/*Top card*/
	return(handValue(1, indCard));

}

int handValue(int value, int card)
{
	return(value*100+card);
}

int init(int cpt)
{
	return(cpt = 0);
}
