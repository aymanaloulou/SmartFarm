#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "capteur.h"
capteur c ; 
capteur c_r;
//capteur x ;
//capteur a;
char id_supp[20];
int choix [2]= {0,0 } ; 
int choix1 [2]= {0,0 } ; 
int choix2 [3] = {0,0,0 } ;
//Debut ajouter : //



void on_ajout_capteur_clicked               (GtkButton       *button,
                                        gpointer         user_data)
	{
		GtkWidget *inp1;
		inp1=create_Ajouter_capteur();
		gtk_widget_show(inp1);

	}





//affichage sur tree //
void
on_button_afficher_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{

GtkWidget *treeview1;


treeview1 = lookup_widget(button,"treeview_capteur");
affiche_capteur(treeview1);
}


//button radio humidite //
void
on_radiobutton4_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
choix[1]=1; 
choix [0]=0;
}

//button radio temperature//
void
on_radiobutton3_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
choix[0]=1 ; 
choix[1]=0 ; 
}


void
on_okbutton_supp_clicked               (GtkButton      *button,
                                        gpointer         user_data)
{
char id[20];
GtkWidget *input1;
GtkWidget *supprimer_capteur;
GtkWidget *dialog = lookup_widget(button,"supprimer_capteur");
	gtk_widget_destroy(dialog);
//supprimer_capteur = lookup_widget(button,"supprimer_capteur");
//gtk_widget_destroy(supprimer_capteur);
input1=lookup_widget(button,"label_sup");

supp_capteur(c.id);

}


//bouton recherche 
void
on_recherche_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *treeview1, *id_input;
	char id_rech[20];


	treeview1 = lookup_widget (button, "treeview_capteur");
	id_input = lookup_widget (button, "entry_rech_capteur");

	strcpy (id_rech,gtk_entry_get_text(GTK_ENTRY(id_input)));
	recherche_capteur (id_rech,treeview1);
}
/////////////////////////////////////
void
on_okbutton_aj_capteur_clicked         (GtkButton       *button,
                                        gpointer         user_data)
	{ 
capteur a;
char text1[20]="" ; 
 
GtkWidget *inp2,*inp3,*inp6,*inp7,*inDe;
//Destroy Dialog//
//
inDe=lookup_widget(button,"Ajouter_capteur");
//

inp2=lookup_widget(button,"entry_id");
inp3=lookup_widget(button,"entry_marque");

inp6=lookup_widget(button,"calendar_capteur");
inp7=lookup_widget(button,"entry_valeur");

strcpy(a.id,gtk_entry_get_text(GTK_ENTRY(inp2)));
strcpy(a.marque,gtk_entry_get_text(GTK_ENTRY(inp3)));

strcpy(a.valeur,gtk_entry_get_text(GTK_ENTRY(inp7)));

 type_capteur ( choix, text1  ) ;
//choix[0]=0 ;
//choix[1]=0 ; 
strcpy(a.type,text1) ;
strcpy(a.etat,"bonne");
strcpy(a.cause,"--");
gtk_calendar_get_date (inp6,&a.date.annee,&a.date.mois,&a.date.jour);
a.date.mois ++ ; 

if (ajoutCapteur(a,button))
{gtk_widget_destroy(inDe);
}}
//Fin AJouter //
void
on_treeview_capteur_row_activated      (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter   iter;
char* id;
char* marque;
char* valeur;
char* type;
char* etat;
char* cause;
char *date1 ;


GtkTreeModel* model=gtk_tree_view_get_model(treeview)  ;
  if (gtk_tree_model_get_iter(model, &iter, path))
  
{
   gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0, &id,1, &type,2, &marque,3, &valeur,4, &date1,5,&etat,6,&cause, -1 ) ;
strcpy(c.id,id);
strcpy(c.marque,marque);
strcpy(c.valeur,valeur);
sscanf (date1,"%d/%d/%d",&c.date.jour,&c.date.mois,&c.date.annee);
strcpy(c.type,type);
strcpy(c.etat,etat);
strcpy(c.cause,cause);
}
}
/*
void
on_treeview_capteur_row_activated      (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)

{
gchar *str_data0;
gchar *str_data1;
gchar *str_data2;
gchar *str_data3;
gchar *etat;
gchar *cause;
char *date4 ;

GtkTreeIter   iter;
GtkTreeModel* model=gtk_tree_view_get_model(treeview)  ;
  if (gtk_tree_model_get_iter(model, &iter, path))
  {

   gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0, &str_data0,1, &str_data1,2, &str_data2,3, &str_data3,4, &date4,5,&etat,6,&cause, -1 ) ;
strcpy(c.id,str_data0);
strcpy(c.marque,str_data2);
strcpy(c.valeur,str_data3);
sscanf (date4,"%d/%d/%d",&c.date.jour,&c.date.mois,&c.date.annee);
strcpy(c.type,str_data1);
strcpy(c.etat,etat);
strcpy(c.cause,cause);


} }*/
void 
on_boutton_sup_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *dialog = create_supprimer_capteur();
	gtk_widget_show(dialog);
		supp_capteur(c.id);
		
	}
 
void
on_okbutton_modif_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
 
char text[20] ; 

GtkWidget *inp2,*inp3,*inp4,*inp5,*inp6,*inp7;
 GtkWidget *modifier_capteur;

//dialogue modif //
modifier_capteur=lookup_widget(button,"modifier_capteur");
//
supp_capteur(c.id);
inp2=lookup_widget(button,"entry_id");
inp3=lookup_widget(button,"entry_marque");

inp7=lookup_widget(button,"entry_valeur");
inp4=lookup_widget(button,"jour");

inp5=lookup_widget(button,"mois");

inp6=lookup_widget(button,"annee");



strcpy(c.id,gtk_entry_get_text(GTK_ENTRY(inp2)));
strcpy(c.marque,gtk_entry_get_text(GTK_ENTRY(inp3)));

strcpy(c.valeur,gtk_entry_get_text(GTK_ENTRY(inp7)));
 type_capteur ( choix, text ) ;
//choix[0]=0 ;
//choix[1]=0 ; 
strcpy(c.type,text) ;
c.date.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(inp4));
c.date.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(inp5));
c.date.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(inp6));

if (ajoutCapteur(c,button)){
gtk_widget_destroy(modifier_capteur);
}}
////////////////////////////////////////////////////////////////////////////


void
on_button_modif_clicked                (GtkButton       *button,
                                        gpointer         user_data)

{

GtkWidget *dialog = create_modifier_capteur();
GtkWidget *label1 = lookup_widget (button,"label_msg");
GtkWidget *inp2,*inp3,*inp7,*inp10,*inp11;
GtkSpinButton *inp4,*inp5,*inp6 ;
char text[20]="" ;
if (strlen (c.id) != 0){
gtk_widget_show(dialog);
inp2=lookup_widget(dialog,"entry_id");
inp3=lookup_widget(dialog,"entry_marque");
inp7=lookup_widget(dialog,"entry_valeur");
inp10=lookup_widget(dialog,"radiobutton3");
inp11=lookup_widget(dialog,"radiobutton4");

inp4=lookup_widget(dialog,"jour");

inp5=lookup_widget(dialog,"mois");

inp6=lookup_widget(dialog,"annee");

gtk_entry_set_text (GTK_ENTRY (inp2), _(c.id));
gtk_entry_set_text (GTK_ENTRY (inp3), _(c.marque));
gtk_entry_set_text (GTK_ENTRY (inp7), _(c.valeur));
gtk_spin_button_set_value(inp4,c.date.jour);
gtk_spin_button_set_value(inp5,c.date.mois);
gtk_spin_button_set_value(inp6,c.date.annee);

type_capteur (choix, text ) ;//radio fct
//choix[0]=0 ;
//choix[1]=0 ;

if (choix[0]==0)
{ gtk_toggle_button_set_active(inp10,TRUE);}
else {
gtk_toggle_button_set_active (inp11,TRUE);}
strcpy(c.type,text) ;
gtk_widget_show(dialog);
gtk_label_set_text(GTK_LABEL(label1),"");
}

else{
gtk_label_set_text(GTK_LABEL(label1),"Double click sur un capteur");
}
}


void
on_bouton_type_affiche_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{

GtkWidget *combobox ; 

GtkWidget *treeview1,*a;	
 char t[50]; 
  
  
treeview1 = lookup_widget(button,"treeview_capteur");
combobox=lookup_widget(button,"comboboxentry1");
strcpy(t,gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox))) ;

affiche_type(treeview1,t);
}


///////////////////////////////////////////////////


void
on_button_alarmante_clicked            (GtkButton       *button,
                                       gpointer         user_data)
{

GtkWidget *treeview1;//,*min_input,*max_input;


treeview1 = lookup_widget(button,"treeview_alarmante");

//char min_rech[20];
//char max_rech[20];



 
	//min_input = lookup_widget (button, "min");
	//max_input = lookup_widget (button, "max");

	//strcpy (min_rech,gtk_entry_get_text(GTK_ENTRY(min_input)));
        //strcpy (max_rech,gtk_entry_get_text(GTK_ENTRY(max_input)));
	capteur_alarmante( treeview1);
}

/////////////////////////

/*
void
on_affichage_defect_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{

}
*/

void
on_button_fiche_capteur_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *inp1;
 GtkButton *combobox1 ;

		inp1=create_dialog_fiche_capteur();
combobox1=lookup_widget(inp1,"comboboxentry_type");
set_combo_fiche(combobox1) ;
		gtk_widget_show(inp1);

}



void
on_okbutton1_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *fiche_capteur;
fiche_capteur=lookup_widget(button,"dialog_fiche_capteur");
gtk_widget_destroy(fiche_capteur);
}


void
on_checkbutton3_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
//if (gtk_toggle_button_get_active(togglebutton))
choix1 [0]==1;
}


void
on_checkbutton4_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
//if (gtk_toggle_button_get_active(togglebutton))
choix1 [1]==1 ;
}



void
on_mise_jour_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
 char i[50]; 
GtkWidget *treeview2;
//GtkButton *combobox1 ;
treeview2 = lookup_widget(button,"treeview_suivi");
//combobox1=lookup_widget(button,"comboboxentry_type");
//strcpy(i,gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox1))) ;

affiche_suivi(treeview2,i);
}




void
on_checkbutton_panne_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{GtkWidget *i1,*i2,*i3,*i4,*i5;
i1=lookup_widget(togglebutton,"detruit_radio");
i2=lookup_widget(togglebutton,"radio_mauvaise");
i3=lookup_widget(togglebutton,"radio_autres");
i4=lookup_widget(togglebutton,"entry_autre_cause");
i5=lookup_widget(togglebutton,"label_cause_capteur");
if(gtk_toggle_button_get_active(togglebutton))
{
gtk_widget_show(i1);
gtk_widget_show(i2);
gtk_widget_show(i3);
gtk_widget_show(i4);
gtk_widget_show(i5);
}
else
{
gtk_widget_hide(i1);
gtk_widget_hide(i2);
gtk_widget_hide(i3);
gtk_widget_hide(i4);
gtk_widget_hide(i5);
}

}

void
on_radio_autres_clicked                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{GtkWidget *i4;
i4=lookup_widget(togglebutton,"entry_autre_cause");
if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
gtk_widget_set_sensitive(i4,TRUE);
else
gtk_widget_set_sensitive(i4,FALSE);

}


void
on_button12_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_treeview_suivi_row_activated        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter   iter;
char* id;
char* marque;
char* valeur;
char* type;
char* etat;
char* cause;
char *date1 ;


GtkTreeModel* model=gtk_tree_view_get_model(treeview)  ;
  if (gtk_tree_model_get_iter(model, &iter, path))
  
{
   gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0, &id,1, &type,2, &marque,3, &valeur,4, &date1,5,&etat,6,&cause, -1 ) ;
strcpy(c_r.id,id);
strcpy(c_r.marque,marque);
strcpy(c_r.valeur,valeur);
sscanf (date1,"%d/%d/%d",&c_r.date.jour,&c_r.date.mois,&c_r.date.annee);
strcpy(c_r.type,type);
strcpy(c_r.etat,etat);
strcpy(c_r.cause,cause);
}
}
void
on_button_capteur_reparee_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
supp_capteur(c_r.id);
strcpy(c_r.etat,"bonne");
strcpy(c_r.cause,"--");
ajoutCapteur(c_r,button);
}
void
on_enregistrer_panne_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *i1,*i2,*i3,*i4,*togglebutton;
int i ;
supp_capteur(c.id) ;

i1=lookup_widget(button,"detruit_radio");
i2=lookup_widget(button,"radio_mauvaise");
i3=lookup_widget(button,"radio_autres");
i4=lookup_widget(button,"entry_autre_cause");
togglebutton=lookup_widget(button,"checkbutton_en_panne");
GSList *List;

List= gtk_radio_button_get_group (GTK_RADIO_BUTTON (i1));
for (i=0;i<3;i++)
{
        if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(List->data)))
{
            strcpy(c.cause,gtk_button_get_label(GTK_BUTTON(List->data)));
   
}
       else
if (i!=2)
            List = g_slist_next(List);
           

}
if (gtk_toggle_button_get_active(i3))
strcpy(c.cause,gtk_entry_get_text(GTK_ENTRY(i4)));
strcpy(c.etat,"en panne");
ajoutCapteur(c,button);

}


void
on_affichage_defect_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
char marq [50] ; 
GtkWidget *dialog = create_max_marque_def();
GtkWidget *inp2 ; 
inp2=lookup_widget(dialog,"entry_def");
marque_defect (marq);
gtk_entry_set_text (GTK_ENTRY (inp2), _(marq));
gtk_widget_show(dialog);

}


void
on_button_alarm_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *dialog = create_window_alarmante();
gtk_widget_show(dialog);
}

