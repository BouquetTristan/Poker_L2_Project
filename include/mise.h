#include "commun.h"
#include "joueur.h"

int egalite(int nbPlayer, player_t * joueur[]);

int all_in(int player);
int reflate(int player, int nbPlayer, player_t * joueur[]);
int follow(int player, int nbPlayer, player_t * joueur[]);

int bet(int player, int nbPlayer, player_t * joueur[]);
void turnOfBet(jeu_t * jeu, player_t * joueur[], int nbPlayer);