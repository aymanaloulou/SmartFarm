#include <string.h>
#include <stdio.h>
#include <gtk/gtk.h>
 struct Date 
{       int jour ; 
	int mois ;
	int annee ; 
}  ;
typedef struct capteur { 
	char type [50] ;
	char id [100] ;
	char marque[50] ;
	char valeur[20] ;
        char etat [20] ; 
        char cause [20] ; 
 	struct Date date  ;  
}capteur ; 

typedef struct mar
{
    char nom[30];
    int nb ;
}mar;

int ajoutCapteur ( capteur c,GtkWidget *objet);
int identifiantExiste (char ch[]) ;
void affiche_capteur(GtkWidget *liste);
void type_capteur (int choix[], char text1[] );
void supp_capteur( char  id_supp[]);
void recherche_capteur (char *id_rech, GtkWidget *liste) ;
void affiche_type(GtkWidget *liste,char t[]);
void etat (int choix [],char texte []) ;
void set_combo_fiche(GtkComboBox     *combobox) ;
void cause (int choix[], char text1[] );
void capteur_alarmante(GtkWidget *liste);
void affiche_suivi(GtkWidget *liste,char i[]);
void marque_defect ( char *marque1) ;

