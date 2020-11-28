#include<gtk/gtk.h>
typedef struct
	{
	char id_eq[20];
	char id_entr[20];
	char date[20];
	char entreteneur[20] ;
	char montant[20];
	char payement[20];
	char type_payement[20];
	char reference[20];		
	}entretiens;


void ajouter_entretien( entretiens entr);
void afficher_entretien(GtkWidget *liste);
void supprimer_entretien( char id[]);
