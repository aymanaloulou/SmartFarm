#include <stdio.h>
#include <stdlib.h>
#include "client.h"

void affichMenu (){
		
		printf ("/////////////////////////////////////////////\n");
		printf ("	1- Ajouter un client\n");
		printf ("	2- Modifier un client\n");
		printf ("	3- Supprimer un client\n");
		printf ("	4- Afiicher la liste des clients\n");
		printf ("	5- Chercher un client\n");
		printf ("	6- Quitter\n");
		printf ("/////////////////////////////////////////////\n");
}

int getChoix (){
	int x;
	do{
		printf ("Donner votre choix : ");
		scanf ("%d",&x);
	}while (x>6 || x<1);
	return x;
}

void main(){
	int choix;
	do{
		affichMenu ();
		choix = getChoix ();
		switch (choix){
				case 1: ajoutClient ();break;
				case 2: modifClient ();break;
				//case 3: //suppClient ();break;
				case 4: affichListeClient ();break;
				case 5: rechercheClient ();break;
		}
	}while (choix != 6);

}
