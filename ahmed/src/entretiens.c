#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
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

void ajouter_entretien( entretiens entr)
{
	FILE* f;
	/*f = fopen("equipements.bin","ab+");
	if (f!=NULL)
		{
			fwrite(&eq,sizeof(equipements),1,f);
			fclose(f);
		}*/
	f = fopen("entretiens.txt","a+");
	if (f!=NULL)
		{
		fprintf(f,"%s %s %s %s %s %s %s %s \n",entr.id_eq,entr.id_entr,entr.date,entr.entreteneur,entr.montant,entr.payement,entr.type_payement,entr.reference);
			fclose(f);
		}
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
	
	char id_eq[20];
	char id_entr[20];
	char date[20];
	char entreteneur[20] ;
	char montant[20];
	char payement[20];
	char type_payement[20];
	char reference[20];
	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("id_eq", renderer, "text",EID1,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("id_entr", renderer, "text",EID2,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("date", renderer, "text",EDATE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("entreteneur", renderer, "text",EENTRETENEUR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("montant", renderer, "text",EMONTANT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("payement", renderer, "text",EPAYEMENT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("type_payement", renderer, "text",ETYPE_PAYEMENT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("reference", renderer, "text",EREFERENCE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	//f=fopen("equipements.bin","rb");
	f=fopen("entretiens.txt","r");
	if(f==NULL)
	{
		return;
	}
	else
	{
		/*f=fopen("equipements.bin","a+b");
		while(fread(&eq,sizeof(equipements),1,f)!=0)*/
		f=fopen("entretiens.txt","a+");
		while(fscanf(f,"%s %s %s %s %s %s %s %s \n",id_eq,id_entr,date,entreteneur,montant,payement,type_payement,reference)!=EOF)
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set (store, &iter, EID1, id_eq,EID2, id_entr, EDATE, date, EENTRETENEUR, entreteneur, EMONTANT, montant, EPAYEMENT, payement, ETYPE_PAYEMENT, type_payement, EREFERENCE, reference, -1);
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
		/*f=fopen("equipements.bin","rb");
		g=fopen("equipements2.bin","wb");*/
		f=fopen("entretiens.txt","r");
		g=fopen("entretiens2.txt","w");
	if (f==NULL || g==NULL)
		return;
	else
	{
		//while(fread(&eq2,sizeof(equipements),1,f)!=0)
		while(fscanf(f,"%s %s %s %s %s %s %s %s \n",entr.id_eq,entr.id_entr,entr.date,entr.entreteneur,entr.montant,entr.payement,entr.type_payement,entr.reference)!=EOF)
			{
				if (strcmp(id,entr.id_entr)!=0)
					//fwrite (&eq2,sizeof(equipements),1,g);
					fprintf(g,"%s %s %s %s %s %s %s %s \n",entr.id_eq,entr.id_entr,entr.date,entr.entreteneur,entr.montant,entr.payement,entr.type_payement,entr.reference);
			}
		fclose(f);
		fclose(g);
		/*remove("equipements.bin");
		rename("equipements2.bin","equipements.bin");*/
		remove("entretiens.txt");
		rename("entretiens2.txt","entretiens.txt");
			
}
}	
/////////////////////////////////////////////////////////
