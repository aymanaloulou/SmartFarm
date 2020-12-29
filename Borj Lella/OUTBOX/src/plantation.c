#include <string.h>
#include "support.h"
#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include "plantation.h"
#include "callbacks.h"
#include <gtk/gtk.h>

enum
{
 REFERENCE,
 QUANTITE,
 UNITE,
 DATE,
 QUANTITER,
 DATERECOLTE,
 ARROSAGE,
 ENGRAIS,
 DATEENGRAIS,
 TAILLE,
 DATETAILLE,
 COMMENTAIRE,
 COLUMNS
};
enum
{
 DATEPRECIPITATION,
 VALEUR,
 COLUMNS1
};
///////


///////
int compare_date(struct Datep a,struct Datep b){
if (b.annee<a.annee)
	return 1;
else if (b.annee>a.annee)
	return 0;
else if (b.annee=a.annee)
	{
	if(b.mois<a.mois)
		return 1;
	
	else if(b.mois>a.mois)
		return 0;
	else if (b.mois=a.mois){
		
		if(b.jour<a.jour)
		return 1;
		
		else if(b.jour>a.jour)
		return 0;
		else if (b.jour=a.jour)
		return 0;}
		}
	 }
int comp(int a,int b){
if (b>a)
	return 0;
else
	return 1;}
int verifREF_plante (char ch[]){
	plante p1;

	FILE* f1;
	f1=fopen("Plantes.bin","rb");

	while (fread (&p1,sizeof (plante),1,f1) != 0) {
		
		if (strcmp (p1.reference,ch) == 0) 
			 return 0;
	}
	fclose(f1);
	return 1;
	
}

void famille(int choix[], char text[])
{
switch (choix[0]){
	case (0):{strcpy(text,"aucun");
			break;}
	case (1):{strcpy(text,"chaque semaine");
			break;}
	case (2):{strcpy(text,"chaque mois");
			break;}
	case (3):{strcpy(text,"chaque annee");
			break;}
}}

/////////

/////////

//Ajouter une plante

int Ajouter_plante(plante p,GtkWidget *objet)
{ 
int valide=1,valide1=1,valide2=1,valide3=1,valide4=1;
GtkWidget *ref_p = lookup_widget (objet,"label_ref_plante");
GtkWidget *ref_pm = lookup_widget (objet,"label_ref_modif_plante");
GtkWidget *quant_m = lookup_widget (objet,"label131_plante");
GtkWidget *quant = lookup_widget (objet,"label_quantite_plante");
GtkWidget *input1=lookup_widget(objet,"label143_plante");
GtkWidget *input2=lookup_widget(objet,"label133_plante");
GtkWidget *input3=lookup_widget(objet,"label134_plante");
GtkWidget *input1_m=lookup_widget(objet,"label144_plante");
GtkWidget *input2_m=lookup_widget(objet,"label145_plante");
GtkWidget *input3_m=lookup_widget(objet,"label146_plante");



if (p.quant.quantite_recolte != 0){
if (compare_date(p.date,p.date_recolte)){
		valide2=0;
		gtk_label_set_text(GTK_LABEL(input1),"Cette date doit etre supèrieure à la date de plantation");
		gtk_label_set_text(GTK_LABEL(input1_m),"Cette date doit etre supèrieure à la date de plantation");}
else {
		valide2=1;
		gtk_label_set_text(GTK_LABEL(input1),"");
		gtk_label_set_text(GTK_LABEL(input1),"");}
}
if (compare_date(p.date,p.date_engrais1)){
		valide3=0;
		gtk_label_set_text(GTK_LABEL(input2),"Cette date doit etre supèrieure à la date de plantation");
		gtk_label_set_text(GTK_LABEL(input2_m),"Cette date doit etre supèrieure à la date de plantation");}
else {
		valide3=1;
		gtk_label_set_text(GTK_LABEL(input2),"");
		gtk_label_set_text(GTK_LABEL(input2_m),"");}

if (strcmp(p.taille,"oui")==0){
if (compare_date(p.date,p.date_taille)){
			valide4=0;
			gtk_label_set_text(GTK_LABEL(input3),"Cette date doit etre supèrieure à la date de plantation");
			gtk_label_set_text(GTK_LABEL(input3_m),"Cette date doit etre supèrieure à la date de plantation");}
else {
			valide4=1;
			gtk_label_set_text(GTK_LABEL(input3),"");
			gtk_label_set_text(GTK_LABEL(input3_m),"");}}
				
if (verifREF_plante(p.reference) == 0){
		valide = 0;
		gtk_label_set_text(GTK_LABEL(ref_p),"Ce nom existe déja");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(ref_p),"");
	}

if (verifREF_plante(p.reference) == 0){
		valide = 0;
		gtk_label_set_text(GTK_LABEL(ref_p),"Ce nom existe déja");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(ref_p),"");
	}
if (verifREF_plante(p.reference) == 0){
		valide = 0;
		gtk_label_set_text(GTK_LABEL(ref_pm),"Ce nom existe déja");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(ref_pm),"");
	}

if (strcmp (p.reference,"") == 0) 
			{valide=0;
			gtk_label_set_text(GTK_LABEL(ref_p),"Veuillez introduire un nom");
			gtk_label_set_text(GTK_LABEL(ref_pm),"Veuillez introduire un nom");}
if(comp(p.quant.quantite,p.quant.quantite_recolte)==0){
	valide1=0;
	gtk_label_set_text(GTK_LABEL(quant),"X");
}
else{
	gtk_label_set_text(GTK_LABEL(quant),"");
}

if(comp(p.quant.quantite,p.quant.quantite_recolte)==0){
	valide1=0;
	gtk_label_set_text(GTK_LABEL(quant_m),"X");
}
else{
	gtk_label_set_text(GTK_LABEL(quant_m),"");
}

if ((valide)&&(valide1)&&(valide2)&&(valide3)&&(valide4)){
FILE *f;
 f=fopen("Plantes.bin","a+b");
 if(f!=NULL)
 	fwrite(&p,sizeof(plante),1,f);
fclose(f);}
return ((valide)&&(valide1)&&(valide2)&&(valide3)&&(valide4));
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
	char date_recolte[20];
	char date2[20];
	char date3[20];
	char val1[20];
	char val2[20];
	store=NULL;



store=gtk_tree_view_get_model(liste);
if (store==NULL)
{

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Nom de plantation",renderer,"text",REFERENCE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Quantité",renderer,"text",QUANTITE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Unité",renderer,"text",UNITE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Date de plantation", renderer, "text",DATE,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Quantite recoltée",renderer,"text",QUANTITER,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Date de recolte",renderer,"text",DATERECOLTE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Arrosage",renderer,"text",ARROSAGE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Engrais chimique",renderer,"text",ENGRAIS,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Date d'utilisation",renderer,"text",DATEENGRAIS,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Taille",renderer,"text",TAILLE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Date de taille ",renderer,"text",DATETAILLE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Commentaire",renderer,"text",COMMENTAIRE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
}
store=gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
f=fopen("Plantes.bin","rb");


if(f==NULL){
return;}
else{

while(fread(&p,sizeof(plante),1,f)!=0)

	{
	gtk_list_store_append(store,&iter);
sprintf (val2,"%d",p.quant.quantite_recolte);
sprintf (val1,"%d",p.quant.quantite);
sprintf (date1,"%2d/%2d/%4d",p.date.jour,p.date.mois,p.date.annee);
sprintf (date_recolte,"%2d/%2d/%4d",p.date_recolte.jour,p.date_recolte.mois,p.date_recolte.annee);
sprintf (date2,"%2d/%2d/%4d",p.date_engrais1.jour,p.date_engrais1.mois,p.date_engrais1.annee);
sprintf (date3,"%2d/%2d/%4d",p.date_taille.jour,p.date_taille.mois,p.date_taille.annee);
gtk_list_store_set(store,&iter,REFERENCE,p.reference,QUANTITE,val1,UNITE,p.unit.unite,DATE,date1,QUANTITER,val2,DATERECOLTE,date_recolte,ARROSAGE,p.arrosage,ENGRAIS,p.engrais,DATEENGRAIS,date2,TAILLE,p.taille,DATETAILLE,date3,COMMENTAIRE,p.commentaire,-1);
		
}
	fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
g_object_unref(store);
    }



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
		
}

}
//Rechercher
void Recherche_plante(char *ref_rech,GtkWidget *liste){
	GtkCellRenderer *renderer;
 	GtkTreeViewColumn *column;
 	GtkTreeIter iter;
 	GtkTreeIter *store;

	FILE *f;
	
	plante p;
	char date1[20];
	char date2[20];
	char date3[20];
	char date_recolte[20];
	char val1[20];
	char val2[20];
	store=NULL;



store=gtk_tree_view_get_model(liste);
if (store==NULL)
{

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Nom de plantation",renderer,"text",REFERENCE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Quantité",renderer,"text",QUANTITE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Unité",renderer,"text",UNITE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Date de plantation", renderer, "text",DATE,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Quantite recoltée",renderer,"text",QUANTITER,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Date de recolte", renderer, "text",DATERECOLTE,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Arrosage",renderer,"text",ARROSAGE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Engrais chimique",renderer,"text",ENGRAIS,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Date d'utilisation ",renderer,"text",DATEENGRAIS,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Taille",renderer,"text",TAILLE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Date de taille ",renderer,"text",DATETAILLE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Commentaire",renderer,"text",COMMENTAIRE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
}
store=gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
f=fopen("Plantes.bin","rb");

	while (fread (&p,sizeof (plante),1,f) != 0){
		sprintf (val2,"%d",p.quant.quantite_recolte);
		sprintf (val1,"%d",p.quant.quantite);
		sprintf (date1,"%d/%d/%d",p.date.jour,p.date.mois,p.date.annee);
		sprintf (date_recolte,"%d/%d/%d",p.date_recolte.jour,p.date_recolte.mois,p.date_recolte.annee);
		sprintf (date2,"%d/%d/%d",p.date_engrais1.jour,p.date_engrais1.mois,p.date_engrais1.annee);
		sprintf (date3,"%d/%d/%d",p.date_taille.jour,p.date_taille.mois,p.date_taille.annee);

		if (strstr (p.reference,ref_rech) != NULL || strstr (date1,ref_rech) != NULL || strstr (p.engrais,ref_rech) != NULL )
			{
			gtk_list_store_append (store, &iter);
	gtk_list_store_append(store,&iter);

gtk_list_store_set(store,&iter,REFERENCE,p.reference,QUANTITE,val1,UNITE,p.unit.unite,DATE,date1,QUANTITER,val2,DATERECOLTE,date_recolte,ARROSAGE,p.arrosage,ENGRAIS,p.engrais,DATEENGRAIS,date2,TAILLE,p.taille,DATETAILLE,date3,COMMENTAIRE,p.commentaire,-1);
	
		}
	}
	fclose (f);
	gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
	g_object_unref (store);

}
//precipitation prec;
void Afficher_precipitation(GtkWidget *liste){
	GtkCellRenderer *renderer;
 	GtkTreeViewColumn *column;
 	GtkTreeIter iter;
 	GtkTreeIter *store;
char val1[30];
char date1[30];
	FILE *f;
	precipitation prec;
	plante p;
	

store=gtk_tree_view_get_model(liste);
if (store==NULL)
{

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Date de precipitation",renderer,"text",DATEPRECIPITATION,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Précipitation (mm/h)",renderer,"text",VALEUR,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);}
store=gtk_list_store_new(COLUMNS1,G_TYPE_STRING,G_TYPE_STRING);
f=fopen("Precipitation.bin","rb");
if(f==NULL){
return;}
else{


while(fread(&prec,sizeof(precipitation),1,f)!=0)

	{
	gtk_list_store_append(store,&iter);

sprintf (date1,"%2d/%2d/%4d",prec.date_precip.jour,prec.date_precip.mois,prec.date_precip.annee);
sprintf (val1,"%d",prec.valeur_precipitation);

gtk_list_store_set(store,&iter,DATEPRECIPITATION,date1,VALEUR,val1,-1);
		
}
fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
g_object_unref(store);
	
}
}
void Ajouter_precipitation(precipitation prec){
FILE *f = fopen ("Precipitation.bin","ab");
		if (f == NULL)
			f = fopen ("Precipitation.bin","w");
		fwrite (&prec,sizeof (precipitation),1,f);
		fclose (f);
}
/*///////////////////////////////////////////////////
		PARTIE2
///////////////////////////////////////////////////*/
///////////////////
void partie2(GtkWidget *window1){
float M[100][14],moy_annee;
FILE *f1;
int nb_annee=0,i,j,indice_min,ind,x,test,min,indice_max;
precipitation prec;
char a0[10],ch1[10],ch2[10],ch3[10],ch4[10],ch5[10],ch6[10],ch7[10],ch8[10],ch9[10],ch10[10],ch11[10],ch12[10],moy_13[10],a0_1[10],ch1_1[10],ch2_1[10],ch3_1[10],ch4_1[10],ch5_1[10],ch6_1[10],ch7_1[10],ch8_1[10],ch9_1[10],ch10_1[10],ch11_1[10],ch12_1[10],moy_13_1[10];
GtkWidget *ao,*m1,*m2,*m3,*m4,*m5,*m6,*m7,*m8,*m9,*m10,*m11,*m12,*moy13;


for(i=0;i<100;i++){
	for(j=0;j<14;j++){
		M[i][j]=0;}}
	f1=fopen("Precipitation.bin","rb");
	while (fread (&prec,sizeof (precipitation),1,f1) != 0){
		
		ind=-1;
		test=0;
		i=0;
		while (i <= nb_annee && test==0){
		x=M[i][0];
		if(x==prec.date_precip.annee){
			ind=i;
			test=1;}
		i++;
		}

		if (ind ==-1){
			nb_annee++;
			M[nb_annee-1][0]=prec.date_precip.annee;
			M[nb_annee-1][prec.date_precip.mois]=prec.valeur_precipitation;
		}
		else{
			M[ind][prec.date_precip.mois]+=prec.valeur_precipitation;
		}
	}
	fclose(f1);
for (i=0;i<nb_annee;i++){
	moy_annee=0;
	for (j=1;j<13;j++){
		moy_annee+=M[i][j];
		switch(j){
			case 1: case 3: case 5: case 7: case 8: case 10: case 12:{
				M[i][j]/=31;
			}
			break;
			case 4: case 6: case 9: case 11:{
				M[i][j]/=30;
			}
			break;
			case 2 :{
				x=M[i][0];
				if(x%4==0)
					M[i][j]/=29;
				else
					M[i][j]/=28;
			}
			break;
		}
	}
	x=M[i][0];
	if(x==0)
		M[i][13]=moy_annee/366;
	else
		M[i][13]=moy_annee/365;
	
}

indice_min=0;
for (i=1;i<nb_annee;i++){
		if(M[i][13]<M[indice_min][13]){
			indice_min=i;
		}
		
	}

indice_max=0;
for (i=1;i<nb_annee;i++){
		if(M[i][13]>M[indice_max][13]){
			indice_max=i;
		}
		
	}

	ao=lookup_widget(window1,"label_annee_seche");
	m1=lookup_widget(window1,"label_m1");
	m2=lookup_widget(window1,"label_m2");
	m3=lookup_widget(window1,"label_m3");
	m4=lookup_widget(window1,"label_m4");
	m5=lookup_widget(window1,"label_m5");
	m6=lookup_widget(window1,"label_m6");
	m7=lookup_widget(window1,"label_m7");
	m8=lookup_widget(window1,"label_m8");
	m9=lookup_widget(window1,"label_m9");
	m10=lookup_widget(window1,"label_m10");
	m11=lookup_widget(window1,"label_m11");
	m12=lookup_widget(window1,"label_m12");
	moy13=lookup_widget(window1,"label_moyenne");

	sprintf(ch1,"%.2f",M[indice_min][1]);
	sprintf(ch2,"%.2f",M[indice_min][2]);
	sprintf(ch3,"%.2f",M[indice_min][3]);
	sprintf(ch4,"%.2f",M[indice_min][4]);
	sprintf(ch5,"%.2f",M[indice_min][5]);
	sprintf(ch6,"%.2f",M[indice_min][6]);
	sprintf(ch7,"%.2f",M[indice_min][7]);
	sprintf(ch8,"%.2f",M[indice_min][8]);
	sprintf(ch9,"%.2f",M[indice_min][9]);
	sprintf(ch10,"%.2f",M[indice_min][10]);
	sprintf(ch11,"%.2f",M[indice_min][11]);
	sprintf(ch12,"%.2f",M[indice_min][12]);
	sprintf(a0,"%.0f",M[indice_min][0]);
	sprintf(moy_13,"%.2f",M[indice_min][13]);

	gtk_label_set_text(GTK_LABEL(ao),a0);
	gtk_label_set_text(GTK_LABEL(m1),ch1);
	gtk_label_set_text(GTK_LABEL(m2),ch2);
	gtk_label_set_text(GTK_LABEL(m3),ch3);
	gtk_label_set_text(GTK_LABEL(m4),ch4);
	gtk_label_set_text(GTK_LABEL(m5),ch5);
	gtk_label_set_text(GTK_LABEL(m6),ch6);
	gtk_label_set_text(GTK_LABEL(m7),ch7);
	gtk_label_set_text(GTK_LABEL(m8),ch8);
	gtk_label_set_text(GTK_LABEL(m9),ch9);
	gtk_label_set_text(GTK_LABEL(m10),ch10);
	gtk_label_set_text(GTK_LABEL(m11),ch11);
	gtk_label_set_text(GTK_LABEL(m12),ch12);
	gtk_label_set_text(GTK_LABEL(moy13),moy_13);

	GtkWidget *ao_1=lookup_widget(window1,"label_moin_seche");
	GtkWidget *m1_1=lookup_widget(window1,"label_m1_1");
	GtkWidget *m2_1=lookup_widget(window1,"label_m2_1");
	GtkWidget *m3_1=lookup_widget(window1,"label_m3_1");
	GtkWidget *m4_1=lookup_widget(window1,"label_m4_1");
	GtkWidget *m5_1=lookup_widget(window1,"label_m5_1");
	GtkWidget *m6_1=lookup_widget(window1,"label_m6_1");
	GtkWidget *m7_1=lookup_widget(window1,"label_m7_1");
	GtkWidget *m8_1=lookup_widget(window1,"label_m8_1");
	GtkWidget *m9_1=lookup_widget(window1,"label_m9_1");
	GtkWidget *m10_1=lookup_widget(window1,"label_m10_1");
	GtkWidget *m11_1=lookup_widget(window1,"label_m11_1");
	GtkWidget *m12_1=lookup_widget(window1,"label_m12_1");
	GtkWidget *moy13_1=lookup_widget(window1,"label_moyenne1");

	sprintf(ch1_1,"%.2f",M[indice_max][1]);
	sprintf(ch2_1,"%.2f",M[indice_max][2]);
	sprintf(ch3_1,"%.2f",M[indice_max][3]);
	sprintf(ch4_1,"%.2f",M[indice_max][4]);
	sprintf(ch5_1,"%.2f",M[indice_max][5]);
	sprintf(ch6_1,"%.2f",M[indice_max][6]);
	sprintf(ch7_1,"%.2f",M[indice_max][7]);
	sprintf(ch8_1,"%.2f",M[indice_max][8]);
	sprintf(ch9_1,"%.2f",M[indice_max][9]);
	sprintf(ch10_1,"%.2f",M[indice_max][10]);
	sprintf(ch11_1,"%.2f",M[indice_max][11]);
	sprintf(ch12_1,"%.2f",M[indice_max][12]);
	sprintf(a0_1,"%.0f",M[indice_max][0]);
	sprintf(moy_13_1,"%.2f",M[indice_max][13]);

	gtk_label_set_text(GTK_LABEL(ao_1),a0_1);
	gtk_label_set_text(GTK_LABEL(m1_1),ch1_1);
	gtk_label_set_text(GTK_LABEL(m2_1),ch2_1);
	gtk_label_set_text(GTK_LABEL(m3_1),ch3_1);
	gtk_label_set_text(GTK_LABEL(m4_1),ch4_1);
	gtk_label_set_text(GTK_LABEL(m5_1),ch5_1);
	gtk_label_set_text(GTK_LABEL(m6_1),ch6_1);
	gtk_label_set_text(GTK_LABEL(m7_1),ch7_1);
	gtk_label_set_text(GTK_LABEL(m8_1),ch8_1);
	gtk_label_set_text(GTK_LABEL(m9_1),ch9_1);
	gtk_label_set_text(GTK_LABEL(m10_1),ch10_1);
	gtk_label_set_text(GTK_LABEL(m11_1),ch11_1);
	gtk_label_set_text(GTK_LABEL(m12_1),ch12_1);
	gtk_label_set_text(GTK_LABEL(moy13_1),moy_13_1);
	/*########################################*/
	float TAB1[200],rapport,val1,val2;
	int nb_total=0,indice1_max;
	FILE *f2;
	plante p;
	f2=fopen("Plantes.bin","rb");
	char rap_max_ch[20];
	plante TAB[200];
	while (fread (&p,sizeof (plante),1,f2) != 0){
		nb_total++;
		TAB[nb_total-1]=p;
		val1=p.quant.quantite_recolte;
		val2=p.quant.quantite;
		TAB1[nb_total-1]=(val1/val2)*100;

	}
	fclose(f2);

	indice1_max=0;
	for (i=1;i<nb_total;i++){
		if(TAB1[i]>TAB1[indice1_max]){
			indice1_max=i;
		}
		
	}
	GtkWidget *ref_max=lookup_widget(window1,"label_ref_max");
	GtkWidget *rap_max=lookup_widget(window1,"label_rapport");
				
	
	sprintf(rap_max_ch,"%.2f",TAB1[indice1_max]);

	gtk_label_set_text(GTK_LABEL(ref_max),TAB[indice1_max].reference);
	gtk_label_set_text(GTK_LABEL(rap_max),rap_max_ch);
}	
///////////////////


///////////////////



















