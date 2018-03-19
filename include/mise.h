#include "commun.h"
#include "joueur.h"

int egalite(int nbPlayer, player_t * joueur[]);

int all_in(int player);
int reflate(int player, int nbPlayer);
int follow(int player, int nbPlayer);

int bet(int player, int nbPlayer);
void turnOfBet(int cpt_turn);