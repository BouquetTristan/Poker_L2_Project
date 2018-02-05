#ifndef _PLATEAU_H_
#define _PLATEAU_H_
#include "carte.h"

typedef struct player_s
{
	carte_t * cartePlayer[5];
	int token;
	char name[20];
};

typedef struct plateau_s
{
	player_t * player[4];
	int pot;
};

#endif