#ifndef _GUI_H_
#define _GUI_H_
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "commun.h"
#include "joueur.h"
#include "jeu.h"

int GUI_Init(void);
void GUI_Quit(void);
int GUI_WindowModeSelect(void);
void GUI_Credits(int window_mode);
int GUI_HomeSelect(int window_mode);
int GUI_Jouer(player_t * joueurs[], int nb_joueurs, int menu_type, int * qte, int window_mode);
int GUI_InitRules(int * nb_joueurs, int * nb_jetons_stock, int window_mode);
int GUI_CreatePlayers(player_t * joueurs[], int nb_joueurs, int nb_jetons_stock, int window_mode);
int GUI_ToucheValide(char touche);

#endif
