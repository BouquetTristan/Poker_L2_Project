#include "gui.h"

int GUI_Init(void) {
    SDL_Init(SDL_INIT_VIDEO); // video
    TTF_Init(); // texte
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024); // initialisation de l'API SDL_mixer
    Mix_AllocateChannels(3);
    Mix_Volume(1, MIX_MAX_VOLUME);
    return GUI_WindowModeSelect();
}

void GUI_Quit(void) {
    Mix_CloseAudio(); // ferme l'API SDL_mixer
    TTF_Quit(); // ferme l'API SDL_ttf
    SDL_Quit(); // ferme l'API SDL
}

int GUI_WindowModeSelect(void) {
    TTF_Font *police = TTF_OpenFont("font/PokerKings-Regular.ttf", 50);
    SDL_Surface * texte = NULL, * ecran = NULL, * menu = NULL, * cursor = NULL;
    SDL_Rect textPos;
    SDL_Color couleurBlanche;
    couleurBlanche.r = 255;
    couleurBlanche.g = 255;
    couleurBlanche.b = 255;
    SDL_Rect posMenu, posCursor;
    SDL_Event event;

    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetIcon(IMG_Load(JETON), NULL);
    SDL_WM_SetCaption("Mode de l'écran", NULL);

    menu = IMG_Load(HOME_WALL);
    posMenu.x = 0;
    posMenu.y = 0;

    cursor = IMG_Load(JETON);
    posCursor.x = LARGEUR_FENETRE/4 ;
    posCursor.y = HAUTEUR_FENETRE/4;

    textPos.x = LARGEUR_FENETRE/2 - LARGEUR_FENETRE/9;

    while(1) {
        SDL_WaitEvent(&event);
        switch(event.type) {
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
                        SDL_FreeSurface(cursor);
                        SDL_FreeSurface(texte);
                        SDL_FreeSurface(menu);
                        SDL_FreeSurface(ecran);
                        TTF_CloseFont(police);
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
}

int GUI_HomeSelect(int window_mode) {
    TTF_Font *police = TTF_OpenFont("font/PokerKings-Regular.ttf", 50);
    SDL_Surface * texte = NULL, * ecran = NULL, * menu = NULL, * cursor = NULL;
    SDL_Rect textPos, posMenu, posCursor;
    SDL_Color couleurBlanche;
        couleurBlanche.r = 255;
        couleurBlanche.g = 255;
        couleurBlanche.b = 255;
    SDL_Event event;
    int continuer = 1;

    if (window_mode == 1)
        ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_FULLSCREEN | SDL_HWSURFACE | SDL_DOUBLEBUF);
    else
        ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    
    SDL_WM_SetIcon(IMG_Load(JETON), NULL);
    SDL_WM_SetCaption("Poker", NULL);

    menu = IMG_Load(HOME_WALL);
    posMenu.x = 0;
    posMenu.y = 0;

    cursor = IMG_Load(JETON);
    posCursor.x = LARGEUR_FENETRE/4 ;
    posCursor.y = HAUTEUR_FENETRE/6;

    SDL_EnableKeyRepeat(10, 100);
    SDL_ShowCursor(SDL_DISABLE);
    //SDL_WarpMouse(ecran->w /2, ecran->h /2);
    
    Mix_Chunk * musique = Mix_LoadWAV("sound/Song_Remains_The_Same.wav"); //Chargement de la musique
    Mix_Chunk * select = Mix_LoadWAV("sound/chipsStack1.wav");
    Mix_Chunk * back = Mix_LoadWAV("sound/cardTakeOutPackage1.wav");
    int vol = MIX_MAX_VOLUME/6;
    Mix_VolumeChunk(musique, vol);
    Mix_VolumeChunk(select, MIX_MAX_VOLUME);
    Mix_VolumeChunk(back, MIX_MAX_VOLUME);
    Mix_PlayChannel(0, musique, -1); //Jouer infiniment la musique
  
    while(continuer) {
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        Mix_PlayChannel(2, back, 0);
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
                        Mix_PlayChannel(1, select, 0);
                        if (posCursor.y == HAUTEUR_FENETRE/6)
                            posCursor.y = HAUTEUR_FENETRE/2;
                        else if (posCursor.y == HAUTEUR_FENETRE/3)
                            posCursor.y = HAUTEUR_FENETRE/6;
                        else if (posCursor.y == HAUTEUR_FENETRE/2)
                            posCursor.y = HAUTEUR_FENETRE/3;
                        break;
                    case SDLK_DOWN:
                        Mix_PlayChannel(1, select, 0);
                        if (posCursor.y == HAUTEUR_FENETRE/6)
                            posCursor.y = HAUTEUR_FENETRE/3;
                        else if (posCursor.y == HAUTEUR_FENETRE/3)
                            posCursor.y = HAUTEUR_FENETRE/2;
                        else if (posCursor.y == HAUTEUR_FENETRE/2)
                            posCursor.y = HAUTEUR_FENETRE/6;
                        break;
                    case SDLK_RETURN:
                        continuer = 0;
                        break;
                }
                break;
        }

        // affiche les elements
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
        // rafraichit l'ecran
        SDL_Flip(ecran);
    }
    
    // surface
    SDL_FreeSurface(cursor);
    SDL_FreeSurface(texte);
    SDL_FreeSurface(menu);
    SDL_FreeSurface(ecran);
    // son
    Mix_FreeChunk(musique);
    Mix_FreeChunk(select);
    Mix_FreeChunk(back);
    // texte
    TTF_CloseFont(police);
    if (posCursor.y == HAUTEUR_FENETRE/6)
        return 1;
    else if (posCursor.y == HAUTEUR_FENETRE/2)
        return 3;
    else
        return 2; 
}

void GUI_Jouer(int window_mode) {
    SDL_Surface
        * ecran = NULL,
        * table = NULL,
        * carte_recto = NULL,
        * carte_verso = NULL;
    
    SDL_Rect
        pos_source,
        pos_dest,
        pos_table;

    Mix_Chunk * musique; //Création du pointeur de type Mix_Music
    musique = Mix_LoadWAV("sound/No_Quarter.wav"); //Chargement de la musique
    int vol = MIX_MAX_VOLUME/6;
    Mix_VolumeChunk(musique, vol);
    Mix_PlayChannel(0, musique, -1); //Jouer infiniment la musique

    SDL_Event event;
    int continuer = 1;

    // plein ecran
    if (window_mode == 1)
        ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_FULLSCREEN | SDL_HWSURFACE | SDL_DOUBLEBUF);
    // fenetre
    else
        ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    SDL_WM_SetIcon(IMG_Load(JETON), NULL);
    SDL_WM_SetCaption("Jeu", NULL);

    // init l'img de la table
    table = IMG_Load(TABLE);
    pos_table.x = 70;
    pos_table.y = 124;

    // init l'img des cartes 
    carte_recto = IMG_Load(JEU_52_CARTES);
    pos_source.w = LARGEUR_CARTE;
    pos_source.h = HAUTEUR_CARTE;
    pos_dest.x = 300;
    pos_dest.y = 365;
    // selectionne la carte de coordonnées [5;3] depuis l'image
    pos_source.x = 5*LARGEUR_CARTE;
    pos_source.y = 3*HAUTEUR_CARTE;

    carte_verso = IMG_Load(VERSO_CARTE);

    while(continuer == 1) {
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                }
                break;
        }

        SDL_BlitSurface(table, NULL, ecran, &pos_table);
        pos_dest.x = 350;
        SDL_BlitSurface(carte_recto, &pos_source, ecran, &pos_dest);
        pos_dest.x += 112+10;
        SDL_BlitSurface(carte_recto, &pos_source, ecran, &pos_dest);
        pos_dest.x += 112+10;
        SDL_BlitSurface(carte_recto, &pos_source, ecran, &pos_dest);
        pos_dest.x += 112+10;
        SDL_BlitSurface(carte_recto, &pos_source, ecran, &pos_dest);
        pos_dest.x += 112+10;
        SDL_BlitSurface(carte_verso, NULL, ecran, &pos_dest);
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(carte_recto);
    SDL_FreeSurface(carte_verso);
    SDL_FreeSurface(table);
    SDL_FreeSurface(ecran);
    Mix_FreeChunk(musique);
}
