
struct datee{
	int j;
	int m;
	int a;
}datee;

typedef struct {
	char nom[20];
	char pren[20];
	char cin[9];
	struct datee date_nais;
	char etat_civil[20];
	char genre[10];
	char num_tel[9];
	char adr[50];
	char email[25];
	char secteur[20];
}employee;

typedef struct {
	char cin[9];
	char secteur[20];
	struct datee date_deb;
	struct datee date_fin;
	char rais[50];
}congee;

int fn_ajout_employee (employee e,GtkWidget *button);
void fn_rech_employee (char *cin_rech, GtkWidget *liste);
void fn_list_employee (GtkWidget *liste);
int fn_modif_employee (employee o,GtkWidget *button);
void fn_supp_employee (char *cin_supp);

void fn_list_conge (GtkWidget *liste);
void fn_approuve_conge (congee c);
void fn_refuse_conge (congee c);
void fn_list_conge_approuve (GtkWidget *liste);
