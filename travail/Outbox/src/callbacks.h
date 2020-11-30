#include <gtk/gtk.h>


void
on_button_ajouter_ouvrier_clicked      (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_ajout_ouvrier_clicked        (GtkWidget       *button,
                                        gpointer         user_data);

void
on_cancelbutton_ajout_ouv_clicked      (GtkWidget       *button,
                                        gpointer         user_data);

void
on_okbutton_ajout_ouv_clicked          (GtkWidget       *button,
                                        gpointer         user_data);



void
on_radiobutton_ouv_male_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_ouv_femelle_clicked     (GtkButton       *button,
                                        gpointer         user_data);



void
on_button_affich_list_ouv_clicked      (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_treeview_affich_ouv_row_activated   (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_button_supp_ouvrier_clicked         (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_modif_ouvrier_clicked        (GtkWidget       *button,
                                        gpointer         user_data);

void
on_cancelbutton_modif_ouvrier_clicked  (GtkWidget      *button,
                                        gpointer         user_data);

void
on_okbutton_modif_ouvrier_clicked      (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_rech_ouvrier_clicked         (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_liste_ouv_point_clicked      (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_rech_point_ouvrier_clicked   (GtkWidget       *button,
                                        gpointer         user_data);

void
on_treeview_affich_point_ouv_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_button_ajout_point_clicked          (GtkWidget       *button,
                                        gpointer         user_data);
