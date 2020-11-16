#include <gtk/gtk.h>
#include <stdio.h>
#include "fct.h"
#include <string.h>



void ajouter (char nom[], char prenom[],char username[], char password[],char role[])
{ 
FILE *f;
f=fopen("inscri.txt","a+");
if (f!=NULL)
{
fprintf (f,"nom : %s prenom :  %s username : %s password : %s role :  %s \n",nom,prenom,username,password,role);}
fclose(f);


}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int verif(char T[], char A[])
{
int test=0;

char n[100];
char m[100];
char s[100];
char z[100];
char a[100];
FILE *f;
f=fopen("inscri.txt","r");
if (f!=NULL)
{while (!feof(f))
{fscanf(f,"nom : %s prenom :  %s username : %s password : %s role :  %s \n",m,a,s,n,z);

if ((strcmp(s,T)==0) && (strcmp(n,A)==0))
test=1;
}
}
fclose(f);

return test ;

}

