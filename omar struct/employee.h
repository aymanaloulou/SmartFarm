struct date{
	int j;
	int m;
	int a;
}

typedef struct employee{
	char nom[20];
	char pren[20];
	char cin[9];
	struct date date_nais;
	char num_tel[9];
	char adr[50];
	char email[25];
	char secteur[20];
}employee;

typedef struct conge{
	char cin[9];
	char secteur[20];
	int dure;
	struct date date_deb;
	struct date date_fin;
	char rais[50];
}

void fn_list_employ (employee* t,int* nb);
void fn_rech_employ (char* rech);
void fn_ajout_employ (employee emp);
void fn_modif_employ (employee emp);
void fn_supp_employ (employee emp);

void fn_list_conge (conge* t,int* nb);
void fn_approuve_conge (conge c);
void fn_refuse_conge (conge c);
void fn_list_conge_approuve (cong* t,int* nb);

