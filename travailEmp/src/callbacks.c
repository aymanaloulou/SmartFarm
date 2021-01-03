#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "employee.h"

employee e,em;
congee cc;
char cin_supp[9];



void
on_button_ajout_emp_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *dialog = create_dialog_ajout_emp();
	gtk_widget_show(dialog);
}


void
on_cancelbutton_ajout_emp_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *dialog = lookup_widget(button,"dialog_ajout_emp");
	gtk_widget_destroy(dialog);
}

void
on_radiobutton_emp_femelle_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
	strcpy (e.genre,"Femelle");
	strcpy (em.genre,"Femelle");
}

void
on_radiobutton_emp_male_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
	strcpy (e.genre,"Male");
	strcpy (em.genre,"Male");
}


void
on_okbutton_ajout_emp_clicked          (GtkWidget       *button,
                                        gpointer         user_data)
{
    GtkWidget *input_nom,*input_pren,*input_cin,*input_j,*input_m,*input_a,*input_etat,*input_num_tel,*input_adr,*input_email,*input_secteur;
	GtkWidget *dialog = lookup_widget(button,"dialog_ajout_emp");

	
	input_nom = lookup_widget(button, "entry_nom_emp");
	input_pren = lookup_widget(button, "entry_pren_emp");
	input_cin = lookup_widget(button, "entry_cin_emp");
	input_j = lookup_widget(button, "spinbutton_jour_nais_emp");
	input_m = lookup_widget(button, "spinbutton_mois_nais_emp");
	input_a = lookup_widget(button, "spinbutton_annee_nais_emp");
	input_etat = lookup_widget(button, "comboboxentry_etat_civil_emp");
	input_num_tel = lookup_widget(button, "entry_num_tel_emp");	
	input_adr = lookup_widget(button, "entry_adr_emp");
	input_email = lookup_widget(button, "entry_email_emp");
	input_secteur = lookup_widget(button, "entry_secteur_emp");

	strcpy(e.nom,gtk_entry_get_text(GTK_ENTRY(input_nom)));
	strcpy(e.pren,gtk_entry_get_text(GTK_ENTRY(input_pren)));
	strcpy(e.cin,gtk_entry_get_text(GTK_ENTRY(input_cin)));
	e.date_nais.j = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_j));
	e.date_nais.m = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_m));
	e.date_nais.a = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_a));
	strcpy(e.etat_civil,gtk_combo_box_get_active_text(GTK_COMBO_BOX(input_etat)));
	strcpy(e.num_tel,gtk_entry_get_text(GTK_ENTRY(input_num_tel)));
	strcpy(e.adr,gtk_entry_get_text(GTK_ENTRY(input_adr)));
	strcpy(e.email,gtk_entry_get_text(GTK_ENTRY(input_email)));
	strcpy(e.secteur,gtk_entry_get_text(GTK_ENTRY(input_secteur)));

	if(fn_ajout_employee (e,button))
		gtk_widget_destroy(dialog);
}






void
on_button_liste_emp_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{

	GtkWidget *treeview_liste_emp;

	treeview_liste_emp = lookup_widget (button, "treeview_liste_emp");
	
	fn_list_employee (treeview_liste_emp);

}


void
on_button_supp_emp_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *label = lookup_widget (button,"cin");
	GtkWidget *treeview = lookup_widget (button, "treeview_liste_emp"); 
	if (strlen (cin_supp) == 8){
		fn_supp_employee (cin_supp);
		gtk_label_set_text(GTK_LABEL(label),"");
		fn_list_employee (treeview);
		strcpy (cin_supp,"");
		strcpy (em.cin,"");
	}
	else{
		gtk_label_set_text(GTK_LABEL(label),"Double click sur un ouvrier");
	}
}


void
on_treeview_liste_emp_row_activated    (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	GtkTreeIter iter;
	char* cinm;
	char* nomm;
	char* prenm;
	char* datem;
	char* genrem;
	char* etatm;
	char* numm;
	char* adrm;
	char* emailm;
	char* secteurm;

	GtkTreeModel *model = gtk_tree_view_get_model (treeview);

	if (gtk_tree_model_get_iter (model, &iter, path)){
		gtk_tree_model_get (GTK_LIST_STORE (model), &iter, 0, &cinm, 1, &nomm, 2, &prenm, 3, &datem, 4, &genrem, 5, &etatm, 6, &numm, 7, &adrm, 8, &emailm, 9, &secteurm,-1);
		strcpy (em.cin, cinm);
		strcpy (em.nom, nomm);
		strcpy (em.pren, prenm);
		strcpy (em.genre, genrem);
		strcpy (em.etat_civil, etatm);
		strcpy (em.num_tel, numm);
		strcpy (em.adr, adrm);
		strcpy (em.email, emailm);
		strcpy (em.secteur, secteurm);
		strcpy (cin_supp, em.cin);
		sscanf (datem,"%d/%d/%d",&em.date_nais.j,&em.date_nais.m,&em.date_nais.a);
	}

}


void
on_button_modif_emp_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{

	GtkWidget *dialog = create_dialog_modif_emp();
	GtkWidget *label = lookup_widget (button,"cin");
	GtkWidget *io_cin, *io_nom, *io_pren, *io_num_tel, *io_adr,*io_genre, *io_email, *io_secteur;
	GtkSpinButton *io_j, *io_m, *io_a;
   
	if (strlen (em.cin) == 8){
		gtk_widget_show(dialog);
		io_nom = lookup_widget(dialog, "entry_nomm_emp");
		io_pren = lookup_widget(dialog, "entry_prenm_emp");
		io_cin = lookup_widget(dialog, "label_cinm_emp");
		io_j = lookup_widget(dialog, "spinbutton_jourm_nais_emp");
		io_m = lookup_widget(dialog, "spinbutton_moism_nais_emp");
		io_a = lookup_widget(dialog, "spinbutton_anneem_nais_emp");
		io_num_tel = lookup_widget(dialog, "entry_numm_tel_emp");	
		io_adr = lookup_widget(dialog, "entry_adrm_emp");
		io_email = lookup_widget(dialog, "entry_emailm_emp");
		io_secteur = lookup_widget(dialog, "entry_secteurm_emp");
		
		gtk_entry_set_text(GTK_ENTRY(io_nom),em.nom);
		gtk_entry_set_text(GTK_ENTRY(io_pren),em.pren);
		gtk_label_set_text(GTK_LABEL(io_cin),em.cin);
		gtk_spin_button_set_value(io_j,em.date_nais.j);
		gtk_spin_button_set_value(io_m,em.date_nais.m);
		gtk_spin_button_set_value(io_a,em.date_nais.a);
		gtk_entry_set_text(GTK_ENTRY(io_num_tel),em.num_tel);
		gtk_entry_set_text(GTK_ENTRY(io_adr),em.adr);
		gtk_entry_set_text(GTK_ENTRY(io_email),em.email);
		gtk_entry_set_text(GTK_ENTRY(io_secteur),em.secteur);
		gtk_label_set_text(GTK_LABEL(label),"");
	}
	else{
		gtk_label_set_text(GTK_LABEL(label),"Double click sur un ouvrier");
	}

}


void
on_cancelbutton_modif_emp_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *dialog = lookup_widget(button,"dialog_modif_emp");
	gtk_widget_destroy(dialog);
	strcpy (em.cin,"");
}


void
on_okbutton_modif_emp_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *dialog = lookup_widget(button,"dialog_modif_emp");
	GtkWidget *input_nom,*input_pren,*input_cin,*input_j,*input_m,*input_a,*input_etat,*input_num_tel,*input_adr,*input_email,*input_secteur;

	
	input_nom = lookup_widget(button, "entry_nomm_emp");
	input_pren = lookup_widget(button, "entry_prenm_emp");
	input_j = lookup_widget(button, "spinbutton_jourm_nais_emp");
	input_m = lookup_widget(button, "spinbutton_moism_nais_emp");
	input_a = lookup_widget(button, "spinbutton_anneem_nais_emp");
	input_etat = lookup_widget(button, "comboboxentry_etatm_civil_emp");
	input_num_tel = lookup_widget(button, "entry_numm_tel_emp");	
	input_adr = lookup_widget(button, "entry_adrm_emp");
	input_email = lookup_widget(button, "entry_emailm_emp");
	input_secteur = lookup_widget(button, "entry_secteurm_emp");

	strcpy(em.nom,gtk_entry_get_text(GTK_ENTRY(input_nom)));
	strcpy(em.pren,gtk_entry_get_text(GTK_ENTRY(input_pren)));
	em.date_nais.j = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_j));
	em.date_nais.m = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_m));
	em.date_nais.a = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_a));
	strcpy(em.etat_civil,gtk_combo_box_get_active_text(GTK_COMBO_BOX(input_etat)));
	strcpy(em.num_tel,gtk_entry_get_text(GTK_ENTRY(input_num_tel)));
	strcpy(em.adr,gtk_entry_get_text(GTK_ENTRY(input_adr)));
	strcpy(em.email,gtk_entry_get_text(GTK_ENTRY(input_email)));
	strcpy(em.secteur,gtk_entry_get_text(GTK_ENTRY(input_secteur)));

	if (fn_modif_employee (em,button)){
		gtk_widget_destroy(dialog);
		strcpy (em.cin,""); 
	}
}


void
on_button_rech_emp_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *treeview_liste_emp, *cin_input;
	char cin_rech[9];

	treeview_liste_emp = lookup_widget (button, "treeview_liste_emp");
	cin_input = lookup_widget (button, "entry_cin_emp_rech");

	strcpy (cin_rech,gtk_entry_get_text(GTK_ENTRY(cin_input)));

	fn_rech_employee (cin_rech,treeview_liste_emp);
}


void
on_treeview_liste_conge_row_activated  (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	GtkTreeIter iter;
	char* cin;
	char* sect;
	char* deb;
	char* fin;
	char* rais;

	GtkTreeModel *model = gtk_tree_view_get_model (treeview);

	if (gtk_tree_model_get_iter (model, &iter, path)){
		gtk_tree_model_get (GTK_LIST_STORE (model), &iter, 0, &cin, 1, &sect, 2, &deb, 3, &fin, 4, &rais,-1);
		strcpy (cc.cin, cin);
		strcpy (cc.secteur, sect);
		strcpy (cc.rais, rais);
		sscanf (deb,"%d/%d/%d",&cc.date_deb.j,&cc.date_deb.m,&cc.date_deb.a);
		sscanf (fin,"%d/%d/%d",&cc.date_fin.j,&cc.date_fin.m,&cc.date_fin.a);
	}

}


void
on_button_valid_cong_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *label = lookup_widget (button,"select_conge");
	GtkWidget *treeview_liste_conge_valide;
	treeview_liste_conge_valide = lookup_widget (button, "treeview_liste_conge_valide");
	GtkWidget *treeview = lookup_widget (button, "treeview_liste_conge"); 
	if (strlen (cc.cin) == 8){
		fn_approuve_conge (cc);
		gtk_label_set_text(GTK_LABEL(label),"");
		fn_list_conge (treeview);
		fn_list_conge_approuve (treeview_liste_conge_valide);
		strcpy (cc.cin,"");
	}
	else{
		gtk_label_set_text(GTK_LABEL(label),"Double click sur une demande");
	}
}


void
on_button_liste_conge_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *treeview_liste_conge;

	treeview_liste_conge = lookup_widget (button, "treeview_liste_conge");
	
	fn_list_conge (treeview_liste_conge);
}


void
on_button_liste_conge_valide_clicked   (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *treeview_liste_conge_valide;

	treeview_liste_conge_valide = lookup_widget (button, "treeview_liste_conge_valide");
	
	fn_list_conge_approuve (treeview_liste_conge_valide);
}


void
on_button_supp_conge_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *label = lookup_widget (button,"select_conge");
	GtkWidget *treeview = lookup_widget (button, "treeview_liste_conge"); 
	if (strlen (cc.cin) == 8){
		fn_refuse_conge (cc);
		gtk_label_set_text(GTK_LABEL(label),"");
		fn_list_conge (treeview);
		strcpy (cc.cin,"");
	}
	else{
		gtk_label_set_text(GTK_LABEL(label),"Double click sur une demande");
	}

}


void
on_button_reset_conge_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
	remove ("conge_approuve.bin");
	FILE* f = fopen ("conge_approuve.bin","w");
	GtkWidget *treeview_liste_conge_valide;
	treeview_liste_conge_valide = lookup_widget (button, "treeview_liste_conge_valide");
	fn_list_conge_approuve (treeview_liste_conge_valide);
	fclose (f);
}

