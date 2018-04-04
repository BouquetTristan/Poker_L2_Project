#include "commun.h"
#include "joueur.h"

int egalite(int nbPlayer, player_t * joueur[]);
void askCard(int player, player_t * joueur[], jeu_t * jeu);

int miser(int player, player_t * joueur[], int jeton_suivi, int qte);
int all_in(int player, player_t * joueur[]);
//int reflate(int player, int nbPlayer, player_t * joueur[], int qte);
int follow(int player, int nbPlayer, player_t * joueur[]);
int sleep(int player, player_t * joueur[]);

int bet(int player, int nbPlayer, player_t * joueur[]);
void turnOfBet(jeu_t * jeu, int nbPlayer, player_t * joueur[]);
