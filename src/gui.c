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
    TTF_Font *police = TTF_OpenFont(MENU_FONT, 50);
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

void GUI_Credits(int window_mode) {
    TTF_Font *police = TTF_OpenFont(MENU_FONT, 50);
    TTF_Font *police_small = TTF_OpenFont(MENU_FONT, 25);
    SDL_Surface * texte = NULL, * ecran = NULL, * menu = NULL;
    SDL_Rect textPos;
    SDL_Color couleurBlanche;
    couleurBlanche.r = 255;
    couleurBlanche.g = 255;
    couleurBlanche.b = 255;
    SDL_Rect posMenu;
    SDL_Event event;

    // reglages fenetre
    if (window_mode == 1) ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_FULLSCREEN | SDL_HWSURFACE | SDL_DOUBLEBUF);
    else ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetIcon(IMG_Load(JETON), NULL);
    SDL_WM_SetCaption("Credits", NULL);

    menu = IMG_Load(HOME_WALL);
    posMenu.x = 0;
    posMenu.y = 0;

    int continuer = 1;
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

        SDL_BlitSurface(menu, NULL, ecran, &posMenu);

        textPos.x = (LARGEUR_FENETRE/20)*7;
        textPos.y = (HAUTEUR_FENETRE/20)*2;
        texte = TTF_RenderText_Blended(police, "Poker PC - 1.0", couleurBlanche);
        SDL_BlitSurface(texte, NULL, ecran, &textPos);

        textPos.x = (LARGEUR_FENETRE/10)*2;
        textPos.y = (HAUTEUR_FENETRE/20)*4;
        texte = TTF_RenderText_Blended(police_small, "https://github.com/BouquetTristan/Poker_L2_Project", couleurBlanche);
        SDL_BlitSurface(texte, NULL, ecran, &textPos);

        textPos.x = (LARGEUR_FENETRE/20)*8;
        textPos.y = (HAUTEUR_FENETRE/20)*7;
        texte = TTF_RenderText_Blended(police, "Credits", couleurBlanche);
        SDL_BlitSurface(texte, NULL, ecran, &textPos);

        textPos.x = (LARGEUR_FENETRE/10)*2;
        textPos.y = (HAUTEUR_FENETRE/20)*9;
        texte = TTF_RenderText_Blended(police_small, "Romain Poupin  -  https://github.com/Romreventon", couleurBlanche);
        SDL_BlitSurface(texte, NULL, ecran, &textPos);

        textPos.x = (LARGEUR_FENETRE/10)*2;
        textPos.y = (HAUTEUR_FENETRE/20)*10;
        texte = TTF_RenderText_Blended(police_small, "Tristan Bouquet  -  https://github.com/BouquetTristan", couleurBlanche);
        SDL_BlitSurface(texte, NULL, ecran, &textPos);

        textPos.x = (LARGEUR_FENETRE/10)*2;
        textPos.y = (HAUTEUR_FENETRE/20)*11;
        texte = TTF_RenderText_Blended(police_small, "William Njofang Ngassam  -  https://github.com/Njofang", couleurBlanche);
        SDL_BlitSurface(texte, NULL, ecran, &textPos);

        SDL_Flip(ecran);
    }
    SDL_FreeSurface(texte);
    SDL_FreeSurface(menu);
    SDL_FreeSurface(ecran);
    TTF_CloseFont(police);
}

int GUI_HomeSelect(int window_mode) {
    TTF_Font *police = TTF_OpenFont(MENU_FONT, 50);
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
    
    Mix_Chunk * musique = Mix_LoadWAV(HOME_MUSIC); //Chargement de la musique
    Mix_Chunk * select = Mix_LoadWAV(MOVE_CURSOR);
    Mix_Chunk * back = Mix_LoadWAV(BACK);
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
        texte = TTF_RenderText_Blended(police, "Credits", couleurBlanche);
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
    musique = Mix_LoadWAV(IN_GAME_MUSIC); //Chargement de la musique
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
    // selectionne la carte depuis l'image
    pos_source.x = AS_PIC_X*LARGEUR_CARTE;
    pos_source.y = AS_PIC_Y*HAUTEUR_CARTE;

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

int GUI_InitRules(int * nb_joueurs, int * nb_jetons_stock, int window_mode) {
    *nb_joueurs = 2; *nb_jetons_stock = 100;
    char nb_players_str[20], nb_jetons_stock_str[330];
    TTF_Font *police = TTF_OpenFont(MENU_FONT, 50);
    SDL_Surface * msg = NULL, * nb_tokens = NULL, * nb_players = NULL, * ecran = NULL, * menu = NULL, * cursor = NULL;
    SDL_Rect posMsg, posNbPlayers, posNbTokens, posMenu, posCursor;
    SDL_Color couleurBlanche;
        couleurBlanche.r = 255;
        couleurBlanche.g = 255;
        couleurBlanche.b = 255;
    SDL_Event event;
    int continuer = 1;
    int escape = 0;

    if (window_mode == 1)
        ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_FULLSCREEN | SDL_HWSURFACE | SDL_DOUBLEBUF);
    else
        ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    
    SDL_WM_SetIcon(IMG_Load(JETON), NULL);
    SDL_WM_SetCaption("Poker", NULL);

    menu = IMG_Load(HOME_WALL);
    posMenu.x = 0;
    posMenu.y = 0;

    posMsg.x = (LARGEUR_FENETRE/10)*2;

    cursor = IMG_Load(JETON);
    posCursor.x = (LARGEUR_FENETRE/10)*1;
    posCursor.y = (HAUTEUR_FENETRE/12)*3;

    posNbPlayers.x = (LARGEUR_FENETRE/10)*6;
    posNbPlayers.y = (HAUTEUR_FENETRE/12)*3;
    sprintf(nb_players_str, "%d", *nb_joueurs);    

    posNbTokens.x = (LARGEUR_FENETRE/10)*6;
    posNbTokens.y = (HAUTEUR_FENETRE/12)*5;
    sprintf(nb_jetons_stock_str, "%d", *nb_jetons_stock);

    SDL_EnableKeyRepeat(10, 100);
    SDL_ShowCursor(SDL_DISABLE);
    //SDL_WarpMouse(ecran->w /2, ecran->h /2);
    
    Mix_Chunk * select = Mix_LoadWAV(MOVE_CURSOR);
    Mix_Chunk * back = Mix_LoadWAV(BACK);
    int vol = MIX_MAX_VOLUME/6;
    Mix_VolumeChunk(select, MIX_MAX_VOLUME);
    Mix_VolumeChunk(back, MIX_MAX_VOLUME);
  
    while(continuer) {
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        Mix_PlayChannel(2, back, 0);
                        continuer = 0; escape = 1;
                        break;
                    case SDLK_UP:
                        if (posCursor.y == (HAUTEUR_FENETRE/12)*3)
                            posCursor.y = (HAUTEUR_FENETRE/12)*5;  
                        else
                            posCursor.y -= 2*(HAUTEUR_FENETRE/12);  
                        break;
                    case SDLK_DOWN:
                        if (posCursor.y == (HAUTEUR_FENETRE/12)*5)
                            posCursor.y = (HAUTEUR_FENETRE/12)*3;
                        else
                            posCursor.y += 2*(HAUTEUR_FENETRE/12);
                        break;
                    case SDLK_RIGHT:
                        Mix_PlayChannel(1, select, 0);
                        if (posCursor.y == (HAUTEUR_FENETRE/12)*3) {
                            if (*nb_joueurs != 5)
                                *nb_joueurs = *nb_joueurs+1;
                        }
                        else {
                            if (*nb_jetons_stock != 5000)
                                *nb_jetons_stock = *nb_jetons_stock+100;   
                        }
                        break;
                    case SDLK_LEFT:
                        Mix_PlayChannel(1, select, 0);
                        if (posCursor.y == (HAUTEUR_FENETRE/12)*3) {
                            if (*nb_joueurs != 2)
                                *nb_joueurs = *nb_joueurs-1;
                        }
                        else {
                            if (*nb_jetons_stock != 100)
                                *nb_jetons_stock = *nb_jetons_stock-100;   
                        }
                        break;
                    case SDLK_RETURN:
                        continuer = 0;
                        break;
                }
                break;
        }

        SDL_BlitSurface(menu, NULL, ecran, &posMenu);
        SDL_BlitSurface(cursor, NULL, ecran, &posCursor);
       
        posMsg.y = (HAUTEUR_FENETRE/12)*3;
        msg = TTF_RenderText_Blended(police, "Joueurs", couleurBlanche);
        SDL_BlitSurface(msg, NULL, ecran, &posMsg);

        posMsg.y = (HAUTEUR_FENETRE/12)*5;
        msg = TTF_RenderText_Blended(police, "Jetons de depart", couleurBlanche);
        SDL_BlitSurface(msg, NULL, ecran, &posMsg);

        sprintf(nb_players_str, "< %d >", *nb_joueurs);
        nb_players = TTF_RenderText_Blended(police, nb_players_str, couleurBlanche);    
        SDL_BlitSurface(nb_players, NULL, ecran, &posNbPlayers);

        sprintf(nb_jetons_stock_str, "< %d >", *nb_jetons_stock);
        nb_tokens = TTF_RenderText_Blended(police, nb_jetons_stock_str, couleurBlanche);    
        SDL_BlitSurface(nb_tokens, NULL, ecran, &posNbTokens);

        SDL_Flip(ecran);
    }
    
    // surface
    SDL_FreeSurface(msg);
    SDL_FreeSurface(menu);
    SDL_FreeSurface(ecran);
    SDL_FreeSurface(nb_players);
    SDL_FreeSurface(nb_tokens);
    SDL_FreeSurface(cursor);
    // son
    Mix_FreeChunk(select);
    Mix_FreeChunk(back);
    // texte
    TTF_CloseFont(police);

    if (escape) return 0;
    else return 1;
}

int GUI_CreatePlayers(player_t * joueurs[], int nb_joueurs, int nb_jetons_stock, int window_mode) {
    char 
        joueur_courant_str[3],
        pseudos[nb_joueurs][11],
        pseudo[11] = "__________",
        msg[30],
        touche;
    

    for (int i = 0; i < nb_joueurs; i++)  {
        strcpy(pseudos[i], "__________");
        printf("pseudos[%d] : '%s'\n", i, pseudos[i]);
    }

    SDL_Surface
        * msg_surf = NULL,
        * msg_error = NULL,
        * pseudo_surf = NULL,
        * ecran = NULL,
        * wall = NULL;
    
    SDL_Rect
        pos_msg,
        pos_msg_error,
        pos_pseudo,
        pos_wall;

    SDL_Color couleurBlanche;
    couleurBlanche.r = 255;
    couleurBlanche.g = 255;
    couleurBlanche.b = 255;

    SDL_Color couleurRouge;
    couleurRouge.r = 255;
    couleurRouge.g = 0;
    couleurRouge.b = 0;

    TTF_Font * police = TTF_OpenFont(MENU_FONT, 50);
    SDL_Event event;
    int continuer = 1; // on continue par defaut
    int escape = 0; // on ne quitte pas par defaut
    int joueur_courant = 0;
    int pos_char = -1;
    int existe_deja = 0;


    // reglages fenetre
    if (window_mode == 1) ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_FULLSCREEN | SDL_HWSURFACE | SDL_DOUBLEBUF);
    else ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetIcon(IMG_Load(JETON), NULL);
    SDL_WM_SetCaption("Poker", NULL);


    wall = IMG_Load(HOME_WALL);
    pos_wall.x = 0;
    pos_wall.y = 0;

    pos_msg.x = (LARGEUR_FENETRE/12)*2;
    pos_msg.y = (HAUTEUR_FENETRE/10)*3;

    pos_msg_error.x = (LARGEUR_FENETRE/12)*3;
    pos_msg_error.y = (HAUTEUR_FENETRE/10)*5;

    pos_pseudo.x = (LARGEUR_FENETRE/10)*6;
    pos_pseudo.y = (HAUTEUR_FENETRE/10)*3;

    SDL_EnableKeyRepeat(100, 100);
    SDL_ShowCursor(SDL_DISABLE);
    
    Mix_Chunk * select = Mix_LoadWAV(MOVE_CURSOR);
    Mix_Chunk * back = Mix_LoadWAV(BACK);
    int vol = MIX_MAX_VOLUME/6;
    Mix_VolumeChunk(select, MIX_MAX_VOLUME);
    Mix_VolumeChunk(back, MIX_MAX_VOLUME);
  
    while(continuer) {
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        Mix_PlayChannel(2, back, 0);
                        continuer = 0; escape = 1;
                        break;
                    case SDLK_UP:  
                        break;
                    case SDLK_DOWN:
                        break;
                    case SDLK_RIGHT:
                        break;
                    case SDLK_LEFT:
                        break;
                    case SDLK_BACKSPACE:
                        
                            pseudo[pos_char] = '_';
                            if (pos_char <= 0)
                                pos_char = -1;
                            else
                                pos_char--;
                            existe_deja = 0;
                            for (int i = 0; i < joueur_courant; i++) {
                                if (strcmp(pseudos[i], pseudo) == 0)
                                    existe_deja = 1;
                            }
                        
                        break;
                    case SDLK_RETURN:
                        if (!existe_deja) {
                            // affecte le pseudo saisit si non vide
                            if (pseudo[0] != '_') {
                                strcpy(pseudos[joueur_courant], pseudo);
                                printf("pseudos[%d] : '%s'\n", joueur_courant, pseudos[joueur_courant]);
                            }
                            // sinon affecte un pseudo par défaut
                            else {
                                strcpy(pseudo, "joueur ");
                                sprintf(joueur_courant_str, "%d", joueur_courant+1);
                                strcat(pseudo, joueur_courant_str);
                                strcpy(pseudos[joueur_courant], pseudo);
                                printf("pseudos[%d] : '%s'\n", joueur_courant, pseudos[joueur_courant]);
                            }
                            strcpy(pseudo, "__________");
                            pos_char = -1; joueur_courant++;
                        }

                        if (joueur_courant == nb_joueurs)
                            continuer = 0;
                        break;
                    default:
                        touche = event.key.keysym.sym;
                        if (pos_char < 10 && GUI_ToucheValide(touche)) {
                            pos_char++;
                            pseudo[pos_char] = touche;
                            if (joueur_courant > 0) {
                                printf("saisie : '%s'\n", pseudo);
                                existe_deja = 0;
                                for (int i = 0; i < joueur_courant; i++) {
                                    if (strcmp(pseudos[i], pseudo) == 0)
                                        existe_deja = 1;
                                }
                            }
                        }
                        break;
                }
                break;
        }           
                    
        if (!continuer) break;           

        SDL_BlitSurface(wall, NULL, ecran, &pos_wall);
        
        strcpy(msg, "Pseudo joueur ");
        sprintf(joueur_courant_str, "%d : ", joueur_courant+1);
        strcat(msg, joueur_courant_str);
        msg_surf = TTF_RenderText_Blended(police, msg, couleurBlanche);
        SDL_BlitSurface(msg_surf, NULL, ecran, &pos_msg);

        if (existe_deja) {
            msg_error = TTF_RenderText_Blended(police, "ce pseudo existe deja !", couleurRouge);
            SDL_BlitSurface(msg_error, NULL, ecran, &pos_msg_error); 
        }
        else {
            msg_error = TTF_RenderText_Blended(police, "", couleurRouge);
            SDL_BlitSurface(msg_error, NULL, ecran, &pos_msg_error); 
        }

        pseudo_surf = TTF_RenderText_Blended(police, pseudo, couleurBlanche);
        SDL_BlitSurface(pseudo_surf, NULL, ecran, &pos_pseudo);

        SDL_Flip(ecran);
    }

    SDL_FreeSurface(msg_surf);
    SDL_FreeSurface(wall);
    SDL_FreeSurface(ecran);
    SDL_FreeSurface(pseudo_surf);
    Mix_FreeChunk(select);
    Mix_FreeChunk(back);
    TTF_CloseFont(police);

    if (escape)
        return 0;
    else {
        for (int j = 0; j < joueur_courant; j++) {
            joueurs[j] = joueur_creer();
            // donne une quantité de jetons de départ
            joueurs[j]->jetons_stock = nb_jetons_stock;
            // affecte le pseudo
            strcpy(joueurs[j]->pseudo, pseudos[j]);
            // supprime les caractères inutilisés du pseudo ('_')
            for (int i = 0; i < 10; i++) {
                if (joueurs[j]->pseudo[i] == '_') {
                    joueurs[j]->pseudo[i] = '\0';    
                    break;
                }
            }
        }
        return 1;
    }
}

int GUI_ToucheValide(char touche) {
    switch(touche) {
        case 'a': return 1; break;
        case 'b': return 1; break;
        case 'c': return 1; break;
        case 'd': return 1; break;
        case 'e': return 1; break;
        case 'f': return 1; break;
        case 'g': return 1; break;
        case 'h': return 1; break;
        case 'i': return 1; break;
        case 'j': return 1; break;
        case 'k': return 1; break;
        case 'l': return 1; break;
        case 'm': return 1; break;
        case 'n': return 1; break;
        case 'o': return 1; break;
        case 'p': return 1; break;
        case 'q': return 1; break;
        case 'r': return 1; break;
        case 's': return 1; break;
        case 't': return 1; break;
        case 'u': return 1; break;
        case 'v': return 1; break;
        case 'w': return 1; break;
        case 'x': return 1; break;
        case 'y': return 1; break;
        case 'z': return 1; break;
        default : return 0; break;
    }
}
