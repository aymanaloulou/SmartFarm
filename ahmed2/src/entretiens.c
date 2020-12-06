#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "support.h"
#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entretiens.h"
#include <gtk/gtk.h>
enum
{
	EID1,
	EID2,
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

void ajouter_entretien( entretiens entr)
{
	FILE* f;
	f = fopen("entretiens.bin","ab+");
	if (f!=NULL)
		{
			fwrite(&entr,sizeof(entretiens),1,f);
			fclose(f);
		}
	/*f = fopen("entretiens.txt","a+");
	if (f!=NULL)
		{
		fprintf(f,"%s %s %s %s %s %s %s %s \n",entr.id_eq,entr.id_entr,entr.date,entr.entreteneur,entr.montant,entr.payement,entr.type_payement,entr.reference);
			fclose(f);
		}*/
}
//////////////////////////////////////////////////////
void afficher_entretien(GtkWidget *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	
	FILE* f;
	entretiens entr;
	
	char date1[20];
	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Identifiant de l'équipement", renderer, "text",EID1,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Identifiant d'entretien", renderer, "text",EID2,NULL);
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
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	f=fopen("entretiens.bin","rb");
	//f=fopen("entretiens.txt","r");
	if(f==NULL)
	{
		return;
	}
	else
	{
		//f=fopen("equipements.bin","a+b");
		while(fread(&entr,sizeof(entretiens),1,f)!=0)
		//f=fopen("entretiens.txt","a+");
		//while(fscanf(f,"%s %s %s %s %s %s %s %s \n",id_eq,id_entr,date,entreteneur,montant,payement,type_payement,reference)!=EOF)
		{
			gtk_list_store_append(store, &iter);
sprintf (date1,"%2d/%2d/%4d",entr.date.jour,entr.date.mois,entr.date.annee);
			gtk_list_store_set (store, &iter, EID1, entr.id_eq,EID2, entr.id_entr, EDATE, date1, EENTRETENEUR, entr.entreteneur, EMONTANT, entr.montant, EPAYEMENT, entr.payement, ETYPE_PAYEMENT, entr.type_payement, EREFERENCE, entr.reference, -1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
		g_object_unref (store);
	}
}
/////////////////////////////////////////////////////
void supprimer_entretien( char id[])
{
	entretiens entr;
	FILE *f, *g;
		f=fopen("entretiens.bin","rb");
		g=fopen("entretiens2.bin","wb");
		/*f=fopen("entretiens.txt","r");
		g=fopen("entretiens2.txt","w");*/
	if (f==NULL || g==NULL)
		return;
	else
	{
		while(fread(&entr,sizeof(entretiens),1,f)!=0)
		//while(fscanf(f,"%s %s %s %s %s %s %s %s \n",entr.id_eq,entr.id_entr,entr.date,entr.entreteneur,entr.montant,entr.payement,entr.type_payement,entr.reference)!=EOF)
			{
				if (strcmp(id,entr.id_entr)!=0)
					fwrite (&entr,sizeof(entretiens),1,g);
					//fprintf(g,"%s %s %s %s %s %s %s %s \n",entr.id_eq,entr.id_entr,entr.date,entr.entreteneur,entr.montant,entr.payement,entr.type_payement,entr.reference);
			}
		fclose(f);
		fclose(g);
		remove("entretiens.bin");
		rename("entretiens2.bin","entretiens.bin");
		/*remove("entretiens.txt");
		rename("entretiens2.txt","entretiens.txt");*/
			
}
}	
/////////////////////////////////////////////////////////
