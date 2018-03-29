#include "carte.h"
#include "jeu.h"
#include "time.h"
#include "mise.h"


int pot = 0;


int first_player(player_t * joueur[], int nbPlayer)
{
	for (int i = 0; i < nbPlayer; ++i)
	{
		if(joueur[i]->actif == 1)
			return i;
	}
	return 0;
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


void guessWinner()
{
	//Pas a faire par toi pour l'instant
}

void changer_carte(int carte[], int player, player_t * joueur[], jeu_t * jeu)
{
	int cpt = 0;
	while(cpt < 4 && carte[cpt] != 0)
	{
		carte_debarasser(jeu, joueur[player], carte[cpt]);
		
	}


}

void askCard(int player, player_t * joueur[], jeu_t * jeu)
{
	int carte[4];
	int exit, out, cpt = 0;
	int choix;


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
		if (choix == 0)
		{
			carte[cpt] = 0;
			exit = 1;
		}
		else
			printf("Carte inexistante\n");

		out = 0;
	}

	changer_carte(carte, player, joueur, jeu);

}

int miser(int player, player_t * joueur[], int jeton_suivi)
{
	int jeton;
	scanf("%i", &jeton);
	while(jeton < 0 || jeton > joueur[player]->jetons_stock - jeton_suivi)
	{
		printf("Vous n'avez pas autant de jeton\nVotre choix : ");
		scanf("%i", &jeton);
	}
	return jeton;
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

int reflate(int player, int nbPlayer, player_t * joueur[])
{
	int jeton;
	int jeton_suivi =  follow(player, nbPlayer, joueur);

	printf("Vous suivez de %i, de combien souhaitez vous relever\n", jeton_suivi);
	printf("Votre choix : ");
	jeton = miser(player, joueur, jeton_suivi);
	return jeton+jeton_suivi;
}

int all_in(int player, player_t * joueur[])
{
	return joueur[player]->jetons_stock;
}

void sleep(int player, player_t * joueur[])
{
	joueur[player]->actif = 0;	
}

int bet(int player, int nbPlayer, player_t * joueur[])
{
	int choice;
	int jeton = 0;
	int menu = 0;

	int first = first_player(joueur, nbPlayer);

	if(joueur[first]->jetons_mise == 0)
		menu = 1;

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


	switch(choice)
	{
		case 1: 
			if(menu == 0)
			{
				jeton = follow(player, nbPlayer, joueur);
				printf("Vous suivez à %i jetons\n", jeton);
				return jeton; 
			}
			else
				return miser(player, joueur, 0);
			break;
		
		case 2: 
			if (menu == 0)
				return reflate(player, nbPlayer, joueur); 
			else
			{
				printf("Vous checkez\n");
				return 0;
			}
			break;
		case 3: 
			jeton = all_in(player, joueur);
			printf("Vous faites un tapis à %i jetons\n", jeton);
			return jeton; 
			break;
		case 4: 
			printf("Vous vous couchez\n"); 
			sleep(player, joueur);
			return  0; 
			break;
		default : printf("Ce choix n'existe pas\n"); break;
	}
}

void maj_jetons(player_t * liste_joueur[], int i, int nbPlayer)
{

	int resultBet = 0;
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
		pot += resultBet;
		liste_joueur[i]->jetons_stock += liste_joueur[i]->jetons_mise - resultBet;
		liste_joueur[i]->jetons_mise = resultBet;
	}
}

void turnOfBet(jeu_t * jeu, int nbPlayer, player_t * liste_joueur[])
{

	int first; 

	for (int cpt_turn = 0; cpt_turn < 3; cpt_turn)
	{
		
		for (int i = 0; i < nbPlayer; ++i)
		{
			liste_joueur[i]->jetons_mise = 0;
		}
	
		do
		{
			for (int i = 0; i < nbPlayer; ++i)
			{
				first = first_player(liste_joueur, nbPlayer);
				if(!egalite(nbPlayer, liste_joueur))
					maj_jetons(liste_joueur, i, nbPlayer);
				
				else
				{
					if(i == first)
						maj_jetons(liste_joueur, i, nbPlayer);
				}
			}
		}
		while(!egalite(nbPlayer, liste_joueur));
		
		if (cpt_turn < 2)
		{
			for (int i = 0; i < nbPlayer; ++i)
			{
				askCard(i, liste_joueur, jeu);
			}
		}	
	}

	guessWinner();
}

