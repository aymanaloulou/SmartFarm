struct date{
	int j;
	int m;
	int a;
}

struct heure {
	int h;
	int m; 
}

typedef struct ouvrier{
	char nom[20];
	char pren[20];
	char cin[9];
	struct date date_nais;
	char num_tel[9];
	char adr[50];
	char email[25];
	char secteur[20];
}ouvrier;

typedef struct pointage{
	char cin[9];
	struct date date_point;
	struct heure entre_matin;
	struct heure sort_matin;
	struct heure entre_soir;
	struct heure sort_soir;
}

typedef struct conge{
	char cin[9];
	char secteur[20];
	int dure;
	struct date date_deb;
	struct date date_fin;
	char rais[50];
}

void fn_list_ouvrier (ouvrier* t,int* nb);
void fn_rech_ouvrier (char* rech);
void fn_ajout_ouvrier (ouvrier ouv);
void fn_modif_ouvrier (ouvrier ouv);
void fn_supp_ouvrier (ouvrier ouv);
int fn_verif_cin (char* c);

void fn_list_point (pointage* t,int* nb);
void fn_rech_point (char* rech);
void fn_ajout_point (pointage p);
void fn_modif_point (pointage p);

void fn_demande_conge (conge c);
