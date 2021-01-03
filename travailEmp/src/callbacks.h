#include <gtk/gtk.h>


void
on_button_ajout_emp_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_cancelbutton_ajout_emp_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void
on_okbutton_ajout_emp_clicked          (GtkWidget       *button,
                                        gpointer         user_data);

void
on_radiobutton_emp_male_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_emp_femelle_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_liste_emp_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_supp_emp_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeview_liste_emp_row_activated    (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_button_modif_emp_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_cancelbutton_modif_emp_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void
on_okbutton_modif_emp_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_rech_emp_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeview_liste_conge_row_activated  (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_button_valid_cong_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_liste_conge_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_liste_conge_valide_clicked   (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_supp_conge_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_reset_conge_clicked          (GtkButton       *button,
                                        gpointer         user_data);
