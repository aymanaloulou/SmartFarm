#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "capteur.h"
#include "interface.h"
#include "support.h"
enum
{       
	EID,
        ETYPE,
	EMARQUE,
	EVALEUR,
        EDATE,
	EETAT,
	ECAUSE,
	COLUMNS
};
int identifiantExiste (char ch[])
{
    capteur c;
    int ok=1;
     
    FILE* f = fopen ("capteur.bin","rb");

    while (fread (&c,sizeof (capteur),1,f) != 0 && ok==1){
       
        if (strcmp (c.id,ch) == 0) 
             ok=0;

    }
    fclose (f);
    return ok;

}
int val_valide_cap (char ch[]){
	int i=0,ok = 1;
	while (ok == 1 && i<strlen (ch)){
		if (ch[i]<'0' || ch[i] >'9')
			ok = 0;
			else
			i++; 	
			
		
	}
	return ok;
}
int ajoutCapteur ( capteur c,GtkWidget *objet)
{ 
FILE *f;
FILE *g ;
int ok =  1 ; 
GtkWidget *c_id = lookup_widget(objet,"label_id");
	GtkWidget *c_marque =lookup_widget(objet,"label_marque");

	GtkWidget *c_valeur =lookup_widget(objet,"label_valeur");
if (identifiantExiste (c.id) == 0 || strcmp(c.id,"") == 0){
		ok = 0;
		gtk_label_set_text(GTK_LABEL(c_id),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(c_id),"");
	}
	
	
	if (strcmp(c.marque,"") == 0){
		ok = 0;
		gtk_label_set_text(GTK_LABEL(c_marque),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(c_marque),"");
	}
	
	
	if (strcmp(c.valeur,"")==0 || val_valide_cap(c.valeur) == 0){
		ok = 0;
		gtk_label_set_text(GTK_LABEL(c_valeur),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(c_valeur),"");
	}
	

	if (ok){		
		g= fopen ("defect.bin","ab");
		f = fopen ("capteur.bin","ab");
		if (f!=NULL)
{            
              fwrite (&c,sizeof(capteur),1,f);

		if (strcmp(c.type,"température")==0)
		{if (strcmp(c.valeur,"-10")<0 || strcmp(c.valeur,"55")>0)	
                      fwrite (&c,sizeof(capteur),1,g); }
if (strcmp(c.type,"humidité")==0)
		{if (strcmp(c.valeur,"30")<0 || strcmp(c.valeur,"85")>0)
                fwrite (&c,sizeof(capteur),1,g); }	
		}

fclose (f);
fclose (g) ;
	 
}
return ok;
}
////////////////////////////////////////////
void type_capteur (int choix[], char text1[] )
{
if (choix[0] == 1)
	strcpy(text1,"température");

else
	strcpy(text1,"humidité");

}
/////////////////////////////////////////
void cause (int choix[], char text1[] )
{
{
if (choix[0] == 1)
	strcpy(text1,"mauvaise lecture ");
}
{if ( choix[1] == 1)
	strcpy(text1,"détruit");
 }
{if ( choix[2] == 1)
	strcpy(text1,"autres");
}}
///////////////////////////////////////
void affiche_capteur(GtkWidget *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	
	FILE* f;
	capteur c;
	
		char date1[15];
	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("id", renderer, "text",EID,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("marque", renderer, "text",EMARQUE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("valeur", renderer, "text",EVALEUR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes ("date ajout ",renderer,"text",EDATE,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes ("type ",renderer,"text",ETYPE,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes ("Etat ",renderer,"text",EETAT,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes ("Cause ",renderer,"text",ECAUSE,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	}
	store=gtk_list_store_new (COLUMNS , G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING );
	f=fopen("capteur.bin","rb");
	
	if(f==NULL)
	{
		return;
	}
	else
	{
		//f=fopen("capteur.bin","a+b");
		while(fread(&c,sizeof(capteur),1,f)!=0)
		
		{
			gtk_list_store_append(store, &iter);
                        sprintf(date1,"%2d/%2d/%4d",c.date.jour,c.date.mois,c.date.annee);
			gtk_list_store_set (store, &iter, EID,c.id,EMARQUE,c.marque, EVALEUR, c.valeur,ETYPE, c.type, EDATE,date1,EETAT,c.etat,ECAUSE,c.cause, -1);
		}
		fclose(f);

		
		gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
		g_object_unref (store);
	}}
/////////////////////////////////////////////////////
void supp_capteur( char  id_supp[])
{
	capteur c;
	FILE *f, *g;
		f=fopen("capteur.bin","rb");
		g=fopen("capteur2.bin","ab");
		
	//if (f!=NULL )
		
	
	
		while(fread(&c,sizeof(capteur),1,f)!=0)

			{
				if (strcmp(c.id,id_supp)!=0)
					fwrite (&c,sizeof(capteur),1,g);
					
			}
		
		remove("capteur.bin");
		rename("capteur2.bin","capteur.bin");
                 fclose(f);
		fclose(g);
		
			
}

/////////////////////////////////////////////////////
void recherche_capteur (char *id_rech, GtkWidget *liste)
{
FILE* f = fopen ("capteur.bin","r+b");
char date1[30]; 
	capteur c;int test = 0;int comp = 0;

	while (fread (&c,sizeof (capteur),1,f)!=0 && test == 0)

{
sprintf (date1,"%d/%d/%d",c.date.jour,c.date.mois,c.date.annee);
		if (strstr (c.id,id_rech) !=NULL || strstr (c.marque,id_rech) !=NULL || strstr (c.valeur,id_rech) !=NULL || strstr(c.type,id_rech)!=NULL || strstr(date1,id_rech)!=NULL)
			test = 1;
		else 
			comp++;
	}

	if (test){
		GtkCellRenderer *renderer;
		GtkTreeViewColumn *column;
		GtkTreeIter iter;
		GtkListStore *store;
		char date1[15];

		store = NULL;
		store = gtk_tree_view_get_model(liste);

if (store==NULL)
{
			renderer = gtk_cell_renderer_text_new ();
			column = gtk_tree_view_column_new_with_attributes (" id",renderer,"text",EID,NULL);
			gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

			renderer = gtk_cell_renderer_text_new ();
			column = gtk_tree_view_column_new_with_attributes (" marque",renderer,"text",EMARQUE,NULL);
			gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

			renderer = gtk_cell_renderer_text_new ();
			column = gtk_tree_view_column_new_with_attributes ("valeur",renderer,"text",EVALEUR,NULL);
			gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

			renderer = gtk_cell_renderer_text_new ();
			column = gtk_tree_view_column_new_with_attributes (" date d ajout",renderer,"text",EDATE,NULL);
			gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

			renderer = gtk_cell_renderer_text_new ();
			column = gtk_tree_view_column_new_with_attributes ("type",renderer,"text",ETYPE,NULL);
			gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new ();
			column = gtk_tree_view_column_new_with_attributes ("Etat",renderer,"text",EETAT,NULL);
			gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new ();
			column = gtk_tree_view_column_new_with_attributes ("Cause",renderer,"text",ECAUSE,NULL);
			gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

			}
			store = gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

			gtk_list_store_append (store, &iter);

			fseek (f,comp*sizeof (capteur),SEEK_SET);
			fread (&c,sizeof (capteur),1,f);
			sprintf (date1,"%d/%d/%d",c.date.jour,c.date.mois,c.date.annee);
			gtk_list_store_set (store, &iter, EID, c.id, EMARQUE, c.marque, EVALEUR, c.valeur,ETYPE,c.type, EDATE, date1,EETAT,c.etat,ECAUSE,c.cause,-1);
			fclose (f);
			gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
			g_object_unref (store);
			
	}
}

void affiche_type(GtkWidget *liste,char t[])
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	
	FILE* f;
	capteur c;
	
		char date1[15];
	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("id", renderer, "text",EID,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("marque", renderer, "text",EMARQUE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("valeur", renderer, "text",EVALEUR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes ("date ajout ",renderer,"text",EDATE,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes ("type ",renderer,"text",ETYPE,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes ("Etat ",renderer,"text",EETAT,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes ("Cause ",renderer,"text",ECAUSE,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


	}
	store=gtk_list_store_new (COLUMNS , G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING );
	f=fopen("capteur.bin","rb");
	
	if(f==NULL)
	{
		return;
	}
	else
	{
		//f=fopen("capteur.bin","a+b");
		while(fread(&c,sizeof(capteur),1,f)!=0)
		if (strcmp(c.type,t)==0)
		{
			gtk_list_store_append(store, &iter);
                        sprintf(date1,"%2d/%2d/%4d",c.date.jour,c.date.mois,c.date.annee);
			gtk_list_store_set (store, &iter, EID,c.id,EMARQUE,c.marque, EVALEUR, c.valeur,ETYPE, c.type, EDATE,date1,EETAT,c.etat,ECAUSE,c.cause, -1);
		}
		fclose(f);


		
		gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
		g_object_unref (store);
	}}




void capteur_alarmante( GtkWidget *liste)
{
GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	
	FILE* f;
	capteur c;
	char date1[20];
		
	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("id", renderer, "text",EID,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("marque", renderer, "text",EMARQUE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("valeur", renderer, "text",EVALEUR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes ("date ajout ",renderer,"text",EDATE,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes ("type ",renderer,"text",ETYPE,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes ("Etat ",renderer,"text",EETAT,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes ("Cause ",renderer,"text",ECAUSE,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


	}
	store=gtk_list_store_new (COLUMNS , G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING );
	f=fopen("capteur.bin","rb");
	
	if(f==NULL)
	{
		return;
	}
	else
	{
		while(fread(&c,sizeof(capteur),1,f)!=0)
		if (strcmp(c.type,"température")==0)
			{if (strcmp(c.valeur,"0")<0 || strcmp(c.valeur,"45")>0)
		
		{
			gtk_list_store_append(store, &iter);
                        sprintf(date1,"%2d/%2d/%4d",c.date.jour,c.date.mois,c.date.annee);
			gtk_list_store_set (store, &iter, EID,c.id,EMARQUE,c.marque, EVALEUR, c.valeur,ETYPE, c.type, EDATE,date1,EETAT,c.etat,ECAUSE,c.cause, -1);
		}}
		//if (strcmp(c.type,"humidité")==0)
		else
			{if (strcmp(c.valeur,"40")<0 || strcmp(c.valeur,"76")>0)
		
		{
			gtk_list_store_append(store, &iter);
                        sprintf(date1,"%2d/%2d/%4d",c.date.jour,c.date.mois,c.date.annee);
			gtk_list_store_set (store, &iter, EID,c.id,EMARQUE,c.marque, EVALEUR, c.valeur,ETYPE, c.type, EDATE,date1,EETAT,c.etat,ECAUSE,c.cause, -1);
		}}
		fclose(f);

		
		gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
		g_object_unref (store);
	}}
//////////////////////////////////////////////////////

void etat (int choix [],char texte [])
{ //strcpy (texte ,"etat : ");
if ( choix[0]==1)
strcpy(texte,"bonne état");
else 
strcpy(texte,"en panne");
}


void set_combo_fiche(GtkComboBox     *combobox)
{
capteur c ;
FILE* f;
char date1[20];
f=fopen("capteur.bin","rb");
if (f==NULL)
return;
else
{
while(fread(&c,sizeof(capteur),1,f)!=0)
{
gtk_combo_box_append_text (GTK_COMBO_BOX (combobox), _(c.id));
}
}
fclose(f);
}
//////////////////////////////////////////:
void affiche_suivi(GtkWidget *liste,char i[])
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	
	FILE* f;
	capteur c;
	
	char date1[20];	
	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("id", renderer, "text",EID,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("marque", renderer, "text",EMARQUE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("valeur", renderer, "text",EVALEUR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes ("date ajout ",renderer,"text",EDATE,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes ("type ",renderer,"text",ETYPE,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes ("Etat ",renderer,"text",EETAT,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes ("Cause ",renderer,"text",ECAUSE,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	}
	store=gtk_list_store_new (COLUMNS , G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
	f=fopen("capteur.bin","rb");
	
	if(f==NULL)
	{
		return;
	}
	else
	{
		//f=fopen("capteur.bin","a+b");
		while(fread(&c,sizeof(capteur),1,f)!=0)
		if (strcmp(c.etat,"en panne")==0)
		{sprintf(date1,"%2d/%2d/%4d",c.date.jour,c.date.mois,c.date.annee);

                        gtk_list_store_append(store, &iter);
                        
			gtk_list_store_set (store, &iter, EID,c.id,EMARQUE,c.marque, EVALEUR, c.valeur,EDATE,date1,ETYPE, c.type, EETAT,c.etat,ECAUSE,c.cause, -1);
		}
		fclose(f);

		
		gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
		g_object_unref (store);
	}}
/////////////////////////////////////////////

void marque_defect ( char *marque1)
{
FILE *f;
FILE *g;
f=fopen("defect.bin","rb");
capteur c,c1;
int compt;
mar m;
strcpy(m.nom,"");
m.nb=0;
while(fread(&c,sizeof(capteur),1,f)!=0)
{
    compt=0;
    g=fopen("defect.bin","rb");
    while(fread(&c1,sizeof(capteur),1,g)!=0)
    {
        if (strcmp(c.marque,c1.marque)==0)
            compt++;
    }
    fclose(g);
    if (compt>m.nb)
    {
        strcpy(m.nom,c.marque);
         
        m.nb=compt;
    }
}
fclose(f);
strcpy(marque1,m.nom);
}


