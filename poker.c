#include <stdio.h>
#include "carte.h"
#include "jeu.h"
#include "joueur.h"

int main(int argc, char * argv[]) { 
    int i, j;

    jeu_t * jeu; // declare un jeu de N cartes
    jeu = jeu_creer(); // alloue la mémoire à ce jeu
    jeu_initialiser(jeu); // affecte les couleurs et hauteurs de chaques cartes
    jeu_afficher(jeu); // affiche le jeu de cartes
    printf("\nAPRES melange :\n\n");
    jeu_melanger(jeu); // mélange le jeu de carte
    jeu_afficher(jeu);
    jeu_detruire(&jeu); // libere la memoire occupee par le jeu

    player_t * joueur;
    joueur = joueur_creer();
    joueur->token = 567;
    strcpy(joueur->name, "richard");
    printf("joueur prenom : %s\n", joueur->name);
    printf("joueur nb jetons : %i\n", joueur->token);
    joueur_detruire(&joueur);

    return(EXIT_SUCCESS) ; 
}
