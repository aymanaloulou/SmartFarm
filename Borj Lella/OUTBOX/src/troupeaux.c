#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "troupeaux.h"
#include "interface.h"
#include "support.h"
#include <time.h>
enum 
{
    EREF ,
    EREFM,
    EDATE,
    EPOIDS ,
    EROBE,
    ELOT ,
    EGENDER,
    ETYPE, 
    EETAT,
    EMALADIE,
    ELAIT,	
    COLUMNS

    
};

int RefExiste (char ch[]){
	animal a;

	FILE* f1;
	f1=fopen("animal.bin","rb");

	while (fread (&a,sizeof (animal),1,f1) != 0) {
		
		if (strcmp (a.ref,ch) == 0) 
			 return 1;
	}
	fclose(f1);
	return 0;
	
}
///////////////
int RefExistemodif (char ch[]){
	animal a;
	FILE* f1;
	f1=fopen("animal.bin","rb");

	while (fread (&a,sizeof (animal),1,f1) != 0) {
		
		if (strcmp (a.ref,ch) == 0) 
			 return 1;
	}
	fclose(f1);
	return 0;
	
}
////////
int TrnomValide (char ch[]){
	int i=0,ok = 1;
	if (strlen (ch) == 0){
		ok = 0;	
	}
	while (ok == 1 && i<strlen (ch)){
		if (toupper (ch[i])>='A' && toupper (ch[i]) <='Z')
			i++;
		else
			ok = 0;
	}
	return ok;
}

int TrnumValide (char ch[]){
	int i=0,ok = 1;
	if (strlen (ch) == 0){
		ok = 0;	
	}
	while (ok == 1 && i<strlen (ch)){
		if ((ch[i]=='0') || (ch[i] =='1') || (ch[i]=='2') || (ch[i] =='3') || (ch[i]=='4') || (ch[i] =='5') || (ch[i]=='6') || (ch[i] =='7') || (ch[i]=='8') || (ch[i] =='9') || (ch[i] =='.') )
			i++; 
			else
			ok = 0;	
			
		
	}
	return ok;
}
/*int RefExiste (char ch[])
{
    animal a;
    int p=-1,test=0;
     
    FILE* f = fopen ("animal.bin","rb");

    while (fread (&a,sizeof (animal),1,f) != 0 && p==-1){
       
        if (strcmp (a.ref,ch) == 0) 
             p=test;
else test++;
    }
    fclose (f);
    return p;

}
*/
int get_animal(char ch1[],animal a)
{
	FILE* f = fopen ("animal.bin","rb");

    while (fread (&a,sizeof (animal),1,f) != 0 ){
       
        if (strcmp (a.ref,ch1) == 0) 
	return 1 ;
	else
	return 0;
}	
}
/////////////////////////


int AjoutAnimal(animal a,GtkWidget *objet)
{
int ok=1;
//char typee[20];
GtkWidget *ref = lookup_widget(objet,"cs_ajout_ref");
GtkWidget *refm =lookup_widget(objet,"cs_ajout_refm");
GtkWidget *robe =lookup_widget(objet,"cs_ajout_robe");
GtkWidget *poids=lookup_widget(objet,"cs_ajout_poids");
GtkWidget *lot = lookup_widget(objet,"cs_ajout_lot");
GtkWidget *type = lookup_widget(objet,"cs_ajout_type");

GtkWidget *eref = lookup_widget(objet,"cs_ajout_msg_ref");
GtkWidget *nref = lookup_widget(objet,"cs_ajout_msg_ref_nv");
GtkWidget *erefm =lookup_widget(objet,"cs_ajout_msg_refm");
GtkWidget *erobe =lookup_widget(objet,"cs_ajout_msg_robe");
GtkWidget *epoids=lookup_widget(objet,"cs_ajout_msg_poids");
GtkWidget *elot = lookup_widget(objet,"cs_ajout_msg_lot");
GtkWidget *etype = lookup_widget(objet,"cs_ajout_msg_type");
//GtkWidget *comboboxx=lookup_widget(objet,"combo_animal");
if(RefExiste (a.ref) == 1)
{
gtk_widget_show(ref);
gtk_widget_show(eref);
ok=0;
}
else
{
gtk_widget_hide(ref);
gtk_widget_hide(eref);
}

if(strcmp(a.ref,"") == 0)
{
gtk_widget_show(ref);
gtk_widget_show(nref);
ok=0;
}
else
{
gtk_widget_hide(ref);
gtk_widget_hide(nref);
}

if(strcmp(a.refm,"") == 0)
{
gtk_widget_show(refm);
gtk_widget_show(erefm);
ok=0;
}
else
{
gtk_widget_hide(refm);
gtk_widget_hide(erefm);
}

if(strcmp(a.robe,"") == 0)
{
gtk_widget_show(robe);
gtk_widget_show(erobe);
ok=0;
}
else
{
gtk_widget_hide(robe);
gtk_widget_hide(erobe);
}

if(strcmp(a.poids,"") == 0)
{
gtk_widget_show(poids);
gtk_widget_show(epoids);
ok=0;
}
else
{
gtk_widget_hide(poids);
gtk_widget_hide(epoids);
}

if(strcmp(a.lot,"") == 0)
{
gtk_widget_show(lot);
gtk_widget_show(elot);
ok=0;
}
else
{
gtk_widget_hide(lot);
gtk_widget_hide(elot);

}
if((strcmp(a.type,"brebis")== 0 ) && (strcmp(a.type,"voeux")== 0 ))
{
//gtk_widget_show(type);
gtk_widget_show(etype);
ok=0;
}
else
{
gtk_widget_hide(type);
gtk_widget_hide(etype);
}
/*

	
	if (RefExiste (a.ref) == 0){
		ok = 0;
		gtk_label_set_text(GTK_LABEL(reff),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(reff),"");
	}


	if (strcmp(a.refm,"") == 0){
		ok = 0;
		gtk_label_set_text(GTK_LABEL(refm),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(refm),"");
	}

	if (TrnomValide(a.robe) == 0){	
		ok = 0;
		gtk_label_set_text(GTK_LABEL(robe),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(robe),"");
	}
 
	if (strcmp(a.poids,"") == 0){	
		ok = 0;
		gtk_label_set_text(GTK_LABEL(poids),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(poids),"");
	}

	if (strcmp(a.lot,"") == 0){	
		ok = 0;
		gtk_label_set_text(GTK_LABEL(lotd),"test");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(lotd),"sdf");
	}
*/
	if (ok == 1){
		FILE* f = fopen ("animal.bin","ab");
		fwrite (&a,sizeof (animal),1,f);
		fclose (f);	
	}

return ok;	
}
/////////////////////////
int CsModifAnimal(animal a,GtkWidget *objet)
{
int ok=1;
char laitg[20];
GtkWidget *ref = lookup_widget(objet,"cs_edit_ref");
GtkWidget *refm =lookup_widget(objet,"cs_edit_refm");
GtkWidget *robe =lookup_widget(objet,"cs_edit_robe");
GtkWidget *poids=lookup_widget(objet,"cs_edit_poids");
GtkWidget *lot = lookup_widget(objet,"cs_edit_lot");
GtkWidget *type = lookup_widget(objet,"cs_edit_type");
GtkWidget *lait = lookup_widget(objet,"cs_edit_lait");

GtkWidget *eref = lookup_widget(objet,"cs_edit_msg_ref");
GtkWidget *nref = lookup_widget(objet,"cs_edit_msg_ref_nv");
GtkWidget *erefm =lookup_widget(objet,"cs_edit_msg_refm");
GtkWidget *erobe =lookup_widget(objet,"cs_edit_msg_robe");
GtkWidget *epoids=lookup_widget(objet,"cs_edit_msg_poids");
GtkWidget *elot = lookup_widget(objet,"cs_edit_msg_lot");
GtkWidget *etype = lookup_widget(objet,"cs_edit_msg_type");
GtkWidget *elait = lookup_widget(objet,"cs_edit_msg_lait");

if(RefExistemodif (a.ref) == 1)
{
gtk_widget_show(ref);
gtk_widget_show(eref);
ok=0;
}
else
{
gtk_widget_hide(ref);
gtk_widget_hide(eref);
}

if(strcmp(a.ref,"") == 0)
{
gtk_widget_show(ref);
gtk_widget_show(nref);
ok=0;
}
else
{
gtk_widget_hide(ref);
gtk_widget_hide(nref);
}

if(strcmp(a.refm,"") == 0)
{
gtk_widget_show(refm);
gtk_widget_show(erefm);
ok=0;
}
else
{
gtk_widget_hide(refm);
gtk_widget_hide(erefm);
}

if(strcmp(a.robe,"") == 0)
{
gtk_widget_show(robe);
gtk_widget_show(erobe);
ok=0;
}
else
{
gtk_widget_hide(robe);
gtk_widget_hide(erobe);
}

if(TrnumValide(a.poids) == 0)
{
gtk_widget_show(poids);
gtk_widget_show(epoids);
ok=0;
}
else
{
gtk_widget_hide(poids);
gtk_widget_hide(epoids);
}

if(strcmp(a.lot,"") == 0)
{
gtk_widget_show(lot);
gtk_widget_show(elot);
ok=0;
}
else
{
gtk_widget_hide(lot);
gtk_widget_hide(elot);

}
if((strcmp(a.type,"brebis")== 0 ) && (strcmp(a.type,"voeux")== 0 ))
{

gtk_widget_show(etype);
ok=0;
}
else
{
gtk_widget_hide(type);
gtk_widget_hide(etype);
}

//char *laitg = g_strdup_printf ("%1.2f",a.laittotale);
sprintf (laitg,"%1.2f",a.laittotale);
g_print ("%s",laitg);
if(TrnumValide(a.lait) == 0)
{
gtk_widget_show(lait);
gtk_widget_show(elait);
ok=0;
}
else
{
gtk_widget_hide(lait);
gtk_widget_hide(elait);
}
/*if (ok == 1){
		FILE* f = fopen ("animal.bin","ab");
		fwrite (&a,sizeof (animal),1,f);
		fclose (f);	
	}*/

return ok;	
}
////////////////
///////////////
	/*if (VerifRef(a.ref) == 0 ||strcmp(a.ref,"") == 0)
	{
		ok = 0;
		gtk_label_set_text(GTK_LABEL(ref),"tt");	
	}	
	else
	{
		gtk_label_set_text(GTK_LABEL(ref),"");
	}
	
	
	if (strcmp(a.refm,"") == 0)
	{
		ok = 0;
		gtk_label_set_text(GTK_LABEL(refm),"tt");	
	}	
	else
	{
		gtk_label_set_text(GTK_LABEL(refm),"");
	}
	
	if (strcmp(a.poids,"") == 0){
		ok = 0;
		gtk_label_set_text(GTK_LABEL(poids),"tt");	
	}	
	else
	{
		gtk_label_set_text(GTK_LABEL(poids),"");
	}
	if (strcmp(a.robe,"") == 0)
	{
		ok = 0;
		gtk_label_set_text(GTK_LABEL(ctrl_robe),"tt");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(ctrl_robe),"");
	}
	if (strcmp(a.lot,"") == 0)
	{
		ok = 0;
		gtk_label_set_text(GTK_LABEL(lot),"tt");	
	}	
	else
	{
		gtk_label_set_text(GTK_LABEL(lot),"");
	}
	
if (ok)
{
	
	FILE* f = fopen("animal.bin","a+b");
	fwrite(&a,sizeof(animal),1,f);
	fclose(f);
		
}
return ok;
}*/
//////////////////////////
/*void AjoutAnimal (animal a){
		FILE *f;
		f = fopen ("animal.bin","ab");
		if (f!=NULL)
		{           
                fwrite(&a,sizeof (animal),1,f); 
			
		}
fclose (f);
}
*/
////////////////////////////////

void ModifAnimal(animal a)  {
animal aux;int test = 0;int comp = 0;
FILE* f;
f = fopen ("animal.bin","r+b");		
do{
	fread (&aux,sizeof (animal),1,f);
	if (strcmp (a.ref,aux.ref) == 0)
		test = 1;
	else 
		comp++;
}while (test == 0);
fseek (f,comp*sizeof(animal),SEEK_SET);
fwrite (&a,sizeof(animal),1,f);
fclose (f);
		
}
//////////////////////////////
void AffichListeAnimal(GtkWidget *liste)
{	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	
	FILE* f;
	animal a;
	
	char date1[20];
        char lait1[20];
	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Identifiant", renderer, "text",EREF,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Identifiant mére", renderer, "text",EREFM,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Date de naissance", renderer, "text",EDATE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Poids", renderer, "text",EPOIDS,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Robe", renderer, "text",EROBE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Lot", renderer, "text",ELOT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Genre", renderer, "text",EGENDER,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text",ETYPE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Etat", renderer, "text",EETAT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Maladie", renderer, "text",EMALADIE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Production Lait", renderer, "text",ELAIT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
		}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
	f=fopen("animal.bin","rb");
	if(f==NULL)
	{
		return;
	}
	else
	{
		
		while(fread(&a,sizeof(animal),1,f)!=0)
		{
			gtk_list_store_append(store, &iter);
sprintf(lait1,"%1.2f",a.laittotale);
sprintf (date1,"%2d/%2d/%4d",a.date1.jour,a.date1.mois,a.date1.annee);
			gtk_list_store_set (store, &iter, EREF, a.ref,EREFM, a.refm, EDATE, date1, EPOIDS, a.poids, EROBE, a.robe, ELOT, a.lot,EGENDER,a.gender,ETYPE,a.type,EETAT,a.etat,EMALADIE,a.maladie,ELAIT,lait1, -1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
		g_object_unref (store);
	}
}

//////////////////////////
void genre(int choix[], char text[])
{
if (choix[0] == 1)
	strcpy(text,"male");
else
	strcpy(text,"femelle");

}
//////////////////////////////////////////////////
void SuppAnimal( char ref[])
{
	animal a;
	FILE *f, *g;
		f=fopen("animal.bin","rb");
		g=fopen("animal2.bin","wb");
		
	if (f==NULL || g==NULL)
		return;
	else
	{
		while(fread(&a,sizeof(animal),1,f)!=0)
		
			{
				if (strcmp(ref,a.ref)!=0)
					fwrite (&a,sizeof(animal),1,g);
					
			}
		fclose(f);
		fclose(g);
		remove("animal.bin");
		rename("animal2.bin","animal.bin");
	}
}
//////////////////////
animal a_f;
void pdfT (animal a_m)
{

char datej[10],datem[10],datea[10];
char agej[10],agem[10],agea[10];
char laitj[20];
FILE *f;
f=fopen("ficheanimal.txt","w");
if (f!=NULL)
{sprintf (datej,"%2d",a_m.date1.jour);
sprintf (datem,"%2d",a_m.date1.mois);
sprintf (datea,"%4d",a_m.date1.annee);
sprintf (laitj,"%1.2f",a_m.laittotale);
/*
g_print ("%d",a_f.date1.jour);
g_print ("%d",a_f.date1.mois);
g_print ("%d",a_f.date1.annee);
*/
sprintf (agej,"%d",a_f.date1.jour);
sprintf (agem,"%d",a_f.date1.mois);
sprintf (agea,"%d",a_f.date1.annee);
fprintf (f,"---------- Fiche Animal : %2s ---------- \n",a_m.ref);
fprintf (f,"\n\n     Reférence mére : %2s  \n \n     Date de naissance : %2s/%2s/%2s    \n \n     Age : %2s année(s) , %2s mois et %2s jour(s)   \n \n     Sexe:  %2s  \n \n     Poids : %2s  \n \n     Robe: %2s  \n \n     Lot: %2s  \n \n     Lait produit :  %2s \n \n     Santé:  %2s \n \n     Type: %2s \n \n ",a_m.refm,datej,datem,datea,agea,agem,agej,a_m.gender,a_m.poids,a_m.robe,a_m.lot,laitj,a_m.etat,a_m.type);}
fprintf (f,"\n----------------------------------------- \n");
fclose(f);



}
//////////////////////////////////

void SuppHistAnimal(animal a)
{
animal ah;
FILE *fh,*gh;
fh= fopen ("histanimal.bin","rb");
gh= fopen ("tmphistanimal.bin","ab");
if (fh==NULL || gh==NULL)
		return;
	else
	{
		while (fread (&ah,sizeof(animal),1,fh)!=0)
		{	
			if (strcmp(ah.ref,a.ref)!=0)
			{
 				fwrite (&ah,sizeof(animal),1,gh);
			}
		}
fclose (fh);
fclose (gh);
remove ("histanimal.bin");
rename ("tmphistanimal.bin","histanimal.bin");
}}
///////////////////////////////
//fonction recherche:
void  RechercheAnimal(char *ref_rech, GtkWidget *liste)
{	
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	
	FILE* f;
	animal a;
	char lait1[20];
	char date1[20];
	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Identifiant", renderer, "text",EREF,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Identifiant mére", renderer, "text",EREFM,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Date de naissance", renderer, "text",EDATE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Poids", renderer, "text",EPOIDS,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Robe", renderer, "text",EROBE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Lot", renderer, "text",ELOT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Genre", renderer, "text",EGENDER,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text",ETYPE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Etat", renderer, "text",EETAT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Maladie", renderer, "text",EMALADIE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Lait Produit", renderer, "text",ELAIT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
		}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
	f=fopen("animal.bin","rb");
	if(f==NULL)
	{
		return;
	}
	else
	{
		
		while(fread(&a,sizeof(animal),1,f)!=0)
		{	sprintf (date1,"%2d/%2d/%4d",a.date1.jour,a.date1.mois,a.date1.annee);
			sprintf (lait1,"%1.2f",a.laittotale);
			if(strstr(a.ref,ref_rech)!=NULL || strstr(a.refm,ref_rech)!=NULL || strstr(date1,ref_rech)!=NULL|| strstr(a.poids,ref_rech)!=NULL || strstr(a.robe,ref_rech)!=NULL || strstr(a.lot,ref_rech)!=NULL || strstr(a.gender,ref_rech)!=NULL || strstr(a.type,ref_rech)!=NULL || strstr(a.etat,ref_rech)!=NULL || strstr(a.maladie,ref_rech)!=NULL || strstr(lait1,ref_rech)!=NULL)
			{
			gtk_list_store_append(store, &iter);

			gtk_list_store_set (store, &iter, EREF, a.ref,EREFM, a.refm, EDATE, date1, EPOIDS, a.poids, EROBE, a.robe, ELOT, a.lot,EGENDER,a.gender,ETYPE,a.type,EETAT,a.etat,EMALADIE,a.maladie,ELAIT,lait1, -1);
		}}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
		g_object_unref (store);
	}
}
///////////////Recherche Historique//////////////////////
void  RechercheHistAnimal(char *ref_rech, GtkWidget *liste)
{	
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	
	FILE* f;
	animal a;
	char lait1[20];
	char date1[20];
	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Identifiant", renderer, "text",EREF,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Identifiant mére", renderer, "text",EREFM,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Date de naissance", renderer, "text",EDATE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Poids", renderer, "text",EPOIDS,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Robe", renderer, "text",EROBE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Lot", renderer, "text",ELOT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Genre", renderer, "text",EGENDER,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text",ETYPE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Etat", renderer, "text",EETAT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Maladie", renderer, "text",EMALADIE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Lait Produit", renderer, "text",ELAIT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
		}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
	f=fopen("histanimal.bin","rb");
	if(f==NULL)
	{
		return;
	}
	else
	{
		
		while(fread(&a,sizeof(animal),1,f)!=0)
		{	sprintf (date1,"%2d/%2d/%4d",a.date1.jour,a.date1.mois,a.date1.annee);
			sprintf (lait1,"%1.2f",a.laittotale);
			if(strstr(a.ref,ref_rech)!=NULL || strstr(a.refm,ref_rech)!=NULL || strstr(date1,ref_rech)!=NULL|| strstr(a.poids,ref_rech)!=NULL || strstr(a.robe,ref_rech)!=NULL || strstr(a.lot,ref_rech)!=NULL || strstr(a.gender,ref_rech)!=NULL || strstr(a.type,ref_rech)!=NULL || strstr(a.etat,ref_rech)!=NULL || strstr(a.maladie,ref_rech)!=NULL || strstr(lait1,ref_rech)!=NULL)
			{
			gtk_list_store_append(store, &iter);

			gtk_list_store_set (store, &iter, EREF, a.ref,EREFM, a.refm, EDATE, date1, EPOIDS, a.poids, EROBE, a.robe, ELOT, a.lot,EGENDER,a.gender,ETYPE,a.type,EETAT,a.etat,EMALADIE,a.maladie,ELAIT,lait1, -1);
		}}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
		g_object_unref (store);
	}
}

////////////////////AFFICHAGE HIST////////////////////////
void AffichListeAnimalHist(GtkWidget *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	
	FILE* f;
	animal ah;
	
	char date1[20];
	char lait1[20];
	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Identifiant", renderer, "text",EREF,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Identifiant mére", renderer, "text",EREFM,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Date de naissance", renderer, "text",EDATE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Poids", renderer, "text",EPOIDS,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Robe", renderer, "text",EROBE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Lot", renderer, "text",ELOT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Genre", renderer, "text",EGENDER,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text",ETYPE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Etat", renderer, "text",EETAT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Maladie", renderer, "text",EMALADIE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Lait produit", renderer, "text",ELAIT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
		}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
	f=fopen("histanimal.bin","rb");
	if(f==NULL)
	{
		return;
	}
	else
	{
		
		while(fread(&ah,sizeof(animal),1,f)!=0)
		{
			gtk_list_store_append(store, &iter);
sprintf (date1,"%2d/%2d/%4d",ah.date1.jour,ah.date1.mois,ah.date1.annee);
sprintf (lait1,"%1.2f",ah.laittotale);
			gtk_list_store_set (store, &iter, EREF, ah.ref,EREFM, ah.refm, EDATE, date1, EPOIDS, ah.poids, EROBE, ah.robe, ELOT, ah.lot,EGENDER,ah.gender,ETYPE,ah.type,EETAT,ah.etat,EMALADIE,ah.maladie,ELAIT,lait1, -1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
		g_object_unref (store);
	}
}
////////////////////////////////////////////////////////
void AffichListeAnimalVoeux(GtkWidget *liste) 
{	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	
	FILE* f;
	animal a;
	char lait1[20];
	char date1[20];
	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
        
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Identifiant", renderer, "text",EREF,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Identifiant mére", renderer, "text",EREFM,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Date de naissance", renderer, "text",EDATE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Poids", renderer, "text",EPOIDS,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Robe", renderer, "text",EROBE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Lot", renderer, "text",ELOT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Genre", renderer, "text",EGENDER,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text",ETYPE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Etat", renderer, "text",EETAT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Maladie", renderer, "text",EMALADIE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Lait Produit", renderer, "text",ELAIT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
		}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
	f=fopen("animal.bin","rb");
	if(f==NULL)
	{
		return;
	}
	else
	{
		
		while(fread(&a,sizeof(animal),1,f)!=0)
		{
			if (strcmp(a.type,"voeux")==0)
			{
			gtk_list_store_append(store, &iter);
			sprintf (date1,"%2d/%2d/%4d",a.date1.jour,a.date1.mois,a.date1.annee);
			sprintf (lait1,"%1.2f",a.laittotale);
			gtk_list_store_set (store, &iter, EREF, a.ref,EREFM, a.refm, EDATE, date1, EPOIDS, a.poids, EROBE, a.robe, ELOT, a.lot,EGENDER,a.gender,ETYPE,a.type,EETAT,a.etat,EMALADIE,a.maladie,ELAIT,lait1, -1);
		}}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
		g_object_unref (store);
	}


}
//////////////////////////
void AffichListeAnimalBrebis(GtkWidget *liste) 
{	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	
	FILE* f;
	animal a;
	char lait1[20];
	char date1[20];
	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
        
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Identifiant", renderer, "text",EREF,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Identifiant mére", renderer, "text",EREFM,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Date de naissance", renderer, "text",EDATE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Poids", renderer, "text",EPOIDS,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Robe", renderer, "text",EROBE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Lot", renderer, "text",ELOT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Genre", renderer, "text",EGENDER,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text",ETYPE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Etat", renderer, "text",EETAT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Maladie", renderer, "text",EMALADIE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Lait Produit", renderer, "text",ELAIT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
		}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
	f=fopen("animal.bin","rb");
	if(f==NULL)
	{
		return;
	}
	else
	{
		
		while(fread(&a,sizeof(animal),1,f)!=0)
		{
			if (strcmp(a.type,"brebis")==0)
			{
			gtk_list_store_append(store, &iter);
			sprintf (date1,"%2d/%2d/%4d",a.date1.jour,a.date1.mois,a.date1.annee);
   			sprintf(lait1,"%1.2f",a.laittotale);
			gtk_list_store_set (store, &iter, EREF, a.ref,EREFM, a.refm, EDATE, date1, EPOIDS, a.poids, EROBE, a.robe, ELOT, a.lot,EGENDER,a.gender,ETYPE,a.type,EETAT,a.etat,EMALADIE,a.maladie,ELAIT,lait1, -1);
		}}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
		g_object_unref (store);
	}


}

/////////////////////////////

void AffichAnimalmalade(GtkWidget *liste) 
{	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	char date1[20];
	char lait1[20];
	FILE* f;
	animal a;
	
	
	store=NULL;
	
	store=gtk_tree_view_get_model(liste);
        
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Identifiant", renderer, "text",EREF,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Identifiant mére", renderer, "text",EREFM,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	
	column = gtk_tree_view_column_new_with_attributes("Maladie", renderer, "text",EMALADIE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
		}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
	f=fopen("animal.bin","rb");
	if(f==NULL)
	{
		return;
	}
	else
	{
		
		while(fread(&a,sizeof(animal),1,f)!=0)
		{
			if (strcmp(a.etat,"malade")==0)
			{
			sprintf (date1,"%2d/%2d/%4d",a.date1.jour,a.date1.mois,a.date1.annee);
			sprintf(lait1,"%1.2f",a.laittotale);
			gtk_list_store_append(store, &iter);
			gtk_list_store_set (store, &iter, EREF, a.ref,EREFM, a.refm, EDATE, date1, EPOIDS, a.poids, EROBE, a.robe, ELOT, a.lot,EGENDER,a.gender,ETYPE,a.type,EETAT,a.etat,EMALADIE,a.maladie,ELAIT,lait1, -1);
		}}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
		g_object_unref (store);
	}


}


////////////////////////////
/*int get_age(char date[20])
{
	int a,m,j,age;
	char *jour[2],*mois[2],*annee[4];
	get_date(&jour,&mois,&annee,date);
	a=atoi(annee);
	m=get_mois(mois);
	j=atoi(jour);
	time_t t = time(NULL);
 	struct tm tm = *localtime(&t);
	if (tm.tm_mon<m)
		return (tm.tm_year+1900-a-1) ;
	else if ((tm.tm_mon==m)&&(tm.tm_mday<j))
		return (tm.tm_year+1900-a-1) ;

  	return (tm.tm_year+1900-a) ;

}*/
/////////////////////
void SuppAlim( char ref[])
{
	alim b;
	FILE *f, *g;
		f=fopen("alim.bin","rb");
		g=fopen("alim2.bin","wb");
		
	if (f==NULL || g==NULL)
		return;
	else
	{
		while(fread(&b,sizeof(alim),1,f)!=0)
		
			{
				if (strcmp(ref,b.MS)!=0)
					fwrite (&b,sizeof(alim),1,g);
					
			}
		fclose(f);
		fclose(g);
		remove("alim.bin");
		rename("alim2.bin","alim.bin");
	}
}
////////////////////////
void AjoutAlim(alim b)
{
		FILE* f = fopen ("alim.bin","w");
		fwrite (&b,sizeof (alim),1,f);
		fclose (f);	
}
////////////////////////
void pdfalim (alim b)
{
FILE *f;
FILE* n = fopen ("alim.bin","r");
fread(&b,sizeof(alim),1,n);
f=fopen("alim.txt","w");
if (f!=NULL)
{
fprintf (f,"---------- Rapport Alimentation :  ---------- \n");
fprintf (f,"\n \n Ingestion"  ); 
fprintf (f,"\n \nMS:  %2s %  \n \nUEM:  %2s %  \n \nUEL:  %2s %  \n \nUEB:  %2s %",b.MS,b.UEM,b.UEL,b.UEB);

fprintf (f,"\n \n Fibrosité"  ); 
fprintf (f,"\n \nNDF:  %2s g/KgMS  \n \nADF:  %2s g/KgMS  \n \nADL:  %2s g/KgMS  \n \nCB:  %2s g/KgMS",b.NDF,b.ADF,b.ADL,b.CB);

fprintf (f,"\n \n Protéines"  ); 
fprintf (f,"\n \nPDIN:  %2s g/KgMS  \n \nPDIE:  %2s g/KgMS  \n \nPDIA:  %2s g/KgMS  \n \nMAT:  %2s g/KgMS  \n \nLYSDI:  %2s%  \n \nMETDI:  %2s%",b.PDIN,b.PDIE,b.PDIA,b.MAT,b.LYSDI,b.METDI);

fprintf (f,"\n \n Energie"  ); 
fprintf (f,"\n \nUFL:  %2s /KgMS \n \nUEV:  %2s /KgMS \n \nMO:  %2s g/KgMS\n \ndMO:  %2s % \n \namidon:  %2s g/KgMS  \n \nsucre:  %2s g/KgMS  \n \nEE/MG:  %2s g/KgMS  ",b.UFL,b.UEV,b.MO,b.dMO,b.amidon,b.sucre,b.EEMG);
}
fprintf (f,"\n----------------------------------------- \n");
fclose(f);
fclose(n);
}
/////////////////
/*b.MS
b.UEM
b.UEL
b.UEB

b.UFL
b.UEV
b.MO
b.dMO
b.amidon
b.sucre
b.EEMG

b.NDF
b.ADF
b.ADL
b.CB

b.PDIN
b.PDIE
b.PDIA
b.MAT
b.LYSDI
b.METDI
*/
//////////////////////:


 
/*check given year is leap year or not*/
int isLeapYear(int year, int mon)
{
    int flag = 0;
    if (year % 100 == 0)
    {
            if (year % 400 == 0)
            {
                    if (mon == 2)
                    {
                            flag = 1;
                    }
            }
    }
    else if (year % 4 == 0)
    {
            if (mon == 2)
            {
                    flag = 1;
            }
    }
    return (flag);
}
 
/////////////////////// 
int get_jour(animal a)
{
 	
    int DaysInMon[] = {31, 28, 31, 30, 31, 30,
                       31, 31, 30, 31, 30, 31};
    int days, month, year;
    char dob[100];
    time_t ts;
    struct tm *ct;
 
        days=a.date1.jour;
	month=a.date1.mois;
	year=a.date1.annee;
    
	
 
    /*get current date.*/
    ts = time(NULL);
    ct = localtime(&ts);
 
    g_print("Current Date: %d/%d/%d\n",
            ct->tm_mday, ct->tm_mon + 1, ct->tm_year + 1900);
 
    days = DaysInMon[month - 1] - days + 1;
 
    /* leap year checking*/
    if (isLeapYear(year, month))
    {
            days = days + 1;
    }
 
    /* calculating age in no of days, years and months */
    days = days + ct->tm_mday;
    month = (12 - month) + (ct->tm_mon);
    year = (ct->tm_year + 1900) - year - 1;
 
    /* checking for leap year feb - 29 days */
    if (isLeapYear((ct->tm_year + 1900), (ct->tm_mon + 1)))
    {
            if (days >= (DaysInMon[ct->tm_mon] + 1))
            {
                    days = days - (DaysInMon[ct->tm_mon] + 1);
                    month = month + 1;
            }
    }
    else if (days >= DaysInMon[ct->tm_mon])
    {
            days = days - (DaysInMon[ct->tm_mon]);
            month = month + 1;
    }
 
    if (month >= 12)
    {
            year = year + 1;
            month = month - 12;
    }
 	
    /* print age */
    g_print("\n## Hey you are  %d years %d months and %d days old. ##\n", year, month, days);
 
    return days;
}
/////////
int get_mois(animal a)
{
 	
    int DaysInMon[] = {31, 28, 31, 30, 31, 30,
                       31, 31, 30, 31, 30, 31};
    int days, month, year;
    char dob[100];
    time_t ts;
    struct tm *ct;
 
        days=a.date1.jour;
	month=a.date1.mois;
	year=a.date1.annee;
    
	
 
    /*get current date.*/
    ts = time(NULL);
    ct = localtime(&ts);
 
    
 
    days = DaysInMon[month - 1] - days + 1;
 
    /* leap year checking*/
    if (isLeapYear(year, month))
    {
            days = days + 1;
    }
 
    /* calculating age in no of days, years and months */
    days = days + ct->tm_mday;
    month = (12 - month) + (ct->tm_mon);
    year = (ct->tm_year + 1900) - year - 1;
 
    /* checking for leap year feb - 29 days */
    if (isLeapYear((ct->tm_year + 1900), (ct->tm_mon + 1)))
    {
            if (days >= (DaysInMon[ct->tm_mon] + 1))
            {
                    days = days - (DaysInMon[ct->tm_mon] + 1);
                    month = month + 1;
            }
    }
    else if (days >= DaysInMon[ct->tm_mon])
    {
            days = days - (DaysInMon[ct->tm_mon]);
            month = month + 1;
    }
 
    if (month >= 12)
    {
            year = year + 1;
            month = month - 12;
    }
 	
 
 
    return month;
}
////////////
int get_annee(animal a)
{
 	
    int DaysInMon[] = {31, 28, 31, 30, 31, 30,
                       31, 31, 30, 31, 30, 31};
    int days, month, year;
    char dob[100];
    time_t ts;
    struct tm *ct;
 
        days=a.date1.jour;
	month=a.date1.mois;
	year=a.date1.annee;
    
	
 
    /*get current date.*/
    ts = time(NULL);
    ct = localtime(&ts);
 
    
 
    days = DaysInMon[month - 1] - days + 1;
 
    /* leap year checking*/
    if (isLeapYear(year, month))
    {
            days = days + 1;
    }
 
    /* calculating age in no of days, years and months */
    days = days + ct->tm_mday;
    month = (12 - month) + (ct->tm_mon);
    year = (ct->tm_year + 1900) - year - 1;
 
    /* checking for leap year feb - 29 days */
    if (isLeapYear((ct->tm_year + 1900), (ct->tm_mon + 1)))
    {
            if (days >= (DaysInMon[ct->tm_mon] + 1))
            {
                    days = days - (DaysInMon[ct->tm_mon] + 1);
                    month = month + 1;
            }
    }
    else if (days >= DaysInMon[ct->tm_mon])
    {
            days = days - (DaysInMon[ct->tm_mon]);
            month = month + 1;
    }
 
    if (month >= 12)
    {
            year = year + 1;
            month = month - 12;
    }
 	
    
 
    return year;
}
  
   


