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
on_button_affich_list_ouv_clicked      (GtkButton       *objet,
                                        gpointer         user_data);
