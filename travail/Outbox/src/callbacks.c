#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "ouvrier.h"

ouvrier o;


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
}


void
on_radiobutton_ouv_femelle_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
	strcpy (o.genre,"Femelle");
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
	//strcpy(o.etat_civil,gtk_entry_get_text(GTK_ENTRY(input_etat)));
	strcpy(o.num_tel,gtk_entry_get_text(GTK_ENTRY(input_num_tel)));
	strcpy(o.adr,gtk_entry_get_text(GTK_ENTRY(input_adr)));
	strcpy(o.email,gtk_entry_get_text(GTK_ENTRY(input_email)));
	strcpy(o.secteur,gtk_entry_get_text(GTK_ENTRY(input_secteur)));

	if(fn_ajout_ouvrier (o,button))
		gtk_widget_destroy(dialog);
}




void
on_button_affich_list_ouv_clicked      (GtkButton       *objet,
                                        gpointer         user_data)
{
	GtkWidget *treeview_liste_ouvrier;

	treeview_liste_ouvrier = lookup_widget (objet, "treeview_affich_ouv");
	
	fn_list_ouvrier (treeview_liste_ouvrier);
}

