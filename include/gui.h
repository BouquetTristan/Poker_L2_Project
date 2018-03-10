#ifndef _GUI_H_
#define _GUI_H_
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "commun.h"

int GUI_Init(void);
void GUI_Quit(void);
int GUI_FullScreenSelect(void);
int GUI_Home_Select(int window_mode);
void GUI_Jouer(int window_mode);

#endif
