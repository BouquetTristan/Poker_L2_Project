#include "carte.h"
#include "jeu.h"
#include "time.h"
#include "mise.h"
#include "partie.h"

/**
	* \ file partie.c
	* \ author Bouquet Tristan
	* \ brief Fonction pour déterminer si le jeu peut continuer
	* \ date 2 Avril 2018
**/

int nb_joueur_debout(player_t * joueur[], int nbJoueur)
{
	int joueur_debout = 0;
	for (int i = 0; i < nbJoueur; ++i)
	{
		if(joueur[i]->jetons_stock > 0)
			joueur_debout++;
	}

	return joueur_debout;
}

void partie(player_t * joueur[], int nbJoueur)
{
	jeu_t * jeu;
	jeu = jeu_creer();
	jeu_initialiser(jeu);
    jeu_melanger(jeu);
    distribution_cartes(jeu, joueur, nbJoueur);

	int joueur_debout = nb_joueur_debout(joueur, nbJoueur);

	if (joueur_debout == 1)
	{
		//Fin de jeu
		jeu_detruire(&jeu);
		printf("Bravo !!\n");
	}
	else
	{
		for (int i = 0; i < nbJoueur; ++i)
		{
			if(joueur[i]->jetons_stock > 0)
				joueur[i]->actif = 1;
		}
		turnOfBet(jeu, nbJoueur, joueur);
		jeu_detruire(&jeu);
		partie(joueur, nbJoueur);
	}
}