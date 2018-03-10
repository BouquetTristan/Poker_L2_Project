#ifndef _GUI_H_
#define _GUI_H_
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

int GUI_init(void);
void GUI_quit(void);
int fullscreenSelect(void);
void jouer(int window_mode);
int GUI_home_menu(int window_mode);

#endif
