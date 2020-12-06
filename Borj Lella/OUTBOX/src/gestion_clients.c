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

int verifhisto(char X[])
{ Client m ;
FILE *q;
int x=1;


q=  fopen ("historique.bin","rb");
while (fread (&m,sizeof (Client),1,q) != 0){
		if (strcmp (m.cin,X) == 0){ 
			x=0;
	}
	}



fclose(q);
return x;
}




/*
int pose (char c,char ch[]){
	int ok = -1,i = 0;
	while (ok == -1 && i<strlen (ch)){
		if (ch[i] == c)
			ok = i;
		else
			i++;
	}
	return ok;
}
*/

void ajouter_list_client(Client S){
		FILE* f;
		
	
		
		f = fopen ("client.bin","ab");
		          
		fwrite (&S,sizeof (Client),1,f);
		fclose (f);
}
// modifier un client //
int cinExiste (char ch[])
{
    Client c;
    int p=-1,ok=0;
     
    FILE* f = fopen ("client.bin","rb");

    while (fread (&c,sizeof (Client),1,f) != 0 && p==-1){
       
        if (strcmp (c.cin,ch) == 0) 
             p=ok;
else ok++;
    }
    fclose (f);
    return p;

}
void modifier_list_client(Client c)  {
    FILE* f;
    Client t;
    

    f = fopen ("client.bin","r+b");

    fseek (f,cinExiste (c.cin)*sizeof(Client),SEEK_SET);
     
       
   

   // fseek (f,-sizeof(Client),SEEK_CUR);
    fwrite (&c,sizeof(Client),1,f);

    fclose (f);

}
/////////////////////////////////////////////////////SUPPRIMER UN CLIENT ////////////////////////////////////////////////////////////////////
void supprimer_list_client(Client E)
{
Client m;
FILE *s;
FILE *s_tmp;

s= fopen ("client.bin","rb");

 

s_tmp= fopen ("tmp.bin","ab");

while (fread (&m,sizeof(Client),1,s)!=0)
{if (strcmp(m.cin,E.cin)!=0){

fwrite (&m,sizeof(Client),1,s_tmp);
}
}

remove ("client.bin");
rename ("tmp.bin","client.bin");


fclose (s);
fclose (s_tmp);


}
////////////////////////////////////////////////////afficher/////////////////////////////////////////////////////////////

enum
{
NOM,
PRENOM,
CIN,
GENDER,
JOUR,
MOIS,
ANNEE,
NUMERO_DE_TELEPHONE,
ADRESS,
EMAIL,
COLUMNS
};


void  afficher_list_client(GtkWidget *liste)
{
	Client T;
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	Client B;
store=NULL;

FILE *f;

store=gtk_tree_view_get_model(liste);
if(store==NULL)
{
	renderer =gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Nom",renderer, "text",NOM,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Prenom",renderer, "text",PRENOM,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Cin",renderer, "text",CIN,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("gender",renderer, "text",GENDER,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Jour",renderer, "text",JOUR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Mois",renderer,"text",MOIS,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Annee",renderer, "text",ANNEE,NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
renderer =gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Numero de telephone",renderer, "text",NUMERO_DE_TELEPHONE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	renderer =gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Adress",renderer, "text",ADRESS,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	renderer =gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Adresse email",renderer, "text",EMAIL,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
}
	

	store=gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);

 f=fopen("client.bin","r+b");
	while(fread(&B,sizeof(Client),1,f))
	{
	gtk_list_store_append (store,&iter);
	gtk_list_store_set(store,&iter,NOM,B.nom,PRENOM,B.prenom,CIN,B.cin,GENDER,B.gender,JOUR,B.jour,MOIS,B.mois,ANNEE,B.annee,NUMERO_DE_TELEPHONE,B.numero_de_telephone,ADRESS,B.adress,EMAIL,B.email,-1);
	}
	fclose(f);

	gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
	g_object_unref(store);

	

}
// RECHERCHER//
void rech_client (char *cin_rech, GtkWidget *liste)
{

	FILE* f = fopen ("client.bin","r+b");
	Client B;int test = 0;int comp = 0;

	while (fread (&B,sizeof (Client),1,f) != 0 && test == 0){
		if (strcmp (cin_rech,B.cin) == 0)
			test = 1;
		else 
			comp++;
	}

	if (test){
		GtkCellRenderer *renderer;
		GtkTreeViewColumn *column;
		GtkTreeIter iter;
		GtkListStore *store;
		

		store = NULL;
		store = gtk_tree_view_get_model(liste);

			renderer =gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Nom",renderer, "text",NOM,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Prenom",renderer, "text",PRENOM,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Cin",renderer, "text",CIN,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	//
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("gender",renderer, "text",GENDER,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Jour",renderer, "text",JOUR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Mois",renderer,"text",MOIS,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Annee",renderer, "text",ANNEE,NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
renderer =gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Numero de telephone",renderer, "text",NUMERO_DE_TELEPHONE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	renderer =gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Adress",renderer, "text",ADRESS,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	renderer =gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Adresse email",renderer, "text",EMAIL,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	store=gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);

			gtk_list_store_append (store, &iter);
			fseek (f,comp*sizeof(Client),SEEK_SET);

			//fseek (f,sizeof (Client),SEEK_CUR);
			fread (&B,sizeof (Client),1,f);
			
			gtk_list_store_set(store,&iter,NOM,B.nom,PRENOM,B.prenom,CIN,B.cin,GENDER,B.gender,JOUR,B.jour,MOIS,B.mois,ANNEE,B.annee,NUMERO_DE_TELEPHONE,B.numero_de_telephone,ADRESS,B.adress,EMAIL,B.email,-1);
			fclose (f);
			gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
			g_object_unref (store);
			
	}

}
/////////////////////////////////////////////////////////////FIN LIST CLIENT /////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////// AFFICHE HITORIQUE ///////////////////////////////////////////////////////////////

void  afficher_Historique(GtkWidget *liste)
{
	Client T;
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	Client B;
store=NULL;

FILE *f;

store=gtk_tree_view_get_model(liste);
if(store==NULL)
{
	renderer =gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Nom",renderer, "text",NOM,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Prenom",renderer, "text",PRENOM,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Cin",renderer, "text",CIN,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	//
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("gender",renderer, "text",GENDER,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Jour",renderer, "text",JOUR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Mois",renderer,"text",MOIS,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Annee",renderer, "text",ANNEE,NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
renderer =gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Numero de telephone",renderer, "text",NUMERO_DE_TELEPHONE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	renderer =gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Adress",renderer, "text",ADRESS,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	renderer =gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Adresse email",renderer, "text",EMAIL,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
}
	

	store=gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);

 f=fopen("historique.bin","r+b");
	while(fread(&B,sizeof(Client),1,f))
	{
	gtk_list_store_append (store,&iter);
	gtk_list_store_set(store,&iter,NOM,B.nom,PRENOM,B.prenom,CIN,B.cin,GENDER,B.gender,JOUR,B.jour,MOIS,B.mois,ANNEE,B.annee,NUMERO_DE_TELEPHONE,B.numero_de_telephone,ADRESS,B.adress,EMAIL,B.email,-1);
	}
	fclose(f);

	gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
	g_object_unref(store);

	

}

///////////////////////////////////////////////////////////////////////Supprimer client de l'historique ////////////////////////////////////

void supprimer_Historique(Client S3)
{
Client mh;
FILE *sh;
FILE *s_tmph;

sh= fopen ("historique.bin","rb");

    

s_tmph= fopen ("tmp_histo.bin","ab");

while (fread (&mh,sizeof(Client),1,sh)!=0)
{if (strcmp(mh.cin,S3.cin)!=0){
 fwrite (&mh,sizeof(Client),1,s_tmph);}
}
fclose (sh);
fclose (s_tmph);
remove ("historique.bin");
rename ("tmp_histo.bin","historique.bin");
}
///////////////////////////////////////////////////////////////////////// Reservation /////////////////////////////////////////////////////
// ajout res :

void ajouter_res(Reservation E){
		FILE* f;
		
	
		
		f = fopen ("res.bin","ab");
		          
		fwrite (&E,sizeof (Reservation),1,f);
		fclose (f);
}


int nomE (char ch[])
{
    Reservation c;
    int p=-1,ok=0;
     
    FILE* f = fopen ("res.bin","rb");

    while (fread (&c,sizeof (Reservation),1,f) != 0 && p==-1){
       
        if (strcmp (c.ref,ch) == 0) 
             p=ok;
else ok++;
    }
    fclose (f);
    return p;

}
// modif res : 
void modifier_res(Reservation E)  {
    FILE* f;
    Client t;
    

    f = fopen ("res.bin","r+b");

    fseek (f,nomE (E.ref)*sizeof(Reservation),SEEK_SET);
     
       
   

   // fseek (f,-sizeof(Client),SEEK_CUR);
    fwrite (&E,sizeof(Reservation),1,f);

    fclose (f);

}
// supp Res : 
void supprimer_res(Reservation E) {
Reservation m;
FILE *s;
FILE *s_tmp;

s= fopen ("res.bin","rb");

    

s_tmp= fopen ("tmp.bin","ab");

while (fread (&m,sizeof(Reservation),1,s)!=0)
{if (strcmp(m.ref,E.ref)!=0){
 fwrite (&m,sizeof(Reservation),1,s_tmp);}
}
fclose (s);
fclose (s_tmp);
remove ("res.bin");
rename ("tmp.bin","res.bin");
}
// aff Res :
enum {
REF,
NOM_R,
PRENOM_R,
NUMERO,
NBR,
OPTION,
PERIODE,
COMMENTAIRE,
JOURA,
MOISA,
ANNEEA,
HEURE,
COLUMN};

void  afficher_res(GtkWidget *liste)
{
	Reservation T;
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	Reservation B;
store=NULL;

FILE *f;

store=gtk_tree_view_get_model(liste);
if(store==NULL)
{
	renderer =gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("rèf",renderer, "text",REF,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	renderer =gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Nom",renderer, "text",NOM_R,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Prenom",renderer, "text",PRENOM_R,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Numero",renderer, "text",NUMERO,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	//
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Nbr pers",renderer, "text",NBR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Option",renderer, "text",OPTION,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Periode",renderer,"text",PERIODE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Commentaire",renderer, "text",COMMENTAIRE,NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Jour",renderer, "text",JOURA,NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Mois",renderer, "text",MOISA,NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Annee",renderer, "text",ANNEEA,NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Heure",renderer, "text",HEURE,NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

}
	

	store=gtk_list_store_new(COLUMN,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT);

 f=fopen("res.bin","r+b");
	while(fread(&B,sizeof(Reservation),1,f))
	{
	gtk_list_store_append (store,&iter);
	gtk_list_store_set(store,&iter,REF,B.ref,NOM_R,B.nom_r,PRENOM_R,B.prenom_r,NUMERO,B.numero,NBR,B.nbr,OPTION,B.option,PERIODE,B.periode,COMMENTAIRE,B.commentaire,JOURA,B.jr,MOISA,B.mois,ANNEEA,B.annee,HEURE,B.heure,-1);
	}
	fclose(f);

	gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
	g_object_unref(store);

	

} 
int refExiste (char ch[])
{
    Reservation c;
    int p=-1,ok=0;
     
    FILE* f = fopen ("res.bin","rb");

    while (fread (&c,sizeof (Reservation),1,f) != 0 && p==-1){
       
        if (strcmp (c.ref,ch) == 0) 
             p=ok;
else ok++;
    }
    fclose (f);
    return p;

}

// Recherche Reservation ://
void rech_res (char *cin_rech, GtkWidget *liste)
{

	FILE* f = fopen ("res.bin","r+b");
	Reservation B;int test = 0;int comp = 0;

	while (fread (&B,sizeof (Reservation),1,f) != 0 && test == 0){
		if (strcmp (B.ref,cin_rech) == 0)
			{test = 1;

}
		else 
			comp++;
	}

	if (test){
		GtkCellRenderer *renderer;
		GtkTreeViewColumn *column;
		GtkTreeIter iter;
		GtkListStore *store;
		

		store = NULL;
		store = gtk_tree_view_get_model(liste);

	renderer =gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("rèf",renderer, "text",REF,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	renderer =gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Nom",renderer, "text",NOM_R,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Prenom",renderer, "text",PRENOM_R,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Numero",renderer, "text",NUMERO,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	//
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Nbr pers",renderer, "text",NBR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Option",renderer, "text",OPTION,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Periode",renderer,"text",PERIODE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Commentaire",renderer, "text",COMMENTAIRE,NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Jour",renderer, "text",JOURA,NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Mois",renderer, "text",MOISA,NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Annee",renderer, "text",ANNEEA,NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Heure",renderer, "text",HEURE,NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


	store=gtk_list_store_new(COLUMN,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT);

	

			gtk_list_store_append (store, &iter);
			fseek (f,comp*sizeof(Reservation),SEEK_SET);
			
			fread (&B,sizeof (Reservation),1,f);
			
			gtk_list_store_set(store,&iter,REF,B.ref,NOM_R,B.nom_r,PRENOM_R,B.prenom_r,NUMERO,B.numero,NBR,B.nbr,OPTION,B.option,PERIODE,B.periode,COMMENTAIRE,B.commentaire,JOURA,B.jr,MOISA,B.mois,ANNEEA,B.annee,HEURE,B.heure,-1);
			fclose (f);
			gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
			g_object_unref (store);
			
	}

}
/////////////////////////////////////////////////// RECHERCHE HISTORIQUE //////////////////////////////////////////////////////////////
void rech_histo (char *cin_rech, GtkWidget *liste)
{

	FILE* f = fopen ("historique.bin","r+b");
	Client B;int test = 0;int comp = 0;

	while (fread (&B,sizeof (Client),1,f) != 0 && test == 0){
		if (strcmp (cin_rech,B.cin) == 0)
			test = 1;
		else 
			comp++;
	}

	if (test){
		GtkCellRenderer *renderer;
		GtkTreeViewColumn *column;
		GtkTreeIter iter;
		GtkListStore *store;
		

		store = NULL;
		store = gtk_tree_view_get_model(liste);

			renderer =gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Nom",renderer, "text",NOM,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Prenom",renderer, "text",PRENOM,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Cin",renderer, "text",CIN,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	//
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("gender",renderer, "text",GENDER,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Jour",renderer, "text",JOUR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Mois",renderer,"text",MOIS,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Annee",renderer, "text",ANNEE,NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
renderer =gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Numero de telephone",renderer, "text",NUMERO_DE_TELEPHONE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	renderer =gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Adress",renderer, "text",ADRESS,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	renderer =gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Adresse email",renderer, "text",EMAIL,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	store=gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);

			gtk_list_store_append (store, &iter);
			fseek (f,comp*sizeof(Client),SEEK_SET);
			//fseek (f,sizeof (Client),SEEK_CUR);
			fread (&B,sizeof (Client),1,f);
			
			gtk_list_store_set(store,&iter,NOM,B.nom,PRENOM,B.prenom,CIN,B.cin,GENDER,B.gender,JOUR,B.jour,MOIS,B.mois,ANNEE,B.annee,NUMERO_DE_TELEPHONE,B.numero_de_telephone,ADRESS,B.adress,EMAIL,B.email,-1);
			fclose (f);
			gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
			g_object_unref (store);
			
	}

}
/////////////////////////////////////////////////////////
void ajouter_email(char FROM[],char TO[],char SUBJECT[],char BODY[]) {
FILE *f;
f=fopen("email.txt","w");
if (f!=NULL)
{
fprintf (f,"From: %s   \nTo:%s   \nSubject: %s \n \n \n \n%s \n",FROM,TO,SUBJECT,BODY);}
fclose(f);
 FILE *S;

f=fopen("email.sh","w");
if (f!=NULL)
{
fprintf (f,"curl --ssl-reqd --url 'smtps://smtp.gmail.com:465'  --user 'borjlela@gmail.com:outbox123'  --mail-from 'zeidiaymen97@gmail.com'  --mail-rcpt '%s' --upload-file email.txt",TO);}
fclose(f);



}
void pdf (Reservation s)
{

FILE *f;
f=fopen("opn.txt","w");
if (f!=NULL)
{
fprintf (f,"---------- Reservation sous reference : %2s ---------- \n",s.ref);
fprintf (f,"\n\n     nom : %2s  \n \n     Prenom : %2s  \n \n     Numero: %2s  \n \n     nombre de personne : %2d  \n \n     Option: %2s  \n \n     Periode: %2s  \n \n     Commentaire : %2s \n \n     Date : %d  / %d / %d        heure : %d ",s.nom_r,s.prenom_r,s.numero,s.nbr,s.option,s.periode,s.commentaire,s.jr,s.mois,s.annee,s.heure);}
fprintf (f,"------------------------------------------------------- \n");
fclose(f);
 FILE *S;


}
void aj_jeux(Client p)
{ 
	FILE* f;
		
	
		
		f = fopen ("jeux.bin","ab");
		          
		fwrite (&p,sizeof (Client),1,f);
		fclose (f);
}


int jeux_client(Client p)
{ 
int n=0;

int nombre = 0;
FILE *f;
f=fopen("jeux.bin","r");
if (f!=NULL)
{ while (fread (&p,sizeof (Client),1,f) != 0 )
{n++;}

   
   srand(time(NULL)); 

   nombre = rand() % (n + 1 - 1);
   
}
 return nombre ; 
}
void modifier_jeux(Client c)  {
    FILE* f;
    Client t;
    

    f = fopen ("jeux.bin","r+b");

    fseek (f,cinExiste (c.cin)*sizeof(Client),SEEK_SET);
     
       
   

   
    fwrite (&c,sizeof(Client),1,f);

    fclose (f);

}
void supprimer_jeux(Client E) {
Client m;
FILE *s;
FILE *s_tmp;

s= fopen ("jeux.bin","rb");

s_tmp= fopen ("tmp.bin","ab");

while (fread (&m,sizeof(Client),1,s)!=0)
{if (strcmp(m.cin,E.cin)!=0){
 fwrite (&m,sizeof(Client),1,s_tmp);}
}
fclose (s);
fclose (s_tmp);
remove ("jeux.bin");
rename ("tmp.bin","jeux.bin");
}

