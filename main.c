#include <library.h>

struct card_t card[N];

void initialisation()
{
	
	for (int i = 1; i < 5; ++i)
	{
		for (int j = 1; j < 14; ++j)
		{
			card[i*j].value = j;
			card[i*j].color = cardColor[i-1];
		}
	}
	
}

void shuffle()
{
	
}

void main(int argc, char const *argv[])
{
	initialisation();
	return 0;
}