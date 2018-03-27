#include "carte.h"
#include "jeu.h"
#include "time.h"
#include "mise.h"



int egalite(int nbPlayer, player_t * joueur[])
{
	for (int i = 0; i < nbPlayer; ++i)
	{
		if (joueur[0]->jetons_mise != joueur[i]->jetons_mise)
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
			if (out == 1)
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

int follow(int player, int nbPlayer, player_t * joueur[])
{
	if(player == 0)
		return joueur[nbPlayer-1]->jetons_mise;
	return joueur[player-1]->jetons_mise;
}

int reflate(int player, int nbPlayer, player_t * joueur[])
{
	int jeton;

	printf("Vous suivez de %i, de combien souhaitez vous relever\n", follow(player, nbPlayer, joueur));
	printf("Votre choix : ");
	scanf("%i", &jeton);
	return jeton+follow(player, nbPlayer, joueur);
}

int all_in(int player)
{
	printf("Pas encore implémenté\n");
	return 1;
}

int sleep(int player)
{
	printf("Pas encore implémenté\n");
	return 1;
}

int bet(int player, int nbPlayer, player_t * joueur[])
{
	int choice;
	int jeton = 0;

	printf("Que souhaitez vous faire ?\n");
	printf("1 - Suivre\n");
	printf("2 - Relancer\n");
	printf("3 - Tapis\n");
	printf("4 - Coucher\n");
	printf("Votre choix : ");
	scanf("%i", &choice);

	switch(choice)
	{
		case 1: printf("Vous suivez de %i jetons\n", jeton); return follow(player, nbPlayer, joueur); break;
		case 2: printf("Vous relancer de %i jeton\n", jeton); return reflate(player, nbPlayer, joueur); break;
		case 3: printf("Vous faites un tapis à %i jetons\n", jeton); return all_in(player); break;
		case 4: printf("Vous vous couchez\n"); return sleep(player); break;
		default : printf("Ce choix n'existe pas\n"); break;
	}
}

void turnOfBet(jeu_t * jeu, int nbPlayer, player_t * joueur[])
{

	int resultBet = 0;
	int pot = 0;
	int i;
	int cpt_turn = 0;

	if(cpt_turn == 3)
	{
		guessWinner();
	}
	else
	{
		for (int i = 0; i < nbPlayer; ++i)
		{
			joueur[i]->jetons_mise = 0;
		}
		/*
		do
		{
			for (i = 0; i < nbPlayer; ++i)
			{
				if(!egalite(nbPlayer, joueur))
				{
					resultBet = bet(i, nbPlayer, joueur);
					pot += resultBet;
					joueur[i]->jetons_stock -= resultBet;
					joueur[i]->jetons_mise = resultBet;
				}
			}
		}
		while(!egalite(nbPlayer, joueur));
		
		if (cpt_turn < 2)
		{
			for (i = 0; i < nbPlayer; ++i)
			{
				askCard(i, joueur, jeu);
			}
		}
		*/
	}
}

