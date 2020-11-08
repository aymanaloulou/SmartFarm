#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"


void
on_button_gestion_clients_clicked      (GtkWidget      *objet_graphique1,
                                        gpointer         user_data)
{
GtkWidget *window_employee;
GtkWidget *window_gestion_des_clients;
window_gestion_des_clients=create_window_gestion_des_clients();
gtk_widget_show (window_gestion_des_clients);
gtk_window_set_policy(GTK_WINDOW(window_gestion_des_clients),FALSE,FALSE,FALSE);
gtk_widget_hide (window_employee);
 
}


void
on_button_ajouter_client_clicked       (GtkWidget      *objet_graphique2,
                                        gpointer         user_data)
{
GtkWidget *window_gestion_des_clients;
GtkWidget *window_ajouter_client;
window_ajouter_client=create_window_ajouter_client();
gtk_window_set_policy(GTK_WINDOW(window_gestion_des_clients),FALSE,FALSE,FALSE);
gtk_widget_show (window_ajouter_client);
gtk_widget_hide (window_gestion_des_clients);

}


void
on_button_modifier_client_clicked      (GtkWidget       *objet_graphique3,
                                        gpointer         user_data)
{
GtkWidget *window_gestion_des_clients;
GtkWidget *window_modifier_client;
window_modifier_client = create_window_modifier_client ();
gtk_window_set_policy(GTK_WINDOW(window_gestion_des_clients),FALSE,FALSE,FALSE);
gtk_widget_show (window_modifier_client);
gtk_widget_hide (window_gestion_des_clients);
}

void
on_button_annuler_aj_clicked           (GtkWidget      *objet_graphique4,
                                        gpointer         user_data)
{
GtkWidget *window_ajouter_client;
GtkWidget *window_gestion_des_clients;
gtk_widget_hide (window_ajouter_client);
gtk_widget_show (window_gestion_des_clients);
}


