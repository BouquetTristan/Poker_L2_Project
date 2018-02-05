#include <stdio.h>
#include "carte.h"
#include "jeu.h"

int main(int argc, char * argv[]) { 
    int i, j;

    jeu_t * jeu; // declare un jeu de N cartes
    jeu = jeu_creer(); // alloue la mémoire à ce jeu
    jeu_initialiser(jeu); // affecte les couleurs et hauteurs de chaques cartes
    jeu_afficher(jeu); // affiche le jeu de cartes
    jeu_detruire(&jeu); // libere la memoire occupee par le jeu

    return(EXIT_SUCCESS) ; 
}
