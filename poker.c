#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
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


    // SDL
    SDL_Surface* ecran = NULL, *menu = NULL, *cursor = NULL;
    SDL_Rect posMenu, posCursor;
    SDL_Event event;
    int continuer = 1;

    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetIcon(IMG_Load(JETON), NULL);
    SDL_WM_SetCaption("Poker", NULL);

    menu = IMG_Load(MENU_WALL);
    posMenu.x = 0;
    posMenu.y = 0;

    cursor = IMG_Load(JETON);
    posCursor.x = 216;
    posCursor.y = 330;

    SDL_EnableKeyRepeat(10, 100);
    SDL_ShowCursor(SDL_DISABLE);
    //SDL_WarpMouse(ecran->w /2, ecran->h /2);
    while(continuer) {
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                    case SDLK_UP:
                        posCursor.y = 330;
                        posCursor.x = 216;
                        break;
                    case SDLK_DOWN:
                        posCursor.y = 355;
                        posCursor.x = 275;
                        break;
                    case SDLK_RETURN:
                        if(posCursor.y == 330)
                            printf("jouer");
                        else
                            printf("quitter");
                        break;
                }
                break;
        }

        SDL_BlitSurface(menu, NULL, ecran, &posMenu);
        SDL_BlitSurface(cursor, NULL, ecran, &posCursor);
        SDL_Flip(ecran);

    }

    jeu_detruire(&jeu); // libere la memoire occupee par le jeu
    joueur_detruire(&joueur);
    SDL_FreeSurface(menu);
    SDL_FreeSurface(ecran);
    SDL_FreeSurface(cursor);
    SDL_Quit();

    return(EXIT_SUCCESS) ; 
}
