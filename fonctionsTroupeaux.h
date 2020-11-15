#include <gtk/gtk.h>

typedef struct
    {
        int jour;
        int mois;
        int annee;
    }date;

typedef struct
    {
   char identifiant;
   int genre ;
   int poids ;
   char identifiant_mere;
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

void ajout_brebis(animal b);
void modif_brebis(animal b);
void suppr_brebis(animal b);
void affiche_liste_brebis(animal b);
void fiche_brebis(animal b);

void ajout_evenement(evenement e);
void ajout_lait(evenement e);

void etat_sante(sante s);
void avis ();
void affichage_alimentation();
