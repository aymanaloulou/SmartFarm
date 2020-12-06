#include <gtk/gtk.h>


void
on_treeview_liste_equipements_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_button_ajouter_equipement_clicked   (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_modifier_equipement_clicked  (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_supprimer_equipement_clicked (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_ajouter_entretien_clicked    (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_modifier_entretien_clicked   (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_supprimer_entretien_clicked  (GtkWidget       *button,
                                        gpointer         user_data);

void
on_treeview_liste_entretiens_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_ok_ajouter1_clicked                 (GtkWidget       *button,
                                        gpointer         user_data);

void
on_ok_modifier1_clicked                (GtkWidget       *button,
                                        gpointer         user_data);

void
on_ok_supprimer1_clicked               (GtkWidget       *button,
                                        gpointer         user_data);

void
on_ok_ajouter2_clicked                 (GtkWidget       *button,
                                        gpointer         user_data);

void
on_ok_modifier2_clicked                (GtkWidget       *button,
                                        gpointer         user_data);

void
on_ok_supprimer2_clicked               (GtkWidget       *button,
                                        gpointer         user_data);

void
on_actualiser_equipement_clicked       (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_affiche_equipements_clicked  (GtkWidget       *button,
                                        gpointer         user_data);

void
on_treeview1_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_treeview2_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_button_affiche_entretiens_clicked   (GtkWidget       *button,
                                        gpointer         user_data);


void
on_checkbutton_ajout_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_espece_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_autre_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_checkbutton_ajout_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data);
