#include "carte.h"
#include "jeu.h"
#include "time.h"
#include "mise.h"
#include "partie.h"

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
		printf("Bravo !!\n");
	}
	else
	{

		turnOfBet(jeu, nbJoueur, joueur);
		jeu_detruire(&jeu);
		partie(joueur, nbJoueur);
	}
}