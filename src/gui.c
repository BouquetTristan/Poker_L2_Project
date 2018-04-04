#include "gui.h"

/**
    * \ file gui.c
    * \ author Poupin Romain
    * \ brief Contient les fonctions liées à la SDL
    * \ date 2 Avril
**/

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
    posCursor.x = (LARGEUR_FENETRE/15)*4 ;
    posCursor.y = (HAUTEUR_FENETRE/20)*8;

    textPos.x = LARGEUR_FENETRE/2 - LARGEUR_FENETRE/9;

    while(1) {
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        if (posCursor.y == (HAUTEUR_FENETRE/20)*8)
                            posCursor.y = (HAUTEUR_FENETRE/20)*11;
                        else
                            posCursor.y = (HAUTEUR_FENETRE/20)*8;
                        break;
                    case SDLK_DOWN:
                        if (posCursor.y == (HAUTEUR_FENETRE/20)*11)
                            posCursor.y = (HAUTEUR_FENETRE/20)*8;
                        else
                            posCursor.y = (HAUTEUR_FENETRE/20)*11;
                        break;
                    case SDLK_RETURN:
                        SDL_FreeSurface(cursor);
                        SDL_FreeSurface(texte);
                        SDL_FreeSurface(menu);
                        SDL_FreeSurface(ecran);
                        TTF_CloseFont(police);
                        if(posCursor.y == (HAUTEUR_FENETRE/20)*8)
                            return 1;
                        else
                            return 0;
                        break;
                }
                break;
        }

        SDL_BlitSurface(menu, NULL, ecran, &posMenu);
        SDL_BlitSurface(cursor, NULL, ecran, &posCursor);
        textPos.y = (HAUTEUR_FENETRE/20)*8;
        texte = TTF_RenderText_Blended(police, "Plein ecran", couleurBlanche);
        SDL_BlitSurface(texte, NULL, ecran, &textPos);
        textPos.y = (HAUTEUR_FENETRE/20)*11;
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
        textPos.y = (HAUTEUR_FENETRE/20)*4;
        texte = TTF_RenderText_Blended(police, "Poker PC - 1.0", couleurBlanche);
        SDL_BlitSurface(texte, NULL, ecran, &textPos);

        textPos.x = (LARGEUR_FENETRE/10)*2;
        textPos.y = (HAUTEUR_FENETRE/20)*6;
        texte = TTF_RenderText_Blended(police_small, "https://github.com/BouquetTristan/Poker_L2_Project", couleurBlanche);
        SDL_BlitSurface(texte, NULL, ecran, &textPos);

        textPos.x = (LARGEUR_FENETRE/20)*8;
        textPos.y = (HAUTEUR_FENETRE/20)*11;
        texte = TTF_RenderText_Blended(police, "Credits", couleurBlanche);
        SDL_BlitSurface(texte, NULL, ecran, &textPos);

        textPos.x = (LARGEUR_FENETRE/10)*2;
        textPos.y = (HAUTEUR_FENETRE/20)*13;
        texte = TTF_RenderText_Blended(police_small, "Romain Poupin  -  https://github.com/Romreventon", couleurBlanche);
        SDL_BlitSurface(texte, NULL, ecran, &textPos);

        textPos.x = (LARGEUR_FENETRE/10)*2;
        textPos.y = (HAUTEUR_FENETRE/20)*14;
        texte = TTF_RenderText_Blended(police_small, "Tristan Bouquet  -  https://github.com/BouquetTristan", couleurBlanche);
        SDL_BlitSurface(texte, NULL, ecran, &textPos);

        textPos.x = (LARGEUR_FENETRE/10)*2;
        textPos.y = (HAUTEUR_FENETRE/20)*15;
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
    posCursor.x = (LARGEUR_FENETRE/10)*3 ;
    posCursor.y = (HAUTEUR_FENETRE/20)*6;

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
                        if (posCursor.y == (HAUTEUR_FENETRE/20)*6)
                            posCursor.y = (HAUTEUR_FENETRE/20)*12;
                        else
                            posCursor.y -= (HAUTEUR_FENETRE/20)*3;
                        break;
                    case SDLK_DOWN:
                        Mix_PlayChannel(1, select, 0);
                        if (posCursor.y == (HAUTEUR_FENETRE/20)*12)
                            posCursor.y = (HAUTEUR_FENETRE/20)*6;
                        else
                            posCursor.y += (HAUTEUR_FENETRE/20)*3;
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
        textPos.x = LARGEUR_FENETRE/2 - LARGEUR_FENETRE/13;
        textPos.y = (HAUTEUR_FENETRE/20)*6;
        texte = TTF_RenderText_Blended(police, "Jouer", couleurBlanche);
        SDL_BlitSurface(texte, NULL, ecran, &textPos);
        textPos.x = LARGEUR_FENETRE/2 - LARGEUR_FENETRE/13;
        textPos.y = (HAUTEUR_FENETRE/20)*9;
        texte = TTF_RenderText_Blended(police, "Credits", couleurBlanche);
        SDL_BlitSurface(texte, NULL, ecran, &textPos);
        textPos.x = LARGEUR_FENETRE/2 - LARGEUR_FENETRE/13;
        textPos.y = (HAUTEUR_FENETRE/20)*12;
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
    if (posCursor.y == (HAUTEUR_FENETRE/20)*6)
        return 1;
    else if (posCursor.y == (HAUTEUR_FENETRE/20)*9)
        return 2;
    else
        return 3; 
}

int GUI_Jouer(player_t * joueurs[], int nb_joueurs, int menu_type, int * qte, int window_mode) {
    TTF_Font * police = TTF_OpenFont(MENU_FONT, 35);
    TTF_Font * police_moy = TTF_OpenFont(MENU_FONT, 30);
    TTF_Font * police_small = TTF_OpenFont(MENU_FONT, 20);
    SDL_Surface
        * ecran = NULL,
        * table = NULL,
        * carte_recto = NULL,
        //* carte_verso = NULL,
        * cursor = NULL,
        * texte = NULL,
        * wall = NULL,
        * pseudo = NULL,
        * icon = NULL,
        * jeton_yellow = NULL,
        * more_less = NULL,
        * qte_mise = NULL;
    
    SDL_Rect
        pos_source,
        pos_dest,
        pos_table,
        menu_pos,
        pos_cursor,
        pos_wall,
        pos_pseudo,
        pos_icon,
        pos_stock,
        pos_mise,
        pos_jeton_yellow,
        pos_qte_mise,
        pos_more_less;

        SDL_Color couleurBlanche;
        couleurBlanche.r = 255;
        couleurBlanche.g = 255;
        couleurBlanche.b = 255;

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

    wall = IMG_Load(GAME_WALL);
    pos_wall.x = 0;
    pos_wall.y = 0;

    char touche;

    char pseudo_str[11];
    char stock_str[6];
    char mise_str[6];
    char menu_str[9];
    char * menu_str_tab[4] = {
        "______",
        "________",
        "tapis",
        "coucher"
    };
    if (menu_type == 0) {
        menu_str_tab[0] = "suivre";
        menu_str_tab[1] = "relancer";
    }
    else {
        menu_str_tab[0] = "miser";
        menu_str_tab[1] = "checker";
    }

    for (int i = 0; i < 2; i++)
        printf("menu[%d] : %s\n", i, menu_str_tab[i]);

    int pos_menu_tab[4] = {150, 400, 700, 1000};
    int pos_cursor_tab[4] = { 
        pos_menu_tab[0]-45-10, // 45px=largeur jeton; 10=espacement
        pos_menu_tab[1]-45-10,
        pos_menu_tab[2]-45-10,
        pos_menu_tab[3]-45-10
    };
    int i_cursor;
    pos_icon.x = 5;
    pos_stock.x = 35;
    pos_mise.x = 35;

    // init l'img de la table
    table = IMG_Load(TABLE);
    pos_table.x = 155;
    pos_table.y = 55;

    // init l'img des cartes 
    carte_recto = IMG_Load(JEU_52_CARTES);
    pos_source.w = LARGEUR_CARTE;
    pos_source.h = HAUTEUR_CARTE;
    pos_dest.y = 248;
    // selectionne la carte depuis l'image
    pos_source.x = AS_PIC_X*LARGEUR_CARTE;
    pos_source.y = AS_PIC_Y*HAUTEUR_CARTE;

    //carte_verso = IMG_Load(VERSO_CARTE);

    cursor = IMG_Load(JETON_SMALL);
    pos_cursor.y = 655;
    pos_cursor.x = pos_cursor_tab[0]; 

    pos_jeton_yellow.x = 1160;

    int pos_char = -1;
    i_cursor = 0; int menu_select_jetons = 0;
    int cursor_mise_x_tab[2] = {
        1160 - (35+25),
        1160 + (45+25)
    };
    int cursor_mise_y_tab[4] = {
        185,
        185 + 80,
        185 + 2*80,
        185 + 3*80
    }; 
    int cursor_mise_y = 0;
    int cursor_mise_x = 0;
    int jeton_yellow_y_tab[4] = {
        185,
        185 + 80,
        185 + 2*80,
        185 + 3*80
    };
    char * jeton_yellow_img_tab[4] = {
        JETON_YELLOW_1,
        JETON_YELLOW_10,
        JETON_YELLOW_100,
        JETON_YELLOW_1000
    };
    char * more_img_tab[4] = { ADD_ON, ADD_OFF, ADD_OFF, ADD_OFF };
    char * less_img_tab[4] = { REMOVE_ON, REMOVE_OFF, REMOVE_OFF, REMOVE_OFF };

char qte_mise_str[6];
    pos_qte_mise.x = 675;
    pos_qte_mise.y = 570;

    while(continuer == 1) {
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                    case SDLK_UP:
                        if (menu_select_jetons == 1) {
                            if (cursor_mise_y == 0) {
                                more_img_tab[cursor_mise_y] = ADD_OFF;
                                less_img_tab[cursor_mise_y] = REMOVE_OFF;
                                cursor_mise_y = 3;
                            }
                            else {
                                more_img_tab[cursor_mise_y] = ADD_OFF;
                                less_img_tab[cursor_mise_y] = REMOVE_OFF;
                                cursor_mise_y--;
                            }
                            more_img_tab[cursor_mise_y] = ADD_ON;
                            less_img_tab[cursor_mise_y] = REMOVE_ON;
                        }
                        break;
                    case SDLK_DOWN:
                        if (menu_select_jetons == 1) {
                            if (cursor_mise_y == 3) {
                                more_img_tab[cursor_mise_y] = ADD_OFF;
                                less_img_tab[cursor_mise_y] = REMOVE_OFF;
                                cursor_mise_y = 0;
                            }
                            else {
                                more_img_tab[cursor_mise_y] = ADD_OFF;
                                less_img_tab[cursor_mise_y] = REMOVE_OFF;
                                cursor_mise_y++;
                            }
                            more_img_tab[cursor_mise_y] = ADD_ON;
                            less_img_tab[cursor_mise_y] = REMOVE_ON;
                        }
                        break;
                    case SDLK_RIGHT:
                        if (menu_select_jetons == 1) {
                            switch (cursor_mise_y) {
                                case 0:
                                    *qte += 1;
                                    break;
                                case 1:
                                    *qte += 10;
                                    break;
                                case 2:
                                    *qte += 100;
                                    break;
                                case 3:
                                    *qte += 1000;
                                    break;
                            }
                            sprintf(qte_mise_str, "%d", *qte);
                        }
                        else {
                            if (i_cursor == 3) {
                                i_cursor = 0;
                                pos_cursor.x = pos_cursor_tab[i_cursor];
                            }
                            else {
                                i_cursor++;
                                pos_cursor.x = pos_cursor_tab[i_cursor];
                            }
                        }
                        break;
                    case SDLK_LEFT:
                         if (menu_select_jetons == 1) {
                            switch (cursor_mise_y) {
                                case 0:
                                    *qte -= 1;
                                    break;
                                case 1:
                                    *qte -= 10;
                                    break;
                                case 2:
                                    *qte -= 100;
                                    break;
                                case 3:
                                    *qte -= 1000;
                                    break;
                            }
                            sprintf(qte_mise_str, "%d", *qte);
                         }
                         else {
                            if (i_cursor == 0) {
                                i_cursor = 3;
                                pos_cursor.x = pos_cursor_tab[i_cursor];
                            }
                            else {
                                i_cursor--;
                                pos_cursor.x = pos_cursor_tab[i_cursor];
                            }
                        }
                        break;
                    case SDLK_RETURN:
                        if (i_cursor == 0) {
                            if (strcmp(menu_str_tab[0], "miser") == 0) {
                                if (menu_select_jetons == 0) {
                                    menu_select_jetons = 1;
                                    *qte = 0;
                                    sprintf(qte_mise_str, "%d", *qte);
                                }
                                else {
                                    menu_select_jetons = 0;
                                    continuer = 0;
                                }
                            }
                            else {
                                continuer = 0;
                            }
                        }
                        else if (i_cursor == 1) {
                            if (strcmp(menu_str_tab[1], "relancer") == 0) {
                                if (menu_select_jetons == 0) {
                                    menu_select_jetons = 1;
                                    *qte = 0;
                                    sprintf(qte_mise_str, "%d", *qte);
                                }
                                else {
                                    menu_select_jetons = 0;
                                    continuer = 0;
                                }
                            }
                            else {
                                continuer=  0;
                            }
                        }
                        else if (i_cursor == 2) {
                            continuer = 0;
                        }
                        else if (i_cursor == 3) {
                            continuer = 0;
                        }
                        break;
                }
                break;
        }

        SDL_BlitSurface(wall, NULL, ecran, &pos_wall);

        // affiche les infos des joueurs
        pos_pseudo.y = 5;
        for (int i = 0; i < nb_joueurs; i++) {
            // pseudonyme
            pos_pseudo.x = 5;
            strcpy(pseudo_str, joueurs[i]->pseudo);
            pseudo = TTF_RenderText_Blended(police_moy, pseudo_str, couleurBlanche);
            SDL_BlitSurface(pseudo, NULL, ecran, &pos_pseudo);    
            // nb jetons en stock
            pos_stock.y = pos_pseudo.y + 42; 
            sprintf(stock_str, "%d", joueurs[i]->jetons_stock);
            pseudo = TTF_RenderText_Blended(police_small, stock_str, couleurBlanche);
            SDL_BlitSurface(pseudo, NULL, ecran, &pos_stock);                
            // nb jetons misés en cours
            pos_mise.y = pos_stock.y + 35; 
            sprintf(mise_str, "%d", joueurs[i]->jetons_mise);
            pseudo = TTF_RenderText_Blended(police_small, mise_str, couleurBlanche);
            SDL_BlitSurface(pseudo, NULL, ecran, &pos_mise);                
            // icone jetons en stock
            pos_icon.y = pos_pseudo.y + 35;
            icon = IMG_Load(BAG);
            SDL_BlitSurface(icon, NULL, ecran, &pos_icon);
            // icone jetons misés en cours
            pos_icon.y = pos_icon.y + 35;
            icon = IMG_Load(MISE);
            SDL_BlitSurface(icon, NULL, ecran, &pos_icon);
            pos_pseudo.y += 120;
        }
        
        // affiche la table
        SDL_BlitSurface(table, NULL, ecran, &pos_table);
        
        // affiche les cartes du joueur en cours
        pos_dest.x = 342;
        for (int i = 0; i < 5; i++) {
            SDL_BlitSurface(carte_recto, &pos_source, ecran, &pos_dest);
            pos_dest.x += LARGEUR_CARTE+ESPACEMENT_CARTE;
        }

        // affiche le panel de sélection des jetons
        if (menu_select_jetons == 1) {
            for (int i = 0; i < 4; i++) {
                // quantité totale misée
                qte_mise = TTF_RenderText_Blended(police, qte_mise_str, couleurBlanche);
                SDL_BlitSurface(qte_mise, NULL, ecran, &pos_qte_mise);
                // jeton
                jeton_yellow = IMG_Load(jeton_yellow_img_tab[i]);
                pos_jeton_yellow.y = jeton_yellow_y_tab[i];
                SDL_BlitSurface(jeton_yellow, NULL, ecran, &pos_jeton_yellow);
                // '+'
                pos_more_less.y = pos_jeton_yellow.y;
                pos_more_less.x = cursor_mise_x_tab[0];
                more_less = IMG_Load(less_img_tab[i]);
                SDL_BlitSurface(more_less, NULL, ecran, &pos_more_less);
                // '-'
                pos_more_less.x = cursor_mise_x_tab[1];
                more_less = IMG_Load(more_img_tab[i]);
                SDL_BlitSurface(more_less, NULL, ecran, &pos_more_less);
            }
        }

        // affiche le curseur de sélection des entrées du menu
        SDL_BlitSurface(cursor, NULL, ecran, &pos_cursor);

        // affiche les entrées du menu
        menu_pos.x = pos_menu_tab[0];
        menu_pos.y = 655;
        for (int i = 0; i < 4; i++) {
            menu_pos.x = pos_menu_tab[i];
            strcpy(menu_str, menu_str_tab[i]);
            texte = TTF_RenderText_Blended(police, menu_str, couleurBlanche);
            SDL_BlitSurface(texte, NULL, ecran, &menu_pos);
        }

        // rafraîchit l'écran
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(texte);
    SDL_FreeSurface(pseudo);
    SDL_FreeSurface(icon);
    SDL_FreeSurface(cursor);
    SDL_FreeSurface(carte_recto);
    //SDL_FreeSurface(carte_verso);
    SDL_FreeSurface(jeton_yellow);
    SDL_FreeSurface(more_less);
    SDL_FreeSurface(qte_mise);
    SDL_FreeSurface(table);
    SDL_FreeSurface(wall);
    SDL_FreeSurface(ecran);
    Mix_FreeChunk(musique);
    TTF_CloseFont(police);
    TTF_CloseFont(police_moy);
    TTF_CloseFont(police_small);
    return i_cursor+1;
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
    posCursor.y = (HAUTEUR_FENETRE/20)*8;

    posNbPlayers.x = (LARGEUR_FENETRE/10)*6;
    posNbPlayers.y = (HAUTEUR_FENETRE/20)*8;
    sprintf(nb_players_str, "%d", *nb_joueurs);    

    posNbTokens.x = (LARGEUR_FENETRE/10)*6;
    posNbTokens.y = (HAUTEUR_FENETRE/20)*11;
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
                        if (posCursor.y == (HAUTEUR_FENETRE/20)*8)
                            posCursor.y = (HAUTEUR_FENETRE/20)*11;  
                        else
                            posCursor.y -= 3*(HAUTEUR_FENETRE/20);  
                        break;
                    case SDLK_DOWN:
                        if (posCursor.y == (HAUTEUR_FENETRE/20)*11)
                            posCursor.y = (HAUTEUR_FENETRE/20)*8;
                        else
                            posCursor.y += 3*(HAUTEUR_FENETRE/20);
                        break;
                    case SDLK_RIGHT:
                        Mix_PlayChannel(1, select, 0);
                        if (posCursor.y == (HAUTEUR_FENETRE/20)*8) {
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
                        if (posCursor.y == (HAUTEUR_FENETRE/20)*8) {
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
       
        posMsg.y = (HAUTEUR_FENETRE/20)*8;
        msg = TTF_RenderText_Blended(police, "Joueurs", couleurBlanche);
        SDL_BlitSurface(msg, NULL, ecran, &posMsg);

        posMsg.y = (HAUTEUR_FENETRE/20)*11;
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
    SDL_FreeSurface(menu);
    SDL_FreeSurface(ecran);
    SDL_FreeSurface(cursor);
    // son
    Mix_FreeChunk(select);
    Mix_FreeChunk(back);
    // texte
    SDL_FreeSurface(msg);
    SDL_FreeSurface(nb_players);
    SDL_FreeSurface(nb_tokens);
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
                        if (pos_char < 9 && GUI_ToucheValide(touche)) {
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
        default: return 0; break;
    }
}
