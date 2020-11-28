#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include "equipements.h"
#include <gtk/gtk.h>
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

void ajouter_equipement( equipements eq)
{
	FILE* f;
	/*f = fopen("equipements.bin","ab+");
	if (f!=NULL)
		{
			fwrite(&eq,sizeof(equipements),1,f);
			fclose(f);
		}*/
	f = fopen("equipements.txt","a+");
	if (f!=NULL)
		{
		fprintf(f,"%s %s %s %s %s %s \n",eq.id,eq.type,eq.marque,eq.date,eq.prix,eq.association);
			fclose(f);
		}
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
	
	char id[20];
	char type[20];
	char marque[20];
	char date[20] ;
	char prix[20];
	char association[20];
	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("id", renderer, "text",EID,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("type", renderer, "text",ETYPE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("marque", renderer, "text",EMARQUE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("date", renderer, "text",EDATE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("prix", renderer, "text",EPRIX,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("association", renderer, "text",EASSOCIATION,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	//f=fopen("equipements.bin","rb");
	f=fopen("equipements.txt","r");
	if(f==NULL)
	{
		return;
	}
	else
	{
		/*f=fopen("equipements.bin","a+b");
		while(fread(&eq,sizeof(equipements),1,f)!=0)*/
		f=fopen("equipements.txt","a+");
		while(fscanf(f,"%s %s %s %s %s %s \n",id,type,marque,date,prix,association)!=EOF)
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set (store, &iter, EID, id, ETYPE, type, EMARQUE, marque, EDATE, date, EPRIX, prix, EASSOCIATION, association, -1);
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
	FILE *f, *g;
		/*f=fopen("equipements.bin","rb");
		g=fopen("equipements2.bin","wb");*/
		f=fopen("equipements.txt","r");
		g=fopen("equipements2.txt","w");
	if (f==NULL || g==NULL)
		return;
	else
	{
		//while(fread(&eq2,sizeof(equipements),1,f)!=0)
		while(fscanf(f,"%s %s %s %s %s %s \n",eq2.id,eq2.type,eq2.marque,eq2.date,eq2.prix,eq2.association)!=EOF)
			{
				if (strcmp(id,eq2.id)!=0)
					//fwrite (&eq2,sizeof(equipements),1,g);
					fprintf(g,"%s %s %s %s %s %s \n",eq2.id,eq2.type,eq2.marque,eq2.date,eq2.prix,eq2.association);
			}
		fclose(f);
		fclose(g);
		/*remove("equipements.bin");
		rename("equipements2.bin","equipements.bin");*/
		remove("equipements.txt");
		rename("equipements2.txt","equipements.txt");
			
}
}	
/////////////////////////////////////////////////////////

