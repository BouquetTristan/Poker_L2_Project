#include "carte.h"
#include "jeu.h"
#include "time.h"
#include "mise.h"
#include "gui.h"

/**
	* \ file mise.c
	* \ author Bouquet Tristan
	* \ brief Contient toutes les fonctionnalitées où le joueur peut jouer au jeu
	* \ date 2 Avril 2018
**/


int first_player(player_t * joueur[], int nbPlayer)
{
	for (int i = 0; i < nbPlayer; ++i)
	{
		if(joueur[i]->actif == 1)
			return i;
	}
	return 0;
}

int nb_joueur_actif(player_t * joueur[], int nbPlayer)
{
	int cpt = 0;
	for (int i = 0; i < nbPlayer; ++i)
	{
		if(joueur[i]->actif == 1)
			cpt++;
	}
	return cpt;
}

int egalite(int nbPlayer, player_t * joueur[])
{
	int first = first_player(joueur, nbPlayer);
	for (int i = 0; i < nbPlayer; ++i)
	{
		if (joueur[i]->actif == 1 && joueur[first]->jetons_mise != joueur[i]->jetons_mise)
			return 0;
	}
	return 1;
}


void guessWinner(player_t * joueur[], int nbPlayer, int pot)
{
	
	int tab_main[2][nbPlayer];
	int nbGagnant = 1;

	for (int i = 0; i < nbPlayer; ++i)
	{
		tab_main[0][i] = i;
		
		if (joueur[i]->actif == 1)
			tab_main[1][i] = main_analyser(joueur[i]);
		else
			tab_main[1][i] = 0;

		printf("J%i : %i\n", tab_main[0][i], tab_main[1][i]);
	}

	/*Algo de tri*/
	int tmp_ind, tmp_main;

	for (int i = 0; i < nbPlayer; ++i)
	{
		for (int j = i+1; j < nbPlayer; ++j)
		{
			if(tab_main[1][i] < tab_main[1][j])
			{
				tmp_main = tab_main[1][j];
				tmp_ind = tab_main[0][j];

				tab_main[1][j] = tab_main[1][i];
				tab_main[0][j] = tab_main[0][i];

				tab_main[1][i] = tmp_main;
				tab_main[0][i] = tmp_ind;
			}
		}
	}

	for (int i = 1; i < nbPlayer; ++i)
	{
		if(tab_main[1][i] == tab_main[1][0])
		{
			nbGagnant++;
		}
	}
	pot = pot/nbGagnant;
	for (int i = 0; i < nbGagnant; ++i)
	{
		joueur[tab_main[0][i]]->jetons_stock += pot;
	}

}

void changer_carte(int carte[], int player, player_t * joueur[], jeu_t * jeu)
{
	int cpt = 0;
	int pos;
	while(cpt < 4 && carte[cpt] != 0)
	{
		pos = top_game_card(jeu);
		carte_debarasser(jeu, joueur[player], carte[cpt]);
		carte_distribuer(jeu, joueur[player], pos);
		cpt++;
	}


}

void askCard(int player, player_t * joueur[], jeu_t * jeu)
{
	int carte[4];
	int exit = 0, out = 0, cpt = 0;
	int choix;

	for (int i = 0; i < 4; ++i)
	{
		carte[i] = 0;
	}

	if(joueur[player]->actif == 1)
	{
		while(cpt < 4 && exit != 1)
		{

			printf("Choisissez la carte à changer ( 0 -> stop) : ");
			scanf("%i", &choix);

			if(choix > 0 && choix < 6)
			{
				for (int j = 0; j < 4; ++j)
				{
					if(carte[j] == choix)
					{
						out = 1;
						printf("Carte déjà choisie\n");
					}
				}
				if (out != 1)
				{
					carte[cpt] = choix;
					cpt++;
				}				
			}
			for (int i = 0; i < 4; ++i)
			{
				printf("carte : %i\n", carte[i]);
			}
			if (choix == 0)
			{
				carte[cpt] = 0;
				exit = 1;
			}

			out = 0;
		}

	changer_carte(carte, player, joueur, jeu);
	}
}

int miser(int player, player_t * joueur[], int jeton_suivi, int qte)
{
	/*
	int jeton;
	scanf("%i", &jeton);
	while(jeton < 0 || jeton > joueur[player]->jetons_stock - jeton_suivi)
	{
		printf("Vous n'avez pas autant de jeton\nVotre choix : ");
		scanf("%i", &jeton);
	}*/
	if (qte < 0 || qte > joueur[player]->jetons_stock - jeton_suivi)
		return -1;
	else
		return qte;
}

int follow(int player, int nbPlayer, player_t * joueur[])
{	

	int i = 1;
	if(player > 0)
	{
		while(joueur[player-i]->actif == 0)
		{
			i++;
		}
		return joueur[player-i]->jetons_mise;
	}
	if(player == 0)
	{
		while(joueur[nbPlayer-i]->actif == 0)
		{
			i++;
		}
		return joueur[nbPlayer-i]->jetons_mise;
	}
}

/*
int reflate(int player, int nbPlayer, player_t * joueur[], int qte)
{
	int jeton;
	int jeton_suivi =  follow(player, nbPlayer, joueur);

	printf("Vous suivez de %i, de combien souhaitez vous relever\n", jeton_suivi);
	printf("Votre choix : ");
	jeton = miser(player, joueur, jeton_suivi, qte);
	return jeton+jeton_suivi;
}*/

int all_in(int player, player_t * joueur[])
{
	return joueur[player]->jetons_stock;
}

int sleep(int player, player_t * joueur[])
{
	joueur[player]->actif = 0;	
	return joueur[player]->jetons_mise;
}

int bet(int player, int nbPlayer, player_t * joueur[])
{
	int choice;
	int jeton = 0;
	int menu = 0;

	int first = first_player(joueur, nbPlayer);

	if(joueur[first]->jetons_mise == 0)
		menu = 1;

	int qte = 0;
	int error = 1;
	int jeton_suivi;
	do {
		choice = GUI_Jouer(joueur, nbPlayer, menu, &qte, 0);
		if (choice == 1 && menu == 1 && miser(player, joueur, 0, qte) == -1)
			error = 1;
		else if (choice == 2 && menu == 0) {
			jeton_suivi = follow(player, nbPlayer, joueur) ;
			if (miser(player, joueur, jeton_suivi, qte) == -1)
				error = 1;
		}
		else error = 0;
	}
	while (error == 1);

	/*
	printf("Que souhaitez vous faire ?\n");
	if(menu == 0)
		printf("1 - Suivre\n");
	else
		printf("1 - Miser\n");
	if(menu == 0)
		printf("2 - Relancer\n");
	else
		printf("2 - Checker\n");
	
	printf("3 - Tapis\n");
	printf("4 - Coucher\n");
	printf("Votre choix : ");
	scanf("%i", &choice);
	*/

	switch(choice) {
		case 1: 
			if(menu == 0)
				return follow(player, nbPlayer, joueur);
			else
				return qte;
			break;

		case 2: 
			if (menu == 0)
				return jeton+jeton_suivi; 
			else
				return 0;
			break;

		case 3: 
			return all_in(player, joueur); 
			break;

		case 4: 
			return  sleep(player, joueur); 
			break;

		default :
			printf("Ce choix n'existe pas\n");
			break;
	}
}

int maj_jetons(player_t * liste_joueur[], int i, int nbPlayer)
{

	int resultBet = 0;
	int pot = 0;
	if(liste_joueur[i]->actif)
	{
		for (int j = 0; j < nbPlayer; ++j)
		{
			printf("Joueur %i :\n", j);
			printf("Jetons : %i\n", liste_joueur[j]->jetons_stock);
			printf("Jetons misés : %i\n", liste_joueur[j]->jetons_mise);
		}

		printf("Joueur %i\n", i);
		resultBet = bet(i, nbPlayer, liste_joueur);
		liste_joueur[i]->jetons_stock += liste_joueur[i]->jetons_mise - resultBet;
		liste_joueur[i]->jetons_mise = resultBet;

		for (int i = 0; i < nbPlayer; ++i)
		{
			pot += liste_joueur[i]->jetons_mise;
			printf("Jetons misés : %i\n", liste_joueur[i]->jetons_mise);

		}
		return pot;
	}
}

void turnOfBet(jeu_t * jeu, int nbPlayer, player_t * liste_joueur[]) {
	int first, nb_j_actif;
	int pot = 0, pot_tour = 0;

	for (int cpt_turn = 0; cpt_turn < 3; cpt_turn++) 
	{
		for (int i = 0; i < nbPlayer; ++i)
			liste_joueur[i]->jetons_mise = 0;

		do {
			for (int i = 0; i < nbPlayer; ++i) 
			{
				first = first_player(liste_joueur, nbPlayer);
				nb_j_actif = nb_joueur_actif(liste_joueur, nbPlayer);
				if( nb_j_actif > 1)
				{	
					if (!egalite(nbPlayer, liste_joueur))
						pot_tour = maj_jetons(liste_joueur, i, nbPlayer);
					else {
						if (i == first)
							pot_tour = maj_jetons(liste_joueur, i, nbPlayer);
					}
				}		
			}
		
		} while (!egalite(nbPlayer, liste_joueur));
		
		pot += pot_tour;
		pot_tour = 0;
		printf("Pot : %i\n", pot);
		
		if (cpt_turn < 2 && nb_j_actif > 1) {
			for (int i = 0; i < nbPlayer; ++i)
				askCard(i, liste_joueur, jeu);
		}	
	}

	guessWinner(liste_joueur, nbPlayer, pot);

	for (int i = 0; i < nbPlayer; ++i) {
		printf("Joueur %i :\n", i);
		printf("Jetons : %i\n", liste_joueur[i]->jetons_stock);
	}
}

