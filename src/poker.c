#include <stdio.h>
#include "carte.h"
#include "jeu.h"
#include "joueur.h"
#include "gui.h"
#include "mise.h"
#include "partie.h"

/**
    * \ file poker.c
    * \ author Poupin Romain, Bouquet Tristan
    * \ brief Fichier d'initialisation du jeu et de la SDL
    * \ date 2 Avril 2018
**/

int main(int argc, char * argv[]) { 
    jeu_t * jeu; // declare un jeu de N cartes
    jeu = jeu_creer(); // alloue la mémoire à ce jeu
    int nb_joueurs, nb_jetons_stock, gagnant;
    int continuer, home_menu = 0;
    
    printf("*** sélection du mode de l'écran ***\n");
    int window_mode = GUI_Init();
    if (window_mode) printf("mode PLEIN ECRAN sélectionné\n");
    else printf("mode FENETRE sélectionné\n");

    do {
        printf("\n*** choix menu principal ***\n");
        home_menu = GUI_HomeSelect(window_mode);
        if (home_menu == 1) {
            printf("menu JOUER sélectionné\n");
            continuer = GUI_InitRules(&nb_joueurs, &nb_jetons_stock, window_mode);
            if (continuer) {
                player_t * joueurs[nb_joueurs];
                continuer = GUI_CreatePlayers(joueurs, nb_joueurs, nb_jetons_stock, window_mode);
                if (continuer) {
                    printf("\n*** joueurs créés ***\n");
                    for (int cpt = 0; cpt < nb_joueurs; cpt++) {
                        printf("j%d - pseudo : '%s'\n", cpt+1, joueurs[cpt]->pseudo);
                        printf("j%d - jetons en stock : %d\n", cpt+1, joueurs[cpt]->jetons_stock);
                        printf("j%d - jetons en mise : %d\n", cpt+1, joueurs[cpt]->jetons_mise);
                        printf("j%d - actif : %d\n\n", cpt+1, joueurs[cpt]->actif);
                    }

                    printf("*** initialisation du jeu de %d cartes ***\n", N);
                    jeu_initialiser(jeu); // affecte les couleurs et hauteurs de chaques cartes
                    jeu_afficher(jeu);
                    printf("\n*** mélange du jeu de cartes ***\n");
                    jeu_melanger(jeu); // mélange le jeu de carte
                    jeu_afficher(jeu); // affiche le jeu de cartes
                    printf("\n*** distribution des cartes ***\n");
                    distribution_cartes(jeu, joueurs, nb_joueurs);
                    jeu_afficher(jeu); // affiche le jeu de cartes

                    printf("\n*** main des joueurs ***\n");
                    for (int i = 0; i < nb_joueurs; i++) { 
                        int comb = main_analyser(joueurs[i]);
                        printf("--> %s\n", joueurs[i]->pseudo);
                        main_afficher(joueurs[i]);
                        printf("code combinaison : %d\n\n", comb);
                    }

                    //partie(joueurs, nb_joueurs);
                    
                    //gagnant = GUI_Jouer(joueurs, nb_joueurs, window_mode);
                    //printf("*** gagant ***\n");
                    //printf("Félicitations %s ! Vous avez gagné avec %d jetons\n", joueurs[gagnant]->pseudo, joueurs[gagnant]->jetons_stock);

                    partie(joueurs, nb_joueurs);

                    printf("\n*** partie finie : %d joueurs à détruire ***\n", nb_joueurs);
                    for (int i = 0; i < nb_joueurs; i++) {
                        printf("destruction du joueur '%s'...\n", joueurs[i]->pseudo);
                        joueur_detruire(&joueurs[i]);
                    }
                }
            }
        }
        else if (home_menu == 2) {
            printf("menu CREDITS sélectionné\n");
            GUI_Credits(window_mode);
        }
    } while (home_menu != 3);

    printf("menu QUITTER sélectionné\n");
    GUI_Quit();
    return EXIT_SUCCESS;
}
