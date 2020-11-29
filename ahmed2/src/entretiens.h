#include<gtk/gtk.h>
struct Date2
{
	int jour;
	int mois;
	int annee;
}Date2;

typedef struct
	{
	char id_eq[20];
	char id_entr[20];
	struct Date2 date; 
	char entreteneur[20] ;
	char montant[20];
	char payement[20];
	char type_payement[20];
	char reference[20];		
	}entretiens;

void payement(int paye[], char text1[], char text2[]);
void ajouter_entretien( entretiens entr);
void afficher_entretien(GtkWidget *liste);
void supprimer_entretien( char id[]);
