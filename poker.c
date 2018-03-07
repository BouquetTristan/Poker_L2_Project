#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "carte.h"
#include "jeu.h"
#include "joueur.h"
//#include "mise.h"

int fullscreenSelect(void) {
    TTF_Font *police = TTF_OpenFont("font/PokerKings-Regular.ttf", 50);
    SDL_Surface * texte = NULL;
    SDL_Rect textPos;
    SDL_Color couleurBlanche = {255, 255, 255};

    SDL_Surface * ecran = NULL, * menu = NULL, * cursor = NULL;
    SDL_Rect posMenu, posCursor;
    SDL_Event event;

    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetIcon(IMG_Load(JETON), NULL);
    SDL_WM_SetCaption("Mode de l'écran", NULL);

    menu = IMG_Load(MENU_WALL);
    posMenu.x = 0;
    posMenu.y = 0;

    cursor = IMG_Load(JETON);
    posCursor.x = LARGEUR_FENETRE/4 ;
    posCursor.y = HAUTEUR_FENETRE/4;

    textPos.x = LARGEUR_FENETRE/2 - LARGEUR_FENETRE/9;


     while(1) {
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT:
                return -1;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        if (posCursor.y == HAUTEUR_FENETRE/4)
                            posCursor.y = HAUTEUR_FENETRE/2;
                        else if (posCursor.y == HAUTEUR_FENETRE/2)
                            posCursor.y = HAUTEUR_FENETRE/4;
                        break;
                    case SDLK_DOWN:
                        if (posCursor.y == HAUTEUR_FENETRE/4)
                            posCursor.y = HAUTEUR_FENETRE/2;
                        else if (posCursor.y == HAUTEUR_FENETRE/2)
                            posCursor.y = HAUTEUR_FENETRE/4;
                        break;
                    case SDLK_RETURN:
                        if(posCursor.y == HAUTEUR_FENETRE/4)
                            return 1;
                        else
                            return 0;
                        break;
                }
                break;
        }

        SDL_BlitSurface(menu, NULL, ecran, &posMenu);
        SDL_BlitSurface(cursor, NULL, ecran, &posCursor);
        textPos.y = HAUTEUR_FENETRE/4;
        texte = TTF_RenderText_Blended(police, "Plein ecran", couleurBlanche);
        SDL_BlitSurface(texte, NULL, ecran, &textPos);
        textPos.y = HAUTEUR_FENETRE/2;
        texte = TTF_RenderText_Blended(police, "Fenetre", couleurBlanche);
        SDL_BlitSurface(texte, NULL, ecran, &textPos);
        SDL_Flip(ecran);

    }
    SDL_FreeSurface(menu);
    SDL_FreeSurface(cursor);
    SDL_FreeSurface(ecran);
}



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
    TTF_Init();
    TTF_Font *police = TTF_OpenFont("font/PokerKings-Regular.ttf", 50);
    SDL_Surface * texte = NULL;
    SDL_Rect textPos;
    SDL_Color couleurBlanche = {255, 255, 255};

    SDL_Surface* ecran = NULL, *menu = NULL, *cursor = NULL;
    SDL_Rect posMenu, posCursor;
    SDL_Event event;
    int continuer = 1;

    SDL_Init(SDL_INIT_VIDEO);

    int window_mode = fullscreenSelect();
    if (window_mode == 1)
        ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_FULLSCREEN | SDL_HWSURFACE | SDL_DOUBLEBUF);
    else
        ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetIcon(IMG_Load(JETON), NULL);
    SDL_WM_SetCaption("Poker", NULL);

    menu = IMG_Load(MENU_WALL);
    posMenu.x = 0;
    posMenu.y = 0;

    cursor = IMG_Load(JETON);
    posCursor.x = LARGEUR_FENETRE/4 ;
    posCursor.y = HAUTEUR_FENETRE/6;

    SDL_EnableKeyRepeat(10, 100);
    SDL_ShowCursor(SDL_DISABLE);
    //SDL_WarpMouse(ecran->w /2, ecran->h /2);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024); // initialisation de l'API SDL_mixer
    Mix_AllocateChannels(10);
    Mix_Volume(1, MIX_MAX_VOLUME);
    Mix_Chunk * musique; //Création du pointeur de type Mix_Music
    Mix_Chunk * select;
    Mix_Chunk * back;
    Mix_Chunk * enter;
    musique = Mix_LoadWAV("sound/Song_Remains_The_Same.wav"); //Chargement de la musique
    select = Mix_LoadWAV("sound/chipsStack1.wav");
    back = Mix_LoadWAV("sound/cardTakeOutPackage1.wav");
    enter = Mix_LoadWAV("sound/cardPlace1.wav");
    int vol = MIX_MAX_VOLUME/6;
    Mix_VolumeChunk(musique, vol);
    Mix_VolumeChunk(select, MIX_MAX_VOLUME);
    Mix_VolumeChunk(back, MIX_MAX_VOLUME);
    Mix_VolumeChunk(enter, MIX_MAX_VOLUME);
    Mix_PlayChannel(1, musique, -1); //Jouer infiniment la musique
    while(continuer) {
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        Mix_PlayChannel(3, back, 0);
                        break;
                    case SDLK_SPACE:
                        Mix_PlayChannel(3, back, 0);
                        break;
                    case SDLK_RIGHTPAREN:
                        vol -= 11;
                        if (vol < 0)
                            vol = 0;
                        Mix_VolumeChunk(musique, vol);
                        printf("vol:%d\n", vol);
                        break;
                    case SDLK_EQUALS:
                        vol += 11;
                        if (vol > 128)
                            vol = 128;
                        Mix_VolumeChunk(musique, vol);
                        printf("vol:%d\n", vol);
                        break;
                    case SDLK_UP:
                        Mix_PlayChannel(2, select, 0);
                        if (posCursor.y == HAUTEUR_FENETRE/6)
                            posCursor.y = HAUTEUR_FENETRE/2;
                        else if (posCursor.y == HAUTEUR_FENETRE/3)
                            posCursor.y = HAUTEUR_FENETRE/6;
                        else if (posCursor.y == HAUTEUR_FENETRE/2)
                            posCursor.y = HAUTEUR_FENETRE/3;
                        break;
                    case SDLK_DOWN:
                        Mix_PlayChannel(2, select, 0);
                        if (posCursor.y == HAUTEUR_FENETRE/6)
                            posCursor.y = HAUTEUR_FENETRE/3;
                        else if (posCursor.y == HAUTEUR_FENETRE/3)
                            posCursor.y = HAUTEUR_FENETRE/2;
                        else if (posCursor.y == HAUTEUR_FENETRE/2)
                            posCursor.y = HAUTEUR_FENETRE/6;
                        break;
                    case SDLK_RETURN:
                        Mix_PlayChannel(4, enter, 0);
                        if(posCursor.y == HAUTEUR_FENETRE/2)
                            continuer = 0;
                        else
                            printf("quitter");
                        break;
                }
                break;
        }

        SDL_BlitSurface(menu, NULL, ecran, &posMenu);
        SDL_BlitSurface(cursor, NULL, ecran, &posCursor);
        textPos.x = LARGEUR_FENETRE/2 - LARGEUR_FENETRE/9;
        textPos.y = HAUTEUR_FENETRE/6;
        texte = TTF_RenderText_Blended(police, "Jouer", couleurBlanche);
        SDL_BlitSurface(texte, NULL, ecran, &textPos);
        textPos.x = LARGEUR_FENETRE/2 - LARGEUR_FENETRE/9;
        textPos.y = HAUTEUR_FENETRE/3;
        texte = TTF_RenderText_Blended(police, "Reglages", couleurBlanche);
        SDL_BlitSurface(texte, NULL, ecran, &textPos);
        textPos.x = LARGEUR_FENETRE/2 - LARGEUR_FENETRE/9;
        textPos.y = HAUTEUR_FENETRE/2;
        texte = TTF_RenderText_Blended(police, "Quitter", couleurBlanche);
        SDL_BlitSurface(texte, NULL, ecran, &textPos);
        SDL_Flip(ecran);

    }

    jeu_detruire(&jeu); // libere la memoire occupee par le jeu
    joueur_detruire(&joueur);
    SDL_FreeSurface(menu);
    SDL_FreeSurface(ecran);
    SDL_FreeSurface(cursor);

    Mix_FreeChunk(musique); //Libération de la musique
    Mix_FreeChunk(select); //Libération de la musique
    Mix_FreeChunk(back); //Libération de la musique
    Mix_FreeChunk(enter); //Libération de la musique
    Mix_CloseAudio(); // fermeture de l'API SDL_mixer
    
    SDL_Quit();
    TTF_CloseFont(police);
    TTF_Quit();


    return(EXIT_SUCCESS) ; 
}
