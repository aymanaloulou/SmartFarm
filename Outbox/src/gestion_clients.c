#include "gestion_clients.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>

                                     /////////////////////// Les cruds ////////////////////////
// ajout d'un client //

int verif_existance(char X[])
{
	Client e;
int nb,o=1;
FILE *p;
p=  fopen ("client.bin","rb");
while (fread (&e,sizeof (Client),1,p) != 0){
		if (strcmp (e.cin,X) == 0){ 
			o=0;
	}
	}




fclose(p);
return o;

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


void ajouter_list_client(Client S){
		FILE* f;
		
	
		
		f = fopen ("client.bin","ab");
		          
		fwrite (&S,sizeof (Client),1,f);
		fclose (f);
}
// modifier un client //
