typedef struct 
{
int jour;
int mois;
int annee;
}date;

typedef struct 
{

char Nom_du_produit[100];
date date_fabrication ;
date date_lim_conso;

int quantite;
float prix;
}produit;

void ajouter_produit (produit P);
void modifier_produit (produit P1);
void supprimer_produit (produit p2);
void afficher_produit( GtkWidget *liste);
int rechercher_produit (produit p , char nom_produit[] );

typedef struct 
{
char ref[100];
date date_facture ; 
char mode_paiement[100];
char produit[100];
int quantite;
float montant_sans_reduction;
float reduction;
float montant_a_payer;
}facutre;

void ajouter(facture S);
void modifier (facutre S1);
void afficher_facture( GtkWidget *liste);
void supprimer_produit (produit S3);
void afficher_facture( GtkWidget *liste);
int rechercher_produit (facture f, char ref_facture[]);


