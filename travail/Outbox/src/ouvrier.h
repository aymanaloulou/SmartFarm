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
	struct date date_point;
	struct heure entre_matin;
	struct heure sort_matin;
	struct heure entre_soir;
	struct heure sort_soir;
}pointage;

typedef struct{
	char cin[9];
	char secteur[20];
	int dure;
	struct date date_deb;
	struct date date_fin;
	char rais[50];
}conge;

void fn_list_ouvrier (GtkWidget *liste);
void fn_rech_ouvrier (char *cin_rech, GtkWidget *liste);
int fn_ajout_ouvrier (ouvrier ouv,GtkWidget *button);
int fn_modif_ouvrier (ouvrier ouv,GtkWidget *button);
void fn_supp_ouvrier (char* cin_supp);

void fn_list_point (pointage* t,int* nb);
void fn_rech_point (char* rech);
void fn_ajout_point (pointage p);
void fn_modif_point (pointage p);

void fn_demande_conge (conge c);
