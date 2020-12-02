#include<gtk/gtk.h>
struct Date
{
	int jour;
	int mois;
	int annee;
}Date;

struct Quant
{
	int quantite;
	int quantite_recolte;
}Quant;

struct Unit
{
	int unite;
	int unite_recolte;
}Unit;

struct Date_r
{
	int jour_r;
	int mois_r;
	int annee_r;
}Date_r;

typedef struct {
char reference[10];
struct Quant quant;
struct Date date;
struct Unit unit;
char engrais[10];
struct Date_r date_r;
char commentaire[10];
}plante;

void Ajouter_plante (plante p);
plante readinfos (FILE *f);
void Supprimer_plante (char reference[]);
void Modifier_plante (char ref[],plante p);
int RefExiste (char ch[]);
void Rechercher_plante();
void Afficher(GtkWidget *liste);

