#include <stdlib.h>
#include <string.h>

#include <gtk/gtk.h>
#include "interface.h"
#include "support.h"
#include "authentification.h"
#include "employee.h"

int CINExiste_emp (char ch[]){
	employee c;

	FILE* f1;
	f1=fopen("employee.bin","rb");

	while (fread (&c,sizeof (employee),1,f1) != 0) {
		
		if (strcmp (c.cin,ch) == 0) 
			 return 1;
	}
	fclose(f1);
	return 0;
}	

void get_pass( char id[], char *pass)
{
	employee c;
	FILE* f1;
	f1=fopen("employee.bin","rb");

	while (fread (&c,sizeof (employee),1,f1) != 0) 
	{
		
		if (strcmp (c.cin,id) == 0) 
			 strcpy(pass,c.secteur);
	}
	fclose(f1);
}

void get_mail( char id[], char mail[])
{
	employee c;
	FILE* f1;
	f1=fopen("employee.bin","rb");

	while (fread (&c,sizeof (employee),1,f1) != 0) 
	{
		
		if (strcmp (c.cin,id) == 0) 
			 strcpy(mail,c.email);
	}
	fclose(f1);
}

void mail_mdp_oub(char TO[],char pass[]) {
FILE *f;
f=fopen("email.txt","w");
char FROM[100], SUBJECT[100], BODY[500];
strcpy(FROM,"borjlela@gmail.com");
strcpy(SUBJECT,"Mot de passe oublié.");
sprintf(BODY,"Le mot de passe d'accès à l'espace Borj Lella correspondant a cette adresse mail est (%s).  \n",pass);
if (f!=NULL)
{
fprintf (f,"From: %s   \nTo:%s   \nSubject: %s \n \n \n \n%s \n",FROM,TO,SUBJECT,BODY);}
fclose(f);
 FILE *S;

f=fopen("email.sh","w");
if (f!=NULL)
{
fprintf (f,"curl --ssl-reqd --url 'smtps://smtp.gmail.com:465'  --user 'borjlela@gmail.com:outbox123'  --mail-from 'borjlela@gmail.com'  --mail-rcpt '%s' --upload-file email.txt",TO);}
fclose(f);

}








				










