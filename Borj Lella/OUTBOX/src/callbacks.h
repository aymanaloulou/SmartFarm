#include <gtk/gtk.h>
#include<stdio.h>


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

////////////////// GESTION CLIENTS /////////
#include <gtk/gtk.h>
#include<stdio.h>

void
on_button_gestion_clients_clicked      (GtkWidget    *objet_graphique1,
                                        gpointer         user_data);




void
on_button_ajouter_client_clicked        (GtkWidget       *objet_graphique3,
                                        gpointer         user_data);
void
on_button_modifier_client_clicked      (GtkWidget       *objet_graphique4,
                                        gpointer         user_data);

void
on_button_supprimer_client_clicked     (GtkWidget       *objet_graphique5,
                                        gpointer         user_data);

void
on_button_cancel_ajouter_client_clicked
                                      (GtkWidget       *objet_graphique6,
                                        gpointer         user_data);
 

void
on_button_cancel_modifier_client_clicked
                                        (GtkWidget       *objet_graphique7,
                                        gpointer         user_data);


void
on_button_aj_client_clicked      (GtkWidget       *objet_graphique18,
                                        gpointer         user_data) ;




                                     
void
on_button_modifier_c_clicked           (GtkWidget       *objet_graphique20,
                                        gpointer         user_data);



void
on_button_aff_clicked                  (GtkWidget      *objet_graphique22,
                                        gpointer         user_data);

void
on_button_recherche_clicked            (GtkWidget       *objet_graphique23,
                                        gpointer         user_data);



void
on_button_rechercheee_client_clicked   (GtkWidget       *objet_graphique25,
                                        gpointer         user_data);

void
on_button_aff_historique_clicked       (GtkWidget       *objet_graphique26,
                                        gpointer         user_data);

void
on_button_supp_histo_clicked           (GtkWidget       *objet_graphique27,
                                        gpointer         user_data);


void
on_button_recup_histo_clicked          (GtkWidget       *objet_graphique29,
                                        gpointer         user_data);



void
on_radiobutton_h_aj_group_changed      (GtkRadioButton  *radiobutton,
                                        gpointer         user_data);

void
on_radiobutton_f_aj_group_changed      (GtkRadioButton  *radiobutton,
                                        gpointer         user_data);

void
on_radiobutton_h_mod_group_changed     (GtkRadioButton  *radiobutton,
                                        gpointer         user_data);

void
on_radiobutton_f_mod_group_changed     (GtkRadioButton  *radiobutton,
                                        gpointer         user_data);

void
on_treeview_client_row_activated       (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *col,
                                        gpointer         user_data);

void
on_button_ajouter_res_clicked          (GtkWidget       *objet_graphique31,
                                        gpointer         user_data);

void
on_okbutton_aj_reser_clicked           (GtkWidget       *objet_graphique32,
                                        gpointer         user_data);

void
on_button_aff_reservation_clicked      (GtkWidget       *objet_graphique33,
                                        gpointer         user_data);
//
void
on_checkbutton3_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton2_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);
//

void
on_cancelbutton1_clicked               (GtkWidget       *objet_graphique34,
                                        gpointer         user_data);


void
on_treeview_reservation_row_activated  (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_button_modifier_res_clicked         (GtkWidget       *objet_graphique35,
                                        gpointer         user_data);

void
on_cancelbutton_rese_mod_clicked       (GtkWidget       *objet_graphique36,
                                        gpointer         user_data);

void
on_okbutton_modifier_reser_clicked     (GtkWidget       *objet_graphique37,
                                        gpointer         user_data);
/*
void
on_button_existe_res_clicked           (GtkWidget       *objet_graphique38,
                                      gpointer         user_data);

*/
void
on_button_rech_res_clicked             (GtkWidget       *objet_graphique39,
                                        gpointer         user_data);

void
on_button_rech_rch_clicked             (GtkWidget       *objet_graphique40,
                                        gpointer         user_data);

void
on_okbutton2_clicked                   (GtkWidget       *objet_graphique41,
                                        gpointer         user_data);

void
on_treeview_historique_row_activated   (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);


void
on_button_rech_hiss_clicked            (GtkButton       *objet_graphique43,
                                        gpointer         user_data);

void
on_button_envoyer_email_clicked        (GtkButton       *bojet_graphique44,
                                        gpointer         user_data);

void
on_button_sp_new_clicked               (GtkButton       *objet_graphique45,
                                        gpointer         user_data);

void
on_open_pdf_clicked                    (GtkButton       *objet_graphique46,
                                        gpointer         user_data);

void
on_button_help_clicked                 (GtkButton       *objet_graphique47,
                                        gpointer         user_data);

void
on_button_jeux_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_stat_client_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_GEO_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_SEXE_clicked                 (GtkButton       *objet_graphique55,
                                        gpointer         user_data);

void
on_button_gangant_but_clicked          (GtkButton       *button,
                                        gpointer         user_data);
//////////////////////////////////////////////////////////////// FIN GESTION CLIENT //////////////////////////////////////////////////////////

void
on_button_stat_client_clicked          (GtkButton       *button,
                                        gpointer         user_data);

/***************************************************************************

	partie 2 ouvrier

***************************************************************************/

void
on_okbutton_meilleur_ouv_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_affich_best_ouv_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void
on_okbutton_taux_abs_clicked           (GtkButton       *button,
                                        gpointer         user_data);

                                        
void
on_button_affich_ta_clicked            (GtkButton       *button,
                                        gpointer         user_data);


void
on_button_gestion_ouv_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_gestion_employee_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_show_bw_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_show_ta_clicked              (GtkButton       *button,
                                        gpointer         user_data);
