#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define N 52


typedef struct card_s card_t;
typedef struct player_s player_t;
typedef struct table_s table_t;

struct card_s
{
	int value;
	char color[10];  
}card_t;

struct table_s
{
	int pot;
	player_t player[4];
}table_t;

struct player_s
{
	card_t * cardP[5];
	int token;
}

typedef enum cardColor
{
	"coeur",
	"carreau",
	"pique",
	"trefle",
};