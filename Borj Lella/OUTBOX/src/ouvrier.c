#include <stdlib.h>
#include <string.h>

#include <gtk/gtk.h>
#include "interface.h"
#include "support.h"
#include "ouvrier.h"

enum
{
	CIN,
	NOM,
	PREN,
	DATE,
	ETAT,
	GENRE,
	NUM,
	ADR,
	EMAIL,
	SECTEUR,
	COLUMNS
};

enum
{
	CINP,
	NOMP,
	PRENP,
	DATEP,
	ABS,
	ENTRE_MATIN,
	SORTIE_MATIN,
	ENTRE_SOIR,
	SORTIE_SOIR,
	COLUMNSS
};

enum{
	CINC,
	SECTC,
	DATE_DEB,
	DATE_FIN,
	RAISC,
	COLUMNSC
};

int verifCIN (char ch[]){
	ouvrier c;
	
	
	
	int i;
	if (strlen (ch) != 8){
		return 0;
		
	}
	for (i=0;i<strlen(ch);i++)
		if (ch[i]<'0' || ch[i]>'9'){
			return 0;
		break;	
		}
	FILE* f1;
	f1=fopen("ouvrier.bin","rb");

	while (fread (&c,sizeof (ouvrier),1,f1) != 0) {
		
		if (strcmp (c.cin,ch) == 0) 
			 return 0;
	}
	fclose(f1);
	return 1;
	
}

int verifCINExiste (char ch[]){
	ouvrier c;

	FILE* f1;
	f1=fopen("ouvrier.bin","rb");

	while (fread (&c,sizeof (ouvrier),1,f1) != 0) {
		
		if (strcmp (c.cin,ch) == 0) 
			 return 1;
	}
	fclose(f1);
	return 0;
	
}

int nomValide (char ch[]){
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

int numValide (char ch[]){
	int i=0,ok = 1;
	if (strlen (ch) == 0){
		ok = 0;	
	}
	while (ok == 1 && i<strlen (ch)){
		if (ch[i]<'0' || ch[i] >'9')
			ok = 0;
			else
			i++; 	
			
		
	}
	return ok;
}
int pos (char c,char ch[]){
	int ok = -1,i = 0;
	while (ok == -1 && i<strlen (ch)){
		if (ch[i] == c)
			ok = i;
		else
			i++;
	}
	return ok;
}
int emailValide (char ch[]){
	if (pos ('@',ch)<1)
		return 0;
	if (pos ('.',ch)<3)
		return 0;
	return 1;
}

int fn_ajout_ouvrier (ouvrier o,GtkWidget *button){	
	int ok = 1;

	GtkWidget *cin = lookup_widget (button,"label_cin_ouv_inv");
	GtkWidget *nom = lookup_widget (button,"label_nom_ouv_inv");
	GtkWidget *pren = lookup_widget (button,"label_pren_ouv_inv");
	GtkWidget *genre = lookup_widget (button,"label_genre_ouv_inv");
	GtkWidget *etat = lookup_widget (button,"label_etat_ouv_inv");
	GtkWidget *num = lookup_widget (button,"label_num_tel_ouv_inv");
	GtkWidget *adr = lookup_widget (button,"label_adr_ouv_inv");
	GtkWidget *email = lookup_widget (button,"label_email_ouv_inv");
	GtkWidget *secteur = lookup_widget (button,"label_secteur_ouv_inv");	
	
	if (verifCIN (o.cin) == 0){
		ok = 0;
		gtk_label_set_text(GTK_LABEL(cin),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(cin),"");
	}

	if (nomValide (o.nom) == 0){	
		ok = 0;
		gtk_label_set_text(GTK_LABEL(nom),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(nom),"");
	}

	if (nomValide (o.pren) == 0){	
		ok = 0;
		gtk_label_set_text(GTK_LABEL(pren),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(pren),"");
	}
	
	if (strlen (o.genre) != 4 && strlen (o.genre) != 7){	
		ok = 0;
		gtk_label_set_text(GTK_LABEL(genre),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(genre),"");
	}

	if (strlen (o.etat_civil) == 0){	
		ok = 0;
		gtk_label_set_text(GTK_LABEL(etat),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(etat),"");
	}

	if (numValide (o.num_tel) == 0){	
		ok = 0;
		gtk_label_set_text(GTK_LABEL(num),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(num),"");
	}

	if (emailValide (o.email) == 0){	
		ok = 0;
		gtk_label_set_text(GTK_LABEL(email),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(email),"");
	}

	if (strlen (o.adr) == 0){	
		ok = 0;
		gtk_label_set_text(GTK_LABEL(adr),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(adr),"");
	}

	if (strlen (o.secteur) == 0){	
		ok = 0;
		gtk_label_set_text(GTK_LABEL(secteur),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(secteur),"");
	}

	if (ok){
		FILE* f = fopen ("ouvrier.bin","a+b");
		fwrite (&o,sizeof (ouvrier),1,f);
		fclose (f);	
	}

	return ok;	
}


void fn_list_ouvrier (GtkWidget *liste){

	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	ouvrier o;
	char date_naiss[15];
	FILE *f;
	
	
	store = NULL;
	store = gtk_tree_view_get_model(liste);
	
	if (store == NULL){
		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (" CIN",renderer,"text",CIN,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (" Nom",renderer,"text",NOM,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (" Prenom",renderer,"text",PREN,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (" Date de naissance",renderer,"text",DATE,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (" Etat civil",renderer,"text",ETAT,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (" Genre",renderer,"text",GENRE,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (" Numero telephone",renderer,"text",NUM,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (" Adresse",renderer,"text",ADR,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (" Email",renderer,"text",EMAIL,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (" Secteur",renderer,"text",SECTEUR,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	}

		store = gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
		
		f = fopen ("ouvrier.bin","r+b");
		
			while (fread (&o,sizeof (ouvrier),1,f) != 0){
				gtk_list_store_append (store, &iter);
				sprintf (date_naiss,"%d/%d/%d",o.date_nais.j,o.date_nais.m,o.date_nais.a);
				gtk_list_store_set (store, &iter, CIN, o.cin, NOM, o.nom, PREN, o.pren, DATE, date_naiss, ETAT, o.etat_civil, GENRE, o.genre, NUM, o.num_tel, ADR, o.adr, EMAIL, o.email, SECTEUR, o.secteur, -1);

			}
			fclose (f);
			gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
			g_object_unref (store);
		


}



void fn_supp_ouvrier (char* cin_supp)
{
	ouvrier m;
	FILE *s;
	FILE *s_tmp;

	s = fopen ("ouvrier.bin","rb");
	s_tmp = fopen ("tmp.bin","ab");
	fseek (s,0,SEEK_SET);

	while (fread (&m,sizeof(ouvrier),1,s)!=0)
		if (strcmp(m.cin,cin_supp) != 0)
			fwrite (&m,sizeof(ouvrier),1,s_tmp);
	
	fclose (s);
	fclose (s_tmp);
	remove ("ouvrier.bin");
	rename ("tmp.bin","ouvrier.bin");
}

int fn_modif_ouvrier (ouvrier o,GtkWidget *button)  {
   	
	int ok = 1;

	GtkWidget *nom = lookup_widget (button,"label_nom_ouv_inv");
	GtkWidget *pren = lookup_widget (button,"label_pren_ouv_inv");
	GtkWidget *num = lookup_widget (button,"label_num_tel_ouv_inv");
	GtkWidget *genre = lookup_widget (button,"label_genre_ouv_inv");
	GtkWidget *etat = lookup_widget (button,"label_etat_ouv_inv");
	GtkWidget *adr = lookup_widget (button,"label_adr_ouv_inv");
	GtkWidget *email = lookup_widget (button,"label_email_ouv_inv");
	GtkWidget *secteur = lookup_widget (button,"label_secteur_ouv_inv");	

	if (nomValide (o.nom) == 0){	
		ok = 0;
		gtk_label_set_text(GTK_LABEL(nom),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(nom),"");
	}

	if (nomValide (o.pren) == 0){	
		ok = 0;
		gtk_label_set_text(GTK_LABEL(pren),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(pren),"");
	}

	if (strlen (o.genre) != 4 && strlen (o.genre) != 7){	
		ok = 0;
		gtk_label_set_text(GTK_LABEL(genre),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(genre),"");
	}

	if (strlen (o.etat_civil) == 0){	
		ok = 0;
		gtk_label_set_text(GTK_LABEL(etat),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(etat),"");
	}
	
	if (numValide (o.num_tel) == 0){	
		ok = 0;
		gtk_label_set_text(GTK_LABEL(num),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(num),"");
	}

	if (emailValide (o.email) == 0){	
		ok = 0;
		gtk_label_set_text(GTK_LABEL(email),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(email),"");
	}

	if (strlen (o.adr) == 0){	
		ok = 0;
		gtk_label_set_text(GTK_LABEL(adr),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(adr),"");
	}

	if (strlen (o.secteur) == 0){	
		ok = 0;
		gtk_label_set_text(GTK_LABEL(secteur),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(secteur),"");
	}

	if (ok){

		FILE* f = fopen ("ouvrier.bin","r+b");
		ouvrier aux;int test = 0;int comp = 0;

		/*while (fread (&aux,sizeof (ouvrier),1,f) != 0 && test == 0){
			if (strcmp (o.cin,aux.cin) == 0)
				test = 1;
			else 
				comp++;
		}*/

		do{
			fread (&aux,sizeof (ouvrier),1,f);
			if (strcmp (o.cin,aux.cin) == 0)
				test = 1;
			else 
				comp++;
		}while (test == 0);
		fseek (f,comp*sizeof(ouvrier),SEEK_SET);
    		fwrite (&o,sizeof(ouvrier),1,f);
		fclose (f);
	}

	return ok;
}


void fn_rech_ouvrier (char *cin_rech, GtkWidget *liste){

	FILE* f = fopen ("ouvrier.bin","r+b");
	ouvrier aux;int test = 0;int comp = 0;
	char* sub = NULL;

	while (fread (&aux,sizeof (ouvrier),1,f) != 0 && test == 0){
		sub = strstr (aux.cin,cin_rech);
		if (sub != NULL)
			test = 1;
		else 
			comp++;
	}

	if (test){
		GtkCellRenderer *renderer;
		GtkTreeViewColumn *column;
		GtkTreeIter iter;
		GtkListStore *store;
		char date_naiss[15];

		store = NULL;
		store = gtk_tree_view_get_model(liste);
/*
			renderer = gtk_cell_renderer_text_new ();
			column = gtk_tree_view_column_new_with_attributes (" CIN",renderer,"text",CIN,NULL);
			gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

			renderer = gtk_cell_renderer_text_new ();
			column = gtk_tree_view_column_new_with_attributes (" Nom",renderer,"text",NOM,NULL);
			gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

			renderer = gtk_cell_renderer_text_new ();
			column = gtk_tree_view_column_new_with_attributes (" Prenom",renderer,"text",PREN,NULL);
			gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

			renderer = gtk_cell_renderer_text_new ();
			column = gtk_tree_view_column_new_with_attributes (" Date de naissance",renderer,"text",DATE,NULL);
			gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

			renderer = gtk_cell_renderer_text_new ();
			column = gtk_tree_view_column_new_with_attributes (" Etat civil",renderer,"text",ETAT,NULL);
			gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

			renderer = gtk_cell_renderer_text_new ();
			column = gtk_tree_view_column_new_with_attributes (" Genre",renderer,"text",GENRE,NULL);
			gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

			renderer = gtk_cell_renderer_text_new ();
			column = gtk_tree_view_column_new_with_attributes (" Numero telephone",renderer,"text",NUM,NULL);
			gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

			renderer = gtk_cell_renderer_text_new ();
			column = gtk_tree_view_column_new_with_attributes (" Adresse",renderer,"text",ADR,NULL);
			gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

			renderer = gtk_cell_renderer_text_new ();
			column = gtk_tree_view_column_new_with_attributes (" Email",renderer,"text",EMAIL,NULL);
			gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

			renderer = gtk_cell_renderer_text_new ();
			column = gtk_tree_view_column_new_with_attributes (" Secteur",renderer,"text",SECTEUR,NULL);
			gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
*/
			store = gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

			gtk_list_store_append (store, &iter);

			fseek (f,comp*sizeof (ouvrier),SEEK_SET);
			fread (&aux,sizeof (ouvrier),1,f);
			sprintf (date_naiss,"%d/%d/%d",aux.date_nais.j,aux.date_nais.m,aux.date_nais.a);
			gtk_list_store_set (store, &iter, CIN, aux.cin, NOM, aux.nom, PREN, aux.pren, DATE, date_naiss, ETAT, aux.etat_civil, GENRE, aux.genre, NUM, aux.num_tel, ADR, aux.adr, EMAIL, aux.email, SECTEUR, aux.secteur, -1);
			fclose (f);
			gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
			g_object_unref (store);
			
	}
}


void fn_ajout_point (pointage p,GtkWidget *button){
	
	FILE *f = fopen ("pointage.bin","rb");
	GtkWidget *warning = lookup_widget (button, "label_warning");
	pointage aux;
	int test = 0;

	if (f == NULL)
	{
		f = fopen ("pointage.bin","w");
	}
	else{
		while (fread (&aux,sizeof (pointage),1,f) != 0) {
			if (strcmp (aux.cin,p.cin) == 0 && aux.date_point.a == p.date_point.a && aux.date_point.m == p.date_point.m && aux.date_point.j == p.date_point.j)  
				test = 1;
		}
	}
	fclose (f);

	if (test == 1){
		gtk_label_set_text(GTK_LABEL(warning),"CIN deja ajouté dans cette date utiliser la zone de modification");
	}
	else
	{
		f = fopen ("pointage.bin","ab");
		fwrite (&p,sizeof (pointage),1,f);
		fclose (f);
		gtk_label_set_text(GTK_LABEL(warning),"");
	}

}



void fn_list_point (GtkWidget *liste){

	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	pointage p;
	char date[15];
	char pres[15];
	char em[10];
	char sm[10];
	char es[10];
	char ss[10];
	FILE *f;
	
	store = NULL;
	store = gtk_tree_view_get_model(liste);

	if (store == NULL){
		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (" CIN",renderer,"text",CIN,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (" NOM",renderer,"text",NOM,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (" Prenom",renderer,"text",PREN,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (" Présence",renderer,"text",ABS,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (" Date pointage",renderer,"text",DATEP,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (" Entrée matin",renderer,"text",ENTRE_MATIN,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (" Sortie matin",renderer,"text",SORTIE_MATIN,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (" Entrée soir",renderer,"text",ENTRE_SOIR,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (" Sortie soir",renderer,"text",SORTIE_SOIR,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	}

	store = gtk_list_store_new (COLUMNSS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING, G_TYPE_STRING);
		
	f = fopen ("pointage.bin","r+b");

	while (fread (&p,sizeof (pointage),1,f) != 0){
		gtk_list_store_append (store, &iter);
		sprintf (date,"%d/%d/%d",p.date_point.j,p.date_point.m,p.date_point.a);
		sprintf (em,"%d:%d",p.entre_matin.h,p.entre_matin.m);
		sprintf (sm,"%d:%d",p.sort_matin.h,p.sort_matin.m);
		sprintf (es,"%d:%d",p.entre_soir.h,p.entre_soir.m);
		sprintf (ss,"%d:%d",p.sort_soir.h,p.sort_soir.m);
		if (p.abs == 1)
			strcpy (pres,"Présent");
		else
			strcpy (pres,"Absence");
		
		gtk_list_store_set (store, &iter, CINP, p.cin, NOMP, p.nom, PRENP, p.pren, DATEP, date, ABS, pres, ENTRE_MATIN, em, SORTIE_MATIN, sm, ENTRE_SOIR, es, SORTIE_SOIR, ss, -1);
	}
	fclose (f);
	gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
	g_object_unref (store);

}

void fn_rech_point (char *rech, GtkWidget *liste){

	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	pointage p;
	char date[15];
	char pres[15];
	char em[10];
	char sm[10];
	char es[10];
	char ss[10];
	FILE *f;
	
	store = NULL;
	store = gtk_tree_view_get_model(liste);

	if (store == NULL){
		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (" CIN",renderer,"text",CIN,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (" NOM",renderer,"text",NOM,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (" Prenom",renderer,"text",PREN,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (" Présence",renderer,"text",ABS,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (" Date pointage",renderer,"text",DATEP,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (" Entrée matin",renderer,"text",ENTRE_MATIN,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (" Sortie matin",renderer,"text",SORTIE_MATIN,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (" Entrée soir",renderer,"text",ENTRE_SOIR,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (" Sortie soir",renderer,"text",SORTIE_SOIR,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	}

	store = gtk_list_store_new (COLUMNSS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING, G_TYPE_STRING);
		
	f = fopen ("pointage.bin","r+b");

	while (fread (&p,sizeof (pointage),1,f) != 0){
		sprintf (date,"%d/%d/%d",p.date_point.j,p.date_point.m,p.date_point.a);
		if (strcmp (date,rech) == 0){
			gtk_list_store_append (store, &iter);
			sprintf (em,"%d:%d",p.entre_matin.h,p.entre_matin.m);
			sprintf (sm,"%d:%d",p.sort_matin.h,p.sort_matin.m);
			sprintf (es,"%d:%d",p.entre_soir.h,p.entre_soir.m);
			sprintf (ss,"%d:%d",p.sort_soir.h,p.sort_soir.m);
			if (p.abs == 0)
				strcpy (pres,"Présent");
			else
				strcpy (pres,"Absence");
			
			gtk_list_store_set (store, &iter, CINP, p.cin, NOMP, p.nom, PRENP, p.pren, DATEP, date, ABS, pres, ENTRE_MATIN, em, SORTIE_MATIN, sm, ENTRE_SOIR, es, SORTIE_SOIR, ss, -1);
		}
	}
	fclose (f);
	gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
	g_object_unref (store);

}


void fn_modif_point (pointage p){

	int test =0;
	int cmp = 0;
	pointage aux;
	FILE* f = fopen ("pointage.bin","r+b");

	do{
		fread (&aux,sizeof (pointage),1,f);
		if (strcmp (aux.cin,p.cin) == 0 && aux.date_point.a == p.date_point.a && aux.date_point.m == p.date_point.m && aux.date_point.j == p.date_point.j)
			test = 1;
		else 
			cmp++;
	}while (test == 0);
	fseek (f,cmp*sizeof(pointage),SEEK_SET);
	fwrite (&p,sizeof (pointage),1,f);
	fclose (f);
}

int fn_demande_conge (conge c,GtkWidget *button){

	GtkWidget *cin_i = lookup_widget (button,"label_cinc_inv");
	GtkWidget *sect_i = lookup_widget (button,"label_sectc_inv");
	int ok = 1;

	if (verifCINExiste (c.cin) == 0){
		ok = 0;
		gtk_label_set_text(GTK_LABEL(cin_i),"X");	
	}
	else{
		gtk_label_set_text(GTK_LABEL(cin_i),"");
	}

	if (strlen (c.secteur) == 0){	
		ok = 0;
		gtk_label_set_text(GTK_LABEL(sect_i),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(sect_i),"");
	}

	if (ok){
		FILE *f = fopen ("conge.bin","ab");
		if (f == NULL)
			f = fopen ("conge.bin","w");
		fwrite (&c,sizeof (conge),1,f);
		fclose (f);
	}

	return ok;

}

void fn_list_conge (GtkWidget *liste){

	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	conge c;
	char de[15];
	char jusqa[15];
	FILE *f;
	
	store = NULL;
	store = gtk_tree_view_get_model(liste);

	if (store == NULL){
		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (" CIN",renderer,"text",CINC,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (" Secteur",renderer,"text",SECTC,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (" Date début",renderer,"text",DATE_DEB,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (" Date fin",renderer,"text",DATE_FIN,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (" Raison",renderer,"text",RAISC,NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	}

	store = gtk_list_store_new (COLUMNSC, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	f = fopen ("conge.bin","r+b");
	while (fread (&c,sizeof (conge),1,f) != 0){
		gtk_list_store_append (store, &iter);
		sprintf (de,"%d/%d/%d",c.date_deb.j,c.date_deb.m,c.date_deb.a);
		sprintf (jusqa,"%d/%d/%d",c.date_fin.j,c.date_fin.m,c.date_fin.a);
		
		gtk_list_store_set (store, &iter, CINC, c.cin, SECTC, c.secteur, DATE_DEB, de, DATE_FIN, jusqa, RAISC, c.rais, -1);
	}
	fclose (f);
	gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
	g_object_unref (store);
}


int fn_pos_tab (char *rech,best *t,int n){
	int i;
	for (i=0;i<n;i++){
		if (strcmp (rech,t[i].p.cin) == 0){
			return i;break;
		}
	}
	return -1;
}

best fn_max (best *t,int n){
	int i;
	best max = t[0];
	for (i=0;i<n;i++)
	if (max.nb_heures < t[i].nb_heures){
		max = t[i];
	}
	return max;

}

int fn_nb_ouv (){
	FILE *f = fopen ("ouvrier.bin","rb");
	int nb = 0;
	ouvrier a;
	while (fread (&a,sizeof (ouvrier),1,f) != 0)
		nb++;
	return nb;
	fclose (f);
}

void fn_meilleur_ouvrier (struct date be, GtkWidget *button){

	int taille = fn_nb_ouv ();
	pointage aux;
	best *t = malloc (taille*sizeof (best));
	FILE *f = fopen ("pointage.bin","rb");
	int n = 0,ind;

	while (fread (&aux,sizeof (pointage),1,f) != 0)
		if (be.m == aux.date_point.m && be.a == aux.date_point.a){
			ind = fn_pos_tab (aux.cin,t,n);
			if (ind == -1){
				n++;
				t[n-1].p = aux;
				if (aux.abs != 1){
					t[n-1].nb_abs = 1;
					t[n-1].nb_heures = 0;
				}
				else{
					t[n-1].nb_heures = ((aux.sort_matin.h*60 + aux.sort_matin.m - aux.entre_matin.h*60 - aux.entre_matin.m + aux.sort_soir.h*60 + aux.sort_soir.m - aux.entre_soir.h*60 - aux.entre_soir.m)/60);
					t[n-1].nb_abs = 0;
				}
			}
			else{
				if (aux.abs != 1)
					t[ind].nb_abs += 1;
				else 
					t[ind].nb_heures += ((aux.sort_matin.h*60 + aux.sort_matin.m - aux.entre_matin.h*60 - aux.entre_matin.m + aux.sort_soir.h*60 + aux.sort_soir.m - aux.entre_soir.h*60 - aux.entre_soir.m)/60);
			}
		}
	
	if (n != 0){
		best ouv_mois = fn_max (t,n);

		GtkWidget *date_o, *cin_o, *nom_o, *pren_o, *nbh_o, *nbabs_o;
		date_o = lookup_widget (button, "label_bo_date");
		cin_o = lookup_widget (button, "label_bo_cin");
		nom_o = lookup_widget (button, "label_bo_nom");
		pren_o = lookup_widget (button, "label_bo_pren");
		nbh_o = lookup_widget (button, "label_bo_nb_heures");
		nbabs_o = lookup_widget (button, "label_bo_nb_abs");
		char d[10];
		sprintf (d,"%d/%d",be.m,be.a);
		char nbh[10];
		sprintf (nbh,"%d",ouv_mois.nb_heures);
		char nba[10];
		sprintf (nba,"%d",ouv_mois.nb_abs);

		gtk_label_set_text(GTK_LABEL(date_o),d);
		gtk_label_set_text(GTK_LABEL(cin_o),ouv_mois.p.cin);
		gtk_label_set_text(GTK_LABEL(nom_o),ouv_mois.p.nom);
		gtk_label_set_text(GTK_LABEL(pren_o),ouv_mois.p.pren);
		gtk_label_set_text(GTK_LABEL(nbh_o),nbh);
		gtk_label_set_text(GTK_LABEL(nbabs_o),nba);
	}
	fclose (f);

}

void fn_taux_abs (struct date be, GtkWidget *button){
	
	int nbh_abs =0;
	FILE *f = fopen ("pointage.bin","rb");
	pointage aux;
	int e;
	while (fread (&aux,sizeof (pointage),1,f) != 0)
		if (be.m == aux.date_point.m && be.a == aux.date_point.a && aux.abs == 0)
			nbh_abs += 8;
	
	if (nbh_abs != 0){

		char nb[8];char ta[15];
		sprintf (nb,"%d",nbh_abs);

		char d[10];
		float y = nbh_abs;
		float x = (y/(8*22))*100;
		sprintf (d,"%d/%d",be.m,be.a);
		sprintf (ta,"%.2f",x);

		GtkWidget *out1, *out2, *out3;
		out1 = lookup_widget (button, "label_date_ta");
		out2 = lookup_widget (button, "label_nbh");
		out3 = lookup_widget (button, "label_ta");

		gtk_label_set_text(GTK_LABEL(out1),d);
		gtk_label_set_text(GTK_LABEL(out2),nb);
		gtk_label_set_text(GTK_LABEL(out3),ta);	
	}
	fclose (f);
}
