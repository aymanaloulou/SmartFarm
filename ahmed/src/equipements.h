#include<gtk/gtk.h>
typedef struct
	{
	char id[20];
	char type[20];
	char marque[20];
	char date[20] ;
	char prix[20];
	char association[20];		
	}equipements;


void ajouter_equipement( equipements eq);
void afficher_equipement(GtkWidget *liste);
void supprimer_equipement( char id[]);
