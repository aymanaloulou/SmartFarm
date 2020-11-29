#include<gtk/gtk.h>
struct Date
{
	int jour;
	int mois;
	int annee;
}Date;
typedef struct
	{
	char id[20];
	char type[20];
	char marque[20];
	struct Date date; 
	char prix[20];
	char association[20];		
	}equipements;

int verifID (char ch[]);
void ajouter_equipement( equipements eq);
void afficher_equipement(GtkWidget *liste);
void supprimer_equipement( char id[]);
