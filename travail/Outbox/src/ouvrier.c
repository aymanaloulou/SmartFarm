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

		store = gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
		
		f = fopen ("ouvrier.bin","r+b");
		
			while (fread (&o,sizeof (ouvrier),1,f) != 0){
				gtk_list_store_append (store, &iter);
				sprintf (date_naiss,"%d/%d/%d",o.date_nais.j,o.date_nais.m,o.date_nais.a);
				/*(strlen (o.genre) != 4 && strlen (o.genre) != 7)
					strcpy (o.genre,"Male");*/
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

	while (fread (&aux,sizeof (ouvrier),1,f) != 0 && test == 0){
		if (strcmp (cin_rech,aux.cin) == 0)
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

			store = gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

			gtk_list_store_append (store, &iter);

			fseek (f,comp*sizeof (ouvrier),SEEK_SET);
			fread (&aux,sizeof (ouvrier),1,f);
			sprintf (date_naiss,"%d/%d/%d",aux.date_nais.j,aux.date_nais.m,aux.date_nais.a);
			/*if (strlen (aux.genre) != 4 && strlen (aux.genre) != 7)
				strcpy (aux.genre,"Male");*/
			gtk_list_store_set (store, &iter, CIN, aux.cin, NOM, aux.nom, PREN, aux.pren, DATE, date_naiss, ETAT, aux.etat_civil, GENRE, aux.genre, NUM, aux.num_tel, ADR, aux.adr, EMAIL, aux.email, SECTEUR, aux.secteur, -1);
			fclose (f);
			gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
			g_object_unref (store);
			
	}
}
