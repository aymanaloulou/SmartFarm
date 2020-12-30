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
/*************************************************************************

			GESTION EQUIPEMENTS

**************************************************************************/

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

void
on_treeview_equipement_row_activated   (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_actualiser_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_recherche1_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeview_entretien_row_activated    (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_recherche2_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_actualiser2_clicked                 (GtkButton       *objet,
                                        gpointer         user_data);

void
on_combobox_id_changed                 (GtkComboBox     *combobox,
                                        gpointer         user_data);

void
on_radiobutton_eq_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_entr_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeview_historique_entr_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_treeview_historique_eq_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_reset_histo_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_supp_histo_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_cancel_aj_eq_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_cancel_moif_eq_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_cancel_aj_entr_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_cancel_modif_entr_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_tri_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_combo_entry_tri_changed             (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_combo_entry_tri_entr_changed        (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_button_gestion_equipements_clicked  (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_declarer_eq_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeview_declar_eq_row_activated    (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_recherche_declar_eq_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_cancel_confirm_supp_eq_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void
on_ok_confirm_supp_eq_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_cancel_confirm_supp_entr_clicked    (GtkButton       *button,
                                        gpointer         user_data);

void
on_ok_confirm_supp_entr_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_supp_declar_eq_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_mettre_en_top_eq_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_actualiser_declar_eq_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_pdf_entr_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_alerte_declar_eq_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_ok_dest_declar_eq_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_stat_equip_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_entr_npaye_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_entr_paye_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_show_eq_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_show_entr_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_cancel_parametre_admin_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void
on_ok_parametre_admin_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_change_admin_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_cancel_par_admin_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_ok_par_admin_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_login_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_mdp_oublie_clicked           (GtkButton       *button,
                                        gpointer         user_data);
//////////////////capteurs///////////////////////////////////////////
#include <gtk/gtk.h>


void
on_ajout_capteur_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_okbutton_aj_capteur_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_afficher_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton3_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton4_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton3_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_okbutton_modif_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_okbutton_supp_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_modif_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_boutton_sup_clicked                 (GtkButton       *button,
                                        gpointer         user_data);





void
on_recherche_clicked                   (GtkButton       *button,
                                        gpointer         user_data);









void
on_treeview_capteur_row_activated      (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_bouton_type_affiche_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_alarmante_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_alarmante_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_valide_alar_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_fiche_capteur_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_okbutton1_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_checkbutton3_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton4_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_autres_radio_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_detruit_radio_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_mauvaise_radio_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_mise_jour_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_mauvaise_radio_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_detruit_radio_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_autres_radio_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_checkbutton_panne_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radio_autres_clicked                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button12_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_capteur_reparee_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeview_suivi_row_activated        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_enregistrer_panne_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_affichage_defect_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_alarm_clicked                (GtkButton       *button,
                                        gpointer         user_data);
///////////////////////////////////////////////////////////////////

void
on_button_road_capteurs_clicked        (GtkButton       *button,
                                        gpointer         user_data);



//void
//on_radio_autres_clicked                (GtkButton       *button,
                                        //gpointer         user_data);

void
on_button_val_alarm_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_button163_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_affichage_defect_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_val_alarm_clicked            (GtkButton       *button,
                                        gpointer         user_data);

////////////////////////////////////////////
////////////////////////////////////////////
void
on_button_login_close_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_ajouter1_clicked             (GtkButton       *button,
                                        gpointer         user_data);

/*void
on_okbutton1_clicked                   (GtkWidget      *objet,
                                        gpointer         user_data);*/

void
on_actualiser_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeview_plante_row_activated       (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_treeview_plante_row_activated       (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_tableau_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_Retour_clicked                      (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeview3_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_treeview3_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_Supprimer_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_okbutton2_clicked                   (GtkWidget      *objet,
                                        gpointer         user_data);

void
on_treeview3_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_radiobutton1_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton2_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeview4_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_okbutton2_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_treeview6_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_Modifier_clicked                    (GtkWidget      *objet,
                                        gpointer         user_data);

void
on_Rechercher_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_okbutton3_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_button15_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_okbutton4_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

/*void
on_button_actualiser2_clicked          (GtkButton       *button,
                                        gpointer         user_data);*/

void
on_button_modif_plante_clicked         (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_radiobutton_arbre_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_plante_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_modif_arbre_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_modif_plante_clicked    (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_modif_arbre_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_modif_plante_clicked    (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeview_plante_row_activated       (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_recherche_plante_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_actualiser_plante_clicked           (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_ajouter_plante_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_modifier_plante_clicked             (GtkButton       *objet,
                                        gpointer         user_data);

void
on_supprimer_plante_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_taille_annee_clicked    (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_taille_mois_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_taille_semaine_clicked  (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_semaine_typez_clicked   (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_semaine_typey_clicked   (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_semaine_typex_clicked   (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_mois_typex_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_mois_typey_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_mois_typez_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_annee_typex_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_anne_typey_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_annee_typez_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_typex_clicked                       (GtkButton       *button,
                                        gpointer         user_data);

void
on_typey_clicked                       (GtkButton       *button,
                                        gpointer         user_data);

void
on_typez_clicked                       (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_semaine_modif_clicked   (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_mois_modif_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_annee_modif_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_taille_semaine_modif_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_taille_mois_modif_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_taille_annee_modif_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_valider_modif_clicked               (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_taille_clicked                      (GtkButton       *button,
                                        gpointer         user_data);

void
on_arrosage_mois_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_arrosage_annee_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_arrosage1_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_checkbutton2_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_button21_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data);

/*void
on_actualiser2_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data);*/

void
on_valid_supp_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_ajout_pr__cipitation_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_ajout_precipitation_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_valide_ajout_precipitation_clicked  (GtkButton       *button,
                                        gpointer         user_data);

void
on_Affiche_tableau_de_bord_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_Affiche_TB_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_cancelbutton_ajouter_plante_clicked (GtkButton       *button,
                                        gpointer         user_data);

void
on_cancelbutton_modifier_plante_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_Ajouter_plante_clicked              (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_Modifier_plante_clicked             (GtkWidget       *objet,
                                        gpointer         user_data);



void
on_actualiser_precipitation_clicked    (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_valide_supp_plante_clicked          (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_valide_modif_plante_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_gestion_des_plantations_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_TB_plantations_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton3_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton4_clicked                (GtkButton       *button,
                                        gpointer         user_data);
