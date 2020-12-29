#include<gtk/gtk.h>
struct Datep
{
	int jour;
	int mois;
	int annee;
}Datep;
struct Date_engrais
{
	int jour;
	int mois;
	int annee;
}Date_engrais;
struct Date_taille
{
	int jour;
	int mois;
	int annee;
}Date_taille;
struct Quant
{
	int quantite;
	int quantite_recolte;
}Quant;

struct Unit
{
	char unite[10];
	char unite_recolte[10];
}Unit;

struct type_engrais
{
	char typex[20];
	char typey[20];
	char typez[20];

}type_engrais;


typedef struct {
char reference[20];
struct Quant quant;
struct Datep date;
struct Datep date_recolte;
struct Unit unit;
char arrosage[20];
char engrais[10];
struct type_engrais date_engrais;
struct Datep date_engrais1;
struct Datep  date_taille;
char type1[20];
char taille[10];
char commentaire[50];
}plante;



typedef struct {
struct Datep date_precip;
int valeur_precipitation;
}precipitation;

int compare_date(struct Datep a,struct Datep b);
int verifREF_plante (char ch[]);
int case_cocher(int choix1[], char text1[]);
void famille(int choix[], char text[]);

int Ajouter_plante (plante p,GtkWidget *objet);
plante readinfos (FILE *f);
void Supprimer_plante (char reference[]);
void Modifier_plante (char ref[],plante p);
int RefExiste (char ch[]);
void Rechercher_plante(char *ref_rech[],GtkWidget *liste);
void Afficher_plante(GtkWidget *liste);
void Afficher_precipitation(GtkWidget *liste);
void Ajouter_precipitation(precipitation prec);
void partie2(GtkWidget *window);
