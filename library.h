#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define N 52

/* Definition of all types */


typedef struct card_s card_t;
typedef struct player_s player_t;
typedef struct table_s table_t;

/* Declaration of board */
char *color[4] = 
{
	"coeur",
	"carreau",
	"trefle",
	"pique"
};

/* Declaration of all types */


struct card_s
{
	int value;
	char *cardColor[];  
};

struct player_s
{
	card_t * cardP[5];
	int token;
};

struct table_s
{
	int pot;
	player_t player[4];
};


