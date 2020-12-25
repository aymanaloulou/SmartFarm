#include<gtk/gtk.h>

typedef struct
	{
	char id[20];
	char type[20];
	char marque[20];
	char date[200]; 
	char prix[20];
	char association[20];	
	int jour;
	int mois;
	int annee;	
	}equipements;

int verifID_eq (char ch[]);
int numValide_eq (char ch[]);
int ajouter_equipement( equipements eq, GtkWidget *objet);
void declarer_eq( equipements eq);
void afficher_equipement(GtkWidget *liste);
void supprimer_equipement( char id[]);
void set_combo_entretien(GtkComboBox     *combobox);
void afficher_histo_eq(GtkWidget *liste);
void rest_eq( equipements eq);
void supp_histo_eq( char id[]);
void rech_eq(char *id,GtkWidget *liste);
void declarer_eq( equipements eq);
void supp_declar_eq( char id[]);
void mettre_top(equipements eq);
void afficher_declar_eq(GtkWidget *liste);
void rech_declar_eq(char *id,GtkWidget *liste);
void mail_declar_eq(char TO[],equipements eq);
int nbre_eq();
int nbre_declar_eq();
int prix_eq();
////////////////////////////////////////////
void afficher_tri_eq(GtkWidget *liste);
void tri_file_min_id_eq();
void tri_file_max_id_eq();
void tri_file_min_prix_eq();
void tri_file_max_prix_eq();
void tri_file_min_type_eq();
void tri_file_max_type_eq();
void tri_file_min_date_eq();
void tri_file_max_date_eq();
void tri_file_min_marque_eq();
void tri_file_max_marque_eq();
void tri_file_min_association_eq();
void tri_file_max_association_eq();

