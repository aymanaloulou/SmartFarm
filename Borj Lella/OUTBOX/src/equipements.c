#include <string.h>
#include "support.h"
#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include "equipements.h"
#include "entretiens.h"
#include <gtk/gtk.h>

int verifID_eq (char ch[]){
	equipements eq;
	int k=1;
	FILE* f1;
	
	f1=fopen("equipements.bin","rb");
	while (fread (&eq,sizeof (equipements),1,f1) != 0 && k == 1) {
		
		if (strcmp (eq.id,ch) == 0) 
			 k=0;
	}
	fclose(f1);
	return k;
	
}
int numValide_eq (char ch[]){
	int i=0,ok = 1;
	while (ok == 1 && i<strlen (ch)){
		if (ch[i]<'0' || ch[i] >'9')
			ok = 0;
			else
			i++; 	
			
		
	}
	return ok;
}
enum
{
	EID,
	ETYPE,
	EMARQUE,
	EDATE,
	EPRIX,
	EASSOCIATION,
	COLUMNS,
};

void rest_eq( equipements eq)
{
	FILE* f;
	f = fopen("equipements.bin","a+b");
	if (f!=NULL)
		{
			fwrite(&eq,sizeof(equipements),1,f);
			fclose(f);
		}
}

int ajouter_equipement( equipements eq, GtkWidget *objet)
{
	int ok = 1;
	GtkWidget *e_id = lookup_widget(objet,"e_id");
	GtkWidget *e_type =lookup_widget(objet,"e_type");
	GtkWidget *e_marque =lookup_widget(objet,"e_marque");
	GtkWidget *e_prix =lookup_widget(objet,"e_prix");
	GtkWidget *e_association =lookup_widget(objet,"e_association");
	if (verifID_eq (eq.id) == 0 || strcmp(eq.id,"") == 0){
		ok = 0;
		gtk_label_set_text(GTK_LABEL(e_id),"invalide");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(e_id),"");
	}
	
	
	if (strcmp(eq.type,"") == 0){
		ok = 0;
		gtk_label_set_text(GTK_LABEL(e_type),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(e_type),"");
	}
	if (strcmp(eq.marque,"") == 0){
		ok = 0;
		gtk_label_set_text(GTK_LABEL(e_marque),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(e_marque),"");
	}
	if (strcmp(eq.prix,"") == 0 || !numValide_eq(eq.prix)){
		ok = 0;
		gtk_label_set_text(GTK_LABEL(e_prix),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(e_prix),"");
	}
	if (strcmp(eq.association,"") == 0){
		ok = 0;
		gtk_label_set_text(GTK_LABEL(e_association),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(e_association),"");
	}

	if (ok){
	FILE* f;
	f = fopen("equipements.bin","ab+");
	if (f!=NULL)
		{
			fwrite(&eq,sizeof(equipements),1,f);
			fclose(f);
		}
	}

	return ok;
}
//////////////////////////////////////////////////////
void afficher_equipement(GtkWidget *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	
	FILE* f;
	equipements eq;
	
	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Identifiant", renderer, "text",EID,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text",ETYPE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Marque", renderer, "text",EMARQUE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Date d'ajout", renderer, "text",EDATE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Prix d'achat", renderer, "text",EPRIX,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Associé à l'ouvrier", renderer, "text",EASSOCIATION,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	f=fopen("equipements.bin","rb");
	//f=fopen("equipements.txt","r");
	if(f==NULL)
	{
		return;
	}
	else
	{
		//f=fopen("equipements.bin","a+b");
		while(fread(&eq,sizeof(equipements),1,f)!=0)
		/*f=fopen("equipements.txt","a+");
		while(fscanf(f,"%s %s %s %s %s %s \n",id,type,marque,date,prix,association)!=EOF)*/
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set (store, &iter, EID, eq.id, ETYPE, eq.type, EMARQUE, eq.marque, EDATE,eq.date, EPRIX, eq.prix, EASSOCIATION, eq.association, -1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
		g_object_unref (store);
	}
}


/////////////////////////////////////////////////////
void supprimer_equipement( char id[])
{
	equipements eq2;
	FILE *f, *g, *h;
		h=fopen("histo_eq.bin","ab");
		f=fopen("equipements.bin","rb");
		g=fopen("equipements2.bin","wb");
		/*f=fopen("equipements.txt","r");
		g=fopen("equipements2.txt","w");*/
	if (f==NULL || g==NULL)
		return;
	else
	{
		while(fread(&eq2,sizeof(equipements),1,f)!=0)
		//while(fscanf(f,"%s %s %s %s %s %s \n",eq2.id,eq2.type,eq2.marque,eq2.date,eq2.prix,eq2.association)!=EOF)
			{
				if (strcmp(id,eq2.id)!=0)
					fwrite (&eq2,sizeof(equipements),1,g);
					//fprintf(g,"%s %s %s %s %s %s \n",eq2.id,eq2.type,eq2.marque,eq2.date,eq2.prix,eq2.association);
				else
					fwrite (&eq2,sizeof(equipements),1,h);
			}
		fclose(f);
		fclose(g);
		fclose(h);
		remove("equipements.bin");
		rename("equipements2.bin","equipements.bin");
		/*remove("equipements.txt");
		rename("equipements2.txt","equipements.txt");*/
			
}
}	

void set_combo_entretien(GtkComboBox     *combobox)
{
equipements eq;
FILE* f;
f=fopen("equipements.bin","rb");
if (f==NULL)
	return;
else
{
while(fread(&eq,sizeof(equipements),1,f)!=0)
{
gtk_combo_box_append_text (GTK_COMBO_BOX (combobox), _(eq.id));
}
}
fclose(f);
}

/////////////////////////////////////////////////////////
void afficher_histo_eq(GtkWidget *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	
	FILE* f;
	equipements eq;

	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Identifiant", renderer, "text",EID,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text",ETYPE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Marque", renderer, "text",EMARQUE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Date d'ajout", renderer, "text",EDATE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Prix d'achat", renderer, "text",EPRIX,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Associé à l'ouvrier", renderer, "text",EASSOCIATION,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	f=fopen("histo_eq.bin","rb");
	if(f==NULL)
	{
		return;
	}
	else
	{
		while(fread(&eq,sizeof(equipements),1,f)!=0)
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set (store, &iter, EID, eq.id, ETYPE, eq.type, EMARQUE, eq.marque, EDATE,eq.date, EPRIX, eq.prix, EASSOCIATION, eq.association, -1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
		g_object_unref (store);
	}
}

void supp_histo_eq( char id[])
{
	equipements eq2;
	FILE *f,*g;
		f=fopen("histo_eq.bin","rb");
		g=fopen("histo_eq2.bin","wb");
		
	if (f==NULL || g==NULL)
		return;
	else
	{
		while(fread(&eq2,sizeof(equipements),1,f)!=0)
			{
				if (strcmp(id,eq2.id)!=0)
					fwrite (&eq2,sizeof(equipements),1,g);
			}
		fclose(f);
		fclose(g);
		
		remove("histo_eq.bin");
		rename("histo_eq2.bin","histo_eq.bin");

}
}	
//////////////////////////////////////////////////////////

void rech_eq(char *id,GtkWidget *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	
	FILE* f;
	equipements eq;
	
	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Identifiant", renderer, "text",EID,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text",ETYPE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Marque", renderer, "text",EMARQUE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Date d'ajout", renderer, "text",EDATE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Prix d'achat", renderer, "text",EPRIX,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Associé à l'ouvrier", renderer, "text",EASSOCIATION,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	f=fopen("equipements.bin","rb");
	if(f==NULL)
	{
		return;
	}
	else
	{
		while(fread(&eq,sizeof(equipements),1,f)!=0)
			if ((strstr(eq.id,id) != NULL) || (strstr(eq.type,id) != NULL) || (strstr(eq.marque,id) != NULL) || (strstr(eq.date,id) != NULL) || (strstr(eq.association,id) != NULL) || (strstr(eq.prix,id) != NULL))
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set (store, &iter, EID, eq.id, ETYPE, eq.type, EMARQUE, eq.marque, EDATE,eq.date, EPRIX, eq.prix, EASSOCIATION, eq.association, -1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
		g_object_unref (store);
	}
}
//////////////////////////////////////////////////////////////////////
void afficher_declar_eq(GtkWidget *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	
	FILE* f;
	equipements eq;
	
	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Identifiant", renderer, "text",EID,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text",ETYPE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Marque", renderer, "text",EMARQUE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Date d'ajout", renderer, "text",EDATE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Prix d'achat", renderer, "text",EPRIX,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Associé à l'ouvrier", renderer, "text",EASSOCIATION,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	f=fopen("declar_eq.bin","rb");
	if(f==NULL)
	{
		return;
	}
	else
	{
		while(fread(&eq,sizeof(equipements),1,f)!=0)
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set (store, &iter, EID, eq.id, ETYPE, eq.type, EMARQUE, eq.marque, EDATE,eq.date, EPRIX, eq.prix, EASSOCIATION, eq.association, -1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
		g_object_unref (store);
	}
}

/////////////////////////////////////////////////////////////////////
void rech_declar_eq(char *id,GtkWidget *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	
	FILE* f;
	equipements eq;
	
	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Identifiant", renderer, "text",EID,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text",ETYPE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Marque", renderer, "text",EMARQUE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Date d'ajout", renderer, "text",EDATE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Prix d'achat", renderer, "text",EPRIX,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Associé à l'ouvrier", renderer, "text",EASSOCIATION,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	f=fopen("declar_eq.bin","rb");
	if(f==NULL)
	{
		return;
	}
	else
	{
		while(fread(&eq,sizeof(equipements),1,f)!=0)
			if ((strstr(eq.id,id) != NULL) || (strstr(eq.type,id) != NULL) || (strstr(eq.marque,id) != NULL) || (strstr(eq.date,id) != NULL) || (strstr(eq.association,id) != NULL) || (strstr(eq.prix,id) != NULL))
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set (store, &iter, EID, eq.id, ETYPE, eq.type, EMARQUE, eq.marque, EDATE,eq.date, EPRIX, eq.prix, EASSOCIATION, eq.association, -1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
		g_object_unref (store);
	}
}
////////////////////////////////////////////////////////////////////////
void declarer_eq( equipements eq)
{

	FILE* f;
	f = fopen("declar_eq.bin","ab+");
	if (f!=NULL)
		{
			fwrite(&eq,sizeof(equipements),1,f);
			fclose(f);
		}
}
///////////////////////////////////////////
void supp_declar_eq( char id[])
{
	equipements eq2;
	FILE *f,*g;
		f=fopen("declar_eq.bin","rb");
		g=fopen("declar_eq2.bin","wb");
		
	if (f==NULL || g==NULL)
		return;
	else
	{
		while(fread(&eq2,sizeof(equipements),1,f)!=0)
			{
				if (strcmp(id,eq2.id)!=0)
					fwrite (&eq2,sizeof(equipements),1,g);
			}
		fclose(f);
		fclose(g);
		
		remove("declar_eq.bin");
		rename("declar_eq2.bin","declar_eq.bin");

}
}	
//////////////////////////////////////////
void mettre_top(equipements eq)
{
	FILE* f;
	FILE* g;
	equipements eq2;
	f=fopen("declar_eq.bin","rb");
	g=fopen("temp0.bin","wb");
		while(fread(&eq2,sizeof(equipements),1,f)!=0 )
		{
				if (strcmp(eq.id,eq2.id)==0)
				{
					fwrite (&eq2,sizeof(equipements),1,g);
				}
		
		}
rewind(f);
		while(fread(&eq2,sizeof(equipements),1,f)!=0 )
			{if (strcmp(eq.id,eq2.id)!=0)
				fwrite (&eq2,sizeof(equipements),1,g);}

		fclose(f);
		fclose(g);
		remove("declar_eq.bin");
		rename("temp0.bin","declar_eq.bin");
}
/*////////////////////////////////////////
 * ////////statistique///////////////////
 * ///////////////////////////////////////*/
 int nbre_eq()
 {
	int c=0;
	equipements eq2;
	FILE *f;
	f=fopen("equipements.bin","rb");
	while(fread(&eq2,sizeof(equipements),1,f)!=0 )
		{c++;}
	fclose(f);
	return c;
 }
 
 int nbre_declar_eq()
 {
	int c=0;
	equipements eq2;
	FILE *f;
	f=fopen("declar_eq.bin","rb");
	while(fread(&eq2,sizeof(equipements),1,f)!=0 )
		{c++;}
	fclose(f);
	return c;
 }
 
 int prix_eq()
 {
	int c=0;
	equipements eq2;
	FILE *f;
	f=fopen("equipements.bin","rb");
	while(fread(&eq2,sizeof(equipements),1,f)!=0 )
		{
			c+=atoi(eq2.prix);
		}
	fclose(f);
	return c;
 }
 
 //////////////////////////////////////
 void mail_declar_eq(char TO[],equipements eq) {
FILE *f;
f=fopen("email.txt","w");
char FROM[100], SUBJECT[100], BODY[500];
strcpy(FROM,"borjlela@gmail.com");
strcpy(SUBJECT,"Alerte équipement en panne !");
sprintf(BODY,"L'équipement d'identifiant %s , associé à l'ouvrier %s , de type %s et de marque %s est déclaré en panne ! \n Cette déclaration est urgente, veuillez prendre les mesures convenables. \n",eq.id,eq.association,eq.type,eq.marque);
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
 //////////////////////////////////////
 
///////////////////////////////////////////
///////////////////////////////////////////
///////////////////////////////////////////

void copy_file_eq(FILE* f, FILE* g)
{
	equipements eq;
	while(fread(&eq,sizeof(equipements),1,g)!=0)
		fwrite(&eq,sizeof(equipements),1,f);
}

int longueur_file()
{
	FILE* f;
	f=fopen("tri.bin","rb");
	equipements eq;
	int c=0;
	while(fread(&eq,sizeof(equipements),1,f)!=0)
		{c++;}
	fclose(f);
	return c;
}

void supprimer_tri( char id[])
{
	equipements eq2;
	FILE *f, *g;
		f=fopen("tri.bin","rb");
		g=fopen("tri2.bin","ab");
	if (f==NULL || g==NULL)
		return;
	else
	{
		while(fread(&eq2,sizeof(equipements),1,f)!=0)
			{
				if (strcmp(id,eq2.id)!=0)
					fwrite (&eq2,sizeof(equipements),1,g);
			}
		fclose(f);
		fclose(g);
		remove("tri.bin");
		rename("tri2.bin","tri.bin");
}
}	
//////////////////////////////////////////////////////////
void get_min_id_eq(char *min)
{
	equipements eq;
	int l,i=0;
	FILE* f;
	f=fopen("tri.bin","rb");
	l = longueur_file();
	fread(&eq,sizeof(equipements),1,f);
		strcpy(min,eq.id);
	
	for	(i=0;i<l;i++)
		{
			fread(&eq,sizeof(equipements),1,f);
			if (strcmp(eq.id,min)<0)
				strcpy(min,eq.id);
		}
	fclose(f);	
}

void get_max_id_eq(char *max)
{
	equipements eq;
	int l,i=0;
	FILE* f;
	f=fopen("tri.bin","rb");
	l = longueur_file();
	fread(&eq,sizeof(equipements),1,f);
		strcpy(max,eq.id);
	
	for	(i=0;i<l;i++)
		{
			fread(&eq,sizeof(equipements),1,f);
			if (strcmp(eq.id,max)>0)
				strcpy(max,eq.id);
		}
	fclose(f);	
}

void tri_file_min_id_eq()
{
equipements eq;
equipements eq2;
FILE* f;
FILE* g;
FILE* j;
FILE* k;
char min[20];
int l;
	f=fopen("equipements.bin","rb");
	g=fopen("tri.bin","ab");
	while(fread(&eq,sizeof(equipements),1,f)!=0)
		fwrite(&eq,sizeof(equipements),1,g);
	fclose(f);
	fclose(g);
	j=fopen("tri.bin","rb");
	k=fopen("temp.bin","ab");
	
	do
	{
	l=longueur_file();
	get_min_id_eq(min);
	while(fread(&eq2,sizeof(equipements),1,j)!=0 )
				if (strcmp(min,eq2.id)==0)
				{
					fwrite (&eq2,sizeof(equipements),1,k);
					supprimer_tri(eq2.id);
				}
		rewind(j);
	}
	while(longueur_file()!=0);
		fclose(k);
		fclose(j);
		
		remove("tri.bin");
		rename("temp.bin","tri.bin");
}

void tri_file_max_id_eq()
{
equipements eq;
equipements eq2;
FILE* f;
FILE* g;
FILE* j;
FILE* k;
char max[20];
int l;
	f=fopen("equipements.bin","rb");
	g=fopen("tri.bin","ab");
	while(fread(&eq,sizeof(equipements),1,f)!=0)
		fwrite(&eq,sizeof(equipements),1,g);
	fclose(f);
	fclose(g);
	j=fopen("tri.bin","rb");
	k=fopen("temp.bin","ab");
	
	do
	{
	l=longueur_file();
	get_max_id_eq(max);
	while(fread(&eq2,sizeof(equipements),1,j)!=0 )
				if (strcmp(max,eq2.id)==0)
				{
					fwrite (&eq2,sizeof(equipements),1,k);
					supprimer_tri(eq2.id);
				}
		rewind(j);
	}
	while(longueur_file()!=0);
		fclose(k);
		fclose(j);
		
		remove("tri.bin");
		rename("temp.bin","tri.bin");
}
///////////////////////////////////////////////////
void get_min_type_eq(char *min)
{
	equipements eq;
	int l,i=0;
	FILE* f;
	f=fopen("tri.bin","rb");
	l = longueur_file();
	fread(&eq,sizeof(equipements),1,f);
		strcpy(min,eq.type);
	
	for	(i=0;i<l;i++)
		{
			fread(&eq,sizeof(equipements),1,f);
			if (strcmp(eq.type,min)<0)
				strcpy(min,eq.type);
		}
	fclose(f);	
}

void get_max_type_eq(char *max)
{
	equipements eq;
	int l,i=0;
	FILE* f;
	f=fopen("tri.bin","rb");
	l = longueur_file();
	fread(&eq,sizeof(equipements),1,f);
		strcpy(max,eq.type);
	
	for	(i=0;i<l;i++)
		{
			fread(&eq,sizeof(equipements),1,f);
			if (strcmp(eq.type,max)>0)
				strcpy(max,eq.type);
		}
	fclose(f);	
}

void tri_file_min_type_eq()
{
equipements eq;
equipements eq2;
FILE* f;
FILE* g;
FILE* j;
FILE* k;
char min[20];
int l;
	f=fopen("equipements.bin","rb");
	g=fopen("tri.bin","ab");
	while(fread(&eq,sizeof(equipements),1,f)!=0)
		fwrite(&eq,sizeof(equipements),1,g);
	fclose(f);
	fclose(g);
	j=fopen("tri.bin","rb");
	k=fopen("temp.bin","ab");
	
	do
	{
	l=longueur_file();
	get_min_type_eq(min);
	while(fread(&eq2,sizeof(equipements),1,j)!=0 )
				if (strcmp(min,eq2.type)==0)
				{
					fwrite (&eq2,sizeof(equipements),1,k);
					supprimer_tri(eq2.id);
				}
		rewind(j);
	}
	while(longueur_file()!=0);
		fclose(k);
		fclose(j);
		
		remove("tri.bin");
		rename("temp.bin","tri.bin");
}

void tri_file_max_type_eq()
{
equipements eq;
equipements eq2;
FILE* f;
FILE* g;
FILE* j;
FILE* k;
char max[20];
int l;
	f=fopen("equipements.bin","rb");
	g=fopen("tri.bin","ab");
	while(fread(&eq,sizeof(equipements),1,f)!=0)
		fwrite(&eq,sizeof(equipements),1,g);
	fclose(f);
	fclose(g);
	j=fopen("tri.bin","rb");
	k=fopen("temp.bin","ab");
	
	do
	{
	l=longueur_file();
	get_max_type_eq(max);
	while(fread(&eq2,sizeof(equipements),1,j)!=0 )
				if (strcmp(max,eq2.type)==0)
				{
					fwrite (&eq2,sizeof(equipements),1,k);
					supprimer_tri(eq2.id);
				}
		rewind(j);
	}
	while(longueur_file()!=0);
		fclose(k);
		fclose(j);
		
		remove("tri.bin");
		rename("temp.bin","tri.bin");
}
///////////////////////////////////////////////////
void get_min_marque_eq(char *min)
{
	equipements eq;
	int l,i=0;
	FILE* f;
	f=fopen("tri.bin","rb");
	l = longueur_file();
	fread(&eq,sizeof(equipements),1,f);
		strcpy(min,eq.marque);
	
	for	(i=0;i<l;i++)
		{
			fread(&eq,sizeof(equipements),1,f);
			if (strcmp(eq.marque,min)<0)
				strcpy(min,eq.marque);
		}
	fclose(f);	
}

void get_max_marque_eq(char *max)
{
	equipements eq;
	int l,i=0;
	FILE* f;
	f=fopen("tri.bin","rb");
	l = longueur_file();
	fread(&eq,sizeof(equipements),1,f);
		strcpy(max,eq.marque);
	
	for	(i=0;i<l;i++)
		{
			fread(&eq,sizeof(equipements),1,f);
			if (strcmp(eq.marque,max)>0)
				strcpy(max,eq.marque);
		}
	fclose(f);	
}

void tri_file_min_marque_eq()
{
equipements eq;
equipements eq2;
FILE* f;
FILE* g;
FILE* j;
FILE* k;
char min[20];
int l;
	f=fopen("equipements.bin","rb");
	g=fopen("tri.bin","ab");
	while(fread(&eq,sizeof(equipements),1,f)!=0)
		fwrite(&eq,sizeof(equipements),1,g);
	fclose(f);
	fclose(g);
	j=fopen("tri.bin","rb");
	k=fopen("temp.bin","ab");
	
	do
	{
	l=longueur_file();
	get_min_marque_eq(min);
	while(fread(&eq2,sizeof(equipements),1,j)!=0 )
				if (strcmp(min,eq2.marque)==0)
				{
					fwrite (&eq2,sizeof(equipements),1,k);
					supprimer_tri(eq2.id);
				}
		rewind(j);
	}
	while(longueur_file()!=0);
		fclose(k);
		fclose(j);
		
		remove("tri.bin");
		rename("temp.bin","tri.bin");
}

void tri_file_max_marque_eq()
{
equipements eq;
equipements eq2;
FILE* f;
FILE* g;
FILE* j;
FILE* k;
char max[20];
int l;
	f=fopen("equipements.bin","rb");
	g=fopen("tri.bin","ab");
	while(fread(&eq,sizeof(equipements),1,f)!=0)
		fwrite(&eq,sizeof(equipements),1,g);
	fclose(f);
	fclose(g);
	j=fopen("tri.bin","rb");
	k=fopen("temp.bin","ab");
	
	do
	{
	l=longueur_file();
	get_max_marque_eq(max);
	while(fread(&eq2,sizeof(equipements),1,j)!=0 )
				if (strcmp(max,eq2.marque)==0)
				{
					fwrite (&eq2,sizeof(equipements),1,k);
					supprimer_tri(eq2.id);
				}
		rewind(j);
	}
	while(longueur_file()!=0);
		fclose(k);
		fclose(j);
		
		remove("tri.bin");
		rename("temp.bin","tri.bin");
}
///////////////////////////////////////////////////
int get_min_date_eq()
{
	equipements eq;
	int l,i=0,min,d;
	FILE* f;
	f=fopen("tri.bin","rb");
	l = longueur_file();
	fread(&eq,sizeof(equipements),1,f);
	min= eq.annee*10000+eq.mois*100+eq.jour;
	for	(i=0;i<l;i++)
		{
			fread(&eq,sizeof(equipements),1,f);
			d= eq.annee*10000+eq.mois*100+eq.jour;
			if (d<min)
				min=d;
		}
	fclose(f);	
	return min;
}

int get_max_date_eq()
{
	equipements eq;
	int l,i=0,max,d;
	FILE* f;
	char aux[50];
	f=fopen("tri.bin","rb");
	l = longueur_file();
	fread(&eq,sizeof(equipements),1,f);
	max = eq.annee*10000+eq.mois*100+eq.jour;
	for	(i=0;i<l;i++)
		{
			fread(&eq,sizeof(equipements),1,f);
			d= eq.annee*10000+eq.mois*100+eq.jour;
			if (d>max)
				max=d;
		}
	fclose(f);	
	return max;
}

void tri_file_min_date_eq()
{
equipements eq;
equipements eq2;
FILE* f;
FILE* g;
FILE* j;
FILE* k;
int min,d;
int l;
	f=fopen("equipements.bin","rb");
	g=fopen("tri.bin","ab");
	while(fread(&eq,sizeof(equipements),1,f)!=0)
		fwrite(&eq,sizeof(equipements),1,g);
	fclose(f);
	fclose(g);
	j=fopen("tri.bin","rb");
	k=fopen("temp.bin","ab");
	
	do
	{
	l=longueur_file();
	min=get_min_date_eq();
	while(fread(&eq2,sizeof(equipements),1,j)!=0 )
	{
		d= eq2.annee*10000+eq2.mois*100+eq2.jour;
				if (min==d)
				{
					fwrite (&eq2,sizeof(equipements),1,k);
					supprimer_tri(eq2.id);
				}
	}
		rewind(j);
	}
	while(longueur_file()!=0);
		fclose(k);
		fclose(j);
		
		remove("tri.bin");
		rename("temp.bin","tri.bin");
}

void tri_file_max_date_eq()
{
equipements eq;
equipements eq2;
FILE* f;
FILE* g;
FILE* j;
FILE* k;
int max,d;
int l;
	f=fopen("equipements.bin","rb");
	g=fopen("tri.bin","ab");
	while(fread(&eq,sizeof(equipements),1,f)!=0)
		fwrite(&eq,sizeof(equipements),1,g);
	fclose(f);
	fclose(g);
	j=fopen("tri.bin","rb");
	k=fopen("temp.bin","ab");
	
	do
	{
	l=longueur_file();
	max=get_max_date_eq();
	while(fread(&eq2,sizeof(equipements),1,j)!=0 )
	{
		d= eq2.annee*10000+eq2.mois*100+eq2.jour;
				if (max==d)
				{
					fwrite (&eq2,sizeof(equipements),1,k);
					supprimer_tri(eq2.id);
				}
	}
		rewind(j);
	}
	while(longueur_file()!=0);
		fclose(k);
		fclose(j);
		
		remove("tri.bin");
		rename("temp.bin","tri.bin");
}
///////////////////////////////////////////////////
int get_min_prix_eq()
{
	equipements eq;
	int l,i=0,min,a;
	FILE* f;
	f=fopen("tri.bin","rb");
	l = longueur_file();
	fread(&eq,sizeof(equipements),1,f);
		min=atoi(eq.prix);
	
	for	(i=0;i<l;i++)
		{
			fread(&eq,sizeof(equipements),1,f);
			a=atoi(eq.prix);
			if (a<min)
				min=a;
		}
	fclose(f);	
	return min;
}

int get_max_prix_eq()
{
	equipements eq;
	int l,i=0,max,a;
	FILE* f;
	f=fopen("tri.bin","rb");
	l = longueur_file();
	fread(&eq,sizeof(equipements),1,f);
		max=atoi(eq.prix);
	
	for	(i=0;i<l;i++)
		{
			fread(&eq,sizeof(equipements),1,f);
			a=atoi(eq.prix);
			if (a>max)
				max=a;
		}
	fclose(f);
	return max;	
}

void tri_file_min_prix_eq()
{
equipements eq;
equipements eq2;
FILE* f;
FILE* g;
FILE* j;
FILE* k;
int min,a;
int l;
	f=fopen("equipements.bin","rb");
	g=fopen("tri.bin","ab");
	while(fread(&eq,sizeof(equipements),1,f)!=0)
		fwrite(&eq,sizeof(equipements),1,g);
	fclose(f);
	fclose(g);
	j=fopen("tri.bin","rb");
	k=fopen("temp.bin","ab");
	
	do
	{
	l=longueur_file();
	min=get_min_prix_eq();
	while(fread(&eq2,sizeof(equipements),1,j)!=0 )
				{a=atoi(eq2.prix);
				if (a==min)
				{
					fwrite (&eq2,sizeof(equipements),1,k);
					supprimer_tri(eq2.id);
				}}
		rewind(j);
	}
	while(longueur_file()!=0);
		fclose(k);
		fclose(j);
		
		remove("tri.bin");
		rename("temp.bin","tri.bin");
}

void tri_file_max_prix_eq()
{
equipements eq;
equipements eq2;
FILE* f;
FILE* g;
FILE* j;
FILE* k;
int max,a;
int l;
	f=fopen("equipements.bin","rb");
	g=fopen("tri.bin","ab");
	while(fread(&eq,sizeof(equipements),1,f)!=0)
		fwrite(&eq,sizeof(equipements),1,g);
	fclose(f);
	fclose(g);
	j=fopen("tri.bin","rb");
	k=fopen("temp.bin","ab");
	
	do
	{
	l=longueur_file();
	max=get_max_prix_eq();
	while(fread(&eq2,sizeof(equipements),1,j)!=0 )
				{a=atoi(eq2.prix);
				if (a==max)
				{
					fwrite (&eq2,sizeof(equipements),1,k);
					supprimer_tri(eq2.id);
				}}
		rewind(j);
	}
	while(longueur_file()!=0);
		fclose(k);
		fclose(j);
		remove("tri.bin");
		rename("temp.bin","tri.bin");
}
///////////////////////////////////////////////////
void get_min_association_eq(char *min)
{
	equipements eq;
	int l,i=0;
	FILE* f;
	f=fopen("tri.bin","rb");
	l = longueur_file();
	fread(&eq,sizeof(equipements),1,f);
		strcpy(min,eq.association);

	for	(i=0;i<l;i++)
		{
			fread(&eq,sizeof(equipements),1,f);
			if (strcmp(eq.association,min)<0)
				strcpy(min,eq.association);
		}
	fclose(f);	
}

void get_max_association_eq(char *max)
{
	equipements eq;
	int l,i=0;
	FILE* f;
	f=fopen("tri.bin","rb");
	l = longueur_file();
	fread(&eq,sizeof(equipements),1,f);
		strcpy(max,eq.association);
	
	for	(i=0;i<l;i++)
		{
			fread(&eq,sizeof(equipements),1,f);
			if (strcmp(eq.association,max)>0)
				strcpy(max,eq.association);
		}
	fclose(f);	
}

void tri_file_min_association_eq()
{
equipements eq;
equipements eq2;
FILE* f;
FILE* g;
FILE* j;
FILE* k;
char min[20];
int l;
	f=fopen("equipements.bin","rb");
	g=fopen("tri.bin","ab");
	while(fread(&eq,sizeof(equipements),1,f)!=0)
		fwrite(&eq,sizeof(equipements),1,g);
	fclose(f);
	fclose(g);
	j=fopen("tri.bin","rb");
	k=fopen("temp.bin","ab");
	
	do
	{
	l=longueur_file();
	get_min_association_eq(min);
	while(fread(&eq2,sizeof(equipements),1,j)!=0 )
				if (strcmp(min,eq2.association)==0)
				{
					fwrite (&eq2,sizeof(equipements),1,k);
					supprimer_tri(eq2.id);
				}
		rewind(j);
	}
	while(longueur_file()!=0);
		fclose(k);
		fclose(j);
		
		remove("tri.bin");
		rename("temp.bin","tri.bin");
}

void tri_file_max_association_eq()
{
equipements eq;
equipements eq2;
FILE* f;
FILE* g;
FILE* j;
FILE* k;
char max[20];
int l;
	f=fopen("equipements.bin","rb");
	g=fopen("tri.bin","ab");
	while(fread(&eq,sizeof(equipements),1,f)!=0)
		fwrite(&eq,sizeof(equipements),1,g);
	fclose(f);
	fclose(g);
	j=fopen("tri.bin","rb");
	k=fopen("temp.bin","ab");
	
	do
	{
	l=longueur_file();
	get_max_association_eq(max);
	while(fread(&eq2,sizeof(equipements),1,j)!=0 )
				if (strcmp(max,eq2.association)==0)
				{
					fwrite (&eq2,sizeof(equipements),1,k);
					supprimer_tri(eq2.id);
				}
		rewind(j);
	}
	while(longueur_file()!=0);
		fclose(k);
		fclose(j);
		
		remove("tri.bin");
		rename("temp.bin","tri.bin");
}
///////////////////////////////////////////////////
void afficher_tri_eq(GtkWidget *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	
	FILE* f;
	equipements eq;
	
	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Identifiant", renderer, "text",EID,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text",ETYPE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Marque", renderer, "text",EMARQUE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Date d'ajout", renderer, "text",EDATE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Prix d'achat", renderer, "text",EPRIX,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Associé à l'ouvrier", renderer, "text",EASSOCIATION,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	f=fopen("tri.bin","rb");
	if(f==NULL)
	{
		return;
	}
	else
	{
		while(fread(&eq,sizeof(equipements),1,f)!=0)
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set (store, &iter, EID, eq.id, ETYPE, eq.type, EMARQUE, eq.marque, EDATE,eq.date, EPRIX, eq.prix, EASSOCIATION, eq.association, -1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
		g_object_unref (store);
	}
	remove("tri.bin");
}

