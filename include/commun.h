#ifndef _COMMUN_H_
#define _COMMUN_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// tailles des objets
#define N 52 // jeu de cartes
#define NB_PLAYERS_MAX 5
#define LARGEUR_FENETRE 1280
#define HAUTEUR_FENETRE 720
#define LARGEUR_CARTE 112
#define HAUTEUR_CARTE 156
#define ESPACEMENT_CARTE 10

// sons
#define HOME_MUSIC "sound/Song_Remains_The_Same.wav"
#define IN_GAME_MUSIC "sound/No_Quarter.wav"
#define MOVE_CURSOR "sound/chipsStack1.wav"
#define BACK "sound/cardTakeOutPackage1.wav"

// polices
#define MENU_FONT "font/GODOFWAR.ttf"

// textures
#define MISE "img/mise.png"
#define BAG "img/bag.png"
#define JETON "img/jeton_70px.png"
#define JETON_SMALL "img/jeton_45px.png"
#define JETON_YELLOW "img/chip_yellow.png"
#define JETON_YELLOW_1 "img/chip_yellow1.png"
#define JETON_YELLOW_10 "img/chip_yellow10.png"
#define JETON_YELLOW_100 "img/chip_yellow100.png"
#define JETON_YELLOW_1000 "img/chip_yellow1000.png"
#define ADD_ON "img/add.png"
#define ADD_OFF "img/add_off.png"
#define REMOVE_ON "img/remove.png"
#define REMOVE_OFF "img/remove_off.png"
#define TAS_JETONS "img/tas_jetons.png"
#define HOME_WALL "img/wall1.jpg"
#define GAME_WALL "img/wall2.jpg"
#define TABLE "img/table.png"
#define JEU_52_CARTES "img/52_cards_deck.png"
#define VERSO_CARTE "img/back_card.png"

// coordonnées des cartes depuis l'image JEU_52_CARTES
#define AS_TREFLE_X 0
#define AS_TREFLE_Y 0
#define AS_CARREAU_X 0
#define AS_CARREAU_Y 1
#define AS_COEUR_X 0
#define AS_COEUR_Y 2
#define AS_PIC_X 0
#define AS_PIC_Y 3
#define DEUX_TREFLE_X 1
#define DEUX_TREFLE_Y 0 
#define DEUX_CARREAU_X 1
#define DEUX_CARREAU_Y 1
#define DEUX_COEUR_X 1
#define DEUX_COEUR_Y 2 
#define DEUX_PIC_X 1
#define DEUX_PIC_Y 3
#define TROIS_TREFLE_X 2 
#define TROIS_TREFLE_Y 0
#define TROIS_CARREAU_X 2
#define TROIS_CARREAU_Y 1
#define TROIS_COEUR_X 2
#define TROIS_COEUR_Y 2 
#define TROIS_PIC_X 2
#define TROIS_PIC_Y 3
#define QUATRE_TREFLE_X 3
#define QUATRE_TREFLE_Y 0
#define QUATRE_CARREAU_X 3
#define QUATRE_CARREAU_Y 1
#define QUATRE_COEUR_X 3
#define QUATRE_COEUR_Y 2 
#define QUATRE_PIC_X 3
#define QUATRE_PIC_Y 3
#define CINQ_TREFLE_X 4
#define CINQ_TREFLE_Y 0 
#define CINQ_CARREAU_X 4
#define CINQ_CARREAU_Y 1 
#define CINQ_COEUR_X 4
#define CINQ_COEUR_Y 2 
#define CINQ_PIC_X 4
#define CINQ_PIC_Y 3 
#define SIX_TREFLE_X 5
#define SIX_TREFLE_Y 0 
#define SIX_CARREAU_X 5
#define SIX_CARREAU_Y 1 
#define SIX_COEUR_X 5
#define SIX_COEUR_Y 2 
#define SIX_PIC_X 5
#define SIX_PIC_Y 3 
#define SEPT_TREFLE_X 6 
#define SEPT_TREFLE_Y 0 
#define SEPT_CARREAU_X 6
#define SEPT_CARREAU_Y 1 
#define SEPT_COEUR_X 6
#define SEPT_COEUR_Y 2 
#define SEPT_PIC_X 6
#define SEPT_PIC_Y 3 
#define HUIT_TREFLE_X 7
#define HUIT_TREFLE_Y 0 
#define HUIT_CARREAU_X 7
#define HUIT_CARREAU_Y 1 
#define HUIT_COEUR_X 7
#define HUIT_COEUR_Y 2 
#define HUIT_PIC_X 7
#define HUIT_PIC_Y 3 
#define NEUF_TREFLE_X 8
#define NEUF_TREFLE_Y 0 
#define NEUF_CARREAU_X 8
#define NEUF_CARREAU_Y 1 
#define NEUF_COEUR_X 8
#define NEUF_COEUR_Y 2 
#define NEUF_PIC_X 8
#define NEUF_PIC_Y 3 
#define DIX_TREFLE_X 9
#define DIX_TREFLE_Y 0 
#define DIX_CARREAU_X 9
#define DIX_CARREAU_Y 1 
#define DIX_COEUR_X 9
#define DIX_COEUR_Y 2 
#define DIX_PIC_X 9
#define DIX_PIC_Y 3 
#define VALET_TREFLE_X 10 
#define VALET_TREFLE_Y 0 
#define VALET_CARREAU_X 10
#define VALET_CARREAU_Y 1 
#define VALET_COEUR_X 10
#define VALET_COEUR_Y 2 
#define VALET_PIC_X 10
#define VALET_PIC_Y 3 
#define DAME_TREFLE_X 11
#define DAME_TREFLE_Y 0 
#define DAME_CARREAU_X 11
#define DAME_CARREAU_Y 1 
#define DAME_COEUR_X 11
#define DAME_COEUR_Y 2 
#define DAME_PIC_X 11
#define DAME_PIC_Y 3 
#define ROI_TREFLE_X 12 
#define ROI_TREFLE_Y 0 
#define ROI_CARREAU_X 12
#define ROI_CARREAU_Y 1 
#define ROI_COEUR_X 12
#define ROI_COEUR_Y 2 
#define ROI_PIC_X 12
#define ROI_PIC_Y 3 

#endif

