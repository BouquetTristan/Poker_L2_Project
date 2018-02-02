#include "library.h"

card_t card[N];

void initialisation()
{
	
	for (int i = 1; i < 5; ++i)
	{
		for (int j = 1; j < 14; ++j)
		{
			card[i*j].value = j;
			card[i*j].cardColor[i] = color[i];
		}
	}
	
}

void shuffle()
{
	
}

void displaycard()
{
	for (int i = 1; i < 5; ++i)
	{
		for (int j = 1; j < 14; ++j)
		{	
			printf("%i de %s\n",
				card[i*j].value, card[i*j].cardColor); 
		}
	}
}

int main(int argc, char const *argv[])
{
	initialisation();
	displaycard();
	return 1;
}