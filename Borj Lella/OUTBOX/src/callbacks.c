#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "ouvrier.h"
#include "employee.h"

employee e,em;
congee cc;


ouvrier o;
ouvrier ouv_m;
pointage pa,pm;
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
		strcpy (cin_supp,"");
		strcpy (ouv_m.cin,"");
	}
	else{
		gtk_label_set_text(GTK_LABEL(label),"Double click sur un ouvrier");
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
		gtk_label_set_text(GTK_LABEL(label),"Double click sur un ouvrier");
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

	if (fn_modif_ouvrier (ouv_m,button)){
		gtk_widget_destroy(dialog);
		strcpy (ouv_m.cin,""); 
	}
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

void
on_button_liste_ouv_point_clicked      (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget *treeview_liste_ouvrier;

	treeview_liste_ouvrier = lookup_widget (button, "treeview_affich_point_ouv");
	
	fn_list_ouvrier (treeview_liste_ouvrier);
}


void
on_button_rech_point_ouvrier_clicked   (GtkWidget       *button,
                                        gpointer         user_data)
{

	GtkWidget *treeview_liste_ouvrier, *cin_input;
	char cin_rech[9];

	treeview_liste_ouvrier = lookup_widget (button, "treeview_affich_point_ouv");
	cin_input = lookup_widget (button, "entry_cin_ouv_point_rech");

	strcpy (cin_rech,gtk_entry_get_text(GTK_ENTRY(cin_input)));

	fn_rech_ouvrier (cin_rech,treeview_liste_ouvrier);

}


void
on_treeview_affich_point_ouv_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	GtkTreeIter iter;
	char* cinm;
	char* nomm;
	char* prenm;

	GtkTreeModel *model = gtk_tree_view_get_model (treeview);

	if (gtk_tree_model_get_iter (model, &iter, path)){
		gtk_tree_model_get (GTK_LIST_STORE (model), &iter, 0, &cinm, 1, &nomm, 2, &prenm,-1);
		strcpy (pa.cin, cinm);
		strcpy (pa.nom, nomm);
		strcpy (pa.pren, prenm);
	}
}



void
on_button_ajout_point_clicked          (GtkWidget    *button,
                                        gpointer         user_data)
{
	GtkWidget *emh,*emm,*esh,*esm,*smh,*smm,*ssh,*ssm,*calendar,*abs;

	if (strlen (pa.cin) == 8){
		emh = lookup_widget (button, "spinbutton_entre_matin_h");
		emm = lookup_widget (button, "spinbutton_entre_matin_m");
		esh = lookup_widget (button, "spinbutton_entre_soir_h");
		esm = lookup_widget (button, "spinbutton_entre_soir_m");
		smh = lookup_widget (button, "spinbutton_sortie_matin_h");
		smm = lookup_widget (button, "spinbutton_sortie_matin_m");
		ssh = lookup_widget (button, "spinbutton_sortie_soir_h");
		ssm = lookup_widget (button, "spinbutton_sortie_soir_m");
		calendar = lookup_widget (button, "calendar_date_point");
		abs = lookup_widget (button, "checkbutton_ouv_abs");

		gtk_calendar_get_date (calendar,&pa.date_point.a,&pa.date_point.m,&pa.date_point.j);
		pa.date_point.m++;
		if (gtk_toggle_button_get_active (abs)){
			pa.abs = 0;
		}
		else{
			pa.abs = 1;
			pa.entre_matin.h = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(emh));
			pa.entre_matin.m = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(emm));
			pa.sort_matin.h = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(smh));
			pa.sort_matin.m = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(smm));
			pa.entre_soir.h = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(esh));
			pa.entre_soir.m = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(esm));
			pa.sort_soir.h = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(ssh));
			pa.sort_soir.m = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(ssm));
		}
		fn_ajout_point (pa,button);
		strcpy (pa.cin,"");
	}
	else
	{
		GtkWidget *warning = lookup_widget (button, "label_warning");
		gtk_label_set_text(GTK_LABEL(warning),"Double click sur un ouvrier");

	}
	
}


void
on_button_liste_point_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *treeview_liste_point;

	treeview_liste_point = lookup_widget (button, "treeview_liste_point");
	
	fn_list_point (treeview_liste_point);

}


void
on_button_rech_point_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{

	GtkWidget *treeview_liste_point, *date_input;
	char date_rech[15];

	treeview_liste_point = lookup_widget (button, "treeview_liste_point");
	date_input = lookup_widget (button, "entry_rech_point");

	strcpy (date_rech,gtk_entry_get_text(GTK_ENTRY(date_input)));

	fn_rech_point (date_rech,treeview_liste_point);

}


void
on_treeview_liste_point_row_activated  (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	GtkTreeIter iter;
	char* cinm;
	char* nomm;
	char* prenm;
	char* absm;
	char* datem;
	char* em_m;
	char* sm_m;
	char* es_m;
	char* ss_m;

	GtkTreeModel *model = gtk_tree_view_get_model (treeview);

	if (gtk_tree_model_get_iter (model, &iter, path)){
		gtk_tree_model_get (GTK_LIST_STORE (model), &iter, 0, &cinm, 1, &nomm, 2, &prenm, 3, &datem, 4, &absm, 5, &em_m, 6, &sm_m, 7, &es_m, 8, &ss_m,-1);
		strcpy (pm.cin, cinm);
		strcpy (pm.nom, nomm);
		strcpy (pm.pren, prenm);
		if (strcmp (absm,"absent") == 0)
			pm.abs = 0;
		else
			pm.abs = 1;
		sscanf (datem,"%d/%d/%d",&pm.date_point.j,&pm.date_point.m,&pm.date_point.a);
		sscanf (em_m,"%d:%d",&pm.entre_matin.h,&pm.entre_matin.m);
		sscanf (sm_m,"%d:%d",&pm.sort_matin.h,&pm.sort_matin.m);
		sscanf (es_m,"%d:%d",&pm.entre_soir.h,&pm.entre_soir.m);
		sscanf (ss_m,"%d:%d",&pm.sort_soir.h,&pm.sort_soir.m);
	}

	GtkWidget *cin_io,*date_io;
	GtkSpinButton *emh,*emm,*esh,*esm,*smh,*smm,*ssh,*ssm;

	emh = lookup_widget (treeview, "spinbutton_entre_matin_modif_h");
	emm = lookup_widget (treeview, "spinbutton_entre_matin_modif_m");
	esh = lookup_widget (treeview, "spinbutton_entre_soir_modif_h");
	esm = lookup_widget (treeview, "spinbutton_entre_soir_modif_m");
	smh = lookup_widget (treeview, "spinbutton_sortie_matin_modif_h");
	smm = lookup_widget (treeview, "spinbutton_sortie_matin_modif_m");
	ssh = lookup_widget (treeview, "spinbutton_sortie_soir_modif_h");
	ssm = lookup_widget (treeview, "spinbutton_sortie_soir_modif_m");
	cin_io = lookup_widget (treeview, "entry_cin_point_modif");
	date_io = lookup_widget (treeview, "entry_date_point_modif");

	gtk_spin_button_set_value(emh,pm.entre_matin.h);
	gtk_spin_button_set_value(emm,pm.entre_matin.m);
	gtk_spin_button_set_value(smh,pm.sort_matin.h);
	gtk_spin_button_set_value(smm,pm.sort_matin.m);
	gtk_spin_button_set_value(esh,pm.entre_soir.h);
	gtk_spin_button_set_value(esm,pm.entre_soir.m);
	gtk_spin_button_set_value(ssh,pm.sort_soir.h);
	gtk_spin_button_set_value(ssm,pm.sort_soir.m);
	gtk_entry_set_text(GTK_ENTRY(cin_io),pm.cin);
	gtk_entry_set_text(GTK_ENTRY(date_io),datem);

}


void
on_button_modif_point_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkSpinButton *emh,*emm,*esh,*esm,*smh,*smm,*ssh,*ssm;
	GtkWidget *cin_io,*date_io;

	emh = lookup_widget (button, "spinbutton_entre_matin_modif_h");
	emm = lookup_widget (button, "spinbutton_entre_matin_modif_m");
	esh = lookup_widget (button, "spinbutton_entre_soir_modif_h");
	esm = lookup_widget (button, "spinbutton_entre_soir_modif_m");
	smh = lookup_widget (button, "spinbutton_sortie_matin_modif_h");
	smm = lookup_widget (button, "spinbutton_sortie_matin_modif_m");
	ssh = lookup_widget (button, "spinbutton_sortie_soir_modif_h");
	ssm = lookup_widget (button, "spinbutton_sortie_soir_modif_m");
	cin_io = lookup_widget (button, "entry_cin_point_modif");
	date_io = lookup_widget (button, "entry_date_point_modif");

	pm.entre_matin.h = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(emh));
	pm.entre_matin.m = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(emm));
	pm.sort_matin.h = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(smh));
	pm.sort_matin.m = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(smm));
	pm.entre_soir.h = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(esh));
	pm.entre_soir.m = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(esm));
	pm.sort_soir.h = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(ssh));
	pm.sort_soir.m = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(ssm));

	if (strlen (pm.cin) == 8){
		fn_modif_point (pm);
		strcpy (pm.cin,"");
	}

	gtk_spin_button_set_value(emh,0);
	gtk_spin_button_set_value(emm,0);
	gtk_spin_button_set_value(smh,0);
	gtk_spin_button_set_value(smm,0);
	gtk_spin_button_set_value(esh,0);
	gtk_spin_button_set_value(esm,0);
	gtk_spin_button_set_value(ssh,0);
	gtk_spin_button_set_value(ssm,0);
	gtk_entry_set_text(GTK_ENTRY(cin_io),"");
	gtk_entry_set_text(GTK_ENTRY(date_io),"");
}


void
on_button_ajout_conge_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *cin_i, *sect_i, *date_de, *date_jusqa,* rais_i;
	conge c;

	cin_i = lookup_widget (button, "entry_cin_conge"); 
	sect_i = lookup_widget (button, "entry_secteur_conge");
	date_de = lookup_widget (button, "calendar_conge_de");
	date_jusqa = lookup_widget (button, "calendar_conge_jusqa");
	rais_i = lookup_widget (button, "entry_raison_conge");

	strcpy(c.cin,gtk_entry_get_text(GTK_ENTRY(cin_i)));
	strcpy(c.secteur,gtk_entry_get_text(GTK_ENTRY(sect_i)));
	strcpy(c.rais,gtk_entry_get_text(GTK_ENTRY(rais_i)));
	gtk_calendar_get_date (date_de,&c.date_deb.a,&c.date_deb.m,&c.date_deb.j);
	c.date_deb.m++;
	gtk_calendar_get_date (date_jusqa,&c.date_fin.a,&c.date_fin.m,&c.date_fin.j);
	c.date_fin.m++;

	if (fn_demande_conge (c,button)){
		gtk_entry_set_text(GTK_ENTRY(cin_i),"");
		gtk_entry_set_text(GTK_ENTRY(sect_i),"");
		gtk_entry_set_text(GTK_ENTRY(rais_i),"");
	}
}


void
on_button_affich_conge_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *treeview_liste_conge;

	treeview_liste_conge = lookup_widget (button, "treeview_liste_conge");
	
	fn_list_conge (treeview_liste_conge);
}



/*************************************************************************

			GESTION D'EMPLOYEE


**************************************************************************/






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
		fn_list_conge_em (treeview);
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
	
	fn_list_conge_em (treeview_liste_conge);
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
		fn_list_conge_em (treeview);
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


