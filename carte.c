#include "carte.h"

/* allocation memoire */
carte_t * carte_creer(void) {
    carte_t * carte = malloc(sizeof(carte_t)); 
    carte->couleur = malloc(sizeof(char *));
    carte->hauteur = malloc(sizeof(char *));

    return(carte) ;
}

/* liberation memoire + pointeurs nuls */
void carte_detruire(carte_t ** carte) {
    free((*carte)->couleur);
    free((*carte)->hauteur);
    (*carte)->couleur = NULL;
    (*carte)->hauteur = NULL;

    free(*carte);
    *carte = NULL;
}

int indice_hauteur(carte_t * carte)
{
    int i;
    for(i = 0; i < 13; i++)
    {
        if(strcmp(carte->hauteur, tab_hauteur[i]) == 0)
            return i;
    }
}

/* couleurs possibles */
char * tab_couleur[4] = {
    "carreau",
    "coeur",
    "trefle",
    "pique"
};

/* hauteurs possibles */
char * tab_hauteur[13] = {
    "deux",
    "trois",
    "quatre",
    "cinq",
    "six",
    "sept",
    "huit",
    "neuf",
    "dix",
    "valet",
    "dame",
    "roi",
    "as"
};
