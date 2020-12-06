typedef struct
{
	char ref[20];
	char ref_mere[20];
	char gender[10] ;
	char poids[10] ;
	char date[10];
	char robe[20];
	char lot[100];
}animal;

void ajoutCapteur (animal a);
int VerifRef (char ch[]);
//void ModifAnimal ();
void suppAnimal  (animal a) ;
void AffichListeAnimal(GtkWidget *liste) ;
//void RechercheAnimal ();
