#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <string.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "equipements.h" 
#include "entretiens.h"

entretiens entr;


//////////////////////////////////////////////////////////////////////////
void
on_button_ajouter_equipement_clicked   (GtkWidget       *button, gpointer         user_data)
{
	GtkWidget* dialog_ajouter_equipement;
	dialog_ajouter_equipement=create_dialog_ajouter_equipement();
	gtk_widget_show(dialog_ajouter_equipement);
}


void
on_button_modifier_equipement_clicked  (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget* dialog_modifier_equipement;
	dialog_modifier_equipement=create_dialog_modifier_equipement();
	gtk_widget_show(dialog_modifier_equipement);
}


void
on_button_supprimer_equipement_clicked (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget* dialog_supprimer_equipement;
	dialog_supprimer_equipement=create_dialog_supprimer_equipement();
	gtk_widget_show(dialog_supprimer_equipement);
}


void
on_button_ajouter_entretien_clicked    (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget* dialog_ajouter_entretien;
	dialog_ajouter_entretien=create_dialog_ajouter_entretien();
	gtk_widget_show(dialog_ajouter_entretien);
}


void
on_button_modifier_entretien_clicked   (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget* dialog_modifier_entretien;
	dialog_modifier_entretien=create_dialog_modifier_entretien();
	gtk_widget_show(dialog_modifier_entretien);
}


void
on_button_supprimer_entretien_clicked  (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget* dialog_supprimer_entretien;
	dialog_supprimer_entretien=create_dialog_supprimer_entretien();
	gtk_widget_show(dialog_supprimer_entretien);
}

///////////////////////////////////////////////////////////////////////

void
on_ok_ajouter1_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)
{

equipements eq;

GtkWidget *input1, *input2, *input3, *input4, *input5, *input6;
/*GtkWidget *window1;
window1 = lookup_widget(objet,"window1");*/
GtkWidget *dialog_ajouter;
dialog_ajouter = lookup_widget(objet,"dialog_ajouter_equipement");

input1=lookup_widget(objet,"id");
input2=lookup_widget(objet,"type");
input3=lookup_widget(objet,"marque");
input4=lookup_widget(objet,"date");
input5=lookup_widget(objet,"prix");
input6=lookup_widget(objet,"association");

strcpy(eq.id,gtk_entry_get_text(GTK_ENTRY(input1)));
strcpy(eq.type,gtk_entry_get_text(GTK_ENTRY(input2)));
strcpy(eq.marque,gtk_entry_get_text(GTK_ENTRY(input3)));
strcpy(eq.date,gtk_entry_get_text(GTK_ENTRY(input4)));
strcpy(eq.prix,gtk_entry_get_text(GTK_ENTRY(input5)));
strcpy(eq.association,gtk_entry_get_text(GTK_ENTRY(input6)));

ajouter_equipement(eq);
gtk_widget_destroy(dialog_ajouter);

}

void
on_button_affiche_equipements_clicked  (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *fenetre_affiche;
GtkWidget *treeview1;

//fenetre_affiche = lookup_widget(objet,"affiche_equipements");
fenetre_affiche=create_affiche_equipements();
gtk_widget_show(fenetre_affiche);

treeview1 = lookup_widget(fenetre_affiche,"treeview1");
afficher_equipement(treeview1);
}


/*void
on_treeview1_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
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
		strcpy(eq.id,id);
		strcpy(eq.type,type);
		strcpy(eq.marque,marque);
		strcpy(eq.date,date);
		strcpy(eq.prix,prix);
		strcpy(eq.association,association);
		supprimer_equipement(eq.id);
		afficher_equipement(treeview);
}
}
*/
void
on_ok_modifier1_clicked                (GtkWidget       *objet,
                                        gpointer         user_data)
{
equipements eq;

GtkWidget *input1, *input2, *input3, *input4, *input5, *input6;
GtkWidget *dialog_modifier;
dialog_modifier = lookup_widget(objet,"dialog_modifier_equipement");

input1=lookup_widget(objet,"id");
input2=lookup_widget(objet,"type");
input3=lookup_widget(objet,"marque");
input4=lookup_widget(objet,"date");
input5=lookup_widget(objet,"prix");
input6=lookup_widget(objet,"association");

strcpy(eq.id,gtk_entry_get_text(GTK_ENTRY(input1)));
strcpy(eq.type,gtk_entry_get_text(GTK_ENTRY(input2)));
strcpy(eq.marque,gtk_entry_get_text(GTK_ENTRY(input3)));
strcpy(eq.date,gtk_entry_get_text(GTK_ENTRY(input4)));
strcpy(eq.prix,gtk_entry_get_text(GTK_ENTRY(input5)));
strcpy(eq.association,gtk_entry_get_text(GTK_ENTRY(input6)));
supprimer_equipement(eq.id);
ajouter_equipement(eq);
gtk_widget_destroy(dialog_modifier);
}


void
on_ok_supprimer1_clicked               (GtkWidget       *objet,
                                        gpointer         user_data)
{
char id[20];
char raison[100];
GtkWidget *input1, *input2;
GtkWidget *dialog_supprimer;
dialog_supprimer = lookup_widget(objet,"dialog_supprimer_equipement");

input1=lookup_widget(objet,"id");
input2=lookup_widget(objet,"raison");

strcpy(id,gtk_entry_get_text(GTK_ENTRY(input1)));
strcpy(raison,gtk_entry_get_text(GTK_ENTRY(input2)));

supprimer_equipement(id);
gtk_widget_destroy(dialog_supprimer);
}


void
on_ok_ajouter2_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)
{
entretiens entr;

GtkWidget *input1, *input2, *input3, *input4, *input5, *input6;

GtkWidget *dialog_ajouter;
dialog_ajouter = lookup_widget(objet,"dialog_ajouter_entretien");

input1=lookup_widget(objet,"id_eq");
input2=lookup_widget(objet,"id_entr");
input3=lookup_widget(objet,"date");
input4=lookup_widget(objet,"entreteneur");
input5=lookup_widget(objet,"montant");
input6=lookup_widget(objet,"reference");

strcpy(entr.id_eq,gtk_entry_get_text(GTK_ENTRY(input1)));
strcpy(entr.id_entr,gtk_entry_get_text(GTK_ENTRY(input2)));
strcpy(entr.date,gtk_entry_get_text(GTK_ENTRY(input3)));
strcpy(entr.entreteneur,gtk_entry_get_text(GTK_ENTRY(input4)));
strcpy(entr.montant,gtk_entry_get_text(GTK_ENTRY(input5)));
strcpy(entr.reference,gtk_entry_get_text(GTK_ENTRY(input6)));

ajouter_entretien(entr);
gtk_widget_destroy(dialog_ajouter);

}


void
on_ok_modifier2_clicked                (GtkWidget       *objet,
                                        gpointer         user_data)
{
entretiens entr;

GtkWidget *input1, *input2, *input3, *input4, *input5, *input6;

GtkWidget *dialog_modifier;
dialog_modifier = lookup_widget(objet,"dialog_modifier_entretien");

input1=lookup_widget(objet,"id_eq");
input2=lookup_widget(objet,"id_entr");
input3=lookup_widget(objet,"date");
input4=lookup_widget(objet,"entreteneur");
input5=lookup_widget(objet,"montant");
input6=lookup_widget(objet,"reference");

strcpy(entr.id_eq,gtk_entry_get_text(GTK_ENTRY(input1)));
strcpy(entr.id_entr,gtk_entry_get_text(GTK_ENTRY(input2)));
strcpy(entr.date,gtk_entry_get_text(GTK_ENTRY(input3)));
strcpy(entr.entreteneur,gtk_entry_get_text(GTK_ENTRY(input4)));
strcpy(entr.montant,gtk_entry_get_text(GTK_ENTRY(input5)));
strcpy(entr.reference,gtk_entry_get_text(GTK_ENTRY(input6)));
supprimer_entretien(entr.id_entr);
ajouter_entretien(entr);
gtk_widget_destroy(dialog_modifier);
}


void
on_ok_supprimer2_clicked               (GtkWidget       *objet,
                                        gpointer         user_data)
{
char id_entr[20];
GtkWidget *input1;
GtkWidget *dialog_supprimer;
dialog_supprimer = lookup_widget(objet,"dialog_supprimer_entretien");

input1=lookup_widget(objet,"id_entr");

strcpy(id_entr,gtk_entry_get_text(GTK_ENTRY(input1)));

supprimer_entretien(id_entr);
gtk_widget_destroy(dialog_supprimer);
}



/*void
on_treeview2_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	GtkTreeIter iter;
	gchar* id_eq;
	gchar* id_entr;
	gchar* date;
	gchar* entreteneur ;
	gchar* montant;
	gchar* payement;
	gchar* type_payement;
	gchar* reference;
	
	entretiens entr;
	
	GtkTreeModel *model = gtk_tree_view_get_model(treeview);
	if (gtk_tree_model_get_iter(model, &iter, path))
	{
		gtk_tree_model_get(GTK_LIST_STORE(model), &iter, 0, &id_eq,1, &id_entr,2, &date,3, &entreteneur,4, &montant,5, &payement,6,&type_payement,7,&reference, -1);
		strcpy(entr.id_eq,id_eq);
		strcpy(entr.id_entr,id_entr);
		strcpy(entr.date,date);
		strcpy(entr.entreteneur,entreteneur);
		strcpy(entr.montant,montant);
		strcpy(entr.payement,payement);
		strcpy(entr.type_payement,type_payement);
		strcpy(entr.reference,reference);
		supprimer_entretien(entr.id_entr);
		afficher_entretien(treeview);
}
}

*/
void
on_button_affiche_entretiens_clicked   (GtkWidget       *button,
                                        gpointer         user_data)
{
GtkWidget *fenetre_affiche;
GtkWidget *treeview2;

//fenetre_affiche = lookup_widget(objet,"affiche_equipements");
fenetre_affiche=create_affiche_entretiens();
gtk_widget_show(fenetre_affiche);

treeview2 = lookup_widget(fenetre_affiche,"treeview2");
afficher_entretien(treeview2);
}


char payement[20]="Non payé";
void
on_checkbutton_ajout_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
	strcpy(payement,"Payé");

}


void
on_radiobutton_espece_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
	strcpy (entr.type_payement,"Espèce");
}


void
on_radiobutton_autre_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
	strcpy (entr.type_payement,"NON Espèce");
}


/*void
on_checkbutton_ajout_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}
*/
