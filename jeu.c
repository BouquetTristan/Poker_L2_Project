#include "carte.h"
#include "jeu.h"
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
			strcpy(jeu->liste[i*13 + j]->prop, "pioche");
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
		printf("jeu[%i] : %s de %s [%s]\n", i, jeu->liste[i]->hauteur, jeu->liste[i]->couleur, jeu->liste[i]->prop);
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
	char * hauteur_temp, * couleur_temp, * prop_temp;
	hauteur_temp = carte1->hauteur;
	couleur_temp = carte1->couleur;
	prop_temp = carte1->prop;

	carte1->hauteur = carte2->hauteur;
	carte1->couleur = carte2->couleur;
	carte1->prop = carte2->prop;

	carte2->hauteur = hauteur_temp;
	carte2->couleur = couleur_temp;
	carte2->prop = prop_temp;

	hauteur_temp = NULL;
	couleur_temp = NULL;
	prop_temp = NULL;
}

int pioche2main(jeu_t * jeu, player_t * joueur, int i) {
    if (!strcmp(jeu->liste[i]->prop, "pioche")) { // vérifie que la carte à distribuer est bien présente dans la pioche
        for (int j = 0; j < 5; j++) {
            if (joueur->cartePlayer[j] == NULL) {
                joueur->cartePlayer[j] = jeu->liste[i];
                strcpy(jeu->liste[i]->prop, joueur->name);
                return 1;
            }             
        }
    }
    return 0;
}

int debarasser_carte(jeu_t * jeu, player_t * joueur, int i) {
	if (i >= 0 && i <= 4) { // verifie la valeur de l'indice i
		if (joueur->cartePlayer[i] != NULL) { // verifie qu'une carte existe dans la main du joueur à l'indice i
			if (!strcmp(joueur->cartePlayer[i]->prop, joueur->name)) { // vérifie que la carte à jeter appartient bien au joueur
				strcpy(joueur->cartePlayer[i]->prop, "jetee"); // tag la carte comme "jetée" de la main d'un joueur
				joueur->cartePlayer[i] = NULL; // défausse la carte de l amain du joueur
		        return 1;	
			}
		}
	}
	return 0;
}

int handValue(int value, int card)
{
	return(value*100+card);
}

int combiner_jeu(player_t * joueur)
{
	int i;
	int cpt = 0;

	int pair = 0, threeKind= 0, indCardThreeKind;

	player_t * joueurTemp;
    joueurTemp = joueur;


	/* Tests */

    
    /*Affecter les cartes du joueur à l'autre*/
	/*trier_carte()*/

    int indCard = indice_hauteur(joueurTemp->cartePlayer[0]);
    char * topCardCouleur = joueurTemp->cartePlayer[0]->couleur;


	/*Quinte Flush Royal*/
	for (int i = 0; i < 5; ++i)
	{
		/*If top card is an ace and if other card follow it*/
		if(strcmp(joueurTemp->cartePlayer[i]->hauteur, tab_hauteur[12-i]) == 0 &&
			strcmp(joueurTemp->cartePlayer[i]->couleur, topCardCouleur) == 0)
		{
			/*printf("n°%s topCardCouleur : %s      cartePlayer couleur : %s\n", tab_hauteur[12-i], topCardCouleur, joueurTemp->cartePlayer[i]->couleur);*/
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

		if(strcmp(joueurTemp->cartePlayer[i]->hauteur, tab_hauteur[indCard-i]) == 0 &&
			strcmp(joueurTemp->cartePlayer[i]->couleur, topCardCouleur) == 0)
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
	
			return(handValue(8, indCard));
		}	
	}
	indCard = indice_hauteur(joueurTemp->cartePlayer[0]);
	cpt = init(cpt);


	/*Full House*/
	for (int i = 0; i < 5; ++i)
	{
		if(strcmp(joueurTemp->cartePlayer[i]->hauteur, tab_hauteur[indCard]) == 0 )
			cpt++;
		else
		{

			printf("indCard b = %i\n", indCard);
			printf("cpt b = %i\n", cpt);

			if(cpt == 2)
			{
				indCard = indice_hauteur(joueurTemp->cartePlayer[2]);
				pair = 1;
				printf("pair b = %i\n", pair);
			}
			if(cpt == 3)
			{
				indCardThreeKind = indCard;
				indCard = indice_hauteur(joueurTemp->cartePlayer[3]);
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
			indCard = indice_hauteur(joueurTemp->cartePlayer[i]);
			pair = 1;
			printf("pair = %i\n", pair);
			cpt = init(cpt);
		}
		if(cpt == 3 && pair == 1)
		{
			indCardThreeKind = indCard;
			indCard = indice_hauteur(joueurTemp->cartePlayer[i]);
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

		if(strcmp(joueurTemp->cartePlayer[i]->couleur, topCardCouleur) == 0)
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

		if(strcmp(joueurTemp->cartePlayer[i]->hauteur, tab_hauteur[indCard-i]) == 0)
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

		if(strcmp(joueurTemp->cartePlayer[i]->hauteur, tab_hauteur[indCard]) == 0 )
			cpt++;
		else
		{
			cpt = init(cpt);
			cpt++;
			indCard = indice_hauteur(joueurTemp->cartePlayer[i]);
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

		if(strcmp(joueurTemp->cartePlayer[i]->hauteur, tab_hauteur[indCard]) == 0 )
			cpt++;
		else
		{
			cpt = init(cpt);
			cpt++;
			indCard = indice_hauteur(joueurTemp->cartePlayer[i]);
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

		if(strcmp(joueurTemp->cartePlayer[i]->hauteur, tab_hauteur[indCard]) == 0 )
			cpt++;
		else
		{
			cpt = init(cpt);
			cpt++;
			indCard = indice_hauteur(joueurTemp->cartePlayer[i]);
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
