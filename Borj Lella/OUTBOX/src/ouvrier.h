struct date{
	int j;
	int m;
	int a;
}date;

struct heure {
	int h;
	int m; 
}heure;

typedef struct{
	char nom[20];
	char pren[20];
	char cin[9];
	struct date date_nais;
	char etat_civil[20];
	char genre[10];
	char num_tel[9];
	char adr[50];
	char email[25];
	char secteur[20];
}ouvrier;

typedef struct{
	char cin[9];
	char nom[20];
	char pren[20];
	struct date date_point;
	struct heure entre_matin;
	struct heure sort_matin;
	struct heure entre_soir;
	struct heure sort_soir;
	int abs;
}pointage;

typedef struct{
	char cin[9];
	char secteur[20];
	struct date date_deb;
	struct date date_fin;
	char rais[50];
}conge;

typedef struct
{
	pointage p;
	int nb_heures;
	int nb_abs;
}best;

void fn_list_ouvrier (GtkWidget *liste);
void fn_rech_ouvrier (char *cin_rech, GtkWidget *liste);
int fn_ajout_ouvrier (ouvrier ouv,GtkWidget *button);
int fn_modif_ouvrier (ouvrier ouv,GtkWidget *button);
void fn_supp_ouvrier (char* cin_supp);

void fn_list_point (GtkWidget *liste);
void fn_rech_point (char *date, GtkWidget *liste);
void fn_ajout_point (pointage p,GtkWidget *button);
void fn_modif_point (pointage p);

int fn_demande_conge (conge c,GtkWidget *button);
void fn_list_conge (GtkWidget *liste);

void fn_meilleur_ouvrier (struct date be, GtkWidget *button);
void fn_taux_abs (struct date be, GtkWidget *button);
