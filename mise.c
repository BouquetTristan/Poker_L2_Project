#include "carte.h"
#include "jeu.h"
#include "time.h"
#include "mise.h"



int egalite(int nbPlayer)
{
	
	for (int i = 0; i < nbPlayer; ++i)
	{
		if(joueur[0]->tokenTurn != joueur[i]->tokenTurn)
			return 0;
		return 1;
	}
}

int changeCard(int player)
{
	//Pas a faire par toi pour l'instant
}

void guessWinner()
{
	//Pas a faire par toi pour l'instant
}

int follow(int player, int nbPlayer, jeu_t * jeu)
{
	if(player == 0)
		return jeu->joueur[nbPlayer-1]->tokenTurn;
	return joueur[player-1]->tokenTurn;
}

int reflate(int player, int nbPlayer)
{
	int jeton;

	printf("Vous suivez de ???, de combien souhaitez vous relever\n");
	printf("Votre choix : ");
	scanf("%i", jeton);
	return jeton+follow(player, nbPlayer);
}

int all_in(int player)
{
	printf("Pas encore implémenté\n");
	return 1;
}

int bet(int player, int nbPlayer)
{
	int choice;
	int jeton = 0;

	printf("Que souhaitez vous faire ?\n");
	printf("1 - Suivre\n");
	printf("2 - Relancer\n");
	printf("3 - Tapis\n");
	printf("4 - Coucher\n");
	printf("Votre choix : ");
	scanf("%i", choice);

	switch(choice)
	{
		case 1: printf("Vous suivez de %i jetons\n", jeton); return follow(player, nbPlayer); break;
		case 2: printf("Vous relancer de %i jeton\n", jeton); return reflate(player, nbPlayer); break;
		case 3: printf("Vous faites un tapis à %i jetons\n", jeton); return all_in(player); break;
		case 4: printf("Vous vous couchez\n"); return sleep(player); break;
		default : printf("Ce choix n'existe pas\n"); break;
	}
}

void turnOfBet(int cpt_turn, jeu_t * jeu, int nbPlayer)
{

	int resultBet = 0;
	jeu->pot = 0;
	int i;

	if(cpt_turn == 3)
	{
		guessWinner();
	}
	else
	{
		for (int i = 0; i < nbPlayer; ++i)
		{
			joueur[i]->tokenTurn = 0;
		}

		do
		{
			for (i = 0; i < nbPlayer; ++i)
			{
				resultBet = bet(i, nbPlayer, jeu);
				jeu -> pot += resultBet;
				jeu->joueur[i]->token -= resultBet;
				jeu->joueur[i]->tokenTurn = resultBet;
			}
		}
		while(!egalite(nbPlayer));
		
		if (cpt_turn < 2)
		{
			for (i = 0; i < nbPlayer; ++i)
			{
				
				changeCard(i);
			}
		}
		
		turnOfBet(cpt_turn++);

	}
}

