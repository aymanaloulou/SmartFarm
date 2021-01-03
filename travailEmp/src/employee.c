#include <stdlib.h>
#include <string.h>

#include <gtk/gtk.h>
#include "interface.h"
#include "support.h"
#include "employee.h"

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

enum{
	CINC,
	SECTC,
	DATE_DEB,
	DATE_FIN,
	RAISC,
	COLUMNSC
};


int verifCIN (char ch[]){
	employee c;
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
	f1=fopen("employee.bin","rb");

	while (fread (&c,sizeof (employee),1,f1) != 0) {
		
		if (strcmp (c.cin,ch) == 0) 
			 return 0;
	}
	fclose(f1);
	return 1;
	
}
/*
int verifCINExiste (char ch[]){
	ouvrier c;

	FILE* f1;
	f1=fopen("ouvrier.bin","rb");

	while (fread (&c,sizeof (employee),1,f1) != 0) {
		
		if (strcmp (c.cin,ch) == 0) 
			 return 1;
	}
	fclose(f1);
	return 0;
	
}*/

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

int fn_ajout_employee (employee e,GtkWidget *button){

   int ok = 1;

	GtkWidget *cin = lookup_widget (button,"label_cin_emp_inv");
	GtkWidget *nom = lookup_widget (button,"label_nom_emp_inv");
	GtkWidget *pren = lookup_widget (button,"label_pren_emp_inv");
	GtkWidget *genre = lookup_widget (button,"label_genre_emp_inv");
	GtkWidget *etat = lookup_widget (button,"label_etat_emp_inv");
	GtkWidget *num = lookup_widget (button,"label_num_tel_emp_inv");
	GtkWidget *adr = lookup_widget (button,"label_adr_emp_inv");
	GtkWidget *email = lookup_widget (button,"label_email_emp_inv");
	GtkWidget *secteur = lookup_widget (button,"label_secteur_emp_inv");	
	
	if (verifCIN (e.cin) == 0){
		ok = 0;
		gtk_label_set_text(GTK_LABEL(cin),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(cin),"");
	}

	if (nomValide (e.nom) == 0){	
		ok = 0;
		gtk_label_set_text(GTK_LABEL(nom),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(nom),"");
	}

	if (nomValide (e.pren) == 0){	
		ok = 0;
		gtk_label_set_text(GTK_LABEL(pren),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(pren),"");
	}
	
	if (strlen (e.genre) != 4 && strlen (e.genre) != 7){	
		ok = 0;
		gtk_label_set_text(GTK_LABEL(genre),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(genre),"");
	}

	if (strlen (e.etat_civil) == 0){	
		ok = 0;
		gtk_label_set_text(GTK_LABEL(etat),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(etat),"");
	}

	if (numValide (e.num_tel) == 0){	
		ok = 0;
		gtk_label_set_text(GTK_LABEL(num),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(num),"");
	}

	if (emailValide (e.email) == 0){	
		ok = 0;
		gtk_label_set_text(GTK_LABEL(email),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(email),"");
	}

	if (strlen (e.adr) == 0){	
		ok = 0;
		gtk_label_set_text(GTK_LABEL(adr),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(adr),"");
	}

	if (strlen (e.secteur) == 0){	
		ok = 0;
		gtk_label_set_text(GTK_LABEL(secteur),"X");	
	}	
	else{
		gtk_label_set_text(GTK_LABEL(secteur),"");
	}

	if (ok){
		FILE* f = fopen ("employee.bin","a+b");
		fwrite (&e,sizeof (employee),1,f);
		fclose (f);	
	}

	return ok;	

}

void fn_list_employee (GtkWidget *liste){

	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	employee o;
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

	f = fopen ("employee.bin","r+b");

	while (fread (&o,sizeof (employee),1,f) != 0){
		gtk_list_store_append (store, &iter);
		sprintf (date_naiss,"%d/%d/%d",o.date_nais.j,o.date_nais.m,o.date_nais.a);
		gtk_list_store_set (store, &iter, CIN, o.cin, NOM, o.nom, PREN, o.pren, DATE, date_naiss, ETAT, o.etat_civil, GENRE, o.genre, NUM, o.num_tel, ADR, o.adr, EMAIL, o.email, SECTEUR, o.secteur, -1);
	}

	fclose (f);
	gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
	g_object_unref (store);
		
}

void fn_supp_employee (char* cin_supp)
{
	employee m;
	FILE *s;
	FILE *s_tmp;

	s = fopen ("employee.bin","rb");
	s_tmp = fopen ("tmp.bin","ab");
	fseek (s,0,SEEK_SET);

	while (fread (&m,sizeof(employee),1,s)!=0)
		if (strcmp(m.cin,cin_supp) != 0)
			fwrite (&m,sizeof(employee),1,s_tmp);
	
	fclose (s);
	fclose (s_tmp);
	remove ("employee.bin");
	rename ("tmp.bin","employee.bin");
}


int fn_modif_employee (employee o,GtkWidget *button)  {
   	
	int ok = 1;

	GtkWidget *nom = lookup_widget (button,"label_nom_emp_inv");
	GtkWidget *pren = lookup_widget (button,"label_pren_emp_inv");
	GtkWidget *num = lookup_widget (button,"label_num_tel_emp_inv");
	GtkWidget *genre = lookup_widget (button,"label_genre_emp_inv");
	GtkWidget *etat = lookup_widget (button,"label_etat_emp_inv");
	GtkWidget *adr = lookup_widget (button,"label_adr_emp_inv");
	GtkWidget *email = lookup_widget (button,"label_email_emp_inv");
	GtkWidget *secteur = lookup_widget (button,"label_secteur_emp_inv");	

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

		FILE* f = fopen ("employee.bin","r+b");
		employee aux;int test = 0;int comp = 0;

		do{
			fread (&aux,sizeof (employee),1,f);
			if (strcmp (o.cin,aux.cin) == 0)
				test = 1;
			else 
				comp++;
		}while (test == 0);
		fseek (f,comp*sizeof(employee),SEEK_SET);
    		fwrite (&o,sizeof(employee),1,f);
		fclose (f);
	}

	return ok;
}



void fn_rech_employee (char *cin_rech, GtkWidget *liste){

	FILE* f = fopen ("employee.bin","r+b");
	employee aux;int test = 0;int comp = 0;
	char* sub = NULL;

	while (fread (&aux,sizeof (employee),1,f) != 0 && test == 0){
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

			fseek (f,comp*sizeof (employee),SEEK_SET);
			fread (&aux,sizeof (employee),1,f);
			sprintf (date_naiss,"%d/%d/%d",aux.date_nais.j,aux.date_nais.m,aux.date_nais.a);
			gtk_list_store_set (store, &iter, CIN, aux.cin, NOM, aux.nom, PREN, aux.pren, DATE, date_naiss, ETAT, aux.etat_civil, GENRE, aux.genre, NUM, aux.num_tel, ADR, aux.adr, EMAIL, aux.email, SECTEUR, aux.secteur, -1);
			fclose (f);
			gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
			g_object_unref (store);
			
	}
}



void fn_approuve_conge (congee c)
{
	congee m;
	FILE *s;
	FILE *s_tmp;
	FILE *capp;

	s = fopen ("conge.bin","rb");
	s_tmp = fopen ("tmp.bin","ab");
	capp = fopen ("conge_approuve.bin","ab");
	fseek (s,0,SEEK_SET);

	if (capp == NULL)
		capp = fopen ("conge_approuve.bin","w");

	while (fread (&m,sizeof(congee),1,s)!=0){
		if (strcmp(m.cin,c.cin) == 0 && m.date_deb.j == c.date_deb.j && m.date_deb.m == c.date_deb.m && c.date_deb.a == c.date_deb.a)
			fwrite(&c,sizeof(congee),1,capp);
		else
			fwrite (&m,sizeof(congee),1,s_tmp);
	}
	
	fclose (s);
	fclose (s_tmp);
	fclose (capp);
	remove ("conge.bin");
	rename ("tmp.bin","conge.bin");
}



void fn_list_conge (GtkWidget *liste){

	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	congee c;
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
	while (fread (&c,sizeof (congee),1,f) != 0){
		gtk_list_store_append (store, &iter);
		sprintf (de,"%d/%d/%d",c.date_deb.j,c.date_deb.m,c.date_deb.a);
		sprintf (jusqa,"%d/%d/%d",c.date_fin.j,c.date_fin.m,c.date_fin.a);
		
		gtk_list_store_set (store, &iter, CINC, c.cin, SECTC, c.secteur, DATE_DEB, de, DATE_FIN, jusqa, RAISC, c.rais, -1);
	}
	fclose (f);
	gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
	g_object_unref (store);
}



void fn_refuse_conge (congee c){
	congee m;
	FILE *s;
	FILE *s_tmp;

	s = fopen ("conge.bin","rb");
	s_tmp = fopen ("tmp.bin","ab");

	fseek (s,0,SEEK_SET);


	while (fread (&m,sizeof(congee),1,s)!=0){
		if (!(strcmp(m.cin,c.cin) == 0 && m.date_deb.j == c.date_deb.j && m.date_deb.m == c.date_deb.m && c.date_deb.a == c.date_deb.a))
			fwrite (&m,sizeof(congee),1,s_tmp);	
	}
	
	fclose (s);
	fclose (s_tmp);
	remove ("conge.bin");
	rename ("tmp.bin","conge.bin");
}

void fn_list_conge_approuve (GtkWidget *liste){
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	congee c;
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
	f = fopen ("conge_approuve.bin","r+b");
	if (f == NULL)
		f = fopen ("conge_approuve.bin","w");

	while (fread (&c,sizeof (congee),1,f) != 0){
		gtk_list_store_append (store, &iter);
		sprintf (de,"%d/%d/%d",c.date_deb.j,c.date_deb.m,c.date_deb.a);
		sprintf (jusqa,"%d/%d/%d",c.date_fin.j,c.date_fin.m,c.date_fin.a);
		
		gtk_list_store_set (store, &iter, CINC, c.cin, SECTC, c.secteur, DATE_DEB, de, DATE_FIN, jusqa, RAISC, c.rais, -1);
	}
	fclose (f);
	gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
	g_object_unref (store);
}