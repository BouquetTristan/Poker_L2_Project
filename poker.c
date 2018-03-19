#include <stdio.h>
#include "carte.h"
#include "jeu.h"
#include "joueur.h"
//#include "gui.h"
#include "mise.h"

int main(int argc, char * argv[]) { 
    int i, j;

    jeu_t * jeu; // declare un jeu de N cartes
    jeu = jeu_creer(); // alloue la mémoire à ce jeu
    jeu_initialiser(jeu); // affecte les couleurs et hauteurs de chaques cartes
    jeu_afficher(jeu); // affiche le jeu de cartes
    //printf("\nAPRES melange :\n\n");
    //jeu_melanger(jeu); // mélange le jeu de carte
    //jeu_afficher(jeu);
    

    /* test de la fonction egalite depuis mise.c */
    // creation de 5 joueurs
    player_t * liste_joueur[5];    
    for (int i = 0; i < 5; i++) {
        liste_joueur[i] = joueur_creer();
        printf("jetons en mise de joueur[%d] : %d\n", i, liste_joueur[i]->jetons_mise);
    }

    int egal = egalite(5, liste_joueur);
    printf("egalité ? %d\n", egal);


    liste_joueur[3]->jetons_mise = 34;
    egal = egalite(5, liste_joueur);
    printf("egalité ? %d\n", egal);  
	turnOfBet(jeu, liste_joueur, 5);	   

    // destruction des 5 joueurs
    for (int i = 0; i < 5; i++)
        joueur_detruire(&liste_joueur[i]);


    player_t * joueur;
    joueur = joueur_creer();
    joueur->jetons_stock = 567;
    strcpy(joueur->pseudo, "richard");
    printf("\n\njoueur prenom : %s\n", joueur->pseudo);
    printf("joueur nb jetons : %i\n", joueur->jetons_stock);
    printf("Main du joueur :\n");
    
    carte_distribuer(jeu, joueur, 47);
    carte_distribuer(jeu, joueur, 48);
    carte_distribuer(jeu, joueur, 49);
    carte_distribuer(jeu, joueur, 50);
    carte_distribuer(jeu, joueur, 51);

    main_trier_desc(joueur);
    printf("\n");
    main_afficher(joueur);

    int comb = main_analyser(joueur);
    printf("combinaison : %d\n", comb);

    //mise();
    
    jeu_detruire(&jeu);
    joueur_detruire(&joueur);
    
    /*
     * Partie SDL
     
    
    int window_mode = GUI_Init();
    int home_menu = 0;
    
    do {
        home_menu = GUI_HomeSelect(window_mode);
        if (home_menu == 1)
            GUI_Jouer(window_mode);
        else if (home_menu == 2)
            printf("Menu Réglages\n");
    } while (home_menu != 3);

    GUI_Quit();
	*/
    return EXIT_SUCCESS;
}
