#include <gtk/gtk.h>
typedef struct 
{
char nom[100];
char prenom[100];
char username[100];
char password[100];
char role[100];
}inscri;

void ajouter (char nom[], char prenom[],char username[], char password[],char role[]);
//////////////////////////////////////
int verif(char T[],char A[]);
