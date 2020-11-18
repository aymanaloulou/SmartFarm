#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "gestion_clients.h"

                           ////////////////////// liaison entre les windows + button supprimer /////////////////////


void
on_button_gestion_clients_clicked      (GtkWidget    *objet_graphique1,
                                        gpointer         user_data)
{
GtkWidget *window_gestion_des_clients;
window_gestion_des_clients=create_window_gestion_des_clients();
gtk_widget_show(window_gestion_des_clients);

}


void
on_button_gestion_d_achats_clicked     (GtkWidget       *objet_graphique2,
                                        gpointer         user_data)
{
GtkWidget *window_gestion_achat;
window_gestion_achat=create_window_gestion_achat();
gtk_widget_show(window_gestion_achat);


}


void
on_button_ajouter_client_clicked        (GtkWidget       *objet_graphique3,
                                        gpointer         user_data)
{
GtkWidget *dialog_ajouter_client;
dialog_ajouter_client=create_dialog_ajouter_client();
gtk_widget_show(dialog_ajouter_client);

}


void
on_button_modifier_client_clicked       (GtkWidget       *objet_graphique4,
                                        gpointer         user_data)
{
GtkWidget *dialog_modifier_client;
dialog_modifier_client=create_dialog_modifier_client();
gtk_widget_show(dialog_modifier_client);
}


void
on_button_supprimer_client_clicked      (GtkWidget       *objet_graphique5,
                                        gpointer         user_data)
{

}


void
on_button_cancel_ajouter_client_clicked
                                        (GtkWidget       *objet_graphique6,
                                        gpointer         user_data)
{
GtkWidget *dialog_ajouter_client;
dialog_ajouter_client=lookup_widget(objet_graphique6,"dialog_ajouter_client");
gtk_widget_destroy(dialog_ajouter_client);
}


void
on_button_cancel_modifier_client_clicked
                                        (GtkWidget       *objet_graphique7,
                                        gpointer         user_data)
{
GtkWidget *dialog_modifier_client;
dialog_modifier_client=lookup_widget(objet_graphique7,"dialog_modifier_client");
gtk_widget_destroy(dialog_modifier_client);
}


void
on_button_ajouter_produit_clicked      (GtkWidget       *objet_graphique8,
                                        gpointer         user_data)
{
GtkWidget *dialog_ajouter_produit;
dialog_ajouter_produit=create_dialog_ajouter_produit();
gtk_widget_show(dialog_ajouter_produit);
}


void
on_button_modifier_produit_clicked    (GtkWidget       *objet_graphique9,
                                        gpointer         user_data)
{
GtkWidget *dialog_modifier_produit;
dialog_modifier_produit=create_dialog_modifier_produit();
gtk_widget_show(dialog_modifier_produit);
}


void
on_button_supprimer_produit_clicked    (GtkWidget       *objet_graphique10,
                                        gpointer         user_data)
{

}


void
on_button_mod_fact_clicked             (GtkWidget       *objet_graphique11,
                                        gpointer         user_data)
{
GtkWidget *dialog_modif_facture;
dialog_modif_facture=create_dialog_modif_facture();
gtk_widget_show(dialog_modif_facture);


}


void
on_button_supp_fact_clicked           (GtkWidget       *objet_graphique12,
                                        gpointer         user_data)
{

}


void
on_button_ajotuer_fact_clicked         (GtkWidget       *objet_graphique13,
                                        gpointer         user_data)
{
GtkWidget *dialog_ajouter_facture;
dialog_ajouter_facture=create_dialog_ajouter_facture();
gtk_widget_show(dialog_ajouter_facture);
}


void
on_button_cancel_aj_produit_clicked    (GtkWidget       *objet_graphique14,
                                        gpointer         user_data)
{GtkWidget *dialog_ajouter_produit;
dialog_ajouter_produit=lookup_widget(objet_graphique14,"dialog_ajouter_produit");
gtk_widget_destroy(dialog_ajouter_produit);


}


void
on_button_cancel_mod_prod_clicked      (GtkWidget       *objet_graphique15,
                                        gpointer         user_data)
{
GtkWidget *dialog_modifier_produit;
dialog_modifier_produit=lookup_widget(objet_graphique15,"dialog_modifier_produit");
gtk_widget_destroy(dialog_modifier_produit);
}


void
on_button_cancel_aj_fact_clicked       (GtkWidget       *objet_graphique16,
                                        gpointer         user_data)
{
GtkWidget *dialog_ajouter_facture;
dialog_ajouter_facture=lookup_widget(objet_graphique16,"dialog_ajouter_facture");
gtk_widget_destroy(dialog_ajouter_facture);
}


void
on_button_cancel_mod_fact_clicked      (GtkWidget       *objet_graphique17,
                                        gpointer         user_data)
{
GtkWidget *dialog_modif_facture;
dialog_modif_facture=lookup_widget(objet_graphique17,"dialog_modif_facture");
gtk_widget_destroy(dialog_modif_facture);
}
                              ///////////////////////// crud list des clients //////////////////////////

void
on_button_aj_client_clicked          (GtkWidget      *objet_graphique18,
                                        gpointer         user_data)
{
GtkWidget *input1,*input2,*input3,*input4,*input5,*input6,*input7,*input8,*input9,*input10,*input11,*input12;
GtkWidget *check,*check_exist;
Client S,c;

// ini input //
input1= lookup_widget(objet_graphique18, "entry_nom_aj_c") ; 
input2 = lookup_widget(objet_graphique18, "entry_prenom_aj_c") ; 
input3 = lookup_widget(objet_graphique18, "entry_cin_aj_c") ; 
input4 = lookup_widget(objet_graphique18, "spinbutton_jr_aj_c") ; 
input5 = lookup_widget(objet_graphique18, "spinbutton_mois_aj_c") ; 
input6 = lookup_widget(objet_graphique18, "spinbutton_annee_aj_c") ;
input7 = lookup_widget(objet_graphique18, "radiobutton_h_aj_c") ;  
input8 = lookup_widget(objet_graphique18, "radiobutton_f_aj_c") ; 
input9 = lookup_widget(objet_graphique18, "entry_tel_aj_c") ; 
input10 = lookup_widget(objet_graphique18, "entry_adr_aj_c") ; 
input11 = lookup_widget(objet_graphique18, "entry_email_aj_c") ; 
input12=lookup_widget(objet_graphique18,"dialog_ajouter_client");
// ini ouput //
check= lookup_widget(objet_graphique18, "label_check_ajc") ; 
check_exist =lookup_widget(objet_graphique18, "label_compte_existe") ; 
//from glade to function //
strcpy(S.nom,gtk_entry_get_text(GTK_ENTRY(input1)));
strcpy(S.prenom,gtk_entry_get_text(GTK_ENTRY(input2)));	
S.date_de_naissance.jour= gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input4));
S.date_de_naissance.mois= gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input5));
S.date_de_naissance.annee= gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input6));
strcpy(S.numero_de_telephone,gtk_entry_get_text(GTK_ENTRY(input9)));
strcpy(S.adress,gtk_entry_get_text(GTK_ENTRY(input10)));
strcpy(S.email,gtk_entry_get_text(GTK_ENTRY(input11)));
strcpy(S.cin,gtk_entry_get_text(GTK_ENTRY(input3)));
// a fixer //
if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(input7 ))==TRUE)
{ strcpy(S.gender,gtk_entry_get_text(GTK_ENTRY(input7)));}
else 
strcpy(S.gender,gtk_entry_get_text(GTK_ENTRY(input8)));
/////////// declaration var de verif num de tel ///////////////////
int TEL1=0,TEL2=0,j=0;
/////////////////// verif numero de tel ///////////////////
if (strlen (S.numero_de_telephone) != 8){
TEL1=1;}
for (j=0;j < strlen(S.numero_de_telephone);j++) {
		if (S.numero_de_telephone[j] < '0' || S.numero_de_telephone[j] >'9'){
	TEL2=1;		
break;}}
	if (TEL1==1|| TEL2==1)
{
gtk_label_set_text(GTK_LABEL(check),"verifier les cordonées  !!");
} 
////////// declaration var de  verif mail ////////
int email=1;
char a='@', b='.';


/////////// verif mail //////////////
	if (pos(a,S.email)<1){
		gtk_label_set_text(GTK_LABEL(check),"verifier les cordonées  !!");
}
	if (pos (b,S.email)<3) {
	gtk_label_set_text(GTK_LABEL(check),"verifier les cordonées  !!");
}
	else
      {email=0;}
  

 



//////////// declaration var de verif cin////////
int CIN1=0,CIN2=0,i,CIN3=0;
///////////////////verif CIN///////////////
// 1st verif//
if (strlen (S.cin) != 8){
CIN1=1;
}
// second verif //
for (i=0;i<strlen(S.cin);i++) {
		if (S.cin[i]<'0' || S.cin[i]>'9'){
	CIN2=1;		
break;
} 
	}
//third verif //
if (verif_existance(S.cin)==0)
{ CIN3=1;}
if (CIN3==1)
{
gtk_label_set_text(GTK_LABEL(check_exist),"Ce Client existe deja ! ! ");
}

	if (CIN1==1 || CIN2==1) 
{
gtk_label_set_text(GTK_LABEL(check),"verifier les cordonées  !!");
}
	

///////////////////////////    Remplissage du fichier . bin          /////////////////////////////
	 if (CIN1==0&&CIN2==0&&CIN3==0&&email==0&&TEL1==0&&TEL2==0)
{ 	
	ajouter_list_client(S);
	gtk_widget_destroy(input12);

}


}
////////////////////////////////////////////////// FIN AJOUTER CLIENT ////////////////////////////////////////////////////////////////////


