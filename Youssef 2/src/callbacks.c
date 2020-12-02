#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "plantation.h" 

plante p;
char ref[10],ref1[10];


//////////////////////////////////////////////////////////////////////////
void
on_button_ajouter1_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
        GtkWidget* dialog2;
	dialog2=create_dialog2();
	gtk_widget_show(dialog2);
}



void
on_Modifier_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data)
{

	GtkWidget* dialog_modif_plante;
	Supprimer_plante (ref);
	dialog_modif_plante=create_dialog_modif_plante();
	gtk_widget_show(dialog_modif_plante);
	//Modifier_plante (ref,p);
	
}
///////////////////////////////////////////////////////////////////////

void
on_okbutton1_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{

plante p;

GtkWidget *input1, *input_q, *input_d, *input_m, *input_y,*input_q_r,*input5,*input6;
GtkWidget *dialog2;
dialog2 = lookup_widget(objet,"dialog2");

input1=lookup_widget(objet,"reference");
input_q=lookup_widget(objet,"spinbutton10");
//input2=lookup_widget(objet,"stock");
input_d=lookup_widget(objet,"day");
input_m=lookup_widget(objet,"month");
input_y=lookup_widget(objet,"year");
input_q_r=lookup_widget(objet,"spinbutton11");
input5=lookup_widget(objet,"engrais_chimique");
input6=lookup_widget(objet,"commentaire");

strcpy(p.reference,gtk_entry_get_text(GTK_ENTRY(input1)));
p.quant.quantite = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_q));
//strcpy(p.stock,gtk_entry_get_text(GTK_ENTRY(input2)));
p.date.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_d));
p.date.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_m));
p.date.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_y));
p.quant.quantite_recolte = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_q_r));
strcpy(p.engrais,gtk_entry_get_text(GTK_ENTRY(input5)));
strcpy(p.commentaire,gtk_entry_get_text(GTK_ENTRY(input6)));

//Modifier_plante (ref,p);
Ajouter_plante(p);

gtk_widget_destroy(dialog2);
//dialog6 = lookup_widget(objet,"dialog6");
//dialog6=create_dialog6();
//gtk_widget_show(dialog6);

}
void
on_tableau_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *gestion_des_plantations;
GtkWidget *treeview6;

treeview6 = lookup_widget(objet,"treeview6");
gestion_des_plantations = lookup_widget(objet,"gestion_des_plantations");

treeview6 = lookup_widget(gestion_des_plantations,"treeview6");

Afficher_plante(treeview6);
}

void
on_Supprimer_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{GtkWidget* dialog5;
	Supprimer_plante (ref);
	dialog5=create_dialog5();
	gtk_widget_show(dialog5);

/*char reference[10];

GtkWidget *input1;
//GtkWidget *dialog5;
dialog5 = lookup_widget(button,"dialog5");

input1=lookup_widget(button,"REF");

strcpy(reference,gtk_entry_get_text(GTK_ENTRY(input1)));
Supprimer_plante(reference);
dialog5=create_dialog5();*/


}


/*void
on_okbutton2_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *dialog5;
gtk_widget_destroy(dialog5);
}*/

void
on_okbutton3_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *dialog6;

dialog6 = lookup_widget(button,"dialog6");
gtk_widget_destroy(dialog6);

}



void
on_radiobutton1_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{

}

///////////////
void
on_radiobutton2_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{

}

///////////////////
void
on_treeview6_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
gchar* reference;

	GtkTreeModel *model = gtk_tree_view_get_model(treeview);
	if (gtk_tree_model_get_iter(model, &iter, path))
	{
		gtk_tree_model_get(GTK_LIST_STORE(model), &iter, 0, &reference,-1);
		strcpy(p.reference,reference);
		strcpy(ref,reference);
		strcpy(ref1,reference);
		
}
}
////////////////////
void
on_okbutton2_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *dialog5;

dialog5 = lookup_widget(objet,"dialog5");
gtk_widget_destroy(dialog5);
}

/////////////////////
void
on_treeview4_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}



void
on_Rechercher_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *treeview6, *recherche_plante_entry;
	char ref_rech[9];

	treeview6 = lookup_widget (button, "treeview6");
	recherche_plante_entry = lookup_widget (button, "recherche_plante_entry");

	strcpy (ref_rech,gtk_entry_get_text(GTK_ENTRY(recherche_plante_entry)));

	Recherche_plante (ref_rech,treeview6);
}





void
on_button15_clicked                    (GtkWidget      *objet,
                                        gpointer         user_data)
{

}


void
on_okbutton4_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button_actualiser2_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button_modif_plante_clicked         (GtkWidget      *objet,
                                        gpointer         user_data)
{
plante p;

GtkWidget *input1,*input_q, *input_j, *input_m, *input_a,*input_q_r,*input5, *input6;
GtkWidget *dialog_modif_plante;
GtkWidget *dialog6;
dialog_modif_plante = lookup_widget(objet,"dialog_modif_plante");

input1=lookup_widget(objet,"reference_modif");
input_q=lookup_widget(objet,"spinbutton_modif");
input_j=lookup_widget(objet,"spinbutton_jour_modif");
input_m=lookup_widget(objet,"spinbutton_mois_modif");
input_a=lookup_widget(objet,"spinbutton_annee_modif");
input_q_r=lookup_widget(objet,"spinbutton_recolte_modif");
input5=lookup_widget(objet,"engrais_chimique_modif");
input6=lookup_widget(objet,"commentaire_modif");

strcpy(p.reference,gtk_entry_get_text(GTK_ENTRY(input1)));
p.quant.quantite = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_q));
p.date.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_j));
p.date.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_m));
p.date.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_a));
p.quant.quantite_recolte = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_q_r));
strcpy(p.engrais,gtk_entry_get_text(GTK_ENTRY(input5)));
strcpy(p.commentaire,gtk_entry_get_text(GTK_ENTRY(input6)));

//Modifier_plante (ref1,p);
Ajouter_plante(p);

gtk_widget_destroy(dialog_modif_plante);
dialog6 = lookup_widget(objet,"dialog6");
dialog6=create_dialog6();
gtk_widget_show(dialog6);
}

