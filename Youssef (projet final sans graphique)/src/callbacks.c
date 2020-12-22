#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "plantation.h" 

plante p;
char ref[10],ref1[10];


/*/////////////////////////////////////////////////////////////////////////
			      Les crudes
/////////////////////////////////////////////////////////////////////////*/
void
on_ajouter_plante_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget* dialog2;
	dialog2=create_dialog2();
	gtk_widget_show(dialog2);

}
void
on_ajout_precipitation_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
precipitation prec;
GtkWidget *date_precipitation, *val,*dialog11;
	date_precipitation = lookup_widget (button, "calendar2");
	val= lookup_widget (button, "precipitation");

	gtk_calendar_get_date (date_precipitation,&prec.date_precip.annee,&prec.date_precip.mois,&prec.date_precip.jour);
	prec.date_precip.mois++;
	prec.valeur_precipitation = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(val));
	
	Ajouter_precipitation(prec);

	dialog11=create_dialog11();
	gtk_widget_show(dialog11);
	

}

void
on_valide_ajout_precipitation_clicked  (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *dialog11;
dialog11 = lookup_widget(button,"dialog11");
gtk_widget_destroy(dialog11);
}

//////
void
on_Affiche_tableau_de_bord_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget* window1;
	window1=create_window1();
	gtk_widget_show(window1);
}
void
on_modifier_plante_clicked             (GtkButton       *objet,
                                        gpointer         user_data)
{
GtkWidget *input1, *input_q,*input_combo_recolte,*input_d, *input_m, *input_y,*input_q_r,*input_combo_p,*input_arrosage,*input_engrais,*input5,*input6,*input_d_e,*input_m_e,*input_a_e,*input_d_t,*input_m_t,*input_a_t;
GtkWidget* dialog9;
	dialog9=create_dialog9();
	gtk_widget_show(dialog9);
//////

//////
input1=lookup_widget(dialog9,"reference_modif");
input_q=lookup_widget(dialog9,"quantite_modif");
input_combo_p=lookup_widget(dialog9,"unite_modif");
input_d=lookup_widget(dialog9,"jour");
input_m=lookup_widget(dialog9,"mois");
input_y=lookup_widget(dialog9,"annee");
input_q_r=lookup_widget(dialog9,"quantite_recolte_modif");

GtkWidget *input_modif1=lookup_widget(dialog9,"spinbutton17");
GtkWidget *input_modif2=lookup_widget(dialog9,"spinbutton18");
GtkWidget *input_modif3=lookup_widget(dialog9,"spinbutton19");

input_combo_recolte=lookup_widget(dialog9,"unite_recolte_modif");
input_engrais=lookup_widget(dialog9,"engrais_modif");
input_d_e=lookup_widget(dialog9,"jour_engrais_modif");
input_m_e=lookup_widget(dialog9,"mois_engrais_modif");
input_a_e=lookup_widget(dialog9,"annee_engrais_modif");
input_d_t=lookup_widget(dialog9,"jour_taille_modif");
input_m_t=lookup_widget(dialog9,"mois_taille_modif");
input_a_t=lookup_widget(dialog9,"annee_taille_modif");
input6=lookup_widget(dialog9,"commentaire_modif");



gtk_entry_set_text(GTK_ENTRY(input1),p.reference);


gtk_spin_button_set_value(input_q,p.quant.quantite);
//////

////////////////
gtk_spin_button_set_value(input_d,p.date.jour);
gtk_spin_button_set_value(input_m,p.date.mois);
gtk_spin_button_set_value(input_y,p.date.annee);
gtk_spin_button_set_value(input_q_r,p.quant.quantite_recolte);

gtk_spin_button_set_value(input_modif1,p.date_recolte.jour);
gtk_spin_button_set_value(input_modif2,p.date_recolte.mois);
gtk_spin_button_set_value(input_modif3,p.date_recolte.annee);

gtk_spin_button_set_value(input_d_e,p.date_engrais1.jour);
gtk_spin_button_set_value(input_m_e,p.date_engrais1.mois);
gtk_spin_button_set_value(input_a_e,p.date_engrais1.annee);

gtk_spin_button_set_value(input_d_t,p.date_taille.jour);
gtk_spin_button_set_value(input_m_t,p.date_taille.mois);
gtk_spin_button_set_value(input_a_t,p.date_taille.annee);
gtk_entry_set_text(GTK_ENTRY(input6),p.commentaire);
}

void
on_supprimer_plante_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget* dialog10;
	Supprimer_plante (ref);
	dialog10=create_dialog10();
	gtk_widget_show(dialog10);
}
void
on_okbutton2_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *dialog5;
dialog5 = lookup_widget(objet,"dialog5");
gtk_widget_destroy(dialog5);
}
void
on_valid_supp_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *dialog10;
dialog10 = lookup_widget(button,"dialog10");
gtk_widget_destroy(dialog10);
}
void
on_okbutton3_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *dialog6;

dialog6 = lookup_widget(button,"dialog6");
gtk_widget_destroy(dialog6);

}


void
on_recherche_plante_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *treeview_plante, *recherche_plante_entry;
	char ref_rech[9];

	treeview_plante = lookup_widget (button, "treeview_plante");
	recherche_plante_entry = lookup_widget (button, "recherche_plante_entry");

	strcpy (ref_rech,gtk_entry_get_text(GTK_ENTRY(recherche_plante_entry)));

	Recherche_plante (ref_rech,treeview_plante);
}
void
on_actualiser_plante_clicked           (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *gestion_des_plantations;
GtkWidget *treeview_plante;

treeview_plante = lookup_widget(objet,"treeview_plante");
gestion_des_plantations = lookup_widget(objet,"Gestion_des_plantations");

treeview_plante = lookup_widget(gestion_des_plantations,"treeview_plante");

Afficher_plante(treeview_plante);
}
void
on_actualiser2_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)

{
GtkWidget *gestion_des_plantations;
GtkWidget *treeview_precipitation;

treeview_precipitation = lookup_widget(objet,"treeview_precipitation");
gestion_des_plantations = lookup_widget(objet,"Gestion_des_plantations");

treeview_precipitation = lookup_widget(gestion_des_plantations,"treeview_precipitation");

Afficher_precipitation(treeview_precipitation);	
}
////////
void
on_Affiche_TB_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *window1;

GtkWidget *objet;



 window1=create_window1();

gtk_widget_show(window1);
partie2(window1);
//

}
/*/////////////////////////////////////////////////////////////////////////
			Les tableaux d'affichage
/////////////////////////////////////////////////////////////////////////*/
void
on_treeview_plante_row_activated       (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
gchar* reference;
gchar* Quantite;
gchar* unite;
gchar* date;
gchar* date1;
gchar* date2;
gchar* Quantite1;
gchar* date_recolte;
gchar* unite_r;
gchar* arrosage;
gchar* engrais_ch;
gchar* use;
gchar* taille;
gchar* commentaire;

	GtkTreeModel *model = gtk_tree_view_get_model(treeview);
	if (gtk_tree_model_get_iter(model, &iter, path))
	{
gtk_tree_model_get (GTK_LIST_STORE (model), &iter, 0, &reference, 1, &Quantite, 2, &unite, 3, &date, 4, &Quantite1,5,&date_recolte, 6, &arrosage, 7, &engrais_ch,8,&date1, 9, &use,10,&date2,11,&commentaire,-1);	
		strcpy(p.reference,reference);
		strcpy(ref,reference);
		strcpy(ref1,reference);
		strcpy (p.unit.unite, unite);
		strcpy (p.arrosage, arrosage);
                sscanf (date,"%d/%d/%d",&p.date.jour,&p.date.mois,&p.date.annee);
		sscanf (date_recolte,"%d/%d/%d",&p.date_recolte.jour,&p.date_recolte.mois,&p.date_recolte.annee);
		sscanf (date1,"%d/%d/%d",&p.date_engrais1.jour,&p.date_engrais1.mois,&p.date_engrais1.annee);
		sscanf (date2,"%d/%d/%d",&p.date_taille.jour,&p.date_taille.mois,&p.date_taille.annee);
		sscanf (Quantite,"%d",&p.quant.quantite);
		sscanf (Quantite1,"%d",&p.quant.quantite_recolte);
		strcpy (p.commentaire, commentaire);
		
				
}
}
/*/////////////////////////////////////////////////////////////////////////
			      Les boutons radio + cases à cocher 
/////////////////////////////////////////////////////////////////////////*/
char TEXT[20];
void
on_radiobutton_taille_semaine_clicked  (GtkButton       *button,
                                        gpointer         user_data)
{ 
 strcpy(TEXT,"quotidien");
}
void
on_radiobutton_taille_mois_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{ 
 strcpy(TEXT,"hebdomadaire");
}
void 
on_radiobutton_taille_annee_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{ 
 strcpy(TEXT,"mensuel");
}


//////////
char TEXT1[20];
void
on_arrosage_mois_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
 strcpy(TEXT1,"hebdomadaire");
}

void
on_arrosage_annee_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
 strcpy(TEXT1,"mensuel");
}

void
on_arrosage1_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
 strcpy(TEXT1,"quotidien");
}


/*/////////////////////////////////////////////////////////////////////////
			Les interfaces d'ajout et modif
/////////////////////////////////////////////////////////////////////////*/
void
on_okbutton1_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{
plante p;
//strcpy(p.taille,"---");
char text1[20]="";
char text2[20]="";
char text3[20]="";
int T;

GtkWidget *taille,*input1, *input_q,*input_combo_recolte,*input_d, *input_m, *input_y,*input_q_r,*input_combo_p,*input_arrosage,*input_engrais,*input5,*input6,*input_d_e,*input_m_e,*input_a_e,*input_d_t,*input_m_t,*input_a_t;
GtkWidget *dialog2;
dialog2 = lookup_widget(objet,"dialog2");

input1=lookup_widget(objet,"reference");
input_q=lookup_widget(objet,"spinbutton10");
input_combo_p=lookup_widget(objet,"unite_plante");
input_d=lookup_widget(objet,"day");
input_m=lookup_widget(objet,"month");
input_y=lookup_widget(objet,"year");

input_q_r=lookup_widget(objet,"spinbutton11");

GtkWidget *input_d_r=lookup_widget(objet,"spinbutton14");
GtkWidget *input_m_r=lookup_widget(objet,"spinbutton15");
GtkWidget *input_y_r=lookup_widget(objet,"spinbutton16");

input_engrais=lookup_widget(objet,"engrais_chimique");
input_d_e=lookup_widget(objet,"spinbutton_j_engrais");
input_m_e=lookup_widget(objet,"spinbutton_m_engrais");
input_a_e=lookup_widget(objet,"spinbutton_a_engrais");
input_d_t=lookup_widget(objet,"taille_jour");
input_m_t=lookup_widget(objet,"taille_mois");
input_a_t=lookup_widget(objet,"taille_annee");
input6=lookup_widget(objet,"commentaire");
taille = lookup_widget (objet, "taille");


strcpy(p.reference,gtk_entry_get_text(GTK_ENTRY(input1)));
p.quant.quantite = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_q));
strcpy(p.unit.unite,gtk_combo_box_get_active_text(GTK_COMBO_BOX(input_combo_p)));

p.date.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_d));
p.date.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_m));
p.date.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_y));

p.quant.quantite_recolte = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_q_r));
if (p.quant.quantite_recolte==0){

p.date_recolte.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(0));
p.date_recolte.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(0));
p.date_recolte.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(0));}
else {
p.date_recolte.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_d_r));
p.date_recolte.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_m_r));
p.date_recolte.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_y_r));}


strcpy(p.arrosage,TEXT);
p.date_engrais1.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_d_e));
p.date_engrais1.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_m_e));
p.date_engrais1.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_a_e));

if (gtk_toggle_button_get_active (taille)){
strcpy(p.taille,"oui");
p.date_taille.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_d_t));
p.date_taille.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_m_t));
p.date_taille.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_a_t));}

else{
strcpy(p.taille,"---");
p.date_taille.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(0));
p.date_taille.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(0));
p.date_taille.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(0));
}
strcpy(p.engrais,gtk_combo_box_get_active_text(GTK_COMBO_BOX(input_engrais)));
if (strcmp(gtk_entry_get_text(GTK_ENTRY(input6)),"") !=0 )
	strcpy(p.commentaire,gtk_entry_get_text(GTK_ENTRY(input6)));
else 
	strcpy(p.commentaire,"RAS");

if (Ajouter_plante(p,objet)){

gtk_widget_destroy(dialog2);}
}

void
on_button21_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data)
{
Supprimer_plante (ref);
plante p;
char text1[20]="";
char text2[20]="";
GtkWidget *input1, *input_q,*input_combo_recolte,*input_d, *input_m, *input_y,*input_q_r,*input_combo_p,*input_arrosage,*input_engrais,*input5,*input6,*input_d_e,*input_m_e,*input_a_e,*input_d_t,*input_m_t,*input_a_t;
GtkWidget *dialog9;
GtkWidget *dialog6;
dialog9 = lookup_widget(objet,"dialog9");


input1=lookup_widget(objet,"reference_modif");
input_q=lookup_widget(objet,"quantite_modif");
input_combo_p=lookup_widget(objet,"unite_modif");
input_d=lookup_widget(objet,"jour");
input_m=lookup_widget(objet,"mois");
input_y=lookup_widget(objet,"annee");

input_q_r=lookup_widget(objet,"quantite_recolte_modif");

GtkWidget *input_d_r=lookup_widget(objet,"spinbutton17");
GtkWidget *input_m_r=lookup_widget(objet,"spinbutton18");
GtkWidget *input_y_r=lookup_widget(objet,"spinbutton19");
GtkWidget *taille = lookup_widget (objet, "checkbutton2");
input_engrais=lookup_widget(objet,"engrais_modif");
input_d_e=lookup_widget(objet,"jour_engrais_modif");
input_m_e=lookup_widget(objet,"mois_engrais_modif");
input_a_e=lookup_widget(objet,"annee_engrais_modif");

input_d_t=lookup_widget(objet,"jour_taille_modif");
input_m_t=lookup_widget(objet,"mois_taille_modif");
input_a_t=lookup_widget(objet,"annee_taille_modif");
input6=lookup_widget(objet,"commentaire_modif");

strcpy(p.reference,gtk_entry_get_text(GTK_ENTRY(input1)));
p.quant.quantite = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_q));
strcpy(p.unit.unite,gtk_combo_box_get_active_text(GTK_COMBO_BOX(input_combo_p)));
p.date.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_d));
p.date.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_m));
p.date.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_y));

p.quant.quantite_recolte = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_q_r));
if (p.quant.quantite_recolte==0){
p.date_recolte.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(0));
p.date_recolte.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(0));
p.date_recolte.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(0));
}
else {
p.date_recolte.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_d_r));
p.date_recolte.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_m_r));
p.date_recolte.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_y_r));}


strcpy(p.arrosage,TEXT1);
p.date_engrais1.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_d_e));
p.date_engrais1.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_m_e));
p.date_engrais1.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_a_e));


if (gtk_toggle_button_get_active (taille)){
strcpy(p.taille,"oui");
p.date_taille.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_d_t));
p.date_taille.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_m_t));
p.date_taille.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input_a_t));}
else {
strcpy(p.taille,"---");

p.date_taille.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(0));
p.date_taille.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(0));
p.date_taille.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(0));}
strcpy(p.engrais,gtk_combo_box_get_active_text(GTK_COMBO_BOX(input_engrais)));
strcpy(p.commentaire,gtk_entry_get_text(GTK_ENTRY(input6)));

if(Ajouter_plante(p,objet)){

gtk_widget_destroy(dialog9);
dialog6 = lookup_widget(objet,"dialog6");
dialog6=create_dialog6();
gtk_widget_show(dialog6);}
}

/*/////////////////////////////////////////////////////////////////////////
			Fin du programme
/////////////////////////////////////////////////////////////////////////*/
//**************************************************

//############################################################











