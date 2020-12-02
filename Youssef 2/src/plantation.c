#include <string.h>
#include "support.h"
#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include "plantation.h"
#include <gtk/gtk.h>

enum
{REFERENCE,
 QUANTITE,
 DATE,
 QUANTITER,
 ENGRAIS,
 COMMENTAIRE,
 COLUMNS
};

//Ajouter une plante

void Ajouter_plante(plante p)
{FILE *f;
 f=fopen("Plantes.bin","a+b");
 if(f!=NULL)
 	fwrite(&p,sizeof(plante),1,f);
fclose(f);
}


//Afficher une plante
void Afficher_plante(GtkWidget *liste)
{
 	GtkCellRenderer *renderer;
 	GtkTreeViewColumn *column;
 	GtkTreeIter iter;
 	GtkTreeIter *store;

	FILE *f;
	
	plante p;
	char date1[20];
	store=NULL;



store=gtk_tree_view_get_model(liste);
if (store==NULL)
{
renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("reference",renderer,"text",REFERENCE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("quantite",renderer,"text",QUANTITE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Date de plantation", renderer, "text",DATE,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("quantite recoltee",renderer,"text",QUANTITER,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("engrais utilisé",renderer,"text",ENGRAIS,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("commentaire",renderer,"text",COMMENTAIRE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
}
store=gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_INT,G_TYPE_STRING,G_TYPE_INT,G_TYPE_STRING,G_TYPE_STRING);
f=fopen("Plantes.bin","rb");


if(f==NULL){
return;}
else{

while(fread(&p,sizeof(plante),1,f)!=0)

	{
	gtk_list_store_append(store,&iter);
sprintf (date1,"%2d/%2d/%4d",p.date.jour,p.date.mois,p.date.annee);
	gtk_list_store_set(store,&iter,REFERENCE,p.reference,QUANTITE,p.quant.quantite,DATE,date1,QUANTITER,p.quant.quantite_recolte,ENGRAIS,p.engrais,COMMENTAIRE,p.commentaire,-1);
	}
	fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
g_object_unref(store);
    }
//}


}
//Supprimer une plante
void Supprimer_plante (char reference[]){
plante p;
	FILE *f, *g;
		f=fopen("Plantes.bin","rb");
		g=fopen("Plantes1.bin","wb");
	if (f==NULL || g==NULL)
		return;
	else
	{
		while(fread(&p,sizeof(plante),1,f)!=0)
		
		
			{
				if (strcmp(reference,p.reference)!=0)
					fwrite (&p,sizeof(plante),1,g);
					
			}
		fclose(f);
		fclose(g);
		remove("Plantes.bin");
		rename("Plantes1.bin","Plantes.bin");
		
}}
//Modifier
void Modifier_plante (char ref[],plante p){
Supprimer_plante(ref);
Ajouter_plante(p);
}
//Rechercher
void Recherche_plante(char *ref_rech,GtkWidget *liste){
FILE* f = fopen ("Plantes.bin","r+b");
	plante p;int test = 0;int comp = 0;

	while (fread (&p,sizeof (plante),1,f) != 0 && test == 0){
		if (strcmp (ref_rech,p.reference) == 0)
			test = 1;
		else 
			comp++;
	}

	if (test){
		GtkCellRenderer *renderer;
		GtkTreeViewColumn *column;
		GtkTreeIter iter;
		GtkListStore *store;
		char date_plantation[15];

		store = NULL;
		store = gtk_tree_view_get_model(liste);
if (store==NULL)
{
			renderer = gtk_cell_renderer_text_new();
			column = gtk_tree_view_column_new_with_attributes("reference",renderer,"text",REFERENCE,NULL);
			gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

			renderer = gtk_cell_renderer_text_new();
			column = gtk_tree_view_column_new_with_attributes("quantite",renderer,"text",QUANTITE,NULL);
			gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

			renderer = gtk_cell_renderer_text_new();
			column = gtk_tree_view_column_new_with_attributes("Date de plantation", renderer, "text",DATE,NULL);
			gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

			renderer = gtk_cell_renderer_text_new();
			column = gtk_tree_view_column_new_with_attributes("quantite recoltee",renderer,"text",QUANTITER,NULL);
			gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

			renderer = gtk_cell_renderer_text_new();
			column = gtk_tree_view_column_new_with_attributes("engrais utilisé",renderer,"text",ENGRAIS,NULL);
			gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

			renderer = gtk_cell_renderer_text_new();
			column = gtk_tree_view_column_new_with_attributes("commentaire",renderer,"text",COMMENTAIRE,NULL);
			gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
}
			store=gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_INT,G_TYPE_STRING,G_TYPE_INT,G_TYPE_STRING,G_TYPE_STRING);
			

			gtk_list_store_append (store, &iter);

			fseek (f,comp*sizeof (plante),SEEK_SET);
			fread (&p,sizeof (plante),1,f);
			sprintf (date_plantation,"%d/%d/%d",p.date.jour,p.date.mois,p.date.annee);
gtk_list_store_set(store,&iter,REFERENCE,p.reference,QUANTITE,p.quant.quantite,DATE,date_plantation,QUANTITER,p.quant.quantite_recolte,ENGRAIS,p.engrais,COMMENTAIRE,p.commentaire,-1);
			//gtk_list_store_set(store,&iter,REFERENCE,p.reference,STOCK,p.stock,DATE,date_plantation,COMMENTAIRE,p.commentaire,-1);
			fclose (f);
			gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
			g_object_unref (store);
			
	}
}

