#include <stdio.h>
#include "gui.h"
#include "carte.h"
#include "jeu.h"
#include "joueur.h"
//#include "mise.h"


int main(int argc, char * argv[]) { 
    int i, j;

    jeu_t * jeu; // declare un jeu de N cartes
    jeu = jeu_creer(); // alloue la mémoire à ce jeu
    jeu_initialiser(jeu); // affecte les couleurs et hauteurs de chaques cartes
    jeu_afficher(jeu); // affiche le jeu de cartes
    //printf("\nAPRES melange :\n\n");
    //jeu_melanger(jeu); // mélange le jeu de carte
    //jeu_afficher(jeu);
    
    player_t * joueur;
    joueur = joueur_creer();
    joueur->token = 567;
    strcpy(joueur->name, "richard");
    printf("\n\njoueur prenom : %s\n", joueur->name);
    printf("joueur nb jetons : %i\n", joueur->token);
    printf("Main du joueur :\n");
    
    pioche2main(jeu, joueur, 47);
    pioche2main(jeu, joueur, 48);
    pioche2main(jeu, joueur, 49);
    pioche2main(jeu, joueur, 50);
    pioche2main(jeu, joueur, 51);

    main_trier_desc(joueur);
    printf("\n");
    afficher_main(joueur);

    int comb = combiner_jeu(joueur);
    printf("combinaison : %d\n", comb);

    //mise();


    /*
     * Partie SDL
     */ 

    int window_mode = GUI_init();

    int menu = GUI_home_menu(window_mode);
    while (menu != 3) {
        if (menu == 1)
            jouer(window_mode);
        else if (menu == 2)
            printf("Réglages\n");
        else if (menu == 3) {
            GUI_quit();
            jeu_detruire(&jeu);
            joueur_detruire(&joueur);
            return EXIT_SUCCESS;   
        }
        menu = GUI_home_menu(window_mode);
    }
}
