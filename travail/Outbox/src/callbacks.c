#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "ouvrier.h"

ouvrier o,ouv_m;
char cin_supp[9];

void
on_button_ajout_ouvrier_clicked        (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget *dialog = create_dialog_ajout_ouvrier();
	gtk_widget_show(dialog);

}


void
on_cancelbutton_ajout_ouv_clicked      (GtkWidget      *button,
                                        gpointer         user_data)
{
	GtkWidget *dialog = lookup_widget(button,"dialog_ajout_ouvrier");
	gtk_widget_destroy(dialog);
}

void
on_radiobutton_ouv_male_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
	strcpy (o.genre,"Male");
	strcpy (ouv_m.genre,"Male");
}


void
on_radiobutton_ouv_femelle_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
	strcpy (o.genre,"Femelle");
	strcpy (ouv_m.genre,"Femelle");
}


void
on_okbutton_ajout_ouv_clicked          (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget *input_nom,*input_pren,*input_cin,*input_j,*input_m,*input_a,*input_etat,*input_num_tel,*input_adr,*input_email,*input_secteur;
	GtkWidget *dialog = lookup_widget(button,"dialog_ajout_ouvrier");

	
	input_nom = lookup_widget(button, "entry_nom_ouv");
	input_pren = lookup_widget(button, "entry_pren_ouv");
	input_cin = lookup_widget(button, "entry_cin_ouv");
	input_j = lookup_widget(button, "spinbutton_jour_nais_ouv");
	input_m = lookup_widget(button, "spinbutton_mois_nais_ouv");
	input_a = lookup_widget(button, "spinbutton_annee_nais_ouv");
	input_etat = lookup_widget(button, "comboboxentry_etat_civil_ouv");
	input_num_tel = lookup_widget(button, "entry_num_tel_ouv");	
	input_adr = lookup_widget(button, "entry_adr_ouv");
	input_email = lookup_widget(button, "entry_email_ouv");
	input_secteur = lookup_widget(button, "entry_secteur_ouv");

	strcpy(o.nom,gtk_entry_get_text(GTK_ENTRY(input_nom)));
	strcpy(o.pren,gtk_entry_get_text(GTK_ENTRY(input_pren)));
	strcpy(o.cin,gtk_entry_get_text(GTK_ENTRY(input_cin)));
	o.date_nais.j = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_j));
	o.date_nais.m = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_m));
	o.date_nais.a = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_a));
	strcpy(o.etat_civil,gtk_combo_box_get_active_text(GTK_COMBO_BOX(input_etat)));
	strcpy(o.num_tel,gtk_entry_get_text(GTK_ENTRY(input_num_tel)));
	strcpy(o.adr,gtk_entry_get_text(GTK_ENTRY(input_adr)));
	strcpy(o.email,gtk_entry_get_text(GTK_ENTRY(input_email)));
	strcpy(o.secteur,gtk_entry_get_text(GTK_ENTRY(input_secteur)));

	if(fn_ajout_ouvrier (o,button))
		gtk_widget_destroy(dialog);

}




void
on_button_affich_list_ouv_clicked      (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *treeview_liste_ouvrier;

	treeview_liste_ouvrier = lookup_widget (objet, "treeview_affich_ouv");
	
	fn_list_ouvrier (treeview_liste_ouvrier);
}


void
on_treeview_affich_ouv_row_activated   (GtkTreeView     *treeview,
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
		strcpy (ouv_m.cin, cinm);
		strcpy (ouv_m.nom, nomm);
		strcpy (ouv_m.pren, prenm);
		strcpy (ouv_m.genre, genrem);
		strcpy (ouv_m.etat_civil, etatm);
		strcpy (ouv_m.num_tel, numm);
		strcpy (ouv_m.adr, adrm);
		strcpy (ouv_m.email, emailm);
		strcpy (ouv_m.secteur, secteurm);
		strcpy (cin_supp, ouv_m.cin);
		sscanf (datem,"%d/%d/%d",&ouv_m.date_nais.j,&ouv_m.date_nais.m,&ouv_m.date_nais.a);
	}
}


void
on_button_supp_ouvrier_clicked         (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget *label = lookup_widget (button,"cin");
	if (strlen (cin_supp) == 8){
		fn_supp_ouvrier (cin_supp);
		gtk_label_set_text(GTK_LABEL(label),"");
	}
	else{
		gtk_label_set_text(GTK_LABEL(label),"Double click sur une ligne");
	}
}


void
on_button_modif_ouvrier_clicked        (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget *dialog = create_dialog_modif_ouvrier();
	GtkWidget *label = lookup_widget (button,"cin");
	GtkWidget *io_cin, *io_nom, *io_pren, *io_num_tel, *io_adr,*io_genre, *io_email, *io_secteur;
	GtkSpinButton *io_j, *io_m, *io_a;
   
	if (strlen (ouv_m.cin) == 8){
		gtk_widget_show(dialog);
		io_nom = lookup_widget(dialog, "entry_nomm_ouv");
		io_pren = lookup_widget(dialog, "entry_prenm_ouv");
		io_cin = lookup_widget(dialog, "label_cinm_ouv");
		io_j = lookup_widget(dialog, "spinbutton_jourm_nais_ouv");
		io_m = lookup_widget(dialog, "spinbutton_moism_nais_ouv");
		io_a = lookup_widget(dialog, "spinbutton_anneem_nais_ouv");
		io_num_tel = lookup_widget(dialog, "entry_numm_tel_ouv");	
		io_adr = lookup_widget(dialog, "entry_adrm_ouv");
		io_email = lookup_widget(dialog, "entry_emailm_ouv");
		io_secteur = lookup_widget(dialog, "entry_secteurm_ouv");
		
		gtk_entry_set_text(GTK_ENTRY(io_nom),ouv_m.nom);
		gtk_entry_set_text(GTK_ENTRY(io_pren),ouv_m.pren);
		gtk_label_set_text(GTK_LABEL(io_cin),ouv_m.cin);
		gtk_spin_button_set_value(io_j,ouv_m.date_nais.j);
		gtk_spin_button_set_value(io_m,ouv_m.date_nais.m);
		gtk_spin_button_set_value(io_a,ouv_m.date_nais.a);
		gtk_entry_set_text(GTK_ENTRY(io_num_tel),ouv_m.num_tel);
		gtk_entry_set_text(GTK_ENTRY(io_adr),ouv_m.adr);
		gtk_entry_set_text(GTK_ENTRY(io_email),ouv_m.email);
		gtk_entry_set_text(GTK_ENTRY(io_secteur),ouv_m.secteur);
		gtk_label_set_text(GTK_LABEL(label),"");
	}
	else{
		gtk_label_set_text(GTK_LABEL(label),"Double click sur une ligne");
	}
}


void
on_cancelbutton_modif_ouvrier_clicked  (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget *dialog = lookup_widget(button,"dialog_modif_ouvrier");
	gtk_widget_destroy(dialog);
	strcpy (ouv_m.cin,""); 
}


void
on_okbutton_modif_ouvrier_clicked      (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget *dialog = lookup_widget(button,"dialog_modif_ouvrier");
	GtkWidget *input_nom,*input_pren,*input_cin,*input_j,*input_m,*input_a,*input_etat,*input_num_tel,*input_adr,*input_email,*input_secteur;

	
	input_nom = lookup_widget(button, "entry_nomm_ouv");
	input_pren = lookup_widget(button, "entry_prenm_ouv");
	input_j = lookup_widget(button, "spinbutton_jourm_nais_ouv");
	input_m = lookup_widget(button, "spinbutton_moism_nais_ouv");
	input_a = lookup_widget(button, "spinbutton_anneem_nais_ouv");
	input_etat = lookup_widget(button, "comboboxentry_etatm_civil_ouv");
	input_num_tel = lookup_widget(button, "entry_numm_tel_ouv");	
	input_adr = lookup_widget(button, "entry_adrm_ouv");
	input_email = lookup_widget(button, "entry_emailm_ouv");
	input_secteur = lookup_widget(button, "entry_secteurm_ouv");

	strcpy(ouv_m.nom,gtk_entry_get_text(GTK_ENTRY(input_nom)));
	strcpy(ouv_m.pren,gtk_entry_get_text(GTK_ENTRY(input_pren)));
	ouv_m.date_nais.j = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_j));
	ouv_m.date_nais.m = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_m));
	ouv_m.date_nais.a = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_a));
	strcpy(ouv_m.etat_civil,gtk_combo_box_get_active_text(GTK_COMBO_BOX(input_etat)));
	strcpy(ouv_m.num_tel,gtk_entry_get_text(GTK_ENTRY(input_num_tel)));
	strcpy(ouv_m.adr,gtk_entry_get_text(GTK_ENTRY(input_adr)));
	strcpy(ouv_m.email,gtk_entry_get_text(GTK_ENTRY(input_email)));
	strcpy(ouv_m.secteur,gtk_entry_get_text(GTK_ENTRY(input_secteur)));

	if (fn_modif_ouvrier (ouv_m,button))
		gtk_widget_destroy(dialog);
	strcpy (ouv_m.cin,""); 
}


void
on_button_rech_ouvrier_clicked         (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget *treeview_liste_ouvrier, *cin_input;
	char cin_rech[9];

	treeview_liste_ouvrier = lookup_widget (button, "treeview_affich_ouv");
	cin_input = lookup_widget (button, "entry_cin_ouv_rech");

	strcpy (cin_rech,gtk_entry_get_text(GTK_ENTRY(cin_input)));

	fn_rech_ouvrier (cin_rech,treeview_liste_ouvrier);
}

