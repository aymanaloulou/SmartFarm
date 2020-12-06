#include <gtk/gtk.h>
typedef struct 
{ 
char nom[100];
char prenom[100];
char cin[100];
char gender[100];
char numero_de_telephone[100];
char adress[100];
char email[100];
int jour;
int mois;
int annee;
}Client;

typedef struct

{char ref[100];
 char nom_r[100];
char prenom_r[100];
char numero[100];
int nbr ;
char option [100];
char periode [100];
char commentaire [100];
int jr;
int mois;
int annee;
int heure;
}Reservation;







/// ajout client //
void ajouter_list_client(Client S);
void pdf (Reservation s);
void supprimer_jeux(Client E);
void modifier_jeux(Client c);
//int pose (char c,char ch[]);
void aj_jeux(Client p);
int jeux_client(Client p);
int verif_existance(char X[]);
int verifhisto(char X[]);
void ajouter_email(char FROM[],char TO[],char SUBJECT[],char BODY[]);
//////////////
void modifier_list_client(Client c);
int cinExiste (char ch[]);
/////////////
void supprimer_list_client(Client E);
int rechercher_produit (char CIN[],Client S);
void rech_client (char *cin_rech, GtkWidget *liste);
////
void supprimer_Historique(Client S3);

////
void rech_histo (char *cin_rech, GtkWidget *liste);
void recuperer_Historique(Client S4);
void afficher_list_client( GtkWidget *liste);
void afficher_Historique( GtkWidget *liste);
void envoyer_mail(char to[],char body[],char objet[]);

void ajouter_res(Reservation E);
int nomE(char ch[]);
int refExiste (char ch[]);
void modifier_res(Reservation E);
void supprimer_res(Reservation E);
void rechercher_res(Reservation E);
void  afficher_res(GtkWidget *liste);
void rech_res (char *cin_rech, GtkWidget *liste);




