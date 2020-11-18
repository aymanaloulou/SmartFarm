#include <gtk/gtk.h>
typedef struct 
{
int jour;
int mois;
int annee;
}date;
typedef struct 
{ char nom[100];
char prenom[100];
char cin[100];
char gender[100];
char numero_de_telephone[100];
char adress[100];
char email[100];
date date_de_naissance;
}Client;
/// ajout client //
void ajouter_list_client(Client S);
int pos (char c,char ch[]);
int verif_existance(char X[]);
//////////////
void modifier_list_client(Client S1);
void supprimer_list_client(Client S2);
int rechercher_produit (char CIN[],Client S);
void supprimer_Historique(Client S3);
void recuperer_Historique(Client S4);
void afficher_list_client( GtkWidget *liste);
void afficher_Historique( GtkWidget *liste);
void envoyer_mail(char to[],char body[],char objet[]);







