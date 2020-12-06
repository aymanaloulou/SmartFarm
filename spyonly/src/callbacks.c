#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "troupeaux.h"



//t7el dialog ajout
void
on_ajout_voeux_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget* dialog_add_animal;
	dialog_add_animal=create_dialog_add_troup();
	gtk_widget_show(dialog_add_animal);
	
	
}

//t7el dialog modif
void
on_modif_voeux_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{	
	GtkWidget* dialog_edit_animal;
	dialog_edit_animal=create_dialog_edit_troup();
	gtk_widget_show(dialog_edit_animal);

}


void
on_supp_voeux_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{

}

//t7el dialog ajout
void
on_ajout_brebis_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget* dialog_add_animal2;
	dialog_add_animal2=create_dialog_add_troup();
	gtk_widget_show(dialog_add_animal2);
}

//t7el dialog modif
void
on_modif_brebis_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget* dialog_edit_animal2;
	dialog_edit_animal2=create_dialog_edit_troup();
	gtk_widget_show(dialog_edit_animal2);

}


void
on_supp_brebis_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button_ajoutanimal_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_afficher_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}

