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

/*************************************************************************

			GESTION D'EMPLOYEE

**************************************************************************/


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

void
on_button_liste_point_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_rech_point_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeview_liste_point_row_activated  (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_button_modif_point_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_ajout_conge_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_affich_conge_clicked         (GtkButton       *button,
                                        gpointer         user_data);

