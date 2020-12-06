struct date
{
	int jour;
	int mois;
	int annee;
};

typedef struct 
{ 
	char nom[100];
	char prenom[100];
	char cin[100];
	char gender[100];
	char numero_de_telephone[100];
	char adress[100];
	char email[100];
	struct date date_de_naissance;
	
}client;

void ajoutClient ();
client readClient (FILE *f);
int emailValide (char ch[]);
int pos (char c,char ch[]);
int numValide (char ch[]);
int nomValide (char ch[]);
int verifCIN (char ch[]);
void modifClient ();
void suppClient ();
void affichListeClient ();
void rechercheClient ();
client lireClient ();
