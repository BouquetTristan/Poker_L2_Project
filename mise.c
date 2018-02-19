#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_Valeur 13
#define MAX_Couleur 4
 
 
int creation_valeur_carte(){

	int J1_carte1_couleur, J1_carte1_valeur, J1_carte2_couleur, J1_carte2_valeur, J2_carte1_couleur, J2_carte1_valeur, J2_carte2_couleur, 		J2_carte2_valeur;

	int x = 13;
	
	char TabCarte[x] ;

	// Création des valeurs des cartes, Ace - King //
	TabCarte[0]=65; // Ace
	TabCarte[1]=50; // 2
	TabCarte[2]=51; // 3
	TabCarte[3]=52; // 4
	TabCarte[4]=53; // 5
	TabCarte[5]=54; // 6
	TabCarte[6]=55; // 7
	TabCarte[7]=56; // 8
	TabCarte[8]=57; // 9
	TabCarte[9]=68; // Ten (Dix)
	TabCarte[10]=74; // Jack (Valet)
	TabCarte[11]=81; // Queen (Reine)
	TabCarte[12]=75; // King (Roi)
	// Création des valeurs des cartes, Ace - King //
 }

int creation_couleur(){

		int y=4;
		char TabCouleur[y];
		int J1_carte1_couleur, J1_carte1_valeur, J1_carte2_couleur, J1_carte2_valeur, J2_carte1_couleur, J2_carte1_valeur, J2_carte2_couleur, 		J2_carte2_valeur;
		// Création des 4 couleurs des cartes //
	TabCouleur[0] = 115; // Spades (Piques)
	TabCouleur[1] = 104; // Hearts (Coeurs)
	TabCouleur[2] = 100; // Diamonds (Carreaux)
	TabCouleur[3] = 99; // Clubs (Trèfles)
	// Création des 4 couleurs des cartes //

}


int flop(){

	int x,y;
	int flop_carte1_couleur, flop_carte1_valeur, flop_carte2_couleur, flop_carte2_valeur, flop_carte3_couleur, flop_carte3_valeur;
	char TabCarte[x], TabCouleur[y];
	// Flop
	flop_carte1_couleur = rand() % MAX_Couleur;
	flop_carte1_valeur = rand() % MAX_Valeur;
	flop_carte2_couleur = rand() % MAX_Couleur;
	flop_carte2_valeur = rand() % MAX_Valeur;
	flop_carte3_couleur = rand() % MAX_Couleur;
	flop_carte3_valeur = rand() % MAX_Valeur;

	printf("\n\nLe Flop : [%c-%c] [%c-%c] [%c-%c]", TabCarte[flop_carte1_valeur], TabCouleur[flop_carte1_couleur], TabCarte[flop_carte2_valeur], TabCouleur[flop_carte2_couleur], TabCarte[flop_carte3_valeur], TabCouleur[flop_carte3_couleur]);
}


int turn(){
	
	int turn_couleur, turn_valeur;
	int x,y;
	int flop_carte1_couleur, flop_carte1_valeur, flop_carte2_couleur, flop_carte2_valeur, flop_carte3_couleur, flop_carte3_valeur;
	char TabCarte[x], TabCouleur[y];

	turn_couleur = rand() % MAX_Couleur;
	turn_valeur = rand() % MAX_Valeur;
	printf("\n\nFlop + Turn : [%c-%c] [%c-%c] [%c-%c] + [%c-%c]", TabCarte[flop_carte1_valeur], TabCouleur[flop_carte1_couleur], TabCarte[flop_carte2_valeur], TabCouleur[flop_carte2_couleur], TabCarte[flop_carte3_valeur], TabCouleur[flop_carte3_couleur], TabCarte[turn_valeur], TabCouleur[turn_couleur]);

}

int river(){

	int turn_couleur, turn_valeur;
	int river_couleur, river_valeur;
	int x,y;
	int flop_carte1_couleur, flop_carte1_valeur, flop_carte2_couleur, flop_carte2_valeur, flop_carte3_couleur, flop_carte3_valeur;
	char TabCarte[x], TabCouleur[y];

	river_couleur = rand() % MAX_Couleur;
	river_valeur = rand() % MAX_Valeur;
	printf("\n\nFlop + Turn + River : [%c-%c] [%c-%c] [%c-%c] + [%c-%c] + [%c-%c]\n", TabCarte[flop_carte1_valeur], TabCouleur[flop_carte1_couleur], TabCarte[flop_carte2_valeur], TabCouleur[flop_carte2_couleur], TabCarte[flop_carte3_valeur], TabCouleur[flop_carte3_couleur], TabCarte[turn_valeur], TabCouleur[turn_couleur], TabCarte[river_valeur], TabCouleur[river_couleur]);
}




int mise()
{
 
	int x = 13, y = 4, Tapis_J1 = 5000, Tapis_J2 = 5000, choix, choix2, mise2, mise1;
	int J1_carte1_couleur, J1_carte1_valeur, J1_carte2_couleur, J1_carte2_valeur, J2_carte1_couleur, J2_carte1_valeur, J2_carte2_couleur, 		J2_carte2_valeur;
	int flop_carte1_couleur, flop_carte1_valeur, flop_carte2_couleur, flop_carte2_valeur, flop_carte3_couleur, flop_carte3_valeur;
	int river_couleur, river_valeur, turn_couleur, turn_valeur;
	char TabCarte[x], TabCouleur[y];
 
 

 
 
	// Main J1
	srand(time(NULL));
	J1_carte1_couleur = rand() % MAX_Couleur;
	J1_carte1_valeur = rand() % MAX_Valeur;
	J1_carte2_couleur = rand() % MAX_Couleur;
	J1_carte2_valeur = rand() % MAX_Valeur;
	// Main J1
 
 
 
	printf("****************POKER******************\n************FIVE DRAW**************\n**************HEAD'S UP****************\\nSpades 		(Piques) - Hearts (Coeurs) - Diamonds (Carreaux) - Clubs (Trefles)\n\n");
 
	printf("***************************************\n********DISTRIBUTION DES CARTES********\n***************************************\n\n");
	printf("Joueur 1, votre main est : [%c-%c] & [%c-%c]\n", TabCarte[J1_carte1_valeur], TabCouleur[J1_carte1_couleur], TabCarte	[J1_carte2_valeur], TabCouleur[J1_carte2_couleur]);
 
	printf("Votre tapis est de %d. \n\nQuelle action desirez-vous effectuer ? \n1. jouer (Play)\n2. quitter (Quit)\n", Tapis_J1);
 
	scanf("\n%d", &choix);
	printf("\n");
	switch(choix)
	{
	case 1:
    		printf("***************************************\n*****************MISE******************\n***************************************\n\nCombien voulez-vous miser ? [Max : %d]\n", Tapis_J1);
    		scanf("\n\n%d", &mise1);
    		Tapis_J1 = Tapis_J1 - mise1;
    		printf("\nVous voulez miser %d, il vous reste %d dans votre tapis.", mise1, Tapis_J1);
    		break;

	case 2:
    		printf("Vous quitter.\n");
		return 0;    		
		break;
	}
 
	// Main J2
	srand(time(NULL));
	J2_carte1_couleur = rand() % MAX_Couleur;
	J2_carte1_valeur = rand() % MAX_Valeur;
	J2_carte2_couleur = rand() % MAX_Couleur;
	J2_carte2_valeur = rand() % MAX_Valeur;
	// Main J2

	
	creation_valeur_carte();
	creation_couleur();

 
	printf("\n\nJoueur 2, votre main est : [%c-%c] & [%c-%c]\n", TabCarte[J2_carte1_valeur], TabCouleur[J2_carte1_couleur], TabCarte[J2_carte2_valeur], TabCouleur[J2_carte2_couleur]);
 
	printf("Votre tapis est de %d. \n\nQuelle action desirez-vous effectuer ? \n1. Se coucher (fold)\n2. Suivre (call)\n3. Miser (bet)\n\n4. Tapis ()\n\n", Tapis_J2);
 
	scanf("\n%d", &choix2);
	printf("\n");
	switch(choix2)
	{
	case 1:
    		printf("Vous vous coucher.\n");
    		break;
	case 2:
    		printf("Vous suivez.");
		Tapis_J2 = Tapis_J2 - mise1;
    		printf("\n il vous reste %d dans votre tapis.\n", Tapis_J2);  		
		break;



		case 3:
    		printf("*******************************Vous relancez******************\n***************************************\n\nCombien voulez-vous miser ? [Max : %d]\n", Tapis_J2);
   		 scanf("\n\n%d", &mise2);

	Tapis_J2 = Tapis_J2 - mise2;
    		printf("\nVous relancez %d, il vous reste %d dans votre tapis.\n", mise2, Tapis_J2);
   		 break;
	
	case 4: 
		printf("tapis");
	  
    		printf("\nVous voulez tout miser , il vous reste aucun jeton dans votre tapis.\n"); break;
	}
 
/*	//flop
	
	flop();
	

 	// Turn
	
	turn();
	
 
	// River
	
	river();*/
	
 
    return 0;
}
