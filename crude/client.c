#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"

int verifCIN (char ch[]){
	client c;
	int k=1;
	
	int i;
	if (strlen (ch) != 8){
		k=0;
		
	}
	for (i=0;i<strlen(ch);i++)
		if (ch[i]<'0' || ch[i]>'9'){
			k=0;
		break;	
		}
		FILE* f1;
		f1=fopen("client.bin","rb");
	
	while (fread (&c,sizeof (client),1,f1) != 0){
		if (strcmp (c.cin,ch) == 0) 
			 k=0;
	}
	fclose(f1);
	return k;
	
}

int nomValide (char ch[]){
	int i=0,ok = 1;
	while (ok == 1 && i<strlen (ch)){
		if (toupper (ch[i])>='A' && toupper (ch[i]) <='Z')
			i++;
		else
			ok = 0;
	}
	return ok;
}

int numValide (char ch[]){
	int i=0,ok = 1;
	while (ok == 1 && i<strlen (ch)){
		if (ch[i]>'0' && ch[i] <'9')
			i++;
		else
			ok = 0;
	}
	return ok;
}
int pos (char c,char ch[]){
	int ok = -1,i = 0;
	while (ok == -1 && i<strlen (ch)){
		if (ch[i] == c)
			ok = i;
		else
			i++;
	}
	return ok;
}
int emailValide (char ch[]){
	if (pos ('@',ch)<1)
		return 0;
	if (pos ('.',ch)<3)
		return 0;
	return 1;
}

client readClient (FILE *f){
	client c;
	do{
		printf ("cin : ");
		getchar();
		gets (c.cin);
	}while (verifCIN (c.cin)==0);
	
	do{
		printf ("Nom : ");
		gets (c.nom);
	}while (nomValide (c.nom) == 0);
	
	do{
		printf ("Prenom : ");
		gets (c.prenom);
	}while (nomValide (c.prenom) == 0);
	
	printf ("Genre : ");
	gets (c.gender);
	
	do{
		printf ("Numero de telephone : ");
		gets (c.numero_de_telephone);
	}while (numValide (c.numero_de_telephone) == 0);
	
	printf ("Adresse : ");
	gets (c.adress);
	
	do{
		printf ("E-mail : ");
		gets (c.email);
	}while (emailValide (c.email) == 0);
	
	printf ("Date de naissance : ");
	scanf ("%d %d %d",&c.date_de_naissance.jour,&c.date_de_naissance.mois,&c.date_de_naissance.annee);
	
	return c;
}


void ajoutClient (){
		FILE* f;
		client c;
		system ("cls");
		
		f = fopen ("client.bin","rb");
		c = readClient (f);
		fclose (f);
			f = fopen ("client.bin","a+b");
			
		fwrite (&c,sizeof (client),1,f);
		fclose (f);
		
}
void affichListeClient()
{
    FILE *F = NULL;
    client t;
    F=fopen("client.bin","rb");


    if (F == NULL)
    {
        printf ("ce fichier n'existe pas ");
    }
    else
    {
     printf("la list des clients est \n \n");
     printf("cin         nom       prenom     gender     numero      date de naissance email          adress");

    while(fread(&t,sizeof(client),1,F)!=0)
    {
           fflush(stdin);
           printf ("\n \n");
           printf("%-12s",t.cin);
           printf("%-9s",t.nom	);
           printf("%-10s",t.prenom);
	printf("%-10s",t.gender);

           printf("%-10s",t.numero_de_telephone);
           printf("%-2d/%-2d/%-11d",t. date_de_naissance.jour,t. date_de_naissance.mois,t. date_de_naissance.annee);
           printf("%-10s",t.email);
           printf("%s \n",t.adress);
	


    }
          fclose(F);
          system("PAUSE");
}
}
