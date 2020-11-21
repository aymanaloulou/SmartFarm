#include <gtk/gtk.h>

typedef struct
    {
        int jour;
        int mois;
        int annee;
    }date;

typedef struct
    {
   char identifiant[20];
   int genre ;
   int poids ;
   char identifiant_mere[20];
   char robe[20];
   char lot[100];
    }animal;

typedef struct 
    {
        int mamites_severe;
        int mamites_sub;
        int caillette ; 
        int acidoses
        int acétonemie ;
        char autres[100];
    }sante;
typedef struct 
    {
        int mort ;
        int maladie ;
        int gestation ;
        int volume_lait; 
    }evenement;    

void ajout_voeux(animal v);
void modif_voeux(animal v);
void suppr_voeux(animal v);
void affiche_liste_voeux(animal v);
void fiche_voeux(animal v);


void ajout_evenement(evenement e);
void ajout_lait(evenement e);

void etat_sante(sante s);
void avis ();
void affichage_alimentation();
//partie 2:
void affichage_nombre_voeux();
void affichage_nombre_brebis();
void affichage_quantite_lait();
