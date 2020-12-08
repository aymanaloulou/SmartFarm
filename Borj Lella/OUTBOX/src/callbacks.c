#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "ouvrier.h"
#include "employee.h"
#include "gestion_clients.h"

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

/*************************************************************************

			GESTION DES CLIENTS


**************************************************************************/

                           ////////////////////// liaison entre les windows + button supprimer /////////////////////

Client A;


void
on_treeview_client_row_activated       (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *col,
                                        gpointer         user_data)
{        
GtkTreeIter iter;
gchar *nom;
gchar *prenom;
gchar *cinn;
gchar *gender;
gint *jour;
gint *mois;
gint *annee;
gchar *numero;
gchar *adress;
gchar *mail;
GtkTreeModel *model;
FILE * Fh;

model= gtk_tree_view_get_model(treeview);
if (gtk_tree_model_get_iter(model,&iter,path)) {
gtk_tree_model_get (GTK_LIST_STORE(model), &iter,0,&nom,1,&prenom,2,&cinn,3,&gender,4,&jour,5,&mois,6,&annee,7,&numero,8,&adress,9,&mail,-1);


strcpy (A.cin,cinn);
strcpy (A.nom,nom);
strcpy (A.prenom,prenom);
strcpy (A.adress,adress);
strcpy (A.numero_de_telephone,numero);
strcpy (A.gender,gender);
strcpy (A.email,mail);
A.jour=jour;
A.mois=mois;
A.annee=annee;



 

}

   
    
}







void
on_button_gestion_clients_clicked      (GtkWidget    *objet_graphique1,
                                        gpointer         user_data)
{
GtkWidget *window_gestion_des_clients;
window_gestion_des_clients=create_window_gestion_des_clients();
gtk_widget_show(window_gestion_des_clients);

}




void
on_button_ajouter_client_clicked        (GtkWidget       *objet_graphique3,
                                        gpointer         user_data)
{
GtkWidget *dialog_ajouter_client;
dialog_ajouter_client=create_dialog_ajouter_client();
gtk_widget_show(dialog_ajouter_client);

}

void
on_button_modifier_client_clicked       (GtkWidget       *objet_graphique4,
                                        gpointer         user_data)
{GtkWidget *dialog_modifier_client;
dialog_modifier_client=create_dialog_modifier_client();
GtkWidget *aa,*a,*input14,*input71,*input81,*input15,*input16,*input17,*input18,*input19,*spin_button1,*spin_button2,*spin_button3;



if (strlen(A.cin)==8) {

gtk_widget_show(dialog_modifier_client);

a=lookup_widget(dialog_modifier_client,"radiobutton_h_mod_group_changed");
aa=lookup_widget(dialog_modifier_client,"radiobutton-f-mod_group_changed");


Client k;

GtkWidget *Outverif;

GtkWidget *input111,*outputmo;
GtkWidget *dialogp;
FILE *fp;
fp=fopen ("client.bin","rb");
int ok=-1;




while (fread (&k,sizeof (Client),1,fp) != 0)
{

if (strcmp (k.cin,A.cin)==0)

{
input14=lookup_widget(dialog_modifier_client, "entry_mod_nom");
input15=lookup_widget(dialog_modifier_client, "entry_mod_pren");
input16=lookup_widget(dialog_modifier_client, "entry_mod_cin");
input17=lookup_widget(dialog_modifier_client, "entry_num_mod");
input18=lookup_widget(dialog_modifier_client, "entry_adress_mod");
input19=lookup_widget(dialog_modifier_client, "entry_email_mod");


spin_button1=lookup_widget(dialog_modifier_client, "spinbutton_jr_mod");
spin_button2=lookup_widget(dialog_modifier_client, "spinbutton_mois_mod");
spin_button3=lookup_widget(dialog_modifier_client, "spinbutton_annee_mod");

if (strcmp(A.gender,"homme")==0)
{
gtk_toggle_button_set_active(a,TRUE);

}else
{
gtk_toggle_button_set_active(aa,TRUE);}


gtk_entry_set_text(GTK_ENTRY(input14),A.nom);
gtk_entry_set_text(GTK_ENTRY(input15),A.prenom);
gtk_entry_set_text(GTK_ENTRY(input16),A.cin);

gtk_entry_set_text(GTK_ENTRY(input81),A.cin);
gtk_entry_set_text(GTK_ENTRY(input17),A.numero_de_telephone);
gtk_entry_set_text(GTK_ENTRY(input18),A.adress);
gtk_entry_set_text(GTK_ENTRY(input19),A.email);

gtk_spin_button_set_value (spin_button1,A.jour);
gtk_spin_button_set_value (spin_button2,A.mois);
gtk_spin_button_set_value (spin_button3,A.annee);


}}



fclose (fp);

}



}

void
on_button_supprimer_client_clicked      (GtkWidget       *objet_graphique5,
                                        gpointer         user_data)
{

FILE *HISTO;
FILE *en;
Client off;
GtkWidget *inp1,*out1,*dest1;


en=fopen ("client.bin","rb");
while(fread(&off,sizeof(Client),1,en))
{
if (strcmp(off.cin,A.cin)==0)
{

HISTO=fopen("historique.bin","ab");
fwrite (&off,sizeof(Client),1,HISTO);
fclose(HISTO);
gtk_widget_destroy (dest1);
supprimer_list_client(A);
supprimer_jeux(A);
}
}


fclose(en);
}




void
on_button_cancel_ajouter_client_clicked
                                        (GtkWidget       *objet_graphique6,
                                        gpointer         user_data)
{
GtkWidget *dialog_ajouter_client;
dialog_ajouter_client=lookup_widget(objet_graphique6,"dialog_ajouter_client");
gtk_widget_destroy(dialog_ajouter_client);
}


void
on_button_cancel_modifier_client_clicked
                                        (GtkWidget       *objet_graphique7,
                                        gpointer         user_data)
{
GtkWidget *dialog_modifier_client;
dialog_modifier_client=lookup_widget(objet_graphique7,"dialog_modifier_client");
gtk_widget_destroy(dialog_modifier_client);
}



                              ///////////////////////// crud list des clients //////////////////////////

void
on_button_aj_client_clicked          (GtkWidget      *objet_graphique18,
                                        gpointer         user_data)
{
GtkWidget *input1,*input2,*input3,*input4,*input5,*input6,*input7,*input8,*input9,*input10,*input11,*input12;
GtkWidget *check,*check_exist;
Client S,c;

// ini input //
input1= lookup_widget(objet_graphique18, "entry_nom_aj_c") ; 
input2 = lookup_widget(objet_graphique18, "entry_prenom_aj_c") ; 
input3 = lookup_widget(objet_graphique18, "entry_cin_aj_c") ; 
input4 = lookup_widget(objet_graphique18, "spinbutton_jr_aj_c") ; 
input5 = lookup_widget(objet_graphique18, "spinbutton_mois_aj_c") ; 
input6 = lookup_widget(objet_graphique18, "spinbutton_annee_aj_c") ;
input7 = lookup_widget(objet_graphique18, "radiobutton_h1_aj") ;  
input8 = lookup_widget(objet_graphique18, "radiobutton_f_aj") ; 
input9 = lookup_widget(objet_graphique18, "entry_tel_aj_c") ; 
input10 = lookup_widget(objet_graphique18, "entry_adr_aj_c") ; 
input11 = lookup_widget(objet_graphique18, "entry_email_aj_c") ; 
input12=lookup_widget(objet_graphique18,"dialog_ajouter_client");
// ini ouput //
check= lookup_widget(objet_graphique18, "label_check_ajc") ; 
check_exist =lookup_widget(objet_graphique18, "label_compte_existe") ; 
//from glade to function //
strcpy(S.nom,gtk_entry_get_text(GTK_ENTRY(input1)));
strcpy(S.prenom,gtk_entry_get_text(GTK_ENTRY(input2)));	
S.jour= gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input4));
S.mois= gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input5));
S.annee= gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input6));
strcpy(S.numero_de_telephone,gtk_entry_get_text(GTK_ENTRY(input9)));
strcpy(S.adress,gtk_entry_get_text(GTK_ENTRY(input10)));
strcpy(S.email,gtk_entry_get_text(GTK_ENTRY(input11)));
strcpy(S.cin,gtk_entry_get_text(GTK_ENTRY(input3)));
// fixed //
if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(input7))==TRUE) {
 strcpy(S.gender,"homme");}
else {
strcpy(S.gender,"femme");}
/////////// declaration var de verif num de tel ///////////////////
int TEL1=0,TEL2=0,j=0;
/////////////////// verif numero de tel ///////////////////
if (strlen (S.numero_de_telephone) != 8){
TEL1=1;}
for (j=0;j < strlen(S.numero_de_telephone);j++) {
		if (S.numero_de_telephone[j] < '0' || S.numero_de_telephone[j] >'9'){
	TEL2=1;		
break;}}
	if (TEL1==1|| TEL2==1)
{
gtk_label_set_text(GTK_LABEL(check),"verifier les cordonées  !!");
} 
////////// declaration var de  verif mail ////////
int email=1;
char a='@', b='.';


/////////// verif mail //////////////
	if (pos(a,S.email)<1){
		gtk_label_set_text(GTK_LABEL(check),"verifier les cordonées  !!");
}
	if (pos (b,S.email)<3) {
	gtk_label_set_text(GTK_LABEL(check),"verifier les cordonées  !!");
}
	else
      {email=0;}
  

 



//////////// declaration var de verif cin////////
int CIN1=0,CIN2=0,i,CIN3=0,CIN4=0;
///////////////////verif CIN///////////////
// 1st verif//
if (strlen (S.cin) != 8){
CIN1=1;
}
// second verif //
for (i=0;i<strlen(S.cin);i++) {
		if (S.cin[i]<'0' || S.cin[i]>'9'){
	CIN2=1;		
break;
} 
	}
//third verif //
if (verif_existance(S.cin)==0)
{ CIN3=1;}
if (CIN3==1)
{
gtk_label_set_text(GTK_LABEL(check_exist),"Ce Client existe deja ! ! ");
}
if (verifhisto(S.cin)==0)
{CIN4=1;}
if (CIN4==1)
gtk_label_set_text(GTK_LABEL(check_exist),"Client existe dans l'historique ");




	if (CIN1==1 || CIN2==1) 
{
gtk_label_set_text(GTK_LABEL(check),"verifier les cordonnées  !!");
}
	

///////////////////////////    Remplissage du fichier . bin          /////////////////////////////
	 if (CIN1==0&&CIN2==0&&CIN3==0&&CIN4==0&&email==0&&TEL1==0&&TEL2==0)
{ 	
	ajouter_list_client(S);
	aj_jeux(S);
	gtk_widget_destroy(input12);

}


}
////////////////////////////////////////////////// FIN AJOUTER CLIENT ////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////// MODIFIER CLIENT //////////////////////////////////////////////////////////////////////
///////////////////////// chercher le client a modifier ///////////////////////////////


// a supp //


void
on_button_modifier_c_clicked           (GtkWidget       *objet_graphique20,
                                        gpointer         user_data)
{ GtkWidget *input30,*input31,*input32,*input33,*input34,*input35,*input36,*input37,*input38,*input39,*input40,*input41,*checkmod;
// ini input //
Client m;
input30= lookup_widget(objet_graphique20, "entry_mod_nom") ; 
input31 = lookup_widget(objet_graphique20, "entry_mod_pren") ; 
input32 = lookup_widget(objet_graphique20, "entry_mod_cin") ; 
input33 = lookup_widget(objet_graphique20, "spinbutton_jr_mod") ; 
input34 = lookup_widget(objet_graphique20, "spinbutton_mois_mod") ; 
input35 = lookup_widget(objet_graphique20, "spinbutton_annee_mod") ;
input36 = lookup_widget(objet_graphique20, "radiobutton_h_mod") ;  
input37 = lookup_widget(objet_graphique20, "radiobutton_f_mod") ; 
input38 = lookup_widget(objet_graphique20, "entry_num_mod") ; 
input39 = lookup_widget(objet_graphique20, "entry_adress_mod") ; 
input40 = lookup_widget(objet_graphique20, "entry_email_mod") ; 
input41=  lookup_widget(objet_graphique20,"dialog_modifier_client");
// ini ouput //
checkmod= lookup_widget(objet_graphique20, "label_verif_mod") ; 
 
//from glade to function //
strcpy(m.nom,gtk_entry_get_text(GTK_ENTRY(input30)));
strcpy(m.prenom,gtk_entry_get_text(GTK_ENTRY(input31)));	
m.jour= gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input33));
m.mois= gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input34));
m.annee= gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input35));
strcpy(m.numero_de_telephone,gtk_entry_get_text(GTK_ENTRY(input38)));
strcpy(m.adress,gtk_entry_get_text(GTK_ENTRY(input39)));
strcpy(m.email,gtk_entry_get_text(GTK_ENTRY(input40)));
strcpy(m.cin,gtk_entry_get_text(GTK_ENTRY(input32)));
if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(input36))==TRUE) {
 strcpy(m.gender,"homme");}
else {
strcpy(m.gender,"femme");}
////////// declaration var de  verif mail ////////
int email=1;
char h='@', e='.';


/////////// verif mail //////////////
	if (pos(h,m.email)<1){
		gtk_label_set_text(GTK_LABEL(checkmod),"verifier les cordonées  !!");
}
	if (pos (e,m.email)<3) {
	gtk_label_set_text(GTK_LABEL(checkmod),"verifier les cordonées  !!");
}
	else
      {email=0;}
 /////////// declaration var de verif num de tel ///////////////////
int TEL11=0,TEL22=0,j=0;
/////////////////// verif numero de tel ///////////////////
if (strlen (m.numero_de_telephone) != 8){
TEL11=1;}
for (j=0;j < strlen(m.numero_de_telephone);j++) {
		if (m.numero_de_telephone[j] < '0' || m.numero_de_telephone[j] >'9'){
	TEL22=1;		
break;}}
	if (TEL11==1|| TEL22==1)
{
gtk_label_set_text(GTK_LABEL(checkmod),"verifier les cordonées  !!");
}
if (TEL11==0&TEL22==0&&email==0)
{
modifier_list_client(m);
 modifier_jeux(m);
gtk_widget_destroy(input41);



}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// SUPPRIMER UN CLIENT /////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////// AFFICHER LIST CLIENT /////////////////////////////////////////////
void
on_button_aff_clicked                  (GtkWidget     *objet_graphique22,
                                        gpointer         user_data)
{
GtkWidget *treeviewCLIENT;

treeviewCLIENT=lookup_widget(objet_graphique22,"treeview_client");
afficher_list_client(treeviewCLIENT);

}

////////////////////////////////////////////////////////////////// Rechercher un client //////////////////////////////////////////////////////



void
on_button_recherche_clicked            (GtkWidget      *objet_graphique23,
                                        gpointer         user_data)
{

	GtkWidget *treeview_liste_client, *cin_input;
	char cin_rech[9];

	treeview_liste_client = lookup_widget (objet_graphique23, "treeview_client");
	cin_input = lookup_widget (objet_graphique23, "entry_rech_cl");

	strcpy (cin_rech,gtk_entry_get_text(GTK_ENTRY(cin_input)));

	rech_client (cin_rech,treeview_liste_client);
}

void
on_button_rechercheee_client_clicked   (GtkWidget       *objet_graphique25,
                                        gpointer         user_data)
{
GtkWidget *dest2;
dest2=lookup_widget(objet_graphique25,"dialog_recherche_client");
gtk_widget_destroy(dest2);
}
//////////////////////////////////////////////////////////////     FIN CRUDE        ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////// AFFICHER LISTE HISTORIQUE //////////////////////////////////////////////

void
on_button_aff_historique_clicked       (GtkWidget      *objet_graphique26,
                                        gpointer         user_data)
{
GtkWidget *affhisto;
affhisto=lookup_widget(objet_graphique26,"treeview_historique");
afficher_Historique(affhisto);
}

////////////////////////////////////////////////////////////////////Supprimer un client de l'historique //////////////////////////////////////
Client b;
void
on_treeview_historique_row_activated   (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

GtkTreeIter iter;
gchar *nom;
gchar *prenom;
gchar *cinn;
gchar *gender;
gint *jour;
gint *mois;
gint *annee;
gchar *numero;
gchar *adress;
gchar *mail;
GtkTreeModel *model;

model= gtk_tree_view_get_model(treeview);
if (gtk_tree_model_get_iter(model,&iter,path)) {
gtk_tree_model_get (GTK_LIST_STORE(model), &iter,0,&nom,1,&prenom,2,&cinn,3,&gender,4,&jour,5,&mois,6,&annee,7,&numero,8,&adress,9,&mail,-1);

g_print ("%s",cinn);
strcpy (b.cin,cinn);
strcpy (b.nom,nom);
strcpy (b.prenom,prenom);
strcpy (b.adress,adress);
strcpy (b.numero_de_telephone,numero);
strcpy (b.gender,gender);
strcpy (b.email,mail);
b.jour=jour;
b.mois=mois;
b.annee=annee;


}

  
}




void
on_button_supp_histo_clicked           (GtkWidget       *objet_graphique27,
                                        gpointer         user_data)
{
	FILE *en;
Client off;

en=fopen ("historique.bin","rb");
while(fread(&off,sizeof(Client),1,en))
{
if (strcmp(off.cin,b.cin)==0)
{
supprimer_Historique(off);
}
}


fclose(en);
	
}


void
on_button_recup_histo_clicked          (GtkWidget      *objet_graphique29,
                                        gpointer         user_data)
{
	Client HQ;
FILE *hip;

hip=fopen("historique.bin","r+b");
fseek (hip,cinExiste(b.cin)*sizeof(Client),SEEK_SET);
fread(&HQ,sizeof(Client),1,hip);

if (strcmp(HQ.cin,b.cin)==0)
{
ajouter_list_client(b);
aj_jeux(b);

supprimer_Historique(HQ);
}}

//


//////////////////// Regroupement des buttons radiobutton ajout +modif /////////////////////////////////////////////////////////////////
void
on_radiobutton_h_aj_group_changed      (GtkRadioButton  *radiobutton,
                                        gpointer         user_data)
{

}


void
on_radiobutton_f_aj_group_changed      (GtkRadioButton  *radiobutton,
                                        gpointer         user_data)
{

}


void
on_radiobutton_h_mod_group_changed     (GtkRadioButton  *radiobutton,
                                        gpointer         user_data)
{

}


void
on_radiobutton_f_mod_group_changed     (GtkRadioButton  *radiobutton,
                                        gpointer         user_data)
{

}
//////////////////////////////////////////////////////////// Supp atravers row on double click/////////////////////////////////////////////

Reservation e1;

////////////////////////////////////////////////////////// RESERVATION /////////////////////////////////////////////////////////////////////

void
on_treeview_reservation_row_activated  (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
gchar *ref;
gchar *preno;
gchar *cin;
gchar *gender;
gint  *numero;
gchar *adress;
gchar *mail;
gchar *jour;
gint *mois;
gint *m;
gint *a;
gint  *annee;

GtkTreeModel *model;


model= gtk_tree_view_get_model(treeview);
if (gtk_tree_model_get_iter(model,&iter,path)) {
gtk_tree_model_get (GTK_LIST_STORE(model), &iter,0,&ref,1,&preno,2,&cin,3,&gender,4,&numero,5,&adress,6,&mail,7,&jour,8,&mois,9,&m,10,&a,11,&annee,-1);
//gtk_tree_model_get (GTK_LIST_STORE(model), &iter,0,&nom,1,&prenom,2,&cinn,3,&gender,4,&jour,5,&mois,6,&annee,7,&numero,8,&adress,9,&mail,-1);



strcpy (e1.ref,ref);
strcpy (e1.nom_r,preno);
strcpy (e1.prenom_r,cin);
strcpy (e1.numero,gender);

e1.nbr=numero;

strcpy (e1.option,adress);
strcpy (e1.periode,mail);
strcpy (e1.commentaire,jour);
e1.jr=mois;
e1.mois=m;
e1.annee=m;
e1.heure=annee;



}
}







void
on_button_ajouter_res_clicked          (GtkWidget      *objet_graphique31,
                                        gpointer         user_data)
{
GtkWidget *inp_res;
inp_res=create_dialog_reserv();
gtk_widget_show(inp_res);
}


void
on_okbutton_aj_reser_clicked           (GtkWidget       *objet_graphique32,
                                        gpointer         user_data)
{
GtkWidget *i0,*i1,*i2,*i3,*i4,*i5,*i6,*i7,*i8,*i9,*i10,*i11,*i16,*i17,*i18;
int ob=0;

i17=lookup_widget(objet_graphique32,"label_res_existe");
i0=lookup_widget(objet_graphique32,"entry_ref_aj");
i1=lookup_widget(objet_graphique32,"entry_nom_res");
i2=lookup_widget(objet_graphique32,"entry_prenom_res");
i3=lookup_widget(objet_graphique32,"entry_numero_tel");
i4=lookup_widget(objet_graphique32,"spinbutton_nbr_res");
i5=lookup_widget(objet_graphique32,"checkbutton1");
i6=lookup_widget(objet_graphique32,"checkbutton2");
i7=lookup_widget(objet_graphique32,"checkbutton3");
i8=lookup_widget(objet_graphique32,"calendar_a");
i9=lookup_widget(objet_graphique32,"comboboxentry_res");
i11=lookup_widget(objet_graphique32,"spinbutton_heure");
i16=lookup_widget(objet_graphique32,"entry_txt_aj");


Reservation W;
strcpy(W.ref,gtk_entry_get_text(GTK_ENTRY(i0)));
if (refExiste(W.ref)==-1)
{
ob=1;
}
int Qa=0;
if (strcmp (W.ref,"")==0)
{
Qa=1;
}
int Sp=0;
strcpy(W.nom_r,gtk_entry_get_text(GTK_ENTRY(i1)));
strcpy(W.prenom_r,gtk_entry_get_text(GTK_ENTRY(i2)));
strcpy(W.numero,gtk_entry_get_text(GTK_ENTRY(i3)));

gtk_calendar_get_date(i8,&W.annee,&W.mois,&W.jr);
W.mois++;


strcpy(W.commentaire,gtk_entry_get_text(GTK_ENTRY(i16)));
strcpy (W.option," ");

if (strlen (W.numero) != 8){
Sp=1;}

if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(i5))==TRUE)
strcat (W.option,"petit-dejeuner ");
  if  (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(i6))==TRUE)
strcat (W.option,"déjeuner  ");
 if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(i7))==TRUE)
strcat (W.option," autre ");
//
strcpy(W.periode,gtk_combo_box_get_active_text(GTK_COMBO_BOX(i9)));
W.nbr= gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(i4));
W.heure=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(i11));
if (Qa==1)
{
gtk_label_set_text(GTK_LABEL(i17)," Ref invalide !!");
}
else if (ob==0)
gtk_label_set_text(GTK_LABEL(i17),"reservation existe deja !!");
 else if (Sp==1)
gtk_label_set_text(GTK_LABEL(i17),"Numero invalide !!");
if (ob==1&&Qa==0&&Sp==0) {
ajouter_res(W);
i10=lookup_widget(objet_graphique32,"dialog_reserv");
gtk_widget_destroy(i10);}

}


void
on_button_aff_reservation_clicked      (GtkWidget       *objet_graphique33,
                                        gpointer         user_data)
{GtkWidget *i11;
i11=lookup_widget(objet_graphique33,"treeview_reservation");
afficher_res(i11);

}

//////// donner un toggle signal pour le case a cocher //
void
on_checkbutton3_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_checkbutton2_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_checkbutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}
/////////////////////////////////////////////////////////////////////


void
on_cancelbutton1_clicked               (GtkWidget       *objet_graphique34,
                                        gpointer         user_data)
{
GtkWidget *i12;
i12=lookup_widget(objet_graphique34,"dialog_reserv");
gtk_widget_destroy(i12);
}


///////////////////////////////////////      Supprimer une reservation ///////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////// MODIFIER UNE RESERVATION //////////////////////////////////////////////////////////////////
void
on_button_modifier_res_clicked         (GtkWidget       *objet_graphique35,
                                        gpointer         user_data)
{
GtkWidget *s12,*s13,*s14,*s15,*s16,*s17,*s18,*s19,*s20,*s21,*s22,*s23;
char Cs[100];
GtkWidget *indialog;



if (strlen(e1.ref)>0) {
indialog =create_dialog_mod_res();
gtk_widget_show(indialog);


s14=lookup_widget(indialog,"entry243");
s15=lookup_widget(indialog,"entry_nom_rmod");
s16=lookup_widget(indialog,"entry_pre_rmod");
s17=lookup_widget(indialog,"entry_tel_rmod");

s13=lookup_widget(indialog,"entry_com_rmod");
s18=lookup_widget(indialog,"spinbutton_rmod");
s19=lookup_widget(indialog,"spinbutton_heure_rmod");
s20=lookup_widget(indialog,"checkbutton6");
s21=lookup_widget(indialog,"checkbutton7");
s22=lookup_widget(indialog,"checkbutton8");
s23=lookup_widget(indialog,"comboboxentry_rmod");
//



gtk_entry_set_text(GTK_ENTRY(s14),e1.ref);
gtk_entry_set_text(GTK_ENTRY(s13),e1.commentaire);
gtk_entry_set_text(GTK_ENTRY(s15),e1.nom_r);
gtk_entry_set_text(GTK_ENTRY(s16),e1.prenom_r);
gtk_entry_set_text(GTK_ENTRY(s17),e1.numero);

if (strstr(e1.option,"petit-dejeuner"))
{ 
gtk_toggle_button_set_active (s20,TRUE);

}
if (strstr(e1.option,"déjeuner"))
{ 
gtk_toggle_button_set_active (s21,TRUE);

}
if (strstr(e1.option,"autre"))
{ 
gtk_toggle_button_set_active (s22,TRUE);

}
//
if (strcmp(e1.periode,"lundi-vendredi")==0)
gtk_combo_box_set_active (s23,1);
else if  (strcmp(e1.periode,"Weekend")==0)
gtk_combo_box_set_active (s23,0);
//
gtk_spin_button_set_value (s18,e1.nbr);
gtk_spin_button_set_value (s19,e1.heure);

}
}


void
on_cancelbutton_rese_mod_clicked       (GtkWidget       *objet_graphique36,
                                        gpointer         user_data)
{GtkWidget *org;
org=lookup_widget(objet_graphique36,"dialog_mod_res");
gtk_widget_destroy(org);

}


void
on_okbutton_modifier_reser_clicked     (GtkWidget       *objet_graphique37,
                                        gpointer         user_data)
{Reservation L;
GtkWidget *i16,*i900,*i26,*i36,*i46,*i56,*i66,*i73,*i76,*i86,*i96,*i106,*i116,*i161,*i105,*i108;

i900=lookup_widget(objet_graphique37,"label_res_mod_ex");
i105=lookup_widget(objet_graphique37,"entry243");
i108=lookup_widget(objet_graphique37,"dialog_mod_res");
i73=lookup_widget(objet_graphique37,"entry_exis_res");
i16=lookup_widget(objet_graphique37,"entry_nom_rmod");
i26=lookup_widget(objet_graphique37,"entry_pre_rmod");
i36=lookup_widget(objet_graphique37,"entry_tel_rmod");
i46=lookup_widget(objet_graphique37,"spinbutton_rmod");
i56=lookup_widget(objet_graphique37,"checkbutton6");
i66=lookup_widget(objet_graphique37,"checkbutton7");
i76=lookup_widget(objet_graphique37,"checkbutton8");
i86=lookup_widget(objet_graphique37,"calendar_mod");
i96=lookup_widget(objet_graphique37,"comboboxentry_rmod");
i116=lookup_widget(objet_graphique37,"spinbutton_heure_rmod");
i161=lookup_widget(objet_graphique37,"entry_com_rmod");
//
int bv=0;
strcpy(L.ref,gtk_entry_get_text(GTK_ENTRY(i105)));
if (strcmp(L.ref,"")==0)
{bv=1;}
strcpy(L.nom_r,gtk_entry_get_text(GTK_ENTRY(i16)));
strcpy(L.prenom_r,gtk_entry_get_text(GTK_ENTRY(i26)));
strcpy(L.numero,gtk_entry_get_text(GTK_ENTRY(i36)));
gtk_calendar_get_date (i86,&L.annee,&L.mois,&L.jr);
L.mois++;
strcpy(L.commentaire,gtk_entry_get_text(GTK_ENTRY(i161)));
int Ss=0;
if (strlen (L.numero) != 8){
Ss=1;}
if(bv==1) 
gtk_label_set_text(GTK_LABEL(i900),"Veuiller saisir la ref!!");
else if (Ss==1)
gtk_label_set_text(GTK_LABEL(i900),"Numero invalide !!");
//
strcpy (L.option," ");
if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(i56))==TRUE)
strcat (L.option,"petit-dejeuner ");
 if  (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(i66))==TRUE)
strcat (L.option,"déjeuner  ");
 if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(i76))==TRUE)
strcat (L.option," autre ");
//
strcpy(L.periode,gtk_combo_box_get_active_text(GTK_COMBO_BOX(i96)));
L.nbr= gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(i46));
L.heure=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(i116));
//
if (bv==0&&Ss==0) {
modifier_res(L);
gtk_widget_destroy(i108);}

}

/*
void
on_button_existe_res_clicked           (GtkWidget       *objet_graphique38,
                                        gpointer         user_data)
{
GtkWidget *s12,*s13,*s14;
char Cs[100];
s12=lookup_widget(objet_graphique38,"entry_exis_res");
s13=lookup_widget(objet_graphique38,"entry_exis_res");

s14=lookup_widget(objet_graphique38,"entry243");
strcpy(Cs,gtk_entry_get_text(GTK_ENTRY(s12)));
if (nomE(Cs)==-1)
gtk_entry_set_text(GTK_ENTRY(s13),"not found");
else 
gtk_entry_set_text(GTK_ENTRY(s14),Cs);
}
*/

void
on_button_rech_res_clicked             (GtkWidget       *objet_graphique39,
                                        gpointer         user_data)
{
GtkWidget *treeview_liste_res, *cin_input;
	char cinrech[9];

	treeview_liste_res = lookup_widget (objet_graphique39, "treeview_reservation");
	cin_input = lookup_widget (objet_graphique39, "entry_rech_rees");

	strcpy (cinrech,gtk_entry_get_text(GTK_ENTRY(cin_input)));

	rech_res (cinrech,treeview_liste_res);

}

/*
void
on_button_rech_rch_clicked             (GtkWidget       *objet_graphique40,
                                        gpointer         user_data)
{
GtkWidget *s121,*s131,*s141,*s151,*s161,*s171,*s181,*s191,*s200,*s210,*s220,*s230;
char Cp[100];
Reservation Z;
s121=lookup_widget(objet_graphique40,"entry_nm_ex");
s131=lookup_widget(objet_graphique40,"entry_nm_ex");
//
s141=lookup_widget(objet_graphique40,"entry_nm_rech");
s230=lookup_widget(objet_graphique40,"entry244");
s151=lookup_widget(objet_graphique40,"entry_pr_rech");
s161=lookup_widget(objet_graphique40,"entry_tl_rech");
s171=lookup_widget(objet_graphique40,"spinbutton_nbr_rech");
s181=lookup_widget(objet_graphique40,"entry_option_rech");
s191=lookup_widget(objet_graphique40,"entry_peri_rech");
s200=lookup_widget(objet_graphique40,"entry236");
s210=lookup_widget(objet_graphique40,"entry_dte_rech");
s220=lookup_widget(objet_graphique40,"spinbutton_hr_res");
strcpy(Cp,gtk_entry_get_text(GTK_ENTRY(s121)));
//
FILE *LO;
int mk=0;
LO = fopen ("res.bin","rb");
while (fread (&Z,sizeof (Reservation),1,LO) != 0)
{
if (strcmp (Z.ref,Cp)==0)
{
gtk_entry_set_text(GTK_ENTRY(s230),Z.ref);
gtk_entry_set_text(GTK_ENTRY(s141),Z.nom_r);
gtk_entry_set_text(GTK_ENTRY(s151),Z.prenom_r);
gtk_entry_set_text(GTK_ENTRY(s161),Z.numero);

gtk_entry_set_text(GTK_ENTRY(s181),Z.option);
gtk_entry_set_text(GTK_ENTRY(s191),Z.periode);
gtk_entry_set_text(GTK_ENTRY(s200),Z.commentaire);
//gtk_entry_set_text(GTK_ENTRY(s210),Z.date);

gtk_spin_button_set_value (s171,Z.nbr);
gtk_spin_button_set_value (s220,Z.heure);
mk=1;
}
}
if (mk==0)
gtk_entry_set_text(GTK_ENTRY(s131),"not found");
fclose (LO);

}

*/
void
on_okbutton2_clicked                   (GtkWidget       *objet_graphique41,
                                        gpointer         user_data)
{
GtkWidget *n1;
n1=lookup_widget(objet_graphique41,"dialog_rech_res");
gtk_widget_destroy(n1);
}




void
on_button_rech_hiss_clicked            (GtkButton       *objet_graphique43,
                                        gpointer         user_data)
{
GtkWidget *treeview_liste_res, *cin_input;
	char cinrech[9];

	treeview_liste_res = lookup_widget (objet_graphique43, "treeview_historique");
	cin_input = lookup_widget (objet_graphique43, "entry_rech_hiss");

	strcpy (cinrech,gtk_entry_get_text(GTK_ENTRY(cin_input)));

	rech_histo  (cinrech,treeview_liste_res);
}


void
on_button_envoyer_email_clicked        (GtkButton       *bojet_graphique44,
                                        gpointer         user_data)
{
GtkWidget *a1,*a2,*a3,*a4;
char n[100],n1[100],n2[100],n3[100];
a1=lookup_widget(bojet_graphique44,"entry_to");
a2=lookup_widget(bojet_graphique44,"entry_from");
a3=lookup_widget(bojet_graphique44,"entry_ob");
a4=lookup_widget(bojet_graphique44,"entry_body");

strcpy(n,gtk_entry_get_text(GTK_ENTRY(a1)));
strcpy(n1,gtk_entry_get_text(GTK_ENTRY(a2)));
strcpy(n2,gtk_entry_get_text(GTK_ENTRY(a3)));
strcpy(n3,gtk_entry_get_text(GTK_ENTRY(a4)));
ajouter_email(n1,n,n2,n3);

char *command;

system ("./email.sh \n");


}
void
on_button_sp_new_clicked               (GtkButton       *objet_graphique45,
                                        gpointer         user_data)
{
FILE *en;
Reservation off;

en=fopen ("res.bin","rb");
while(fread(&off,sizeof(Reservation),1,en))
{
if (strcmp(off.ref,e1.ref)==0)
{



supprimer_res(e1);
}
}


fclose(en);
}



void
on_open_pdf_clicked                    (GtkButton       *objet_graphique46,
                                        gpointer         user_data)
{
pdf (e1);
system ("./pdf.sh");
system ("evince opn.pdf \n");


}


void
on_button_help_clicked                 (GtkButton       *objet_graphique47,
                                        gpointer         user_data)
{
system ("evince help.pdf \n");
}

Client k;
void
on_button_jeux_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
int ab;
FILE *f;
GtkWidget *a,*a1,*a2,*a3,*a4;
char FROM[100],TO[100],SUBJECT[100],BODY[1000];
strcpy (FROM,"CONTACT BORJ LELA");
strcpy (SUBJECT,"Annonce gain concours");
strcpy (BODY,"Chers Client , vous avez gaganer une journée pour deux personne petit-dej et dejeuner inclus , Veuillez nous contacter sur le numero XXXXXXXX . Merci pour votre confiance ");

a=lookup_widget (button,"entry_jeux");
a1=lookup_widget (button,"entry_nom_jx");
a2=lookup_widget (button,"entry_prenom_jx");
a3=lookup_widget (button,"entry_email_jx");
a4=lookup_widget (button,"entry_gsm_jx");

f=fopen("jeux.bin","rb");
ab=jeux_client(k);

g_print("%d",ab);

fseek (f,ab*sizeof(Client),SEEK_SET);
 fread (&k,sizeof (Client),1,f);
 

gtk_entry_set_text(GTK_ENTRY(a),k.cin);
gtk_entry_set_text(GTK_ENTRY(a1),k.nom);
gtk_entry_set_text(GTK_ENTRY(a2),k.prenom);
gtk_entry_set_text(GTK_ENTRY(a3),k.email);
gtk_entry_set_text(GTK_ENTRY(a4),k.numero_de_telephone);
ajouter_email(FROM,k.email,SUBJECT,BODY);
system ("./email.sh \n");
fclose(f);

}


void
on_button_stat_client_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *stat;
stat=create_window_dashbord_client();
gtk_widget_show(stat);
}


void
on_button_GEO_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
Client p;
int nTUNIS=0,nMANOUBA=0,nSEL=0,nKEF=0,nMAH=0,nKAI=0,nBEJA=0,nNAB=0,nSOUSSE=0,nKEB=0,nZAG=0,nBEN=0,nMON=0,nSIDI=0,nKASS=0,nSFAX=0,nTOUZ=0,nMED=0,nGAS=0,nTATA=0,nJEN=0,nBIZ=0,nARIANA=0,nGAB=0;
GtkWidget *nTUNIS1,*nMANOUBA1,*nSEL1,*nKEF1,*nMAH1,*nKAI1,*nBEJA1,*nNAB1,*nSOUSSE1,*nKEB1,*nZAG1,*nBEN1,*nMON1,*nSIDI1,*nKASS1,*nSFAX1,*nTOUZ1,*nMED1,*nGAS1,*nTATA1,*nJEN1,*nBIZ1,*nARIANA1,*nGAB1;

FILE *q;
int kn=0;

q=fopen ("client.bin","rb");

while (fread (&p,sizeof (Client),1,q)!=0)
{ 
	if (strcmp (p.adress,"TUNIS")==0)
	
	nTUNIS++;
	if (strcmp (p.adress,"MANOUBA")==0)
	nMANOUBA++;
	if (strcmp (p.adress,"SELIANA")==0)
	nSEL++;
	if (strcmp (p.adress,"KEF")==0)
	nKEF++;
	if (strcmp (p.adress,"MAHDIA")==0)
	nMAH++;
	if (strcmp (p.adress,"KAIROUAN")==0)
	nKAI++;
	if (strcmp (p.adress,"BEJA")==0)
	nBEJA++;
	if (strcmp (p.adress,"NABEUL")==0)
	nNAB++;
	if (strcmp (p.adress,"SOUSSE")==0)
	nSOUSSE++;
	if (strcmp (p.adress,"KEBILI")==0)
	nKEB++;
	if (strcmp (p.adress,"ZAGHOUAN")==0)
	nZAG++;
	if (strcmp (p.adress,"BEN AROUS")==0)
	nBEN++;
	if (strcmp (p.adress,"MONASTIR")==0)
	nMON++;
	if (strcmp (p.adress,"SIDI BOUZID")==0)
	nSIDI++;
	if (strcmp (p.adress,"KASSERINE")==0)
	nKASS++;
	if (strcmp (p.adress,"SFAX")==0)
	nSFAX++;
	if (strcmp (p.adress,"TOUZEUR")==0)
	nTOUZ++;
	if (strcmp (p.adress,"MEDNINE")==0)
	nMED++;
	if (strcmp (p.adress,"GAFSA")==0)
	nGAS++;
	if (strcmp (p.adress,"TATAOUINE")==0)
	nTATA++;
	if (strcmp (p.adress,"JENDOUBA")==0)
	nJEN++;
	if (strcmp (p.adress,"BIZERTE")==0)
	nBIZ++;
	if (strcmp (p.adress,"ARIANA")==0)
	nARIANA++;
	if (strcmp (p.adress,"GABES")==0)
	nGAB++;
	
kn++;


}
g_print ("%d",nTUNIS);
fclose (q);
nTUNIS1=lookup_widget (button,"entryTn");
	float m= (nTUNIS*100)/kn;
	
  char *str = g_strdup_printf ("%.1f",m);
	strcat (str," %");
gtk_entry_set_text(GTK_ENTRY(nTUNIS1),str);

nMANOUBA1=lookup_widget (button,"entryMAN");
float m1= (nMANOUBA*100)/kn;
 char *str1 = g_strdup_printf ("%.1f", m1);
	strcat (str1," %");
gtk_entry_set_text(GTK_ENTRY(nMANOUBA1),str1);

nSEL1=lookup_widget (button,"entryS");
float m2= (nSEL*100)/kn;
 char *str2 = g_strdup_printf ("%.1f", m2);
strcat (str2," %");
gtk_entry_set_text(GTK_ENTRY(nSEL1),str2);

nKEF1=lookup_widget (button,"entryKE");
	float m3= (nKEF*100)/kn;
 char *str3 = g_strdup_printf ("%.1f", m3);
strcat (str3," %");
gtk_entry_set_text(GTK_ENTRY(nKEF1),str3);

nMAH1=lookup_widget (button,"entryMA");
	float m4= (nMAH*100)/kn;
 char *str4 = g_strdup_printf ("%.1f", m4);
	strcat (str4," %");
gtk_entry_set_text(GTK_ENTRY(nMAH1),str4);

nKAI1=lookup_widget (button,"entryKA");
	float m5= (nKAI*100)/kn;
 char *str5 = g_strdup_printf ("%.1f", m5);
	strcat (str5," %");
gtk_entry_set_text(GTK_ENTRY(nKAI1),str5);

nBEJA1=lookup_widget (button,"entryBE");
float m6= (nBEJA*100)/kn;
 char *str6 = g_strdup_printf ("%.1f", m6);
	strcat (str6," %");
gtk_entry_set_text(GTK_ENTRY(nBEJA1),str6);

nNAB1=lookup_widget (button,"entryNAB");
	float m7= (nNAB*100)/kn;
 char *str7 = g_strdup_printf ("%.1f", m7);
	strcat (str7," %");
gtk_entry_set_text(GTK_ENTRY(nNAB1),str7);

nSOUSSE1=lookup_widget (button,"entrySO");
	float m8= (nSOUSSE*100)/kn;
 char *str8 = g_strdup_printf ("%.1f", m8);
	strcat (str8," %");
gtk_entry_set_text(GTK_ENTRY(nSOUSSE1),str8);
///////
nKEB1=lookup_widget (button,"entryKEB");
	float m9= (nKEB*100)/kn;
 char *str9 = g_strdup_printf ("%.1f", m9);
		strcat (str9," %");
gtk_entry_set_text(GTK_ENTRY(nKEB1),str9);

nZAG1=lookup_widget (button,"entryZAG");
	float m10= (nZAG*100)/kn;
 char *str10 = g_strdup_printf ("%.1f", m10);
	strcat (str10," %");
gtk_entry_set_text(GTK_ENTRY(nZAG1),str10);



nBEN1=lookup_widget (button,"entryBEN");
	float m11= (nBEN*100)/kn;
 char *str11 = g_strdup_printf ("%.1f", m11);
	strcat (str11," %");
gtk_entry_set_text(GTK_ENTRY(nBEN1),str11);


nMON1=lookup_widget (button,"entryMO");
	float m12= (nMON*100)/kn;
 char *str12 = g_strdup_printf ("%.1f", m12);
	strcat (str12," %");
gtk_entry_set_text(GTK_ENTRY(nMON1),str12);

nSIDI1=lookup_widget (button,"entrySI");
	float m13= (nSIDI*100)/kn;
 char *str13 = g_strdup_printf ("%.1f", m13);
	strcat (str13," %");
gtk_entry_set_text(GTK_ENTRY(nSIDI1),str13);


nKASS1=lookup_widget (button,"entryKAS");
	float m14= (nKASS*100)/kn;
 char *str14 = g_strdup_printf ("%.1f", m14);
	strcat (str14," %");
gtk_entry_set_text(GTK_ENTRY(nKASS1),str14);


nSFAX1=lookup_widget (button,"entrySF");
	float m15= (nSFAX*100)/kn;
 char *str15 = g_strdup_printf ("%.1f", m15);
	strcat (str15," %");
gtk_entry_set_text(GTK_ENTRY(nSFAX1),str15);

nTOUZ1=lookup_widget (button,"entryTO");
	float m16= (nTOUZ*100)/kn;
 char *str16 = g_strdup_printf ("%.1f", m16);
	strcat (str16," %");
gtk_entry_set_text(GTK_ENTRY(nTOUZ1),str16);




nMED1=lookup_widget (button,"entryME");
	float m17= (nMED*100)/kn;
 char *str17 = g_strdup_printf ("%.1f", m17);
	strcat (str17," %");
gtk_entry_set_text(GTK_ENTRY(nMED1),str17);


nGAS1=lookup_widget (button,"entryGAF");
	float m18= (nGAS*100)/kn;
 char *str18 = g_strdup_printf ("%.1f", m18);
	strcat (str18," %");
gtk_entry_set_text(GTK_ENTRY(nGAS1),str18);


nTATA1=lookup_widget (button,"entryTATA");
	float m19= (nTATA*100)/kn;
 char *str19 = g_strdup_printf ("%.1f", m19);
	strcat (str19," %");
gtk_entry_set_text(GTK_ENTRY(nTATA1),str19);


nJEN1=lookup_widget (button,"entryJEN");
	float m20= (nJEN*100)/kn;
 char *str20 = g_strdup_printf ("%.1f", m20);
strcat (str20," %");	
gtk_entry_set_text(GTK_ENTRY(nJEN1),str20);


nBIZ1=lookup_widget (button,"entryBI");
	float m21= (nBIZ*100)/kn;
 char *str21 = g_strdup_printf ("%.1f", m21);
	strcat (str21," %");
gtk_entry_set_text(GTK_ENTRY(nBIZ1),str21);



nARIANA1=lookup_widget (button,"entryAR");
	float m22= (nARIANA*100)/kn;
 char *str22 = g_strdup_printf ("%.1f", m22);
	strcat (str22," %");
gtk_entry_set_text(GTK_ENTRY(nARIANA1),str22);


nGAB1=lookup_widget (button,"entryGA");
	float m23= (nGAB*100)/kn;
 char *str23 = g_strdup_printf ("%.1f", m23);
	strcat (str23," %");
gtk_entry_set_text(GTK_ENTRY(nGAB1),str23);











}


void
on_button_SEXE_clicked                 (GtkButton       *objet_graphique55,
                                        gpointer         user_data)
{GtkWidget *d,*MA;
FILE *m;
Client i;
int nbh=0,nbf=0;
m=fopen ("client.bin","rb");
int n=0;
while (fread (&i,sizeof (Client),1,m)!=0)
{ 
	if (strcmp (i.gender,"homme")==0)
	
	nbh++;
	if (strcmp (i.gender,"femme")==0)
	
	nbf++;

	n++;
}
fclose (m);

float o= (nbh*100)/n;
g_print ("%f",o);
float x= (nbf*100)/n;
d=lookup_widget (objet_graphique55,"entrygh");
 char *str30 = g_strdup_printf ("%f", o);
	strcat (str30, " %");
gtk_entry_set_text(GTK_ENTRY(d),str30);


MA=lookup_widget (objet_graphique55,"entrygf");
 char *str31 = g_strdup_printf ("%f", x);
strcat (str31, " %");
gtk_entry_set_text(GTK_ENTRY(MA),str31);




}

void
on_button_gangant_but_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *d1,*MA1,*D5;
FILE *m1;
Client i1;

//m1=fopen ("jeux.bin","rb");

d1=lookup_widget (button,"entry_GCIN");
MA1=lookup_widget (button,"entryGNOM");
D5=lookup_widget (button,"entryGGSM");
//while (fread (&i1,sizeof (Client),1,m1)!=0)

{ 
gtk_entry_set_text(GTK_ENTRY(d1),k.cin);
gtk_entry_set_text(GTK_ENTRY(MA1),k.nom);
gtk_entry_set_text(GTK_ENTRY(D5),k.numero_de_telephone);


}
}
//////////////////////////////////////////////////////////////////////// FIN GESTION CLIENT /////////////////////////////////////////////////



