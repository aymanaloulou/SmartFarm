#include "support.h"
#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entretiens.h"
#include "equipements.h"
#include <gtk/gtk.h>
enum
{
	EID,
	EDATE,
	EENTRETENEUR,
	EMONTANT,
	EPAYEMENT,
	ETYPE_PAYEMENT,
	EREFERENCE,
	COLUMNS,
};



void payement(int paye[], char text1[], char text2[])
{
if (paye[0] == 1)
	strcpy(text1,"Payé");
else
	strcpy(text1,"Non Payé");
if (paye[1] == 1)
	strcpy(text2,"Espèce");
if (paye[2] == 1)
	strcpy (text2,"NON Espèce");
}
/////////////////////////////////////////////////////////

int verifID_entr (char ch[]){
	equipements eq;
	int k=0;
	FILE* f1;
	
	f1=fopen("equipements.bin","rb");
	while (fread (&eq,sizeof (equipements),1,f1) != 0 && k == 0) {
		
		if (strcmp (eq.id,ch) == 0) 
			 k=1;
	}
	fclose(f1);
	return k;
	
}

int ajouter_entretien( entretiens entr, GtkWidget *objet)
{
	int ok = 1;
	GtkWidget *e_id = lookup_widget(objet,"e_id");
	GtkWidget *e_entreteneur =lookup_widget(objet,"e_entreteneur");
	GtkWidget *e_montant =lookup_widget(objet,"e_montant");
	GtkWidget *e_reference =lookup_widget(objet,"e_reference");
	
	if (verifID_entr (entr.id_eq) == 0 || strcmp(entr.id_eq,"") == 0){
		ok = 0;
		gtk_label_set_text(GTK_LABEL(e_id),"invalide");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(e_id),"");
	}
	
	
	if (strcmp(entr.entreteneur,"") == 0){
		ok = 0;
		gtk_label_set_text(GTK_LABEL(e_entreteneur),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(e_entreteneur),"");
	}
	if (strcmp(entr.montant,"") == 0 || !numValide_eq(entr.montant)){
		ok = 0;
		gtk_label_set_text(GTK_LABEL(e_montant),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(e_montant),"");
	}
	if (strcmp(entr.reference,"") == 0){
		ok = 0;
		gtk_label_set_text(GTK_LABEL(e_reference),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(e_reference),"");
	}
	
	if (ok){
	FILE* f;
	f = fopen("entretiens.bin","ab+");
	if (f!=NULL)
		{
			fwrite(&entr,sizeof(entretiens),1,f);
			fclose(f);
}
}
	return ok;
}
//////////////////////////////////////////////////////
void afficher_entretien(GtkTreeView *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	
	FILE* f;
	entretiens entr;
	
	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Identifiant de l'équipement", renderer, "text",EID,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Date", renderer, "text",EDATE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Entreteneur", renderer, "text",EENTRETENEUR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Montant", renderer, "text",EMONTANT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Payement", renderer, "text",EPAYEMENT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Type de payement", renderer, "text",ETYPE_PAYEMENT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Reference de payement/facture", renderer, "text",EREFERENCE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	f=fopen("entretiens.bin","rb");

	if(f==NULL)
	{
		return;
	}
	else
	{
		while(fread(&entr,sizeof(entretiens),1,f)!=0)
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set (store, &iter, EID, entr.id_eq, EDATE, entr.date, EENTRETENEUR, entr.entreteneur, EMONTANT, entr.montant, EPAYEMENT, entr.payement, ETYPE_PAYEMENT, entr.type_payement, EREFERENCE, entr.reference, -1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
		g_object_unref (store);
	}
}

void rech_entr(char *id, GtkWidget *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	
	FILE* f;
	entretiens entr;
	
	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Identifiant de l'équipement", renderer, "text",EID,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Date", renderer, "text",EDATE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Entreteneur", renderer, "text",EENTRETENEUR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Montant", renderer, "text",EMONTANT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Payement", renderer, "text",EPAYEMENT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Type de payement", renderer, "text",ETYPE_PAYEMENT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Reference de payement/facture", renderer, "text",EREFERENCE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	f=fopen("entretiens.bin","rb");

	if(f==NULL)
	{
		return;
	}
	else
	{
		while(fread(&entr,sizeof(entretiens),1,f)!=0)
			if ((strstr(entr.id_eq,id) != NULL) || (strstr(entr.date,id) != NULL) || (strstr(entr.entreteneur,id) != NULL) || (strstr(entr.montant,id) != NULL) || (strstr(entr.payement,id) != NULL)|| (strstr(entr.type_payement,id) != NULL) || (strstr(entr.reference,id) != NULL))
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set (store, &iter, EID, entr.id_eq, EDATE, entr.date, EENTRETENEUR, entr.entreteneur, EMONTANT, entr.montant, EPAYEMENT, entr.payement, ETYPE_PAYEMENT, entr.type_payement, EREFERENCE, entr.reference, -1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
		g_object_unref (store);
	}
}


/////////////////////////////////////////////////////
void supprimer_entretien( entretiens e)
{
	
	FILE *f;
	FILE *g;
	entretiens entr;
FILE* h;
	h = fopen("histo_entr.bin","ab");

		f=fopen("entretiens.bin","rb");
		g=fopen("temp.bin","ab");
		
	if (f==NULL || g==NULL)
		return;
	else
	{
		while (fread(&entr,sizeof(entretiens),1,f)!=0)

			{
				
				if (strcmp(e.id_entr,entr.id_entr) !=0 )  
					fwrite (&entr,sizeof(entretiens),1,g);
				else{
					fwrite(&entr,sizeof(entretiens),1,h);
				}
			}
		


		remove("entretiens.bin");
		rename("temp.bin","entretiens.bin");
		fclose(f);
		fclose(g);
		fclose(h);
		
}
}	


/////////////////////////////////////////////////////////
void afficher_histo_entr(GtkTreeView *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	
	FILE* f;
	entretiens entr;
	
	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Identifiant de l'équipement", renderer, "text",EID,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Date", renderer, "text",EDATE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Entreteneur", renderer, "text",EENTRETENEUR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Montant", renderer, "text",EMONTANT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Payement", renderer, "text",EPAYEMENT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Type de payement", renderer, "text",ETYPE_PAYEMENT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Reference de payement/facture", renderer, "text",EREFERENCE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	f=fopen("histo_entr.bin","rb");
	if(f==NULL)
	{
		return;
	}
	else
	{
		while(fread(&entr,sizeof(entretiens),1,f)!=0)
		{
			gtk_list_store_append(store, &iter);
//sprintf (date1,"%2d/%2d/%4d",entr.date.jour,entr.date.mois,entr.date.annee);
			gtk_list_store_set (store, &iter, EID, entr.id_eq, EDATE, entr.date, EENTRETENEUR, entr.entreteneur, EMONTANT, entr.montant, EPAYEMENT, entr.payement, ETYPE_PAYEMENT, entr.type_payement, EREFERENCE, entr.reference, -1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
		g_object_unref (store);
	}
}

void rest_entr( entretiens entr)
{
	FILE* f;
	f = fopen("entretiens.bin","a+b");
	if (f!=NULL)
		{
			fwrite(&entr,sizeof(entretiens),1,f);
			fclose(f);
		}
}

void supp_histo_entr( char id[])
{
	entretiens entr2;
	FILE *f,*g;
		f=fopen("histo_entr.bin","rb");
		g=fopen("histo_entr2.bin","wb");
		
	if (f==NULL || g==NULL)
		return;
	else
	{
		while(fread(&entr2,sizeof(entretiens),1,f)!=0)
			{
				if (strcmp(id,entr2.id_entr)!=0)
					fwrite (&entr2,sizeof(entretiens),1,g);
			}
		fclose(f);
		fclose(g);
		
		remove("histo_entr.bin");
		rename("histo_entr2.bin","histo_entr.bin");

}
}	
/*////////////////////////////////////////
 * ////////statistique///////////////////
 * ///////////////////////////////////////*/
 void afficher_entr_payement(GtkTreeView *liste, char *ch)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	
	FILE* f;
	entretiens entr;
	
	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Identifiant de l'équipement", renderer, "text",EID,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Date", renderer, "text",EDATE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Entreteneur", renderer, "text",EENTRETENEUR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Montant", renderer, "text",EMONTANT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Payement", renderer, "text",EPAYEMENT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Type de payement", renderer, "text",ETYPE_PAYEMENT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Reference de payement/facture", renderer, "text",EREFERENCE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	f=fopen("entretiens.bin","rb");

	if(f==NULL)
	{
		return;
	}
	else
	{
		while(fread(&entr,sizeof(entretiens),1,f)!=0)
			if (strcmp(entr.payement,ch) ==0)
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set (store, &iter, EID, entr.id_eq, EDATE, entr.date, EENTRETENEUR, entr.entreteneur, EMONTANT, entr.montant, EPAYEMENT, entr.payement, ETYPE_PAYEMENT, entr.type_payement, EREFERENCE, entr.reference, -1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
		g_object_unref (store);
	}
}

int prix_entr_paye()
 {
	int c=0;
	entretiens entr;
	FILE *f;
	f=fopen("entretiens.bin","rb");
	while(fread(&entr,sizeof(entretiens),1,f)!=0 )
		{
			if (strcmp(entr.payement,"Payé")==0)
				c+=atoi(entr.montant);
		}
	fclose(f);
	return c;
 }
 
 int prix_entr_non_paye()
 {
	int c=0;
	entretiens entr;
	FILE *f;
	f=fopen("entretiens.bin","rb");
	while(fread(&entr,sizeof(entretiens),1,f)!=0 )
		{
			if (strcmp(entr.payement,"Non Payé")==0)
				c+=atoi(entr.montant);
		}
	fclose(f);
	return c;
 }
 
 /////////////////////////////////////////
 void pdf_entr (entretiens entr)
{

FILE *f;
f=fopen("opn.txt","w");
if (f!=NULL)
{
fprintf (f,"---------- Entretien de l'équipement d'identifiant : %2s ---------- \n",entr.id_eq);
fprintf (f,"\n\n     Entretenu par : %2s  \n \n     Montant d'entretien : %2s  \n \n     Payement : %2s  \n \n     Type de règlement : %2s  \n \n     Référence de payement : %2s  \n \n           Date : %d  / %d / %d       ",entr.entreteneur,entr.montant,entr.payement,entr.type_payement,entr.reference,entr.jour,entr.mois,entr.annee);}
fprintf (f,"------------------------------------------------------- \n");
fclose(f);
}
 /////////////////////////////////////

 
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

int longueur_file_entr()
{
	FILE* a;
	a=fopen("tri1.bin","rb");
	entretiens entr;
	int c=0;
	while(fread(&entr,sizeof(entretiens),1,a)!=0)
		{c++;}
	fclose(a);
	return c;
}

void supprimer_tri_entr( char id[])
{
	entretiens entr2;
	FILE *f, *g;
		f=fopen("tri1.bin","rb");
		g=fopen("tri2.bin","ab");
	if (f==NULL || g==NULL)
		return;
	else
	{
		while(fread(&entr2,sizeof(entretiens),1,f)!=0)
			{
				if (strcmp(id,entr2.id_entr)!=0)
					fwrite (&entr2,sizeof(entretiens),1,g);
			}
		fclose(f);
		fclose(g);
		remove("tri1.bin");
		rename("tri2.bin","tri1.bin");
}
}	
/////////////////////////////////////////////////////////////
void get_min_id_entr(char *min)
{
	entretiens entr;
	int l,i=0;
	l = longueur_file_entr();
	FILE* f;
	f=fopen("tri1.bin","rb");
	fread(&entr,sizeof(entretiens),1,f);
		strcpy(min,entr.id_eq);
	
	for	(i=0;i<l;i++)
		{
			fread(&entr,sizeof(entretiens),1,f);
			if (strcmp(entr.id_eq,min)<0)
				strcpy(min,entr.id_eq);
		}
	fclose(f);	
}

void get_max_id_entr(char *max)
{
	entretiens entr;
	int l,i=0;
	l = longueur_file_entr();
	FILE* f;
	f=fopen("tri1.bin","rb");
	fread(&entr,sizeof(entretiens),1,f);
		strcpy(max,entr.id_eq);
	
	for	(i=0;i<l;i++)
		{
			fread(&entr,sizeof(entretiens),1,f);
			if (strcmp(entr.id_eq,max)>0)
				strcpy(max,entr.id_eq);
		}
	fclose(f);	
}

void tri_file_min_id_entr()
{
entretiens entr;
entretiens entr2;
FILE* f;
FILE* g;
FILE* j;
FILE* k;
char min[20];
int l;
	f=fopen("entretiens.bin","rb");
	g=fopen("tri1.bin","ab");
	while(fread(&entr,sizeof(entretiens),1,f)!=0)
		fwrite(&entr,sizeof(entretiens),1,g);
	fclose(f);
	fclose(g);
	j=fopen("tri1.bin","rb");
	k=fopen("temp.bin","ab");
	
	do
	{
	l=longueur_file_entr();
	get_min_id_entr(min);
	while(fread(&entr2,sizeof(entretiens),1,j)!=0 )
				if (strcmp(min,entr2.id_eq)==0)
				{
					fwrite (&entr2,sizeof(entretiens),1,k);
					supprimer_tri_entr(entr2.id_entr);
				}
		rewind(j);
	}
	while(longueur_file_entr()!=0);
		fclose(k);
		fclose(j);
		
		remove("tri1.bin");
		rename("temp.bin","tri1.bin");
}

void tri_file_max_id_entr()
{
entretiens entr;
entretiens entr2;
FILE* f;
FILE* g;
FILE* j;
FILE* k;
char max[20];
int l;
	f=fopen("entretiens.bin","rb");
	g=fopen("tri1.bin","ab");
	while(fread(&entr,sizeof(entretiens),1,f)!=0)
		fwrite(&entr,sizeof(entretiens),1,g);
	fclose(f);
	fclose(g);
	j=fopen("tri1.bin","rb");
	k=fopen("temp.bin","ab");
	
	do
	{
	l=longueur_file_entr();
	get_max_id_entr(max);
	while(fread(&entr2,sizeof(entretiens),1,j)!=0 )
				if (strcmp(max,entr2.id_eq)==0)
				{
					fwrite (&entr2,sizeof(entretiens),1,k);
					supprimer_tri_entr(entr2.id_entr);
				}
		rewind(j);
	}
	while(longueur_file_entr()!=0);
		fclose(k);
		fclose(j);
		
		remove("tri1.bin");
		rename("temp.bin","tri1.bin");
}
//////////////////////////////////////////////////////////
void get_min_entreteneur_entr(char *min)
{
	entretiens entr;
	int l,i=0;
	FILE* f;
	f=fopen("tri1.bin","rb");
	l = longueur_file_entr();
	fread(&entr,sizeof(entretiens),1,f);
		strcpy(min,entr.entreteneur);
	
	for	(i=0;i<l;i++)
		{
			fread(&entr,sizeof(entretiens),1,f);
			if (strcmp(entr.entreteneur,min)<0)
				strcpy(min,entr.entreteneur);
		}
	fclose(f);	
}

void get_max_entreteneur_entr(char *max)
{
	entretiens entr;
	int l,i=0;
	FILE* f;
	f=fopen("tri1.bin","rb");
	l = longueur_file_entr();
	fread(&entr,sizeof(entretiens),1,f);
		strcpy(max,entr.entreteneur);
	
	for	(i=0;i<l;i++)
		{
			fread(&entr,sizeof(entretiens),1,f);
			if (strcmp(entr.entreteneur,max)>0)
				strcpy(max,entr.entreteneur);
		}
	fclose(f);	
}

void tri_file_min_entreteneur_entr()
{
entretiens entr;
entretiens entr2;
FILE* f;
FILE* g;
FILE* j;
FILE* k;
char min[20];
int l;
	f=fopen("entretiens.bin","rb");
	g=fopen("tri1.bin","ab");
	while(fread(&entr,sizeof(entretiens),1,f)!=0)
		fwrite(&entr,sizeof(entretiens),1,g);
	fclose(f);
	fclose(g);
	j=fopen("tri1.bin","rb");
	k=fopen("temp.bin","ab");
	
	do
	{
	l=longueur_file_entr();
	get_min_entreteneur_entr(min);
	while(fread(&entr2,sizeof(entretiens),1,j)!=0 )
				if (strcmp(min,entr2.entreteneur)==0)
				{
					fwrite (&entr2,sizeof(entretiens),1,k);
					supprimer_tri_entr(entr2.id_entr);
				}
		rewind(j);
	}
	while(longueur_file_entr()!=0);
		fclose(k);
		fclose(j);
		
		remove("tri1.bin");
		rename("temp.bin","tri1.bin");
}

void tri_file_max_entreteneur_entr()
{
entretiens entr;
entretiens entr2;
FILE* f;
FILE* g;
FILE* j;
FILE* k;
char max[20];
int l;
	f=fopen("entretiens.bin","rb");
	g=fopen("tri1.bin","ab");
	while(fread(&entr,sizeof(entretiens),1,f)!=0)
		fwrite(&entr,sizeof(entretiens),1,g);
	fclose(f);
	fclose(g);
	j=fopen("tri1.bin","rb");
	k=fopen("temp.bin","ab");
	
	do
	{
	l=longueur_file_entr();
	get_max_entreteneur_entr(max);
	while(fread(&entr2,sizeof(entretiens),1,j)!=0 )
				if (strcmp(max,entr2.entreteneur)==0)
				{
					fwrite (&entr2,sizeof(entretiens),1,k);
					supprimer_tri_entr(entr2.id_entr);
				}
		rewind(j);
	}
	while(longueur_file_entr()!=0);
		fclose(k);
		fclose(j);
		
		remove("tri1.bin");
		rename("temp.bin","tri1.bin");
}
//////////////////////////////////////////////////////////
int get_min_montant_entr()
{
	entretiens entr;
	int l,i=0,min,a;
	FILE* f;
	f=fopen("tri1.bin","rb");
	l = longueur_file_entr();
	fread(&entr,sizeof(entretiens),1,f);
		min=atoi(entr.montant);
	
	for	(i=0;i<l;i++)
		{
			fread(&entr,sizeof(entretiens),1,f);
			a=atoi(entr.montant);
			if (a<min)
				min=a;
		}
	fclose(f);
	return min;	
}

int get_max_montant_entr()
{
	entretiens entr;
	int l,i=0,max=0,a=0;
	FILE* f;
	f=fopen("tri1.bin","rb");
	l = longueur_file_entr();
	fread(&entr,sizeof(entretiens),1,f);
		max=atoi(entr.montant);
	
	for	(i=0;i<l;i++)
		{
			fread(&entr,sizeof(entretiens),1,f);
			a=atoi(entr.montant);
			if (a>max)
				max=a;
		}
	fclose(f);	
	return max;
}

void tri_file_min_montant_entr()
{
entretiens entr;
entretiens entr2;
FILE* f;
FILE* g;
FILE* j;
FILE* k;
int l,min,a;
	f=fopen("entretiens.bin","rb");
	g=fopen("tri1.bin","ab");
	while(fread(&entr,sizeof(entretiens),1,f)!=0)
		fwrite(&entr,sizeof(entretiens),1,g);
	fclose(f);
	fclose(g);
	j=fopen("tri1.bin","rb");
	k=fopen("temp.bin","ab");
	
	do
	{
	l=longueur_file_entr();
	min=get_min_montant_entr();
	while(fread(&entr2,sizeof(entretiens),1,j)!=0 )
				{a=atoi(entr2.montant);
				if (a==min)
				{
					fwrite (&entr2,sizeof(entretiens),1,k);
					supprimer_tri_entr(entr2.id_entr);
				}
			}
		rewind(j);
	}
	while(longueur_file_entr()!=0);
		fclose(k);
		fclose(j);
		
		remove("tri1.bin");
		rename("temp.bin","tri1.bin");
}

void tri_file_max_montant_entr()
{
entretiens entr;
entretiens entr2;
FILE* f;
FILE* g;
FILE* j;
FILE* k;
int l,max,a;
	f=fopen("entretiens.bin","rb");
	g=fopen("tri1.bin","ab");
	while(fread(&entr,sizeof(entretiens),1,f)!=0)
		fwrite(&entr,sizeof(entretiens),1,g);
	fclose(f);
	fclose(g);
	j=fopen("tri1.bin","rb");
	k=fopen("temp.bin","ab");
	
	do
	{
	l=longueur_file_entr();
	max = get_max_montant_entr();
	while(fread(&entr2,sizeof(entretiens),1,j)!=0 )
				{a=atoi(entr2.montant);
				if (a==max)
				{
					fwrite (&entr2,sizeof(entretiens),1,k);
					supprimer_tri_entr(entr2.id_entr);
				}}
		rewind(j);
	}
	while(longueur_file_entr()!=0);
		fclose(k);
		fclose(j);
		
		remove("tri1.bin");
		rename("temp.bin","tri1.bin");
}
//////////////////////////////////////////////////////////
void get_min_payement_entr(char *min)
{
	entretiens entr;
	int l,i=0;
	FILE* f;
	f=fopen("tri1.bin","rb");
	l = longueur_file_entr();
	fread(&entr,sizeof(entretiens),1,f);
		strcpy(min,entr.payement);
	
	for	(i=0;i<l;i++)
		{
			fread(&entr,sizeof(entretiens),1,f);
			if (strcmp(entr.payement,min)<0)
				strcpy(min,entr.payement);
		}
	fclose(f);	
}

void tri_file_min_payement_entr()
{
entretiens entr;
entretiens entr2;
FILE* f;
FILE* g;
FILE* j;
FILE* k;
char min[20];
int l;
	f=fopen("entretiens.bin","rb");
	g=fopen("tri1.bin","ab");
	while(fread(&entr,sizeof(entretiens),1,f)!=0)
		fwrite(&entr,sizeof(entretiens),1,g);
	fclose(f);
	fclose(g);
	j=fopen("tri1.bin","rb");
	k=fopen("temp.bin","ab");
	
	do
	{
	l=longueur_file_entr();
	get_min_payement_entr(min);
	while(fread(&entr2,sizeof(entretiens),1,j)!=0 )
				if (strcmp(min,entr2.payement)==0)
				{
					fwrite (&entr2,sizeof(entretiens),1,k);
					supprimer_tri_entr(entr2.id_entr);
				}
		rewind(j);
	}
	while(longueur_file_entr()!=0);
		fclose(k);
		fclose(j);
		
		remove("tri1.bin");
		rename("temp.bin","tri1.bin");
}
//////////////////////////////////////////////////////////
void get_min_type_payement_entr(char *min)
{
	entretiens entr;
	int l,i=0;
	FILE* f;
	f=fopen("tri1.bin","rb");
	l = longueur_file_entr();
	fread(&entr,sizeof(entretiens),1,f);
		strcpy(min,entr.type_payement);
	
	for	(i=0;i<l;i++)
		{
			fread(&entr,sizeof(entretiens),1,f);
			if (strcmp(entr.type_payement,min)<0)
				strcpy(min,entr.type_payement);
		}
	fclose(f);	
}

void tri_file_min_type_payement_entr()
{
entretiens entr;
entretiens entr2;
FILE* f;
FILE* g;
FILE* j;
FILE* k;
char min[20];
int l;
	f=fopen("entretiens.bin","rb");
	g=fopen("tri1.bin","ab");
	while(fread(&entr,sizeof(entretiens),1,f)!=0)
		fwrite(&entr,sizeof(entretiens),1,g);
	fclose(f);
	fclose(g);
	j=fopen("tri1.bin","rb");
	k=fopen("temp.bin","ab");
	
	do
	{
	l=longueur_file_entr();
	get_min_type_payement_entr(min);
	while(fread(&entr2,sizeof(entretiens),1,j)!=0 )
				if (strcmp(min,entr2.type_payement)==0)
				{
					fwrite (&entr2,sizeof(entretiens),1,k);
					supprimer_tri_entr(entr2.id_entr);
				}
		rewind(j);
	}
	while(longueur_file_entr()!=0);
		fclose(k);
		fclose(j);
		
		remove("tri1.bin");
		rename("temp.bin","tri1.bin");
}
//////////////////////////////////////////////////////////
void get_min_reference_entr(char *min)
{
	entretiens entr;
	int l,i=0;
	FILE* f;
	f=fopen("tri1.bin","rb");
	l = longueur_file_entr();
	fread(&entr,sizeof(entretiens),1,f);
		strcpy(min,entr.reference);
	
	for	(i=0;i<l;i++)
		{
			fread(&entr,sizeof(entretiens),1,f);
			if (strcmp(entr.reference,min)<0)
				strcpy(min,entr.reference);
		}
	fclose(f);	
}

void get_max_reference_entr(char *max)
{
	entretiens entr;
	int l,i=0;
	FILE* f;
	f=fopen("tri1.bin","rb");
	l = longueur_file_entr();
	fread(&entr,sizeof(entretiens),1,f);
		strcpy(max,entr.reference);
	
	for	(i=0;i<l;i++)
		{
			fread(&entr,sizeof(entretiens),1,f);
			if (strcmp(entr.reference,max)>0)
				strcpy(max,entr.reference);
		}
	fclose(f);	
}

void tri_file_min_reference_entr()
{
entretiens entr;
entretiens entr2;
FILE* f;
FILE* g;
FILE* j;
FILE* k;
char min[20];
int l;
	f=fopen("entretiens.bin","rb");
	g=fopen("tri1.bin","ab");
	while(fread(&entr,sizeof(entretiens),1,f)!=0)
		fwrite(&entr,sizeof(entretiens),1,g);
	fclose(f);
	fclose(g);
	j=fopen("tri1.bin","rb");
	k=fopen("temp.bin","ab");
	
	do
	{
	l=longueur_file_entr();
	get_min_reference_entr(min);
	while(fread(&entr2,sizeof(entretiens),1,j)!=0 )
				if (strcmp(min,entr2.reference)==0)
				{
					fwrite (&entr2,sizeof(entretiens),1,k);
					supprimer_tri_entr(entr2.id_entr);
				}
		rewind(j);
	}
	while(longueur_file_entr()!=0);
		fclose(k);
		fclose(j);
		
		remove("tri1.bin");
		rename("temp.bin","tri1.bin");
}

void tri_file_max_reference_entr()
{
entretiens entr;
entretiens entr2;
FILE* f;
FILE* g;
FILE* j;
FILE* k;
char max[20];
int l;
	f=fopen("entretiens.bin","rb");
	g=fopen("tri1.bin","ab");
	while(fread(&entr,sizeof(entretiens),1,f)!=0)
		fwrite(&entr,sizeof(entretiens),1,g);
	fclose(f);
	fclose(g);
	j=fopen("tri1.bin","rb");
	k=fopen("temp.bin","ab");
	
	do
	{
	l=longueur_file_entr();
	get_max_reference_entr(max);
	while(fread(&entr2,sizeof(entretiens),1,j)!=0 )
				if (strcmp(max,entr2.reference)==0)
				{
					fwrite (&entr2,sizeof(entretiens),1,k);
					supprimer_tri_entr(entr2.id_entr);
				}
		rewind(j);
	}
	while(longueur_file_entr()!=0);
		fclose(k);
		fclose(j);
		
		remove("tri1.bin");
		rename("temp.bin","tri1.bin");
}
//////////////////////////////////////////////////////////////
int get_min_date_entr()
{
	entretiens entr;
	int l,i=0,min,d;
	l = longueur_file_entr();
	FILE* f;
	f=fopen("tri1.bin","rb");
	fread(&entr,sizeof(entretiens),1,f);
		min= entr.annee*10000+entr.mois*100+entr.jour;
	
	for	(i=0;i<l;i++)
		{
			fread(&entr,sizeof(entretiens),1,f);
			d= entr.annee*10000+entr.mois*100+entr.jour;
			if (d<min)
				min=d;
		}
	fclose(f);	
	return min;
}

int get_max_date_entr()
{
	entretiens entr;
	int l,i=0,max,d;
	l = longueur_file_entr();
	FILE* f;
	f=fopen("tri1.bin","rb");
	fread(&entr,sizeof(entretiens),1,f);
		max= entr.annee*10000+entr.mois*100+entr.jour;
		
	for	(i=0;i<l;i++)
		{
			fread(&entr,sizeof(entretiens),1,f);
			d= entr.annee*10000+entr.mois*100+entr.jour;
			if (d>max)
				max=d;
		}
	fclose(f);	
	return max;
}

void tri_file_min_date_entr()
{
entretiens entr;
entretiens entr2;
FILE* f;
FILE* g;
FILE* j;
FILE* k;
int min,d;
int l;
	f=fopen("entretiens.bin","rb");
	g=fopen("tri1.bin","ab");
	while(fread(&entr,sizeof(entretiens),1,f)!=0)
		fwrite(&entr,sizeof(entretiens),1,g);
	fclose(f);
	fclose(g);
	j=fopen("tri1.bin","rb");
	k=fopen("temp.bin","ab");
	
	do
	{
	l=longueur_file_entr();
	min=get_min_date_entr();
	while(fread(&entr2,sizeof(entretiens),1,j)!=0 )
	{
		d= entr2.annee*10000+entr2.mois*100+entr2.jour;
				if (min==d)
				{
					fwrite (&entr2,sizeof(entretiens),1,k);
					supprimer_tri_entr(entr2.id_entr);
				}
	}
		rewind(j);
	}
	while(longueur_file_entr()!=0);
		fclose(k);
		fclose(j);
		
		remove("tri1.bin");
		rename("temp.bin","tri1.bin");
}

void tri_file_max_date_entr()
{
entretiens entr;
entretiens entr2;
FILE* f;
FILE* g;
FILE* j;
FILE* k;
int max,d;
int l;
	f=fopen("entretiens.bin","rb");
	g=fopen("tri1.bin","ab");
	while(fread(&entr,sizeof(entretiens),1,f)!=0)
		fwrite(&entr,sizeof(entretiens),1,g);
	fclose(f);
	fclose(g);
	j=fopen("tri1.bin","rb");
	k=fopen("temp.bin","ab");
	
	do
	{
	l=longueur_file_entr();
	max=get_max_date_entr();
	while(fread(&entr2,sizeof(entretiens),1,j)!=0 )
	{
		d= entr2.annee*10000+entr2.mois*100+entr2.jour;
				if (d==max)
				{
					fwrite (&entr2,sizeof(entretiens),1,k);
					supprimer_tri_entr(entr2.id_entr);
				}
	}
		rewind(j);
	}
	while(longueur_file_entr()!=0);
		fclose(k);
		fclose(j);
		
		remove("tri1.bin");
		rename("temp.bin","tri1.bin");
}
//////////////////////////////////////////////////////////////
/*void inverseMot2(char *dest ,char *src)
{
    int i=strlen(src);
    for(int j=0; j<i; j++) 
    dest[i-j-1]=src[j];
}

void get_min_date_entr(char *min)
{
	entretiens entr;
	int l,i=0;
	l = longueur_file_entr();
	FILE* f;
	char aux[200];
	strcpy(aux,"");
	f=fopen("tri1.bin","rb");
	fread(&entr,sizeof(entretiens),1,f);
		inverseMot2(aux,entr.date);
		strcpy(min,aux);
		strcpy(aux,"");
	
	for	(i=0;i<l;i++)
		{
			fread(&entr,sizeof(entretiens),1,f);
			inverseMot2(aux,entr.date);
			if (strcmp(aux,min)<0)
				strcpy(min,aux);
			strcpy(aux,"");
		}
	inverseMot2(aux,min);
	strcpy(min,aux);
	strcpy(aux,"");
	fclose(f);	
}

void get_max_date_entr(char *max)
{
	entretiens entr;
	int l,i=0;
	l = longueur_file_entr();
	FILE* f;
	char aux1[200];
	strcpy(aux1,"");
	f=fopen("tri1.bin","rb");
	fread(&entr,sizeof(entretiens),1,f);
		inverseMot2(aux1,entr.date);
		strcpy(max,aux1);
		strcpy(aux1,"");
		
	for	(i=0;i<l;i++)
		{
			fread(&entr,sizeof(entretiens),1,f);
			inverseMot2(aux1,entr.date);
			if (strcmp(aux1,max)>0)
				strcpy(max,aux1);
			strcpy(aux1,"");
		}
	inverseMot2(aux1,max);
	strcpy(max,aux1);
	strcpy(aux1,"");
	fclose(f);	
}

void tri_file_min_date_entr()
{
entretiens entr;
entretiens entr2;
FILE* f;
FILE* g;
FILE* j;
FILE* k;
char min[200];
int l;
	f=fopen("entretiens.bin","rb");
	g=fopen("tri1.bin","ab");
	while(fread(&entr,sizeof(entretiens),1,f)!=0)
		fwrite(&entr,sizeof(entretiens),1,g);
	fclose(f);
	fclose(g);
	j=fopen("tri1.bin","rb");
	k=fopen("temp.bin","ab");
	
	do
	{
	l=longueur_file_entr();
	get_min_date_entr(min);
	while(fread(&entr2,sizeof(entretiens),1,j)!=0 )
				if (strcmp(min,entr2.date)==0)
				{
					fwrite (&entr2,sizeof(entretiens),1,k);
					supprimer_tri_entr(entr2.id_entr);
				}
		rewind(j);
	}
	while(longueur_file_entr()!=0);
		fclose(k);
		fclose(j);
		
		remove("tri1.bin");
		rename("temp.bin","tri1.bin");
}

void tri_file_max_date_entr()
{
entretiens entr;
entretiens entr2;
FILE* f;
FILE* g;
FILE* j;
FILE* k;
char max[200];
int l;
	f=fopen("entretiens.bin","rb");
	g=fopen("tri1.bin","ab");
	while(fread(&entr,sizeof(entretiens),1,f)!=0)
		fwrite(&entr,sizeof(entretiens),1,g);
	fclose(f);
	fclose(g);
	j=fopen("tri1.bin","rb");
	k=fopen("temp.bin","ab");
	
	do
	{
	l=longueur_file_entr();
	get_max_date_entr(max);
	while(fread(&entr2,sizeof(entretiens),1,j)!=0 )
				if (strcmp(max,entr2.date)==0)
				{
					fwrite (&entr2,sizeof(entretiens),1,k);
					supprimer_tri_entr(entr2.id_entr);
				}
		rewind(j);
	}
	while(longueur_file_entr()!=0);
		fclose(k);
		fclose(j);
		
		remove("tri1.bin");
		rename("temp.bin","tri1.bin");
}*/
//////////////////////////////////////////////////////////////
void afficher_tri_entretien(GtkTreeView *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	
	FILE* f;
	entretiens entr;
	
	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Identifiant de l'équipement", renderer, "text",EID,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Date", renderer, "text",EDATE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Entreteneur", renderer, "text",EENTRETENEUR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Montant", renderer, "text",EMONTANT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Payement", renderer, "text",EPAYEMENT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Type de payement", renderer, "text",ETYPE_PAYEMENT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Reference de payement/facture", renderer, "text",EREFERENCE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	f=fopen("tri1.bin","rb");

	if(f==NULL)
	{
		return;
	}
	else
	{
		while(fread(&entr,sizeof(entretiens),1,f)!=0)
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set (store, &iter, EID, entr.id_eq, EDATE, entr.date, EENTRETENEUR, entr.entreteneur, EMONTANT, entr.montant, EPAYEMENT, entr.payement, ETYPE_PAYEMENT, entr.type_payement, EREFERENCE, entr.reference, -1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
		g_object_unref (store);
	}
	remove("tri1.bin");
}
