#include <string.h>
#include <stdio.h>
#include <gtk/gtk.h>

struct Date1
{
int jour;
int mois;
int annee;
}Date1;
typedef struct animal
{
	char ref[20];
	char refm[20];
	char poids[20] ;
	char robe[20];
	char lot[20];
	char gender[20];
	char type[20];
	char etat[20];
	char maladie[40];
	char lait[20];
	float laittotale ; 
	struct Date1 date1;
	
}animal;

typedef struct fiche
{
	char ref[20];
	char refm[20];
	char poids[20] ;
	char robe[20];
	char lot[20];
	char gender[20];
	char type[20];
	struct Date1 date1;
	char age[20];
	char lait[20];
	float laittotale ; 
	char sante[20];
	
}fiche;


typedef struct alim
{
	char MS[20];
	char UEM[20];
	char UEL[20] ;
	char UEB[20];

	char UFL[20];
	char UEV[20];
	char MO[20];
	char dMO[20];
	char amidon[20];
	char sucre[20];
	char EEMG[20];

	char NDF[20] ;
	char ADF[20];
	char ADL[20];
	char CB[20];

	char PDIN[20];
	char PDIE[20];
	char PDIA[20];
	char MAT[20];
	char LYSDI[20];
	char METDI[20];
	
}alim;




int AjoutAnimal(animal a,GtkWidget *objet);
void ModifAnimal(animal a);
int CsModifAnimal(animal a,GtkWidget *objet);
void AffichListeAnimal(GtkWidget *liste) ;
void RechercheAnimal(char *ref_rech, GtkWidget *liste);
void SuppAnimal( char ref[]);
//............................
int RefExiste (char ch[]);
int TrnomValide (char ch[]);
int RefExistemodif (char ch[]);
int TrnumValide (char ch[]);

void AffichListeAnimalVoeux(GtkWidget *liste) ;
void AffichListeAnimalBrebis(GtkWidget *liste) ;

void genre(int choix[], char text[]);
//............................
void SuppHistAnimal(animal d);
void AffichListeAnimalHist(GtkWidget *liste);
void  RechercheHistAnimal(char *ref_rech, GtkWidget *liste);
//............................
void pdfT (animal a);
void AffichAnimalmalade(GtkWidget *liste) ;
//............................
void AjoutAlim(alim b);
void SuppAlim( char ref[]);
void pdfalim (alim b);
//.......................
int get_jour(animal a);
int get_mois(animal a);
int get_annee(animal a);



