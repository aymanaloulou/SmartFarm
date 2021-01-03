#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "ouvrier.h"
#include "employee.h"
#include "gestion_clients.h"
#include "equipements.h" 
#include "entretiens.h"
#include "authentification.h"
#include "capteur.h"
#include "plantation.h"
#include "troupeaux.h"









entretiens entr;
employee e,em;
congee cc;

admin ad;
ouvrier o;
ouvrier ouv_m;
pointage pa,pm;
char cin_supp[9];

animal a_s,ah,a,a_m,a_l,a_f;
alim b1 ;
fiche af ; 
int choixt[]={0,0} ; 
char text[20]="" ;
char ref_supp[20];
char ref_supp_hisst[20];
char laitp[20];
char aux[100]="" ;
char age[20];
////////////////////////////////////////////////
void
on_button_change_admin_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget* dialog_modif_admin;
	dialog_modif_admin= create_dialog_modif_admin();
	GtkWidget *input1, *input2, *input3;
	input1 = lookup_widget(dialog_modif_admin, "admin_username");
	input2 = lookup_widget(dialog_modif_admin, "admin_mdp");
	input3 = lookup_widget(dialog_modif_admin, "admin_email");
FILE *f;
f=fopen("admin.bin","rb");
fread(&ad,sizeof(admin),1,f);
	gtk_entry_set_text(GTK_ENTRY(input1),ad.username);
	gtk_entry_set_text(GTK_ENTRY(input2),ad.mdp);
	gtk_entry_set_text(GTK_ENTRY(input3),ad.email);
fclose(f);
	gtk_widget_show(dialog_modif_admin);
}

void
on_cancel_par_admin_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *dialog = lookup_widget(button,"dialog_modif_admin");
gtk_widget_destroy(dialog);
}


void
on_ok_par_admin_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *input1, *input2, *input3;
GtkWidget *dialog = lookup_widget(button,"dialog_modif_admin");
input1 = lookup_widget(dialog, "admin_username");
input2 = lookup_widget(dialog, "admin_mdp");
input3 = lookup_widget(dialog, "admin_email");
FILE *f;
f=fopen("admin.bin","wb");
strcpy(ad.username,gtk_entry_get_text(GTK_ENTRY(input1)));
strcpy(ad.mdp,gtk_entry_get_text(GTK_ENTRY(input2)));
strcpy(ad.email,gtk_entry_get_text(GTK_ENTRY(input3)));
fwrite (&ad,sizeof(admin),1,f);
fclose(f);
gtk_widget_destroy(dialog);
}

///////////////////////////////////////////////
char to_auth[100];
char pass_auth[50];
void
on_button_login_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
FILE *f;
f=fopen("admin.bin","rb");
fread(&ad,sizeof(admin),1,f);
fclose(f);
GtkWidget *input1, *input2;
GtkWidget *window_mdp = create_window_wrong_pass();
GtkWidget *window_id = create_window_wrong_id();
GtkWidget *window_admin = create_window_espace_admin();
GtkWidget *window_employee = create_window_employee_space();
GtkWidget *window_auth = lookup_widget(button,"window_authentification");
char id[50],mdp[50];
input1 = lookup_widget(button, "user_id");
input2 = lookup_widget(button, "user_mdp");
strcpy(id,gtk_entry_get_text(GTK_ENTRY(input1)));
strcpy(mdp,gtk_entry_get_text(GTK_ENTRY(input2)));

if (strcmp(id,ad.username)==0)
	{
		if (strcmp(mdp,ad.mdp)==0)
			{gtk_widget_show(window_admin);
			gtk_widget_destroy(window_auth);}
		else
			{
				strcpy(to_auth,ad.email);
				strcpy(pass_auth,ad.mdp);
				gtk_widget_show(window_mdp);
			}
	}
else
	{
		if (CINExiste_emp (id))
			{
				get_pass(id, pass_auth);
				get_mail( id, to_auth);
				if (strcmp(mdp,pass_auth)==0)
					{gtk_widget_show(window_employee);
					gtk_widget_destroy(window_auth);}
				else
					gtk_widget_show(window_mdp);
			}
		else
			gtk_widget_show(window_id);
	}
}


void
on_button_mdp_oublie_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *window_mdp = lookup_widget(button,"window_wrong_pass");
GtkWidget *window_mail = create_window_mail_envoye();
mail_mdp_oub(to_auth,pass_auth);
system ("./email.sh \n");
gtk_widget_destroy(window_mdp);
gtk_widget_show(window_mail);
}

///////////////////////////////////////////////

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
GtkWidget *window_emp = lookup_widget(objet_graphique1,"window_employee_space");
gtk_widget_destroy(window_emp);

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



/****************************************************
 
 * Meilleur ouvrier / taux absentéisme

*****************************************************/
void
on_okbutton_meilleur_ouv_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *dialog = lookup_widget(button,"dialog_meilleur_ouv");
	gtk_widget_destroy(dialog);
}


void
on_button_affich_best_ouv_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
    struct date be;
    GtkWidget *calendar = lookup_widget (button,"calendar_best_ouv");
    gtk_calendar_get_date (calendar,&be.a,&be.m,&be.j);
	be.m++;
    fn_meilleur_ouvrier (be,button);
}


void
on_okbutton_taux_abs_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *dialog = lookup_widget(button,"dialog_taux_abs");
	gtk_widget_destroy(dialog);
}

void
on_button_affich_ta_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
    struct date be;
    GtkWidget *calendar = lookup_widget (button,"calendar_ta");
    gtk_calendar_get_date (calendar,&be.a,&be.m,&be.j);
	be.m++;
    fn_taux_abs (be, button);    
}






void
on_button_gestion_ouv_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *window_gest_ouvrier;
  	window_gest_ouvrier = create_window_gest_ouvrier ();
 	gtk_widget_show (window_gest_ouvrier);
GtkWidget *window_emp = lookup_widget(button,"window_employee_space");
gtk_widget_destroy(window_emp);
}


void
on_button_gestion_employee_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *window_gest_emp;	
	window_gest_emp = create_window_gest_emp ();
  	gtk_widget_show (window_gest_emp);
}


void
on_button_show_bw_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *dialog = create_dialog_meilleur_ouv ();
	gtk_widget_show(dialog);
}


void
on_button_show_ta_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *dialog = create_dialog_taux_abs ();
	gtk_widget_show(dialog);
}

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////   GESTION D'EQUIPEMENTS ET SES ENTRETIENS  //////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

void
on_button_gestion_equipements_clicked  (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *window1;
  	window1 = create_window_equipements ();
 	gtk_widget_show (window1);
	GtkWidget *window_emp = lookup_widget(button,"window_employee_space");
gtk_widget_destroy(window_emp);
}




///////////////////////////////////////////////////////////////////////
/* EQUIPEMENTS !!!
//////////////////////////////////////////////////////////////////////*/

equipements eq2;
char info0[200]="";

void
on_button_ajouter_equipement_clicked   (GtkWidget       *button, gpointer         user_data)
{
	GtkWidget* dialog_ajouter_equipement;
	dialog_ajouter_equipement=create_dialog_ajouter_equipement();
	gtk_widget_show(dialog_ajouter_equipement);
}

void
on_treeview_equipement_row_activated   (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	GtkWidget* window_choix;
	window_choix=create_choix_equipement();
	GtkWidget *e_id = lookup_widget (window_choix,"e_id");

	GtkTreeIter iter;
	gchar* id;
	gchar* type;
	gchar* marque;
	gchar* date;
	gchar* prix;
	gchar* association;
	equipements eq;
	
	GtkTreeModel *model = gtk_tree_view_get_model(treeview);
	if (gtk_tree_model_get_iter(model, &iter, path))
	{
		gtk_tree_model_get(GTK_LIST_STORE(model), &iter, 0, &id,1, &type,2, &marque,3, &date,4, &prix,5, &association, -1);
		strcpy(eq2.id,id);
		strcpy(eq2.type,type);
		strcpy(eq2.marque,marque);
		strcpy(eq2.date,date);
		sscanf (eq2.date,"%2d/%2d/%4d",&eq2.jour,&eq2.mois,&eq2.annee);
		strcpy(eq2.prix,prix);
		strcpy(eq2.association,association);
		strcat(info0,"Equipement d'identifiant ");
		strcat(info0,eq2.id);
		strcat(info0," qui a été ajouté le ");
		strcat(info0,date);

		gtk_label_set_text(GTK_LABEL(e_id),info0);
		gtk_widget_show(window_choix);
strcpy(info0,"");
		
}
}


void
on_actualiser_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *treeview;
treeview = lookup_widget(button,"treeview_equipement");
afficher_equipement(treeview);
}


void
on_recherche1_clicked                  (GtkButton       *objet,
                                        gpointer         user_data)
{
GtkTreeView *treeview;
treeview = lookup_widget(objet,"treeview_equipement");
GtkWidget  *input_1;
input_1 = lookup_widget (objet, "entry_eq");
rech_eq(gtk_entry_get_text(GTK_ENTRY(input_1)),treeview);
}

void
on_ok_ajouter1_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)
{

equipements eq;
GtkWidget *input1, *input2, *input3, *input5, *input6, *input_date;

GtkWidget *dialog_ajouter;
dialog_ajouter = lookup_widget(objet,"dialog_ajouter_equipement");

input1=lookup_widget(objet,"id");
input2=lookup_widget(objet,"type");
input3=lookup_widget(objet,"marque");
input_date = lookup_widget(objet, "calendar_aj_eq");
input5=lookup_widget(objet,"prix");
input6=lookup_widget(objet,"association");
strcpy(eq.date,"");
strcpy(eq.id,gtk_entry_get_text(GTK_ENTRY(input1)));
strcpy(eq.type,gtk_entry_get_text(GTK_ENTRY(input2)));
strcpy(eq.marque,gtk_entry_get_text(GTK_ENTRY(input3)));
gtk_calendar_get_date(input_date,&eq.annee,&eq.mois,&eq.jour);
eq.mois++;
sprintf (eq.date,"%d/%d/%d",eq.jour,eq.mois,eq.annee);
strcpy(eq.prix,gtk_entry_get_text(GTK_ENTRY(input5)));
strcpy(eq.association,gtk_entry_get_text(GTK_ENTRY(input6)));

if(ajouter_equipement(eq,objet))
	gtk_widget_destroy(dialog_ajouter);

}

void
on_cancel_aj_eq_clicked                (GtkButton       *objet,
                                        gpointer         user_data)
{
GtkWidget *dialog_ajouter;
dialog_ajouter = lookup_widget(objet,"dialog_ajouter_equipement");
	gtk_widget_destroy(dialog_ajouter);
}


void
on_button_modifier_equipement_clicked  (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget* dialog_modifier_equipement;
	GtkWidget* window_choix;
	GtkWidget *input1, *input2, *input3, *input4, *input5, *input_j, *input_a, *input_m;
dialog_modifier_equipement=create_dialog_modifier_equipement();
input1=lookup_widget(dialog_modifier_equipement,"id");
input2=lookup_widget(dialog_modifier_equipement,"type");
input3=lookup_widget(dialog_modifier_equipement,"marque");
input4=lookup_widget(dialog_modifier_equipement,"prix");
input5=lookup_widget(dialog_modifier_equipement,"association");
input_j = lookup_widget(dialog_modifier_equipement, "jour");
input_m = lookup_widget(dialog_modifier_equipement, "mois");
input_a = lookup_widget(dialog_modifier_equipement, "annee");
	gtk_entry_set_text (GTK_ENTRY (input1), _(eq2.id));
	gtk_entry_set_text (GTK_ENTRY (input2), _(eq2.type));
	gtk_entry_set_text (GTK_ENTRY (input3), _(eq2.marque));
	gtk_entry_set_text (GTK_ENTRY (input4), _(eq2.prix));
	gtk_entry_set_text (GTK_ENTRY (input5), _(eq2.association));
	gtk_spin_button_set_value (input_j,eq2.jour);
	gtk_spin_button_set_value (input_m,eq2.mois);
	gtk_spin_button_set_value (input_a,eq2.annee);
	window_choix=lookup_widget(objet,"choix_equipement");
	gtk_widget_destroy(window_choix);
	gtk_widget_show(dialog_modifier_equipement);
}

	
void
on_ok_modifier1_clicked                (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *input1, *input2, *input3, *input5, *input6, *input_j, *input_m, *input_a, *input_annee;
GtkWidget *dialog_modifier;
dialog_modifier = lookup_widget(objet,"dialog_modifier_equipement");
supprimer_equipement(eq2.id);
input1=lookup_widget(objet,"id");
input2=lookup_widget(objet,"type");
input3=lookup_widget(objet,"marque");
input_j = lookup_widget(objet, "jour");
input_m = lookup_widget(objet, "mois");
input_a = lookup_widget(objet, "annee");
input5=lookup_widget(objet,"prix");
input6=lookup_widget(objet,"association");

strcpy(eq2.id,gtk_entry_get_text(GTK_ENTRY(input1)));
strcpy(eq2.type,gtk_entry_get_text(GTK_ENTRY(input2)));
strcpy(eq2.marque,gtk_entry_get_text(GTK_ENTRY(input3)));
eq2.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_j));
eq2.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_m));
eq2.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_a));
sprintf (eq2.date,"%d/%d/%d",eq2.jour,eq2.mois,eq2.annee);
strcpy(eq2.prix,gtk_entry_get_text(GTK_ENTRY(input5)));
strcpy(eq2.association,gtk_entry_get_text(GTK_ENTRY(input6)));

if(ajouter_equipement(eq2,objet))
	gtk_widget_destroy(dialog_modifier);
}

void
on_cancel_moif_eq_clicked              (GtkButton       *objet,
                                        gpointer         user_data)
{
GtkWidget *dialog_modifier;
dialog_modifier = lookup_widget(objet,"dialog_modifier_equipement");
	gtk_widget_destroy(dialog_modifier);
}

void
on_button_supprimer_equipement_clicked (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget* window_choix;
	window_choix=lookup_widget(objet,"choix_equipement");
	supprimer_equipement(eq2.id);
	gtk_widget_destroy(window_choix);

}

void
on_button_declarer_eq_clicked          (GtkButton       *objet,
                                        gpointer         user_data)
{
GtkWidget* window_choix;
window_choix=lookup_widget(objet,"choix_equipement");
declarer_eq(eq2);
gtk_widget_destroy(window_choix);
}

void
on_combo_entry_tri_changed             (GtkEditable     *editable,
                                        gpointer         user_data)
{
GtkWidget *treeview, *combotri, *combo_entry_tri ;
char ch[20];
combotri = lookup_widget(editable,"combotri");
combo_entry_tri = GTK_COMBO(combotri)->entry;
strcpy(ch,gtk_entry_get_text(GTK_ENTRY(combo_entry_tri)));
treeview = lookup_widget(editable,"treeview_equipement");
if (strcmp("ID+",ch )==0)
	{
	tri_file_min_id_eq();
	afficher_tri_eq(treeview);
	}
if (strcmp("ID-",ch )==0)
	{
	tri_file_max_id_eq();
	afficher_tri_eq(treeview);
	}
if (strcmp("Prix-",ch )==0)
	{
	tri_file_max_prix_eq();
	afficher_tri_eq(treeview);
	}
if (strcmp("Prix+",ch )==0)
	{
	tri_file_min_prix_eq();
	afficher_tri_eq(treeview);
	}
if (strcmp("Type+",ch )==0)
	{
	tri_file_min_type_eq();
	afficher_tri_eq(treeview);
	}
if (strcmp("Type-",ch )==0)
	{
	tri_file_max_type_eq();
	afficher_tri_eq(treeview);
	}
if (strcmp("Marque+",ch )==0)
	{
	tri_file_min_marque_eq();
	afficher_tri_eq(treeview);
	}
if (strcmp("Marque-",ch )==0)
	{
	tri_file_max_marque_eq();
	afficher_tri_eq(treeview);
	}
if (strcmp("Ouvriers+",ch )==0)
	{
	tri_file_min_association_eq();
	afficher_tri_eq(treeview);
	}
if (strcmp("Ouvriers-",ch )==0)
	{
	tri_file_max_association_eq();
	afficher_tri_eq(treeview);
	}
if (strcmp("Date+",ch )==0)
	{
	tri_file_min_date_eq();
	afficher_tri_eq(treeview);
	}
if (strcmp("Date-",ch )==0)
	{
	tri_file_max_date_eq();
	afficher_tri_eq(treeview);
	}
}

///////////////////////////////////////////////////////////////////////
/* ENTRETIENS !!!
//////////////////////////////////////////////////////////////////////*/
int paye[]={0,0,0};
void
on_checkbutton_ajout_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

if (gtk_toggle_button_get_active(togglebutton))
	paye[0]=1;

}


void
on_radiobutton_espece_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{

	paye[1]=1;
	paye[2]=0;
}


void
on_radiobutton_autre_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
	paye[2]=1;
	paye[1]=0;
}

//////////////////////////////////////////////////////

void
on_button_ajouter_entretien_clicked    (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget* dialog_ajouter_entretien;
	GtkComboBox *combobox;
	dialog_ajouter_entretien=create_dialog_ajouter_entretien();
	combobox = lookup_widget(dialog_ajouter_entretien,"combobox_id");
	set_combo_entretien(combobox);
	gtk_widget_show(dialog_ajouter_entretien);
}

entretiens entr2;
char info[1000]="";

void
on_treeview_entretien_row_activated    (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	GtkWidget* window_choix;
	window_choix=create_choix_entretien();
	GtkWidget *e_id = lookup_widget (window_choix,"e_id");

	GtkTreeIter iter;
	gchar* id_eq;
	gchar* id_entr;
	gchar* date;
	gchar* entreteneur ;
	gchar* montant;
	gchar* payement;
	gchar* type_payement;
	gchar* reference;
	
	GtkTreeModel *model = gtk_tree_view_get_model(treeview);
	if (gtk_tree_model_get_iter(model, &iter, path))
	{
		gtk_tree_model_get(GTK_LIST_STORE(model), &iter, 0, &id_eq,1, &date,2, &entreteneur,3, &montant,4, &payement,5,&type_payement,6,&reference, -1);
		strcpy(entr2.id_eq,id_eq);
		strcpy(entr2.date,date);
		sscanf (entr2.date,"%2d/%2d/%4d",&entr2.jour,&entr2.mois,&entr2.annee);
		strcpy(entr2.entreteneur,entreteneur);
		strcpy(entr2.montant,montant);
		strcpy(entr2.payement,payement);
		strcpy(entr2.type_payement,type_payement);
		strcpy(entr2.reference,reference);
		strcat(info,"Entretien de l'équipements ");
		strcat(info,entr2.id_eq);
		strcat(info," qui a été le ");
		strcat(info,date);

strcpy(entr2.id_entr,entr2.date);
strcat(entr2.id_entr,entr2.id_eq);


		gtk_label_set_text(GTK_LABEL(e_id),info);
		gtk_widget_show(window_choix);
strcpy(info,"");
		
}
}

void
on_button_modifier_entretien_clicked   (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget* dialog_modifier_entretien;
	GtkComboBox *combobox;
	GtkWidget* window_choix;
dialog_modifier_entretien=create_dialog_modifier_entretien();
GtkWidget *id_modif = lookup_widget (dialog_modifier_entretien,"id_modif");

GtkWidget  *input2, *input3, *input4, *input_j, *input_m, *input_a;

input2=lookup_widget(dialog_modifier_entretien,"entreteneur");
input3=lookup_widget(dialog_modifier_entretien,"montant");
input4=lookup_widget(dialog_modifier_entretien,"reference");
input_j = lookup_widget(dialog_modifier_entretien, "jour");
input_m = lookup_widget(dialog_modifier_entretien, "mois");
input_a = lookup_widget(dialog_modifier_entretien, "annee");

	window_choix=lookup_widget(objet,"choix_entretien");

	combobox = lookup_widget(dialog_modifier_entretien,"combobox_id");
	set_combo_entretien(combobox);
	gtk_entry_set_text (GTK_ENTRY (input2), _(entr2.entreteneur));
	gtk_entry_set_text (GTK_ENTRY (input3), _(entr2.montant));
	gtk_entry_set_text (GTK_ENTRY (input4), _(entr2.reference));
	gtk_spin_button_set_value (input_j,entr2.jour);
	gtk_spin_button_set_value (input_m,entr2.mois);
	gtk_spin_button_set_value (input_a,entr2.annee);

	
		strcat(info,"Entretien de l'équipements ");
		strcat(info,entr2.id_eq);
		strcat(info," qui a été le ");
		strcat(info,entr2.date);
 	gtk_label_set_text(GTK_LABEL(id_modif),info);
	gtk_widget_show(dialog_modifier_entretien);
	gtk_widget_destroy(window_choix);
strcpy(info,"");

}

void
on_button_pdf_entr_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
pdf_entr (entr2);
system ("./pdf.sh");
system ("evince opn.pdf \n");
}

void
on_ok_ajouter2_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)
{
entretiens entr;
char text1[20]="";
char text2[20]="";
GtkWidget  *input2, *input3,*input4, *input_date;
GtkComboBox *input1;
GtkWidget *dialog_ajouter;
dialog_ajouter = lookup_widget(objet,"dialog_ajouter_entretien");

input1 = lookup_widget(objet,"combobox_id");
input_date = lookup_widget(objet, "calendar_aj_entr");
input2=lookup_widget(objet,"entreteneur");
input3=lookup_widget(objet,"montant");
input4=lookup_widget(objet,"reference");

payement(paye, text1,text2);
paye[0]=0;
paye[1]=0;
paye[2]=0;
strcpy(entr.payement,text1);
strcpy(entr.type_payement,text2);
strcpy(entr.id_eq, gtk_combo_box_get_active_text(GTK_COMBO_BOX(input1)));
gtk_calendar_get_date(input_date,&entr.annee,&entr.mois,&entr.jour);
entr.mois++;
sprintf (entr.date,"%d/%d/%d",entr.jour,entr.mois,entr.annee);
strcpy(entr.entreteneur,gtk_entry_get_text(GTK_ENTRY(input2)));
strcpy(entr.montant,gtk_entry_get_text(GTK_ENTRY(input3)));
strcpy(entr.reference,gtk_entry_get_text(GTK_ENTRY(input4)));


strcpy(entr.id_entr,entr.date);
strcat(entr.id_entr,entr.id_eq);

if (ajouter_entretien(entr,objet))
	gtk_widget_destroy(dialog_ajouter);
}


void
on_cancel_aj_entr_clicked              (GtkButton       *objet,
                                        gpointer         user_data)
{
GtkWidget *dialog_ajouter;
dialog_ajouter = lookup_widget(objet,"dialog_ajouter_entretien");
	gtk_widget_destroy(dialog_ajouter);
}


void
on_ok_modifier2_clicked                (GtkWidget       *objet,
                                        gpointer         user_data)
{

char text1[20]="";
char text2[20]="";
int j,m,a;
GtkWidget  *input2, *input3, *input4, *input_j, *input_m, *input_a, *input_annee;
GtkComboBox *input1;
GtkWidget *dialog_modifier;

dialog_modifier = lookup_widget(objet,"dialog_modifier_entretien");


supprimer_entretien(entr2);

input1 = lookup_widget(objet,"combobox_id");
input_j = lookup_widget(objet, "jour");
input_m = lookup_widget(objet, "mois");
input_a = lookup_widget(objet, "annee");
input2=lookup_widget(objet,"entreteneur");
input3=lookup_widget(objet,"montant");
input4=lookup_widget(objet,"reference");

payement(paye, text1,text2);
paye[0]=0;
paye[1]=0;
paye[2]=0;
strcpy(entr2.payement,text1);
strcpy(entr2.type_payement,text2);
strcpy(entr2.id_eq, gtk_combo_box_get_active_text(GTK_COMBO_BOX(input1)));
entr2.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_j));
entr2.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_m));
entr2.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_a));
sprintf (entr2.date,"%d/%d/%d",entr2.jour,entr2.mois,entr2.annee);
strcpy(entr2.entreteneur,gtk_entry_get_text(GTK_ENTRY(input2)));
strcpy(entr2.montant,gtk_entry_get_text(GTK_ENTRY(input3)));
strcpy(entr2.reference,gtk_entry_get_text(GTK_ENTRY(input4)));
strcpy(entr2.id_entr,entr2.date);
strcat(entr2.id_entr,entr2.id_eq);

if (ajouter_entretien(entr2,objet))
	gtk_widget_destroy(dialog_modifier);
}

void
on_cancel_modif_entr_clicked           (GtkButton       *objet,
                                        gpointer         user_data)
{
GtkWidget *dialog_modifier;
dialog_modifier = lookup_widget(objet,"dialog_modifier_entretien");
	gtk_widget_destroy(dialog_modifier);
}

void
on_button_supprimer_entretien_clicked  (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget* window_choix;
	window_choix=lookup_widget(objet,"choix_entretien");

supprimer_entretien(entr2);
gtk_widget_destroy(window_choix);
}

void
on_recherche2_clicked                  (GtkButton       *objet,
                                        gpointer         user_data)
{
GtkTreeView *treeview;
treeview = lookup_widget(objet,"treeview_entretien");
GtkWidget  *input_1;
input_1 = lookup_widget (objet, "entry_entr");
rech_entr(gtk_entry_get_text(GTK_ENTRY(input_1)),treeview);

}

void
on_actualiser2_clicked                 (GtkButton       *objet,
                                        gpointer         user_data)
{
GtkTreeView *treeview;
treeview = lookup_widget(objet,"treeview_entretien");
afficher_entretien(treeview);
}


void
on_combobox_id_changed                 (GtkComboBox     *combobox,
                                        gpointer         user_data)
{

}

void
on_combo_entry_tri_entr_changed        (GtkEditable     *editable,
                                        gpointer         user_data)
{
GtkWidget *treeview, *combotri, *combo_entry_tri ;
char ch[20];
combotri = lookup_widget(editable,"combotrientr");
combo_entry_tri = GTK_COMBO(combotri)->entry;
strcpy(ch,gtk_entry_get_text(GTK_ENTRY(combo_entry_tri)));
treeview = lookup_widget(editable,"treeview_entretien");
if (strcmp("ID+",ch )==0)
	{
	tri_file_min_id_entr();
	afficher_tri_entretien(treeview);
	}
if (strcmp("ID-",ch )==0)
	{
	tri_file_max_id_entr();
	afficher_tri_entretien(treeview);
	}
if (strcmp("Date+",ch )==0)
	{
	tri_file_min_date_entr();
	afficher_tri_entretien(treeview);
	}
if (strcmp("Date-",ch )==0)
	{
	tri_file_max_date_entr();
	afficher_tri_entretien(treeview);
	}
if (strcmp("Entreteneur+",ch )==0)
	{
	tri_file_min_entreteneur_entr();
	afficher_tri_entretien(treeview);
	}
if (strcmp("Entreteneur-",ch )==0)
	{
	tri_file_max_entreteneur_entr();
	afficher_tri_entretien(treeview);
	}
if (strcmp("Montant+",ch )==0)
	{
	tri_file_min_montant_entr();
	afficher_tri_entretien(treeview);
	}
if (strcmp("Montant-",ch )==0)
	{
	tri_file_max_montant_entr();
	afficher_tri_entretien(treeview);
	}
if (strcmp("Reference+",ch )==0)
	{
	tri_file_min_reference_entr();
	afficher_tri_entretien(treeview);
	}
if (strcmp("Reference-",ch )==0)
	{
	tri_file_max_reference_entr();
	afficher_tri_entretien(treeview);
	}
if (strcmp("Payement",ch )==0)
	{
	tri_file_min_payement_entr();
	afficher_tri_entretien(treeview);
	}
if (strcmp("Type de payement",ch )==0)
	{
	tri_file_min_type_payement_entr();
	afficher_tri_entretien(treeview);
	}
}

/*//////////////////////////////////////////////////////
//////////// HISTORIQUE ///////////////////////*/
int h;
void
on_radiobutton_eq_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *scrolledwindow14; 
 GtkWidget *scrolledwindow13; 
GtkWidget *treeview_historique_eq;
h=0;
treeview_historique_eq = lookup_widget(button,"treeview_historique_eq");
scrolledwindow14 = lookup_widget(button,"scrolledwindow14");
scrolledwindow13 = lookup_widget(button,"scrolledwindow13");
gtk_widget_show_all(scrolledwindow13);
gtk_widget_hide_all(scrolledwindow14);
afficher_histo_eq(treeview_historique_eq);

}


void
on_radiobutton_entr_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{

 GtkWidget *scrolledwindow14; 
 GtkWidget *scrolledwindow13; 
GtkWidget *treeview_historique_entr;
h=1;
treeview_historique_entr = lookup_widget(button,"treeview_historique_entr");
scrolledwindow14 = lookup_widget(button,"scrolledwindow14");
scrolledwindow13 = lookup_widget(button,"scrolledwindow13");
gtk_widget_hide_all(scrolledwindow13);
gtk_widget_show_all(scrolledwindow14);
afficher_histo_entr(treeview_historique_entr);

}


void
on_treeview_historique_entr_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	GtkWidget* window_choix;
	window_choix=create_choix_historique();

	GtkTreeIter iter;
	gchar* id_eq;
	gchar* id_entr;
	gchar* date;
	gchar* entreteneur ;
	gchar* montant;
	gchar* payement;
	gchar* type_payement;
	gchar* reference;
	
	GtkTreeModel *model = gtk_tree_view_get_model(treeview);
	if (gtk_tree_model_get_iter(model, &iter, path))
	{
		gtk_tree_model_get(GTK_LIST_STORE(model), &iter, 0, &id_eq,1, &date,2, &entreteneur,3, &montant,4, &payement,5,&type_payement,6,&reference, -1);
		strcpy(entr2.id_eq,id_eq);
		strcpy(entr2.date,date);
		strcpy(entr2.entreteneur,entreteneur);
		strcpy(entr2.montant,montant);
		strcpy(entr2.payement,payement);
		strcpy(entr2.type_payement,type_payement);
		strcpy(entr2.reference,reference);

strcpy(entr2.id_entr,entr2.date);
strcat(entr2.id_entr,entr2.id_eq);


		gtk_widget_show(window_choix);
}
}

void
on_treeview_historique_eq_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	GtkWidget* window_choix;
	window_choix=create_choix_historique();

	GtkTreeIter iter;
	gchar* id;
	gchar* type;
	gchar* marque;
	gchar* date;
	gchar* prix;
	gchar* association;

	
	GtkTreeModel *model = gtk_tree_view_get_model(treeview);
	if (gtk_tree_model_get_iter(model, &iter, path))
	{
		gtk_tree_model_get(GTK_LIST_STORE(model), &iter, 0, &id,1, &type,2, &marque,3, &date,4, &prix,5, &association, -1);
		strcpy(eq2.id,id);
		strcpy(eq2.type,type);
		strcpy(eq2.marque,marque);
		strcpy(eq2.date,date);
		strcpy(eq2.prix,prix);
		strcpy(eq2.association,association);

		gtk_widget_show(window_choix);
}

}
void
on_reset_histo_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget* window_choix;
window_choix=lookup_widget(button,"choix_historique");

if (h==0)
	{
	rest_eq(eq2);
	supp_histo_eq(eq2.id);
	}
else
	{
	rest_entr(entr2);
	supp_histo_entr(entr2.id_entr);
	}
gtk_widget_destroy(window_choix);	
}


void
on_supp_histo_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget* window_choix;
window_choix=lookup_widget(button,"choix_historique");
GtkWidget* dialog_confirmer_supp_eq;
GtkWidget* dialog_confirmer_supp_entr;
dialog_confirmer_supp_eq=create_dialog_confirmer_supp_eq();
dialog_confirmer_supp_entr=create_dialog_confirmer_supp_entr();
if (h==0)
gtk_widget_show(dialog_confirmer_supp_eq);
else
	gtk_widget_show(dialog_confirmer_supp_entr);
gtk_widget_destroy(window_choix);
}

void
on_cancel_confirm_supp_eq_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget* dialog_confirm;
dialog_confirm=lookup_widget(button,"dialog_confirmer_supp_eq");
gtk_widget_destroy(dialog_confirm);
}

void
on_ok_confirm_supp_eq_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget* dialog_confirm;
dialog_confirm=lookup_widget(button,"dialog_confirmer_supp_eq");
supp_histo_eq(eq2.id);
gtk_widget_destroy(dialog_confirm);
}

void
on_cancel_confirm_supp_entr_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget* dialog_confirm;
dialog_confirm=lookup_widget(button,"dialog_confirmer_supp_entr");
gtk_widget_destroy(dialog_confirm);
}


void
on_ok_confirm_supp_entr_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget* dialog_confirm;
dialog_confirm=lookup_widget(button,"dialog_confirmer_supp_entr");
supp_histo_entr(entr2.id_entr);
gtk_widget_destroy(dialog_confirm);
}


equipements eqp;

void
on_treeview_declar_eq_row_activated    (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	GtkWidget* window_choix;
	window_choix=create_choix_declar_eq();

	GtkTreeIter iter;
	gchar* id;
	gchar* type;
	gchar* marque;
	gchar* date;
	gchar* prix;
	gchar* association;
	
	GtkTreeModel *model = gtk_tree_view_get_model(treeview);
	if (gtk_tree_model_get_iter(model, &iter, path))
	{
		gtk_tree_model_get(GTK_LIST_STORE(model), &iter, 0, &id,1, &type,2, &marque,3, &date,4, &prix,5, &association, -1);
		strcpy(eqp.id,id);
		strcpy(eqp.type,type);
		strcpy(eqp.marque,marque);
		strcpy(eqp.date,date);
		sscanf (eqp.date,"%2d/%2d/%4d",&eqp.jour,&eqp.mois,&eqp.annee);
		strcpy(eqp.prix,prix);
		strcpy(eqp.association,association);
		
		gtk_widget_show(window_choix);
		
}
}


void
on_recherche_declar_eq_clicked         (GtkButton       *objet,
                                        gpointer         user_data)
{
GtkTreeView *treeview;
treeview = lookup_widget(objet,"treeview_declar_eq");
GtkWidget  *input_1;
input_1 = lookup_widget (objet, "entry_declar_eq");
rech_declar_eq(gtk_entry_get_text(GTK_ENTRY(input_1)),treeview);
}


void
on_supp_declar_eq_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget* window_choix;
GtkWidget* dialog_ajouter_entretien;
GtkComboBox *combobox;
dialog_ajouter_entretien=create_dialog_ajouter_entretien();
combobox = lookup_widget(dialog_ajouter_entretien,"combobox_id");
window_choix=lookup_widget(button,"choix_declar_eq");
supp_declar_eq(eqp.id);
gtk_widget_destroy(window_choix);
set_combo_entretien(combobox);
gtk_widget_show(dialog_ajouter_entretien);
}


void
on_mettre_en_top_eq_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget* window_choix;
window_choix=lookup_widget(button,"choix_declar_eq");
mettre_top(eqp);
gtk_widget_destroy(window_choix);
}


void
on_actualiser_declar_eq_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *treeview;
treeview = lookup_widget(button,"treeview_declar_eq");
afficher_declar_eq(treeview);
}


void
on_alerte_declar_eq_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget* window_choix;
window_choix=lookup_widget(button,"choix_declar_eq");
GtkWidget* dialog_dest_declar_eq;
dialog_dest_declar_eq = create_dialog_dest_declar_eq();
gtk_widget_destroy(window_choix);
gtk_widget_show(dialog_dest_declar_eq);
}


void
on_ok_dest_declar_eq_clicked           (GtkButton       *objet,
                                        gpointer         user_data)
{
GtkWidget  *input ;
GtkWidget* window_dest;
window_dest=lookup_widget(objet,"dialog_dest_declar_eq");
input=lookup_widget(objet,"dest_declar_eq");
char TO[200];
strcpy(TO,gtk_entry_get_text(GTK_ENTRY(input)));
mail_declar_eq(TO, eqp);
system ("./email.sh \n");
gtk_widget_destroy(window_dest);
}

/******************************************************************
************************ DASHBORD *********************************
******************************************************************/

void
on_button_stat_equip_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget* window_stat;
window_stat = create_window_affiche_equip();
gtk_widget_show(window_stat);
}


void
on_radiobutton_entr_npaye_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *treeview_stat_entr;
treeview_stat_entr = lookup_widget(button,"treeview_stat_entr");
afficher_entr_payement(treeview_stat_entr,"Non Payé");
}


void
on_radiobutton_entr_paye_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *treeview_stat_entr;
treeview_stat_entr = lookup_widget(button,"treeview_stat_entr");
afficher_entr_payement(treeview_stat_entr,"Payé");
}


void
on_button_show_eq_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *treeview_stat_eq;
treeview_stat_eq = lookup_widget(button,"treeview_stat_eq");
GtkWidget *output1,*output2, *output3;
output1 = lookup_widget(button,"nbr_eq");
output2 = lookup_widget(button,"prix_tot");
output3 = lookup_widget(button,"nbr_declar");
int ne,nd,pt;
ne= nbre_eq();
nd= nbre_declar_eq();
pt= prix_eq();
char *n1 = g_strdup_printf ("%d", ne);
char *n2 = g_strdup_printf ("%d", pt);
strcat(n2," DT");
char *n3 = g_strdup_printf ("%d", nd);
gtk_entry_set_text(GTK_ENTRY(output1),n1);
gtk_entry_set_text(GTK_ENTRY(output2),n2);
gtk_entry_set_text(GTK_ENTRY(output3),n3);
afficher_declar_eq(treeview_stat_eq);
}


void
on_button_show_entr_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *output1,*output2, *output3;
output1 = lookup_widget(button,"cout_tot");
output2 = lookup_widget(button,"mont_paye");
output3 = lookup_widget(button,"mont_npaye");
int ct,mp,mn;
mp= prix_entr_paye();
mn= prix_entr_non_paye();
ct= mn+mp;
char *n1 = g_strdup_printf ("%d", ct);
strcat(n1," DT");
char *n2 = g_strdup_printf ("%d", mp);
strcat(n2," DT");
char *n3 = g_strdup_printf ("%d", mn);
strcat(n3," DT");
gtk_entry_set_text(GTK_ENTRY(output1),n1);
gtk_entry_set_text(GTK_ENTRY(output2),n2);
gtk_entry_set_text(GTK_ENTRY(output3),n3);
}
/*************************************************************************

			GESTION CAPTEURS


**************************************************************************/
capteur c ; 
capteur c_r;
char id_supp[20];
int choix [2]= {0,0 } ; 
int choix1 [2]= {0,0 } ; 
int choix2 [3] = {0,0,0 } ;
//Debut ajouter : //



void on_ajout_capteur_clicked               (GtkButton       *button,
                                        gpointer         user_data)
	{
		GtkWidget *inp1;
		inp1=create_Ajouter_capteur();
		gtk_widget_show(inp1);

	}





//affichage sur tree //
void
on_button_afficher_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{

GtkWidget *treeview1;


treeview1 = lookup_widget(button,"treeview_capteur");
affiche_capteur(treeview1);
}


//button radio humidite //
void
on_radiobutton4_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
choix[1]=1; 
choix [0]=0;
}

//button radio temperature//
void
on_radiobutton3_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
choix[0]=1 ; 
choix[1]=0 ; 
}


void
on_okbutton_supp_clicked               (GtkButton      *button,
                                        gpointer         user_data)
{
char id[20];
GtkWidget *input1;
GtkWidget *supprimer_capteur;
GtkWidget *dialog = lookup_widget(button,"supprimer_capteur");
	gtk_widget_destroy(dialog);
//supprimer_capteur = lookup_widget(button,"supprimer_capteur");
//gtk_widget_destroy(supprimer_capteur);
input1=lookup_widget(button,"label_sup");

supp_capteur(c.id);

}


//bouton recherche 
void
on_recherche_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *treeview1, *id_input;
	char id_rech[20];


	treeview1 = lookup_widget (button, "treeview_capteur");
	id_input = lookup_widget (button, "entry_rech_capteur");

	strcpy (id_rech,gtk_entry_get_text(GTK_ENTRY(id_input)));
	recherche_capteur (id_rech,treeview1);
}
/////////////////////////////////////
void
on_okbutton_aj_capteur_clicked         (GtkButton       *button,
                                        gpointer         user_data)
	{ 
capteur a;
char text1[20]="" ; 
 
GtkWidget *inp2,*inp3,*inp6,*inp7,*inDe;
//Destroy Dialog//
//
inDe=lookup_widget(button,"Ajouter_capteur");
//

inp2=lookup_widget(button,"entry_id");
inp3=lookup_widget(button,"entry_marque");

inp6=lookup_widget(button,"calendar_capteur");
inp7=lookup_widget(button,"entry_valeur");

strcpy(a.id,gtk_entry_get_text(GTK_ENTRY(inp2)));
strcpy(a.marque,gtk_entry_get_text(GTK_ENTRY(inp3)));

strcpy(a.valeur,gtk_entry_get_text(GTK_ENTRY(inp7)));

 type_capteur ( choix, text1  ) ;
//choix[0]=0 ;
//choix[1]=0 ; 
strcpy(a.type,text1) ;
strcpy(a.etat,"bonne");
strcpy(a.cause,"--");
gtk_calendar_get_date (inp6,&a.date.annee,&a.date.mois,&a.date.jour);
a.date.mois ++ ; 

if (ajoutCapteur(a,button))
{gtk_widget_destroy(inDe);
}}
//Fin AJouter //
void
on_treeview_capteur_row_activated      (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter   iter;
char* id;
char* marque;
char* valeur;
char* type;
char* etat;
char* cause;
char *date1 ;


GtkTreeModel* model=gtk_tree_view_get_model(treeview)  ;
  if (gtk_tree_model_get_iter(model, &iter, path))
  
{
   gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0, &id,1, &type,2, &marque,3, &valeur,4, &date1,5,&etat,6,&cause, -1 ) ;
strcpy(c.id,id);
strcpy(c.marque,marque);
strcpy(c.valeur,valeur);
sscanf (date1,"%d/%d/%d",&c.date.jour,&c.date.mois,&c.date.annee);
strcpy(c.type,type);
strcpy(c.etat,etat);
strcpy(c.cause,cause);
}
}
/*
void
on_treeview_capteur_row_activated      (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)

{
gchar *str_data0;
gchar *str_data1;
gchar *str_data2;
gchar *str_data3;
gchar *etat;
gchar *cause;
char *date4 ;

GtkTreeIter   iter;
GtkTreeModel* model=gtk_tree_view_get_model(treeview)  ;
  if (gtk_tree_model_get_iter(model, &iter, path))
  {

   gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0, &str_data0,1, &str_data1,2, &str_data2,3, &str_data3,4, &date4,5,&etat,6,&cause, -1 ) ;
strcpy(c.id,str_data0);
strcpy(c.marque,str_data2);
strcpy(c.valeur,str_data3);
sscanf (date4,"%d/%d/%d",&c.date.jour,&c.date.mois,&c.date.annee);
strcpy(c.type,str_data1);
strcpy(c.etat,etat);
strcpy(c.cause,cause);


} }*/
void 
on_boutton_sup_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *dialog = create_supprimer_capteur();
	gtk_widget_show(dialog);
		supp_capteur(c.id);
		
	}
 
void
on_okbutton_modif_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
 
char text[20] ; 

GtkWidget *inp2,*inp3,*inp4,*inp5,*inp6,*inp7;
 GtkWidget *modifier_capteur;

//dialogue modif //
modifier_capteur=lookup_widget(button,"modifier_capteur");
//
supp_capteur(c.id);
inp2=lookup_widget(button,"entry_id");
inp3=lookup_widget(button,"entry_marque");

inp7=lookup_widget(button,"entry_valeur");
inp4=lookup_widget(button,"jour");

inp5=lookup_widget(button,"mois");

inp6=lookup_widget(button,"annee");



strcpy(c.id,gtk_entry_get_text(GTK_ENTRY(inp2)));
strcpy(c.marque,gtk_entry_get_text(GTK_ENTRY(inp3)));

strcpy(c.valeur,gtk_entry_get_text(GTK_ENTRY(inp7)));
 type_capteur ( choix, text ) ;
//choix[0]=0 ;
//choix[1]=0 ; 
strcpy(c.type,text) ;
c.date.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(inp4));
c.date.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(inp5));
c.date.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(inp6));

if (ajoutCapteur(c,button)){
gtk_widget_destroy(modifier_capteur);
}}
////////////////////////////////////////////////////////////////////////////


void
on_button_modif_clicked                (GtkButton       *button,
                                        gpointer         user_data)

{

GtkWidget *dialog = create_modifier_capteur();
GtkWidget *label1 = lookup_widget (button,"label_msg");
GtkWidget *inp2,*inp3,*inp7,*inp10,*inp11;
GtkSpinButton *inp4,*inp5,*inp6 ;
char text[20]="" ;
if (strlen (c.id) != 0){
gtk_widget_show(dialog);
inp2=lookup_widget(dialog,"entry_id");
inp3=lookup_widget(dialog,"entry_marque");
inp7=lookup_widget(dialog,"entry_valeur");
inp10=lookup_widget(dialog,"radiobutton3");
inp11=lookup_widget(dialog,"radiobutton4");

inp4=lookup_widget(dialog,"jour");

inp5=lookup_widget(dialog,"mois");

inp6=lookup_widget(dialog,"annee");

gtk_entry_set_text (GTK_ENTRY (inp2), _(c.id));
gtk_entry_set_text (GTK_ENTRY (inp3), _(c.marque));
gtk_entry_set_text (GTK_ENTRY (inp7), _(c.valeur));
gtk_spin_button_set_value(inp4,c.date.jour);
gtk_spin_button_set_value(inp5,c.date.mois);
gtk_spin_button_set_value(inp6,c.date.annee);

type_capteur (choix, text ) ;//radio fct
//choix[0]=0 ;
//choix[1]=0 ;

if (choix[0]==0)
{ gtk_toggle_button_set_active(inp10,TRUE);}
else {
gtk_toggle_button_set_active (inp11,TRUE);}
strcpy(c.type,text) ;
gtk_widget_show(dialog);
gtk_label_set_text(GTK_LABEL(label1),"");
}

else{
gtk_label_set_text(GTK_LABEL(label1),"Double click sur un capteur");
}
}


void
on_bouton_type_affiche_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{

GtkWidget *combobox ; 

GtkWidget *treeview1,*a;	
 char t[50]; 
  
  
treeview1 = lookup_widget(button,"treeview_capteur");
combobox=lookup_widget(button,"comboboxentry1");
strcpy(t,gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox))) ;

affiche_type(treeview1,t);
}


///////////////////////////////////////////////////


void
on_button_alarmante_clicked            (GtkButton       *button,
                                       gpointer         user_data)
{

GtkWidget *treeview1;//,*min_input,*max_input;


treeview1 = lookup_widget(button,"treeview_alarmante");

//char min_rech[20];
//char max_rech[20];



 
	//min_input = lookup_widget (button, "min");
	//max_input = lookup_widget (button, "max");

	//strcpy (min_rech,gtk_entry_get_text(GTK_ENTRY(min_input)));
        //strcpy (max_rech,gtk_entry_get_text(GTK_ENTRY(max_input)));
	capteur_alarmante( treeview1);
}

/////////////////////////

/*
void
on_affichage_defect_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{

}
*/

void
on_button_fiche_capteur_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *inp1;
 GtkButton *combobox1 ;

		inp1=create_dialog_fiche_capteur();
combobox1=lookup_widget(inp1,"comboboxentry_type");
set_combo_fiche(combobox1) ;
		gtk_widget_show(inp1);

}



void
on_okbutton1_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *fiche_capteur;
fiche_capteur=lookup_widget(button,"dialog_fiche_capteur");
gtk_widget_destroy(fiche_capteur);
}




/*void
on_checkbutton4_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
//if (gtk_toggle_button_get_active(togglebutton))
choix1 [1]==1 ;
}
*/


void
on_mise_jour_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
 char i[50]; 
GtkWidget *treeview2;
//GtkButton *combobox1 ;
treeview2 = lookup_widget(button,"treeview_suivi");
//combobox1=lookup_widget(button,"comboboxentry_type");
//strcpy(i,gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox1))) ;

affiche_suivi(treeview2,i);
}




void
on_checkbutton_panne_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{GtkWidget *i1,*i2,*i3,*i4,*i5;
i1=lookup_widget(togglebutton,"detruit_radio");
i2=lookup_widget(togglebutton,"radio_mauvaise");
i3=lookup_widget(togglebutton,"radio_autres");
i4=lookup_widget(togglebutton,"entry_autre_cause");
i5=lookup_widget(togglebutton,"label_cause_capteur");
if(gtk_toggle_button_get_active(togglebutton))
{
gtk_widget_show(i1);
gtk_widget_show(i2);
gtk_widget_show(i3);
gtk_widget_show(i4);
gtk_widget_show(i5);
}
else
{
gtk_widget_hide(i1);
gtk_widget_hide(i2);
gtk_widget_hide(i3);
gtk_widget_hide(i4);
gtk_widget_hide(i5);
}

}

void
on_radio_autres_clicked                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{GtkWidget *i4;
i4=lookup_widget(togglebutton,"entry_autre_cause");
if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
gtk_widget_set_sensitive(i4,TRUE);
else
gtk_widget_set_sensitive(i4,FALSE);

}


void
on_button12_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_treeview_suivi_row_activated        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter   iter;
char* id;
char* marque;
char* valeur;
char* type;
char* etat;
char* cause;
char *date1 ;


GtkTreeModel* model=gtk_tree_view_get_model(treeview)  ;
  if (gtk_tree_model_get_iter(model, &iter, path))
  
{
   gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0, &id,1, &type,2, &marque,3, &valeur,4, &date1,5,&etat,6,&cause, -1 ) ;
strcpy(c_r.id,id);
strcpy(c_r.marque,marque);
strcpy(c_r.valeur,valeur);
sscanf (date1,"%d/%d/%d",&c_r.date.jour,&c_r.date.mois,&c_r.date.annee);
strcpy(c_r.type,type);
strcpy(c_r.etat,etat);
strcpy(c_r.cause,cause);
}
}
void
on_button_capteur_reparee_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
supp_capteur(c_r.id);
strcpy(c_r.etat,"bonne");
strcpy(c_r.cause,"--");
ajoutCapteur(c_r,button);
}
void
on_enregistrer_panne_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *i1,*i2,*i3,*i4,*togglebutton;
int i ;
supp_capteur(c.id) ;

i1=lookup_widget(button,"detruit_radio");
i2=lookup_widget(button,"radio_mauvaise");
i3=lookup_widget(button,"radio_autres");
i4=lookup_widget(button,"entry_autre_cause");
togglebutton=lookup_widget(button,"checkbutton_en_panne");
GSList *List;

List= gtk_radio_button_get_group (GTK_RADIO_BUTTON (i1));
for (i=0;i<3;i++)
{
        if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(List->data)))
{
            strcpy(c.cause,gtk_button_get_label(GTK_BUTTON(List->data)));
   
}
       else
if (i!=2)
            List = g_slist_next(List);
           

}
if (gtk_toggle_button_get_active(i3))
strcpy(c.cause,gtk_entry_get_text(GTK_ENTRY(i4)));
strcpy(c.etat,"en panne");
ajoutCapteur(c,button);

}


void
on_affichage_defect_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
char marq [50] ; 
GtkWidget *dialog = create_max_marque_def();
GtkWidget *inp2 ; 
inp2=lookup_widget(dialog,"entry_def");
marque_defect (marq);
gtk_entry_set_text (GTK_ENTRY (inp2), _(marq));
gtk_widget_show(dialog);

}


void
on_button_road_capteurs_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *dialog = create_window1_gestion_capteurs();
gtk_widget_show(dialog);

GtkWidget *window_emp = lookup_widget(button,"window_employee_space");
gtk_widget_destroy(window_emp);
}


void
on_button_val_alarm_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *dialog = create_window_alarmante();
gtk_widget_show(dialog);
}
////////////////////////////////////////////////
////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
////////////Gestion des plantations///////////////
//////////////////////////////////////////////////////////////////
plante p;
char ref[10],ref1[10];
/*/////////////////////////////////////////////////////////////////////////
			      Les crudes
/////////////////////////////////////////////////////////////////////////*/
void
on_ajouter_plante_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget* ajout_plantation;
	ajout_plantation=create_ajout_plantation();
	gtk_widget_show(ajout_plantation);

}
void
on_ajout_precipitation_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
precipitation prec;
GtkWidget *date_precipitation, *val,*dialog_valid_ajout;
	date_precipitation = lookup_widget (button, "calendar_precipitation");
	val= lookup_widget (button, "precipitation");

	gtk_calendar_get_date (date_precipitation,&prec.date_precip.annee,&prec.date_precip.mois,&prec.date_precip.jour);
	prec.date_precip.mois++;
	prec.valeur_precipitation = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(val));
	
	Ajouter_precipitation(prec);

	dialog_valid_ajout=create_dialog_valid_ajout();
	gtk_widget_show(dialog_valid_ajout);
	

}

void
on_valide_ajout_precipitation_clicked  (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *dialog_valid_ajout;
dialog_valid_ajout = lookup_widget(button,"dialog_valid_ajout");
gtk_widget_destroy(dialog_valid_ajout);
}

//////
void
on_Affiche_tableau_de_bord_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget* Tableau_de_bord_des_plantations;
	Tableau_de_bord_des_plantations=create_Tableau_de_bord_des_plantations();
	gtk_widget_show(Tableau_de_bord_des_plantations);
}
void
on_modifier_plante_clicked             (GtkButton       *objet,
                                        gpointer         user_data)
{
GtkWidget *input1, *input_q,*input_combo_recolte,*input_d, *input_m, *input_y,*input_q_r,*input_combo_p,*input_arrosage,*input_engrais,*input5,*input6,*input_d_e,*input_m_e,*input_a_e,*input_d_t,*input_m_t,*input_a_t;
GtkWidget* modif_plantation;
if(strcmp(ref,"")){
	modif_plantation=create_modif_plantation();
	gtk_widget_show(modif_plantation);
//////
GtkWidget *quotidien= lookup_widget(modif_plantation,"radiobutton_quotidien_modif");
GtkWidget *hebdo= lookup_widget(modif_plantation,"radiobutton_hebdo_modif");
GtkWidget *mensuel= lookup_widget(modif_plantation,"radiobutton_mensuel_modif");
if ((strcmp(p.arrosage, "quotidien") == 0))
    {
      gtk_toggle_button_set_active(GTK_RADIO_BUTTON(quotidien), 1);
      gtk_toggle_button_set_active(GTK_RADIO_BUTTON(hebdo), 0);
      gtk_toggle_button_set_active(GTK_RADIO_BUTTON(mensuel), 0);
    }
    else if ((strcmp(p.arrosage, "hebdomadaire") == 0))
    {
      gtk_toggle_button_set_active(GTK_RADIO_BUTTON(quotidien), 0);
      gtk_toggle_button_set_active(GTK_RADIO_BUTTON(hebdo), 1);
      gtk_toggle_button_set_active(GTK_RADIO_BUTTON(mensuel), 0);
    }
    else if ((strcmp(p.arrosage, "mensuel") == 0))
    {
      gtk_toggle_button_set_active(GTK_RADIO_BUTTON(quotidien), 0);
      gtk_toggle_button_set_active(GTK_RADIO_BUTTON(hebdo), 0);
      gtk_toggle_button_set_active(GTK_RADIO_BUTTON(mensuel), 1);
    }
///////
GtkWidget *unit= lookup_widget(modif_plantation,"unite_modif_plante");
GtkWidget *engrais= lookup_widget(modif_plantation,"engrais_modif_plante");
GtkWidget *coche= lookup_widget(modif_plantation,"checkbutton2_plante");
if (strcmp(p.unit.unite,"---")==0)
gtk_combo_box_set_active (unit,0);
else if  (strcmp(p.unit.unite,"G")==0)
gtk_combo_box_set_active (unit,1);
else if  (strcmp(p.unit.unite,"KG")==0)
gtk_combo_box_set_active (unit,2);

if (strcmp(p.engrais,"Type x")==0)
gtk_combo_box_set_active (engrais,0);
else if  (strcmp(p.engrais,"Type y")==0)
gtk_combo_box_set_active (engrais,1);
else if  (strcmp(p.engrais,"Type z")==0)
gtk_combo_box_set_active (engrais,2);
///////////////////////////////////////////
if (strstr(p.taille,"oui"))
{ 
gtk_toggle_button_set_active (coche,TRUE);

}
///////
input1=lookup_widget(modif_plantation,"reference_modif_plante");
input_q=lookup_widget(modif_plantation,"quantite_modif_plante");
input_combo_p=lookup_widget(modif_plantation,"unite_modif_plante");
input_d=lookup_widget(modif_plantation,"jour_plante");
input_m=lookup_widget(modif_plantation,"mois_plante");
input_y=lookup_widget(modif_plantation,"annee_plante");
input_q_r=lookup_widget(modif_plantation,"quantite_recolte_modif_plante");

GtkWidget *input_modif1=lookup_widget(modif_plantation,"spinbutton17_plante");
GtkWidget *input_modif2=lookup_widget(modif_plantation,"spinbutton18_plante");
GtkWidget *input_modif3=lookup_widget(modif_plantation,"spinbutton19_plante");


input_engrais=lookup_widget(modif_plantation,"engrais_modif_plante");
input_d_e=lookup_widget(modif_plantation,"jour_engrais_modif_plante");
input_m_e=lookup_widget(modif_plantation,"mois_engrais_modif_plante");
input_a_e=lookup_widget(modif_plantation,"annee_engrais_modif_plante");
input_d_t=lookup_widget(modif_plantation,"jour_taille_modif_plante");
input_m_t=lookup_widget(modif_plantation,"mois_taille_modif_plante");
input_a_t=lookup_widget(modif_plantation,"annee_taille_modif_plante");
input6=lookup_widget(modif_plantation,"commentaire_modif_plante");



gtk_entry_set_text(GTK_ENTRY(input1),p.reference);


gtk_spin_button_set_value(input_q,p.quant.quantite);
//////

////////////////
gtk_spin_button_set_value(input_d,p.date.jour);
gtk_spin_button_set_value(input_m,p.date.mois);
gtk_spin_button_set_value(input_y,p.date.annee);
gtk_spin_button_set_value(input_q_r,p.quant.quantite_recolte);

gtk_spin_button_set_value(input_modif1,p.date_recolte.jour);
gtk_spin_button_set_value(input_modif2,p.date_recolte.mois);
gtk_spin_button_set_value(input_modif3,p.date_recolte.annee);

gtk_spin_button_set_value(input_d_e,p.date_engrais1.jour);
gtk_spin_button_set_value(input_m_e,p.date_engrais1.mois);
gtk_spin_button_set_value(input_a_e,p.date_engrais1.annee);

gtk_spin_button_set_value(input_d_t,p.date_taille.jour);
gtk_spin_button_set_value(input_m_t,p.date_taille.mois);
gtk_spin_button_set_value(input_a_t,p.date_taille.annee);
gtk_entry_set_text(GTK_ENTRY(input6),p.commentaire);

}
strcpy(ref,"");
}

void
on_supprimer_plante_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget* dialog_valid_supp;
	Supprimer_plante (ref);
if (strcmp(ref,"")!=0){
	dialog_valid_supp=create_dialog_valid_supp();
	gtk_widget_show(dialog_valid_supp);
			}
strcpy(ref,"");

}
/*void
on_okbutton2_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *dialog5;
dialog5 = lookup_widget(objet,"dialog5");
gtk_widget_destroy(dialog5);
}*/
/*void
on_valid_supp_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *dialog10;
dialog10 = lookup_widget(button,"dialog10");
gtk_widget_destroy(dialog10);
}*/
/*void
on_okbutton3_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *dialog6;

dialog6 = lookup_widget(button,"dialog6");
gtk_widget_destroy(dialog6);

}*/


void
on_recherche_plante_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *treeview_plante, *recherche_plante_entry;
	char ref_rech[9];

	treeview_plante = lookup_widget (button, "treeview_plante");
	recherche_plante_entry = lookup_widget (button, "recherche_plante_entry");

	strcpy (ref_rech,gtk_entry_get_text(GTK_ENTRY(recherche_plante_entry)));

	Recherche_plante (ref_rech,treeview_plante);
}
void
on_actualiser_plante_clicked           (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *gestion_des_plantations;
GtkWidget *treeview_plante;

treeview_plante = lookup_widget(objet,"treeview_plante");
gestion_des_plantations = lookup_widget(objet,"Gestion_des_plantations");

treeview_plante = lookup_widget(gestion_des_plantations,"treeview_plante");

Afficher_plante(treeview_plante);
}
/*void
on_actualiser2_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)

{
GtkWidget *gestion_des_plantations;
GtkWidget *treeview_precipitation;

treeview_precipitation = lookup_widget(objet,"treeview_precipitation");
gestion_des_plantations = lookup_widget(objet,"Gestion_des_plantations");

treeview_precipitation = lookup_widget(gestion_des_plantations,"treeview_precipitation");

Afficher_precipitation(treeview_precipitation);	
}*/
////////
void
on_Affiche_TB_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *Tableau_de_bord_des_plantations;

GtkWidget *objet;



Tableau_de_bord_des_plantations=create_Tableau_de_bord_des_plantations();

gtk_widget_show(Tableau_de_bord_des_plantations);
partie2(Tableau_de_bord_des_plantations);
//

}
/*/////////////////////////////////////////////////////////////////////////
			Les tableaux d'affichage
/////////////////////////////////////////////////////////////////////////*/
void
on_treeview_plante_row_activated       (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
gchar* reference;
gchar* Quantite;
gchar* unite;
gchar* date;
gchar* date1;
gchar* date2;
gchar* Quantite1;
gchar* date_recolte;
gchar* unite_r;
gchar* arrosage;
gchar* engrais_ch;
gchar* use;
gchar* taille;
gchar* commentaire;

	GtkTreeModel *model = gtk_tree_view_get_model(treeview);
	if (gtk_tree_model_get_iter(model, &iter, path))
	{
gtk_tree_model_get (GTK_LIST_STORE (model), &iter, 0, &reference, 1, &Quantite, 2, &unite, 3, &date, 4, &Quantite1,5,&date_recolte, 6, &arrosage, 7, &engrais_ch,8,&date1, 9, &taille,10,&date2,11,&commentaire,-1);	
		strcpy(p.reference,reference);
		strcpy(ref,reference);
		strcpy(ref1,reference);
		strcpy (p.unit.unite, unite);
		strcpy (p.arrosage, arrosage);
		strcpy (p.engrais, engrais_ch);
                sscanf (date,"%d/%d/%d",&p.date.jour,&p.date.mois,&p.date.annee);
		sscanf (date_recolte,"%d/%d/%d",&p.date_recolte.jour,&p.date_recolte.mois,&p.date_recolte.annee);
		sscanf (date1,"%d/%d/%d",&p.date_engrais1.jour,&p.date_engrais1.mois,&p.date_engrais1.annee);
		sscanf (date2,"%d/%d/%d",&p.date_taille.jour,&p.date_taille.mois,&p.date_taille.annee);
		sscanf (Quantite,"%d",&p.quant.quantite);
		sscanf (Quantite1,"%d",&p.quant.quantite_recolte);
if (strcmp(taille,"oui"))
		strcpy(p.taille,taille);
else 
		strcpy (p.taille,taille);		
		strcpy (p.commentaire, commentaire);
		
				
}
}
/*/////////////////////////////////////////////////////////////////////////
			      Les boutons radio + cases à cocher 
/////////////////////////////////////////////////////////////////////////*/
char TEXT[20];
void
on_radiobutton_taille_semaine_clicked  (GtkButton       *button,
                                        gpointer         user_data)
{ 
 strcpy(TEXT,"quotidien");
}
void
on_radiobutton_taille_mois_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{ 
 strcpy(TEXT,"hebdomadaire");
}
void 
on_radiobutton_taille_annee_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{ 
 strcpy(TEXT,"mensuel");
}


//////////
char TEXT1[20];
void
on_arrosage_mois_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
 strcpy(TEXT1,"hebdomadaire");
}

void
on_arrosage_annee_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
 strcpy(TEXT1,"mensuel");
}

void
on_arrosage1_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
 strcpy(TEXT1,"quotidien");
}


/*/////////////////////////////////////////////////////////////////////////
			Les interfaces d'ajout et modif
/////////////////////////////////////////////////////////////////////////*/
void
on_Ajouter_plante_clicked              (GtkWidget       *objet,
                                        gpointer         user_data)
{
plante p;

char text1[20]="";
char text2[20]="";
char text3[20]="";
int T;

GtkWidget *taille,*input1, *input_q,*input_combo_recolte,*input_d, *input_m, *input_y,*input_q_r,*input_combo_p,*input_arrosage,*input_engrais,*input5,*input6,*input_d_e,*input_m_e,*input_a_e,*input_d_t,*input_m_t,*input_a_t;
GtkWidget *ajout_plantation;
ajout_plantation = lookup_widget(objet,"ajout_plantation");

input1=lookup_widget(objet,"reference");
input_q=lookup_widget(objet,"quantite");
input_combo_p=lookup_widget(objet,"unite_plante");
input_d=lookup_widget(objet,"day");
input_m=lookup_widget(objet,"month");
input_y=lookup_widget(objet,"year");

input_q_r=lookup_widget(objet,"quantite_recolte");

GtkWidget *input_d_r=lookup_widget(objet,"spinbutton_jour");
GtkWidget *input_m_r=lookup_widget(objet,"spinbutton_mois");
GtkWidget *input_y_r=lookup_widget(objet,"spinbutton_annee");

input_engrais=lookup_widget(objet,"engrais_chimique");
input_d_e=lookup_widget(objet,"spinbutton_j_engrais");
input_m_e=lookup_widget(objet,"spinbutton_m_engrais");
input_a_e=lookup_widget(objet,"spinbutton_a_engrais");
input_d_t=lookup_widget(objet,"taille_jour");
input_m_t=lookup_widget(objet,"taille_mois");
input_a_t=lookup_widget(objet,"taille_annee");
input6=lookup_widget(objet,"commentaire");
taille = lookup_widget (objet, "taille");


strcpy(p.reference,gtk_entry_get_text(GTK_ENTRY(input1)));
p.quant.quantite = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_q));
strcpy(p.unit.unite,gtk_combo_box_get_active_text(GTK_COMBO_BOX(input_combo_p)));

p.date.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_d));
p.date.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_m));
p.date.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_y));

p.quant.quantite_recolte = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_q_r));
if (p.quant.quantite_recolte==0){

p.date_recolte.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(0));
p.date_recolte.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(0));
p.date_recolte.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(0));}
else {
p.date_recolte.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_d_r));
p.date_recolte.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_m_r));
p.date_recolte.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_y_r));}


strcpy(p.arrosage,TEXT);
p.date_engrais1.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_d_e));
p.date_engrais1.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_m_e));
p.date_engrais1.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_a_e));

if (gtk_toggle_button_get_active (taille)){
strcpy(p.taille,"oui");
p.date_taille.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_d_t));
p.date_taille.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_m_t));
p.date_taille.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_a_t));}

else{
strcpy(p.taille,"---");
p.date_taille.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(0));
p.date_taille.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(0));
p.date_taille.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(0));
}
strcpy(p.engrais,gtk_combo_box_get_active_text(GTK_COMBO_BOX(input_engrais)));
if (strcmp(gtk_entry_get_text(GTK_ENTRY(input6)),"") !=0 )
	strcpy(p.commentaire,gtk_entry_get_text(GTK_ENTRY(input6)));
else 
	strcpy(p.commentaire,"RAS");

if (Ajouter_plante(p,objet)){

gtk_widget_destroy(ajout_plantation);}
}

void
on_cancelbutton_ajouter_plante_clicked (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *ajout_plantation;
ajout_plantation = lookup_widget(button,"ajout_plantation");

gtk_widget_destroy(ajout_plantation);
}

void
on_Modifier_plante_clicked             (GtkWidget      *objet,
                                        gpointer         user_data)
{

plante p;
char text1[20]="";
char text2[20]="";
GtkWidget *input1, *input_q,*input_combo_recolte,*input_d, *input_m, *input_y,*input_q_r,*input_combo_p,*input_arrosage,*input_engrais,*input5,*input6,*input_d_e,*input_m_e,*input_a_e,*input_d_t,*input_m_t,*input_a_t;
GtkWidget *modif_plantation;
GtkWidget *dialog_valid_modif;
modif_plantation = lookup_widget(objet,"modif_plantation");


input1=lookup_widget(objet,"reference_modif_plante");
input_q=lookup_widget(objet,"quantite_modif_plante");
input_combo_p=lookup_widget(objet,"unite_modif_plante");
input_d=lookup_widget(objet,"jour_plante");
input_m=lookup_widget(objet,"mois_plante");
input_y=lookup_widget(objet,"annee_plante");

input_q_r=lookup_widget(objet,"quantite_recolte_modif_plante");

GtkWidget *input_d_r=lookup_widget(objet,"spinbutton17_plante");
GtkWidget *input_m_r=lookup_widget(objet,"spinbutton18_plante");
GtkWidget *input_y_r=lookup_widget(objet,"spinbutton19_plante");
GtkWidget *taille = lookup_widget (objet, "checkbutton2_plante");
input_engrais=lookup_widget(objet,"engrais_modif_plante");
input_d_e=lookup_widget(objet,"jour_engrais_modif_plante");
input_m_e=lookup_widget(objet,"mois_engrais_modif_plante");
input_a_e=lookup_widget(objet,"annee_engrais_modif_plante");

input_d_t=lookup_widget(objet,"jour_taille_modif_plante");
input_m_t=lookup_widget(objet,"mois_taille_modif_plante");
input_a_t=lookup_widget(objet,"annee_taille_modif_plante");
input6=lookup_widget(objet,"commentaire_modif_plante");

strcpy(p.reference,gtk_entry_get_text(GTK_ENTRY(input1)));
p.quant.quantite = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_q));
strcpy(p.unit.unite,gtk_combo_box_get_active_text(GTK_COMBO_BOX(input_combo_p)));
p.date.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_d));
p.date.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_m));
p.date.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_y));

p.quant.quantite_recolte = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_q_r));
if (p.quant.quantite_recolte==0){
p.date_recolte.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(0));
p.date_recolte.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(0));
p.date_recolte.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(0));
}
else {
p.date_recolte.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_d_r));
p.date_recolte.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_m_r));
p.date_recolte.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_y_r));}


strcpy(p.arrosage,TEXT1);
p.date_engrais1.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_d_e));
p.date_engrais1.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_m_e));
p.date_engrais1.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_a_e));


if (gtk_toggle_button_get_active (taille)){
strcpy(p.taille,"oui");
p.date_taille.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_d_t));
p.date_taille.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_m_t));
p.date_taille.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_a_t));}
else {
strcpy(p.taille,"---");

p.date_taille.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(0));
p.date_taille.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(0));
p.date_taille.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(0));}
strcpy(p.engrais,gtk_combo_box_get_active_text(GTK_COMBO_BOX(input_engrais)));
strcpy(p.commentaire,gtk_entry_get_text(GTK_ENTRY(input6)));
Supprimer_plante (ref1);
if(Ajouter_plante(p,objet)){

gtk_widget_destroy(modif_plantation);
dialog_valid_modif = lookup_widget(objet,"dialog_valid_modif");
dialog_valid_modif=create_dialog_valid_modif();
gtk_widget_show(dialog_valid_modif);

}

}

void
on_cancelbutton_modifier_plante_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *modif_plantation;
modif_plantation = lookup_widget(button,"modif_plantation");

gtk_widget_destroy(modif_plantation);
}



void
on_actualiser_precipitation_clicked    (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *gestion_des_plantations;
GtkWidget *treeview_precipitation;

treeview_precipitation = lookup_widget(objet,"treeview_precipitation");
gestion_des_plantations = lookup_widget(objet,"Gestion_des_plantations");

treeview_precipitation = lookup_widget(gestion_des_plantations,"treeview_precipitation");

Afficher_precipitation(treeview_precipitation);	
}


void
on_valide_supp_plante_clicked          (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *dialog_valid_supp;
dialog_valid_supp= lookup_widget(objet,"dialog_valid_supp");
gtk_widget_destroy(dialog_valid_supp);
}


void
on_valide_modif_plante_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *dialog_valid_modif;

dialog_valid_modif= lookup_widget(button,"dialog_valid_modif");
gtk_widget_destroy(dialog_valid_modif);
}


void
on_button_gestion_des_plantations_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget* Gestion_des_plantations;
	Gestion_des_plantations=create_Gestion_des_plantations();
	gtk_widget_show(Gestion_des_plantations);
GtkWidget *window_emp = lookup_widget(button,"window_employee_space");
gtk_widget_destroy(window_emp);
}


void
on_TB_plantations_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *Tableau_de_bord_des_plantations;

GtkWidget *objet;
Tableau_de_bord_des_plantations=create_Tableau_de_bord_des_plantations();

gtk_widget_show(Tableau_de_bord_des_plantations);
partie2(Tableau_de_bord_des_plantations);
}

//////////////////////////////////////////////////////////
/////////////////// fin partie plantation ////////////////
//////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/*..........................................................

                    GESTION DES TROUPEAUX

............................................................*/
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
/*..........................................................

                         CRUDE

............................................................*/
////////////////////////////////////////////////////////////


////////////////////////AJOUT///////////////////////////////
void
on_buttonok_ajoutanimal_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
animal a;
char text[100]="";
GtkWidget *input1, *input2, *input3, *input4, *input5,*combobox, /* *input7,*input8,*input9*/*input6;
GtkWidget *add ;
add=lookup_widget(button,"dialog_add_troup");
input1=lookup_widget(button,"entry_ref");
input2=lookup_widget(button,"entry_ref_mere");
input3=lookup_widget(button,"entry_poids");
input4=lookup_widget(button,"entry_robe");
input5=lookup_widget(button,"entry_lot");
combobox=lookup_widget(button,"combo_animal");
input6=lookup_widget(button,"calendar_troup");
//input7=lookup_widget(button,"spinbutton_jour"); 
//input8=lookup_widget(button,"spinbutton_mois");
//input9=lookup_widget(button,"spinbutton_annee");




genre(choixt,text);
strcpy(a.gender,text);

strcpy(a.ref,gtk_entry_get_text(GTK_ENTRY(input1)));
strcpy(a.refm,gtk_entry_get_text(GTK_ENTRY(input2)));
strcpy(a.poids,gtk_entry_get_text(GTK_ENTRY(input3)));
strcpy(a.robe,gtk_entry_get_text(GTK_ENTRY(input4)));
strcpy(a.lot,gtk_entry_get_text(GTK_ENTRY(input5)));
strcpy(a.type,gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox)));
strcpy(a.etat,"sein(e)");
strcpy(a.maladie,"--");
a.laittotale= 0 ;

gtk_calendar_get_date (input6,&a.date1.annee,&a.date1.mois,&a.date1.jour);
a.date1.mois ++ ; 
	//a.date.jour  = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input7));
	//a.date.mois  = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input8));
	//a.date.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input9)); 



if(AjoutAnimal(a,button))
gtk_widget_destroy(add);



}




////////////////////////MODIF///////////////////////////////
void
on_modif_voeux_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *dialog = create_dialog_edit_troup();
GtkWidget *label1 = lookup_widget (button,"labeldouble");
GtkWidget *inp2, *inp3,*inp7, *inp8, *inp9, *inp10;
GtkSpinButton *inp4, *inp5, *inp6;
char text[20]="" ; 
if (strlen (a_m.ref) != 0){
gtk_widget_show(dialog);
inp2=lookup_widget(dialog,"entry_edit_ref");
inp3=lookup_widget(dialog,"entry_edit_refm");
inp4=lookup_widget(dialog,"spinbutton_edit_jour");
inp5=lookup_widget(dialog,"spinbutton_edit_mois");
inp6=lookup_widget(dialog,"spinbutton_edit_annee");
inp7=lookup_widget(dialog,"entry_edit_poids");
inp8=lookup_widget(dialog,"entry_edit_robe");
inp9=lookup_widget(dialog,"entry_edit_lot");
inp10=lookup_widget(dialog,"entry_edit_lait");

gtk_entry_set_text(GTK_ENTRY(inp2),a_m.ref);
gtk_entry_set_text(GTK_ENTRY(inp3),a_m.refm);
gtk_entry_set_text(GTK_LABEL(inp7),a_m.poids);
gtk_entry_set_text(GTK_ENTRY(inp8),a_m.robe);
gtk_entry_set_text(GTK_ENTRY(inp9),a_m.lot);

gtk_spin_button_set_value(inp4,a_m.date1.jour);
gtk_spin_button_set_value(inp5,a_m.date1.mois);
gtk_spin_button_set_value(inp6,a_m.date1.annee);

char *lait = g_strdup_printf ("%1.3f", a_m.laittotale);
gtk_entry_set_text(GTK_ENTRY(inp10),lait);

genre( choixt, text ) ;
choixt[0]=0 ;
choixt[1]=0 ;
strcpy(a_m.gender,text) ;

gtk_label_set_text(GTK_LABEL(label1),"");
}

else{
gtk_label_set_text(GTK_LABEL(label1),"Double click sur un animal"); 
}
}



///////////////////////////////////////////
void
on_buttonok_modifanimal_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
animal a ;
char text[20]="" ; 
float i;
char charlait[20]; 
 
GtkWidget *inp2,*inp3,*inp4,*inp5,*inp6,*inp7,*inp8,*inp9,*comboboxm;

GtkWidget *modifier_animal;
modifier_animal=lookup_widget(button,"dialog_edit_troup");
GtkWidget * input_lait=lookup_widget(button,"entry_edit_lait");
/*if(CsModifAnimal(a_m,button))
SuppAnimal(a_m.ref) ;*/

g_print ("%s",aux);
inp2=lookup_widget(button,"entry_edit_ref");
inp3=lookup_widget(button,"entry_edit_refm");
inp4=lookup_widget(button,"spinbutton_edit_jour");
inp5=lookup_widget(button,"spinbutton_edit_mois");
inp6=lookup_widget(button,"spinbutton_edit_annee");
inp7=lookup_widget(button,"entry_edit_poids");
inp8=lookup_widget(button,"entry_edit_robe");
inp9=lookup_widget(button,"entry_edit_lot");
comboboxm=lookup_widget(button,"combo_edit_spec"); 

strcpy(a_m.type,gtk_combo_box_get_active_text(GTK_COMBO_BOX(comboboxm)));
strcpy(a_m.ref,gtk_entry_get_text(GTK_ENTRY(inp2)));
strcpy(a_m.refm,gtk_entry_get_text(GTK_ENTRY(inp3)));
strcpy(a_m.poids,gtk_entry_get_text(GTK_ENTRY(inp7)));
strcpy(a_m.robe,gtk_entry_get_text(GTK_ENTRY(inp8)));
strcpy(a_m.lot,gtk_entry_get_text(GTK_ENTRY(inp9)));

genre( choixt, text ) ;
choixt[0]=0 ;
choixt[1]=0 ; 
strcpy(a_m.gender,text) ;

a_m.date1.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(inp4));
a_m.date1.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(inp5));
a_m.date1.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(inp6));
g_print ("\n %s",a_m.ref);

strcpy(charlait,gtk_entry_get_text(GTK_ENTRY(input_lait)));
sscanf (charlait,"%f",&i);
a_m.laittotale=i;
strcpy(a_m.lait,gtk_entry_get_text(GTK_ENTRY(input_lait)));
if((CsModifAnimal(a_m,button))||(strcmp(aux,a_m.ref)==0))
{
SuppAnimal(aux);
AjoutAnimal(a_m,button);

gtk_widget_destroy(modifier_animal);
}
}
///

	
	
	
	
//
/////////////////////SUPPRESSION////////////////////////////
void
on_supp_animal_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{	FILE *hist;
	GtkWidget *label = lookup_widget (button,"labeldouble");
	if (strlen (ref_supp) != 0){
		GtkWidget*  dialog_check=create_dialog_supprimer_check();
		gtk_widget_show(dialog_check);
		
		gtk_label_set_text(GTK_LABEL(label),"");
		
		
	}
	else{
		gtk_label_set_text(GTK_LABEL(label),"Double click sur un animal");
	}
}
////////////////////////////////
void
on_button_supp_check_trp_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
FILE *hist;
	
		GtkWidget* dialog_check=lookup_widget(button,"dialog_supprimer_check");
		hist=fopen("histanimal.bin","ab");
		fwrite (&a_m,sizeof(animal),1,hist);
		fclose(hist);
		SuppAnimal(ref_supp);
		strcpy (ref_supp,"");
		gtk_widget_destroy(dialog_check);
		
}
//////////////////////AFFICHAGE/////////////////////////////
//Actualiser////////////////////////////
void
on_afficher_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *treeview12;
treeview12 = lookup_widget(button,"treeview_animal");
AffichListeAnimal(treeview12);
}

//row-activated//////////////////////////
void
on_treeview_animal_row_activated       (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	GtkTreeIter iter;
	char* ref;
	char* refm;
	char* date;
	char* gender;
	char* poids;
	char* robe;
	char* lot;
	char* type;
	char* etat;
	char* maladie;
	char* lait;
	

	GtkTreeModel *model = gtk_tree_view_get_model (treeview);

	if (gtk_tree_model_get_iter (model, &iter, path)){
		gtk_tree_model_get (GTK_LIST_STORE (model), &iter, 0, &ref, 1, &refm, 2, &date, 3, &poids, 4, &robe, 5, &lot, 6, &gender,7,&type,8,&etat,9,&maladie,10,&lait, -1);
		strcpy (a_m.ref, ref);
		strcpy (a_m.refm, refm);
		strcpy (a_m.gender, gender);
		strcpy (a_m.poids, poids);
		strcpy (a_m.robe, robe);
		strcpy (a_m.lot, lot);
		strcpy (a_m.type, type);
		strcpy (ref_supp, a_m.ref);
		sscanf (date,"%d/%d/%d",&a_m.date1.jour,&a_m.date1.mois,&a_m.date1.annee);
		strcpy (a_m.etat, etat);
		strcpy(a_m.maladie,maladie);
		sscanf(lait,"%f",&a_m.laittotale);
		strcpy(aux,a_m.ref);
	}
}
/////////////////////////////////////
void
on_treeview_hiss_troup_row_activated   (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
	char* ref;
	char* refm;
	char* date;
	char* gender;
	char* poids;
	char* robe;
	char* lot;
	char* type;
	char* etat;
	char* maladie;
	char* lait;
	

	GtkTreeModel *model = gtk_tree_view_get_model (treeview);

	if (gtk_tree_model_get_iter (model, &iter, path)){
		gtk_tree_model_get (GTK_LIST_STORE (model), &iter, 0, &ref, 1, &refm, 2, &date, 3, &poids, 4, &robe, 5, &lot, 6, &gender,7,&type,8,&etat,9,&maladie,10,&lait, -1);
		strcpy (ah.ref, ref);
		strcpy (ah.refm, refm);
		strcpy (ah.gender, gender);
		strcpy (ah.poids, poids);
		strcpy (ah.robe, robe);
		strcpy (ah.lot, lot);
		strcpy (ah.type, type);
		//strcpy (ref_supp_hisst, ah.ref);
		sscanf (date,"%d/%d/%d",&ah.date1.jour,&ah.date1.mois,&ah.date1.annee);
		strcpy (ah.etat, etat);
	        strcpy(ah.maladie,maladie);
		sscanf(lait,"%f",&ah.laittotale);
}
}
/////////////////////////
void
on_treeview_maladie_row_activated      (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
	
	char* ref;
	char* refm;
	char* date;
	char* gender;
	char* poids;
	char* robe;
	char* lot;
	char* type;
	char* etat;
	char* maladie;
	char* lait;
	

	GtkTreeModel *model = gtk_tree_view_get_model (treeview);

	if (gtk_tree_model_get_iter (model, &iter, path)){
		gtk_tree_model_get (GTK_LIST_STORE (model), &iter, 0, &ref, 1, &refm, 2, &date, 3, &poids, 4, &robe, 5, &lot, 6, &gender,7,&type,8,&etat,9,&maladie,10,&lait, -1);
		strcpy (a_s.ref, ref);
		strcpy (a_s.refm, refm);
		strcpy (a_s.gender, gender);
		strcpy (a_s.poids, poids);
		strcpy (a_s.robe, robe);
		strcpy (a_s.lot, lot);
		strcpy (a_s.type, type);
		
		sscanf (date,"%2d/%2d/%4d",&a_s.date1.jour,&a_s.date1.mois,&a_s.date1.annee);
		strcpy (a_s.etat, etat);
		strcpy(a_s.maladie,maladie);
		sscanf (lait,"%1.2f",&a_s.laittotale);
		strcpy(laitp,lait);
		
	
	}
}

//////////////////////RECHERCHE/////////////////////////////
void
on_button_rech_animal_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *treeview_liste_animal, *ref_input;
	char ref_rech[20];

	treeview_liste_animal = lookup_widget (button, "treeview_animal");
	ref_input = lookup_widget (button, "entry_recherche_animal");

	strcpy (ref_rech,gtk_entry_get_text(GTK_ENTRY(ref_input)));

	RechercheAnimal(ref_rech,treeview_liste_animal);
}


///////////////////////






////////////////////////////////////////////////////////////
/*..........................................................

                        HISTORIQUE

............................................................*/
////////////////////////////////////////////////////////////
void
on_button_reccuperer_troup_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
animal h;
FILE *j;

int test = 0;int comp = 0;
j=fopen("histanimal.bin","r+b");

	while (fread (&h,sizeof (animal),1,j) != 0 && test == 0){
		if (strcmp (h.ref,ah.ref) == 0)
			test = 1;
		else 
			comp++;
	}

	if (test)
		{
			AjoutAnimal(ah,button);
			SuppHistAnimal(h);
		 }
}


//////////////////
void
on_button_confirmer_supp_troup_clicked (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget*  dialog_doublecheck=create_dialog_supprimer_doublecheck();
		gtk_widget_show(dialog_doublecheck);
//SuppHistAnimal(ah);
}



	


void
on_button_recherche_historique_trp_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *treeview_liste_animal, *ref_input;
	char ref_rech[20];

	treeview_liste_animal = lookup_widget (button, "treeview_hiss_troup");
	ref_input = lookup_widget (button, "entry_rech_historique_troup");

	strcpy (ref_rech,gtk_entry_get_text(GTK_ENTRY(ref_input)));

	RechercheHistAnimal(ref_rech,treeview_liste_animal);
}

////////////
void
on_afficher_hiss_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *treeviewhis;
treeviewhis = lookup_widget(button,"treeview_hiss_troup");
AffichListeAnimalHist(treeviewhis);
}

//////////////////
void
on_button_supp_doublecheck_trp_clicked (GtkButton       *button,
                                        gpointer         user_data)
{	GtkWidget* dialog_doublecheck=lookup_widget(button,"dialog_supprimer_doublecheck");
	SuppHistAnimal(ah);		
	gtk_widget_destroy(dialog_doublecheck);
		
}





////////////////////////////////////////////////////////////
/*..........................................................

                         SANTE

............................................................*/
////////////////////////////////////////////////////////////
void
on_button_confirmer_maladie_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{GtkWidget *i1,*i2,*i3,*i4,*i5,*i6,*i7,*maladie_animal;
int i ; 
SuppAnimal(a_m.ref) ;
maladie_animal=lookup_widget(button,"dialog_maladie");
i1=lookup_widget(button,"radiobutton_sub");
i2=lookup_widget(button,"radiobutton_severe");
i3=lookup_widget(button,"radiobutton_caillette");
i4=lookup_widget(button,"radiobutton_acidoses");
i5=lookup_widget(button,"radiobutton_acetonomie");
i6=lookup_widget(button,"radiobutton_autres");
i7=lookup_widget(button,"entry_autres_maladies");
GSList *List;
        List= gtk_radio_button_get_group (GTK_RADIO_BUTTON (i1));
	for (i=0;i<6;i++)
{
        if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(List->data)))
{
            strcpy(a_m.maladie,gtk_button_get_label(GTK_BUTTON(List->data)));
	    	
}
       else 
		if (i!=5)
            	List = g_slist_next(List);
            

}
if (gtk_toggle_button_get_active(i6))
strcpy(a_m.maladie,gtk_entry_get_text(GTK_ENTRY(i7)));
//strcpy(a.maladie,ah.maladie);
strcpy(a_m.etat,"malade");
AjoutAnimal(a_m,button);
gtk_widget_destroy(maladie_animal);
}
///////////////////////////////////////////////
void
on_checkbutton_meta_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{GtkWidget *i1,*i2,*i3;
i1=lookup_widget(togglebutton,"radiobutton_caillette");
i2=lookup_widget(togglebutton,"radiobutton_acidoses");
i3=lookup_widget(togglebutton,"radiobutton_acetonomie");


if(gtk_toggle_button_get_active(togglebutton))
{
gtk_widget_show(i1);
gtk_widget_show(i2);
gtk_widget_show(i3);

}
else
{
gtk_widget_hide(i1);
gtk_widget_hide(i2);
gtk_widget_hide(i3);

}
}
//////////////////////////////////
void
on_checkbutton_mamelle_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{GtkWidget *i1,*i2;
i1=lookup_widget(togglebutton,"radiobutton_sub");
i2=lookup_widget(togglebutton,"radiobutton_severe");

if(gtk_toggle_button_get_active(togglebutton))
{
gtk_widget_show(i1);
gtk_widget_show(i2);
}
else
{
gtk_widget_hide(i1);
gtk_widget_hide(i2);

}
}

///////////////////////////////
void
on_button_supp_sante_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
float i ;
char charlait[20];

SuppAnimal(a_s.ref);
strcpy(a_s.etat,"sein(e)");
strcpy(a_s.maladie,"--");

strcpy(charlait,laitp);
sscanf (charlait,"%f",&i);
a_s.laittotale=i;

AjoutAnimal(a_s,button);
}

///////////////////////////////
void
on_afficher_malade_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *treeviewmal;
	treeviewmal = lookup_widget(button,"treeview_maladie");
	AffichAnimalmalade(treeviewmal);
}




////////////////////////////////////////////////////////////
/*..........................................................

                         LAIT

............................................................*/
////////////////////////////////////////////////////////////

void
on_button_confirm_lait_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{float i;
char charlait[20];
	GtkWidget *input_lait , *lait_animal;
	lait_animal=lookup_widget(button,"dialog_lait");
	SuppAnimal(a_m.ref);
	input_lait=lookup_widget(button,"entry_lait_produit");
	strcpy(charlait,gtk_entry_get_text(GTK_ENTRY(input_lait)));
	sscanf (charlait,"%f",&i);
	a_m.laittotale=a_m.laittotale+i;
	AjoutAnimal(a_m,button);
gtk_widget_destroy(lait_animal);
}





////////////////////////////////////////////////////////////
/*..........................................................

                         ALIMENTATION

............................................................*/
////////////////////////////////////////////////////////////
void
on_button_effacer_tout_alim_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *window = create_window_troup();
GtkWidget *inp1, *inp2,*inp3, *inp4, *inp5, *inp6,*inp7, *inp8, *inp9;
GtkWidget *inp10,*inp11, *inp12, *inp13, *inp14,*inp15, *inp16, *inp17, *inp18,*inp19, *inp20, *inp21;


inp1=lookup_widget(button,"entry_ms");
inp2=lookup_widget(button,"entry_uem");
inp3=lookup_widget(button,"entry_uel");
inp4=lookup_widget(button,"entry_ueb");

inp5=lookup_widget(button,"entry_ufl");
inp6=lookup_widget(button,"entry_uev");
inp7=lookup_widget(button,"entry_mo");
inp8=lookup_widget(button,"entry_dmo");
inp9=lookup_widget(button,"entry_amidon");
inp10=lookup_widget(button,"entry_sucre");
inp11=lookup_widget(button,"entry_eemg");

inp12=lookup_widget(button,"entry_ndf");
inp13=lookup_widget(button,"entry_adf");
inp14=lookup_widget(button,"entry_adl");
inp15=lookup_widget(button,"entry_cb");

inp16=lookup_widget(button,"entry_pdin");
inp17=lookup_widget(button,"entry_pdie");
inp18=lookup_widget(button,"entry_pdia");
inp19=lookup_widget(button,"entry_mat");
inp20=lookup_widget(button,"entry_lysdi");
inp21=lookup_widget(button,"entry_metdi");



gtk_entry_set_text(GTK_ENTRY(inp1),"0");
gtk_entry_set_text(GTK_ENTRY(inp2),"0");
gtk_entry_set_text(GTK_LABEL(inp3),"0");
gtk_entry_set_text(GTK_ENTRY(inp4),"0");
gtk_entry_set_text(GTK_ENTRY(inp5),"0");
gtk_entry_set_text(GTK_ENTRY(inp6),"0");
gtk_entry_set_text(GTK_ENTRY(inp7),"0");
gtk_entry_set_text(GTK_ENTRY(inp8),"0");
gtk_entry_set_text(GTK_LABEL(inp9),"0");
gtk_entry_set_text(GTK_ENTRY(inp10),"0");
gtk_entry_set_text(GTK_ENTRY(inp11),"0");
gtk_entry_set_text(GTK_ENTRY(inp12),"0");
gtk_entry_set_text(GTK_ENTRY(inp13),"0");
gtk_entry_set_text(GTK_ENTRY(inp14),"0");
gtk_entry_set_text(GTK_LABEL(inp15),"0");
gtk_entry_set_text(GTK_ENTRY(inp16),"0");
gtk_entry_set_text(GTK_ENTRY(inp17),"0");
gtk_entry_set_text(GTK_ENTRY(inp18),"0");
gtk_entry_set_text(GTK_ENTRY(inp19),"0");
gtk_entry_set_text(GTK_ENTRY(inp20),"0");
gtk_entry_set_text(GTK_LABEL(inp21),"0");





}


void
on_button_imprimer_alim_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
pdfalim (b1);
system ("./pdf_alim.sh");
system ("evince alim.pdf \n");
}


void
on_button_ajouter_alim_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
alim b1;
GtkWidget *window = create_window_troup();
GtkWidget *inp1, *inp2,*inp3, *inp4, *inp5, *inp6,*inp7, *inp8, *inp9;
GtkWidget *inp10,*inp11, *inp12, *inp13, *inp14,*inp15, *inp16, *inp17, *inp18,*inp19, *inp20, *inp21;

//SuppAlim(b.MS) ;
inp1=lookup_widget(button,"entry_ms");
inp2=lookup_widget(button,"entry_uem");
inp3=lookup_widget(button,"entry_uel");
inp4=lookup_widget(button,"entry_ueb");

inp5=lookup_widget(button,"entry_ufl");
inp6=lookup_widget(button,"entry_uev");
inp7=lookup_widget(button,"entry_mo");
inp8=lookup_widget(button,"entry_dmo");
inp9=lookup_widget(button,"entry_amidon");
inp10=lookup_widget(button,"entry_sucre");
inp11=lookup_widget(button,"entry_eemg");

inp12=lookup_widget(button,"entry_ndf");
inp13=lookup_widget(button,"entry_adf");
inp14=lookup_widget(button,"entry_adl");
inp15=lookup_widget(button,"entry_cb");

inp16=lookup_widget(button,"entry_pdin");
inp17=lookup_widget(button,"entry_pdie");
inp18=lookup_widget(button,"entry_pdia");
inp19=lookup_widget(button,"entry_mat");
inp20=lookup_widget(button,"entry_lysdi");
inp21=lookup_widget(button,"entry_metdi");

strcpy(b1.MS,gtk_entry_get_text(GTK_ENTRY(inp1)));
strcpy(b1.UEM,gtk_entry_get_text(GTK_ENTRY(inp2)));
strcpy(b1.UEL,gtk_entry_get_text(GTK_ENTRY(inp3)));
strcpy(b1.UEB,gtk_entry_get_text(GTK_ENTRY(inp4)));

strcpy(b1.UFL,gtk_entry_get_text(GTK_ENTRY(inp5)));
strcpy(b1.UEV,gtk_entry_get_text(GTK_ENTRY(inp6)));
strcpy(b1.MO,gtk_entry_get_text(GTK_ENTRY(inp7)));
strcpy(b1.dMO,gtk_entry_get_text(GTK_ENTRY(inp8)));
strcpy(b1.amidon,gtk_entry_get_text(GTK_ENTRY(inp9)));
strcpy(b1.sucre,gtk_entry_get_text(GTK_ENTRY(inp10)));
strcpy(b1.EEMG,gtk_entry_get_text(GTK_ENTRY(inp11)));

strcpy(b1.NDF,gtk_entry_get_text(GTK_ENTRY(inp12)));
strcpy(b1.ADF,gtk_entry_get_text(GTK_ENTRY(inp13)));
strcpy(b1.ADL,gtk_entry_get_text(GTK_ENTRY(inp14)));
strcpy(b1.CB,gtk_entry_get_text(GTK_ENTRY(inp15)));

strcpy(b1.PDIN,gtk_entry_get_text(GTK_ENTRY(inp16)));
strcpy(b1.PDIE,gtk_entry_get_text(GTK_ENTRY(inp17)));
strcpy(b1.PDIA,gtk_entry_get_text(GTK_ENTRY(inp18)));
strcpy(b1.MAT,gtk_entry_get_text(GTK_ENTRY(inp19)));
strcpy(b1.LYSDI,gtk_entry_get_text(GTK_ENTRY(inp20)));
strcpy(b1.METDI,gtk_entry_get_text(GTK_ENTRY(inp21)));
AjoutAlim(b1);
}









void
on_button_actualiser_alim_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
alim b1;
GtkWidget *window = create_window_troup();
GtkWidget *inp1, *inp2,*inp3, *inp4, *inp5, *inp6,*inp7, *inp8, *inp9;
GtkWidget *inp10,*inp11, *inp12, *inp13, *inp14,*inp15, *inp16, *inp17, *inp18,*inp19, *inp20, *inp21;

FILE* n = fopen ("alim.bin","r");
fread(&b1,sizeof(alim),1,n);

inp1=lookup_widget(button,"entry_ms");
inp2=lookup_widget(button,"entry_uem");
inp3=lookup_widget(button,"entry_uel");
inp4=lookup_widget(button,"entry_ueb");

inp5=lookup_widget(button,"entry_ufl");
inp6=lookup_widget(button,"entry_uev");
inp7=lookup_widget(button,"entry_mo");
inp8=lookup_widget(button,"entry_dmo");
inp9=lookup_widget(button,"entry_amidon");
inp10=lookup_widget(button,"entry_sucre");
inp11=lookup_widget(button,"entry_eemg");

inp12=lookup_widget(button,"entry_ndf");
inp13=lookup_widget(button,"entry_adf");
inp14=lookup_widget(button,"entry_adl");
inp15=lookup_widget(button,"entry_cb");

inp16=lookup_widget(button,"entry_pdin");
inp17=lookup_widget(button,"entry_pdie");
inp18=lookup_widget(button,"entry_pdia");
inp19=lookup_widget(button,"entry_mat");
inp20=lookup_widget(button,"entry_lysdi");
inp21=lookup_widget(button,"entry_metdi");


gtk_entry_set_text(GTK_ENTRY(inp1),b1.MS);
gtk_entry_set_text(GTK_ENTRY(inp2),b1.UEM);
gtk_entry_set_text(GTK_LABEL(inp3),b1.UEL);
gtk_entry_set_text(GTK_ENTRY(inp4),b1.UEB);

gtk_entry_set_text(GTK_ENTRY(inp5),b1.UFL);
gtk_entry_set_text(GTK_ENTRY(inp6),b1.UEV);
gtk_entry_set_text(GTK_ENTRY(inp7),b1.MO);
gtk_entry_set_text(GTK_ENTRY(inp8),b1.dMO);
gtk_entry_set_text(GTK_LABEL(inp9),b1.amidon);
gtk_entry_set_text(GTK_ENTRY(inp10),b1.sucre);
gtk_entry_set_text(GTK_ENTRY(inp11),b1.EEMG);

gtk_entry_set_text(GTK_ENTRY(inp12),b1.NDF);
gtk_entry_set_text(GTK_ENTRY(inp13),b1.ADF);
gtk_entry_set_text(GTK_ENTRY(inp14),b1.ADL);
gtk_entry_set_text(GTK_LABEL(inp15),b1.CB);

gtk_entry_set_text(GTK_ENTRY(inp16),b1.PDIN);
gtk_entry_set_text(GTK_ENTRY(inp17),b1.PDIE);
gtk_entry_set_text(GTK_ENTRY(inp18),b1.PDIA);
gtk_entry_set_text(GTK_ENTRY(inp19),b1.MAT);
gtk_entry_set_text(GTK_ENTRY(inp20),b1.LYSDI);
gtk_entry_set_text(GTK_ENTRY(inp21),b1.METDI);

fclose(n);
}

////////////////////////////////////////////////////////////
/*..........................................................

                         FICHE ANIMAL

............................................................*/
////////////////////////////////////////////////////////////
void
on_fiche_animal_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *dialog = create_dialog_fiche_animal();
GtkWidget *label1 = lookup_widget (button,"labeldouble");
GtkWidget *inp1, *inp2,*inp3j,*inp3m,*inp3a, *inp4, *inp5,*inp6, *inp7,*inp8, *inp9, *inp10,*inp11,*inp12,*inp13,*inp14;
char datej[10],datem[10],datea[10],laitt[10];
char jour[10];
char mois[10];
char annee[10];
if (strlen (a_m.ref) != 0){
gtk_widget_show(dialog);
inp1=lookup_widget(dialog,"label_fiche_animal_ref");
inp2=lookup_widget(dialog,"label_fiche_animal_refm");
inp3j=lookup_widget(dialog,"label_fiche_animal_jour");
inp3m=lookup_widget(dialog,"label_fiche_animal_mois");
inp3a=lookup_widget(dialog,"label_fiche_animal_annee");
//inp4=lookup_widget(dialog,"label_fiche_animal_age");
inp5=lookup_widget(dialog,"label_fiche_animal_genre");
inp6=lookup_widget(dialog,"label_fiche_animal_poids");
inp7=lookup_widget(dialog,"label_fiche_animal_robe");
inp8=lookup_widget(dialog,"label_fiche_animal_lot");
inp9=lookup_widget(dialog,"label_fiche_animal_lait");
inp10=lookup_widget(dialog,"label_fiche_animal_sante");
inp11=lookup_widget(dialog,"label_fiche_animal_gender");

inp12=lookup_widget(dialog,"label_fiche_animal_joura");
inp13=lookup_widget(dialog,"label_fiche_animal_moisa");
inp14=lookup_widget(dialog,"label_fiche_animal_anneea");

sprintf (datej,"%2d",a_m.date1.jour);
sprintf (datem,"%2d",a_m.date1.mois);
sprintf (datea,"%4d",a_m.date1.annee);
sprintf (laitt,"%1.2f",a_m.laittotale);


gtk_label_set_text(GTK_LABEL(inp1),a_m.ref);
gtk_label_set_text(GTK_LABEL(inp2),a_m.refm);
gtk_label_set_text(GTK_LABEL(inp3j),datej);
gtk_label_set_text(GTK_LABEL(inp3m),datem);
gtk_label_set_text(GTK_LABEL(inp3a),datea);


int jourint=get_jour(a_m);
int moisint=get_mois(a_m);
int anneeint=get_annee(a_m);
sprintf (jour,"%d",jourint);
sprintf (mois,"%d",moisint);
sprintf (annee,"%d",anneeint);
////////

a_f.date1.jour=jourint;
a_f.date1.mois=moisint;
a_f.date1.annee=anneeint;


gtk_label_set_text(GTK_LABEL(inp12),jour);
gtk_label_set_text(GTK_LABEL(inp13),mois);
gtk_label_set_text(GTK_LABEL(inp14),annee);

gtk_label_set_text(GTK_LABEL(inp5),a_m.gender);
gtk_label_set_text(GTK_LABEL(inp6),a_m.poids);

gtk_label_set_text(GTK_LABEL(inp7),a_m.robe);
gtk_label_set_text(GTK_LABEL(inp8),a_m.lot);
gtk_label_set_text(GTK_LABEL(inp9),laitt);
gtk_label_set_text(GTK_LABEL(inp10),a_m.etat);
gtk_label_set_text(GTK_LABEL(inp11),a_m.type);





gtk_label_set_text(GTK_LABEL(label1),"");
}

else{
gtk_label_set_text(GTK_LABEL(label1),"Double click sur un animal"); 
}
}
////////////////////////////////////////////////////////////
/*..........................................................

                        RADIO/CHECK/dialog

............................................................*/
////////////////////////////////////////////////////////////
void
on_radiobutton1_female1_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
	choixt[0]=0;
}


void
on_radiobutton1_male1_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
	choixt[0]=1;
}


//signal female ajout
void
on_radiobutton_female_clicked0         (GtkButton       *button,
                                        gpointer         user_data)
{
	choixt[0]=0;
}

//signal male ajout
void
on_radiobutton_male_clicked0           (GtkButton       *button,
                                        gpointer         user_data)
{
	choixt[0]=1;
}


/////////////////////////////
void
on_button_lait_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *dialog = create_dialog_lait();
gtk_widget_show(dialog);
}
////////////////////////
void
on_ajout_voeux_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget* dialog_add_animal;
	dialog_add_animal=create_dialog_add_troup();
	gtk_widget_show(dialog_add_animal);
}

/////////////////////////
void
on_okbutton_deleteanimal_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{char ref[20];
GtkWidget *input1;
GtkWidget *dialog_delete ;
dialog_delete = lookup_widget(button,"dialog_delete_troup");

input1=lookup_widget(button,"entry_delete_ref");


strcpy(ref,gtk_entry_get_text(GTK_ENTRY(input1)));


SuppAnimal(ref);
gtk_widget_destroy(dialog_delete);

}


//////////////////////////////////////
void
on_button_pdf_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
pdfT (a_m);
system ("./pdf_ficheanimal.sh");
system ("evince ficheanimal.pdf \n");
}




///////////////////////
void
on_radiobutton_affichage_voeux_clicked (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *treeview13;
treeview13 = lookup_widget(button,"treeview_animal");
AffichListeAnimalVoeux(treeview13);
}

///////////////////////
void
on_radiobutton_affichage_brebis_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *treeview14;
treeview14 = lookup_widget(button,"treeview_animal");
AffichListeAnimalBrebis(treeview14);
}

///////////////////////
void
on_button_declaration_maladie_clicked  (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *dialog = create_dialog_maladie();
gtk_widget_show(dialog);

}


///////////////////////
void
on_radiobutton_autres_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
GtkWidget *i7;
i7=lookup_widget(togglebutton,"entry_autres_maladies");
if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
{
gtk_widget_set_sensitive(i7,TRUE);
gtk_widget_show(i7);
}
else
{
gtk_widget_set_sensitive(i7,FALSE);

}

}
///////////////////////





	
////////////////////////////////////////////////////////////
/*..........................................................

                         DASHBOARD

............................................................*/
////////////////////////////////////////////////////////////
void
on_button_actualiser_aff_troup_clicked (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *b,*v,*l;
FILE *f;
animal a;
int nbb=0,nbv=0;
float nbl=0;
f=fopen ("animal.bin","rb");
int i=0;
while (fread (&a,sizeof (animal),1,f)!=0)
{ 
	if (strcmp (a.type,"brebis")==0)
	
	nbb++;
	if (strcmp (a.type,"voeux")==0)
	
	nbv++;
	nbl=nbl+a.laittotale;
	i++;
}
fclose (f);

b=lookup_widget (button,"label_nbr_breb");
 char *breb = g_strdup_printf ("%d", nbb);
gtk_label_set_text(GTK_LABEL(b),breb);


v=lookup_widget (button,"label_nbr_voeux");
 char *voeux = g_strdup_printf ("%d", nbv);
gtk_label_set_text(GTK_LABEL(v),voeux);

l=lookup_widget (button,"label_nbr_lait");
 char *lait = g_strdup_printf ("%1.2f", nbl);
gtk_label_set_text(GTK_LABEL(l),lait);


}

////////////////////////

void
on_button_gestion_troup_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget* window_gestion_troup=create_window_troup();
	gtk_widget_show(window_gestion_troup);
	GtkWidget *window_emp = lookup_widget(button,"window_employee_space");
gtk_widget_destroy(window_emp);
}


void
on_button_dash_trp_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget* dialog_dash_troup=create_dialog_dash_troup();
	gtk_widget_show(dialog_dash_troup);	
}


void
on_button_retour_maladie_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *dialog = lookup_widget(button,"dialog_maladie");
	gtk_widget_destroy(dialog);
}


void
on_button_non_supp_trp_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *dialog = lookup_widget(button,"dialog_supprimer_check");
	gtk_widget_destroy(dialog);
}


void
on_button_retour_maladie_trp_clicked   (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *dialog = lookup_widget(button,"dialog_maladie");
	gtk_widget_destroy(dialog);
}


void
on_button_cancel_dash_trp_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *dialog = lookup_widget(button,"dialog_dash_troup");
	gtk_widget_destroy(dialog);
}


void
on_button_non_def_trp_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *dialog = lookup_widget(button,"dialog_supprimer_doublecheck");
	gtk_widget_destroy(dialog);
}


void
on_button_top_client_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{GtkWidget *p;
p=lookup_widget(button,"treeview_client");
TOP(A);
afficher_list_client(p);

}





void
on_combo_client_tris_date_changed      (GtkEditable     *editable,
                                        gpointer         user_data)
{


GtkWidget *treeview, *combotri, *combo_entry_tri ;
char ch[20];
combotri = lookup_widget(editable,"comboclient");
combo_entry_tri = GTK_COMBO(combotri)->entry;
strcpy(ch,gtk_entry_get_text(GTK_ENTRY(combo_entry_tri)));
treeview = lookup_widget(editable,"treeview_reservation");







if (strcmp("dateUp",ch )==0)
	{
	tri_min();
	tri_aff(treeview);
	}
if (strcmp("dateDown",ch )==0)
	{
	tri_max();
	tri_aff(treeview);
	}
}



void
on_button_go_to_menu_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{

GtkWidget *window_troup = lookup_widget(button,"window_troup");
GtkWidget *window_equipment = lookup_widget(button,"window_equipements");
GtkWidget *window_client = lookup_widget(button,"window_gestion_des_clients");
GtkWidget *window_capteur = lookup_widget(button,"window1_gestion_capteurs");
GtkWidget *window_plantation = lookup_widget(button,"Gestion_des_plantations");
GtkWidget *window_ouvrier = lookup_widget(button,"window_gest_ouvrier");


GtkWidget *window_employee = create_window_employee_space();
gtk_widget_show(window_employee);

gtk_widget_destroy(window_troup);
gtk_widget_destroy(window_equipment);
gtk_widget_destroy(window_client);
gtk_widget_destroy(window_capteur);
gtk_widget_destroy(window_plantation);
gtk_widget_destroy(window_ouvrier);
}


void
on_button_go_to_auth_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *window_auth = create_window_authentification();
gtk_widget_show(window_auth);

GtkWidget *window_emp = lookup_widget(button,"window_employee_space");
GtkWidget *window_admin = lookup_widget(button,"window_espace_admin");

gtk_widget_destroy(window_emp);
gtk_widget_destroy(window_admin);


}

///////////////////
gboolean
on_user_mdp_button_press_event         (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
GtkWidget *entry;
  entry=lookup_widget(widget,"user_mdp");
  if (strcmp(gtk_entry_get_text(entry),"Mot de passe")==0){
        gtk_entry_set_text(entry,"");
	gtk_entry_set_visibility (GTK_ENTRY (entry), FALSE);}
  return FALSE;
}


gboolean
on_user_id_button_press_event          (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
GtkWidget *entry;
  entry=lookup_widget(widget,"user_id");
  if (strcmp(gtk_entry_get_text(entry),"Identifiant")==0)
        gtk_entry_set_text(entry,"");
  return FALSE;
}


gboolean
on_button_visualise_button_press_event (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	GtkWidget *entry;
  entry=lookup_widget(widget,"user_mdp");
  gtk_entry_set_visibility (GTK_ENTRY (entry), TRUE);
  return FALSE;
}


gboolean
on_button_visualise_button_release_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	GtkWidget *entry;
  entry=lookup_widget(widget,"user_mdp");
  gtk_entry_set_visibility (GTK_ENTRY (entry), FALSE);
  return FALSE;
}
/////////////



void
on_button_ok__affiche__animal_clicked  (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *p;
p=lookup_widget (button,"dialog_fiche_animal");
gtk_widget_destroy(p);
}

