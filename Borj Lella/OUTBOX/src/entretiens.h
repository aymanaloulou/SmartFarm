#include<gtk/gtk.h>
struct Date_entr
{
	int jour;
	int mois;
	int annee;
}Date_entr;

typedef struct
	{
	char id_eq[20];
	char id_entr[100];
	char date[200]; 
	char entreteneur[20] ;
	char montant[20];
	char payement[20];
	char type_payement[20];
	char reference[200];
	int jour;
	int mois;
	int annee;
	}entretiens;

void payement(int paye[], char text1[], char text2[]);
int ajouter_entretien( entretiens entr, GtkWidget *objet);
void afficher_entretien(GtkTreeView *liste);
void supprimer_entretien(entretiens entr);
void afficher_histo_entr(GtkTreeView *liste);
void rest_entr( entretiens entr);
void supp_histo_entr( char id[]);
int verifID_entr (char ch[]);
int str_istr (const char *cs, const char *ct);
void rech_entr(char *id, GtkWidget *liste);
void pdf_entr (entretiens entr);
void afficher_entr_payement(GtkTreeView *liste, char *ch);
int prix_entr_paye();
int prix_entr_non_paye();
///////////////////////////////////////////
void afficher_tri_entretien(GtkTreeView *liste);
void tri_file_min_id_entr();
void tri_file_max_id_entr();
void tri_file_min_date_entr();
void tri_file_max_date_entr();
void tri_file_min_entreteneur_entr();
void tri_file_max_entreteneur_entr();
void tri_file_min_montant_entr();
void tri_file_max_montant_entr();
void tri_file_min_reference_entr();
void tri_file_max_reference_entr();
void tri_file_min_payement_entr();
void tri_file_min_type_payement_entr();
