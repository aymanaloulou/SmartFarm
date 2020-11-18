#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "fct.h"


void
on_cancelbutton1_clicked               (GtkWidget     *button1,
                                        gpointer         user_data)
{
gtk_main_quit();
}


void
on_okbutton1_clicked                   (GtkWidget      *button1,
                                        gpointer         user_data)
{GtkWidget *dialog2;
GtkWidget *dialog1;

char nom[100], prenom[100],username[100], password[100]; 
char role[100];

dialog2=create_dialog2();
dialog1=lookup_widget(button1,"dialog1" );


 GtkWidget *input1,*input2,*input3,*input4,*input5;

input1 = lookup_widget(button1, "entry_nom") ; 
input2 = lookup_widget(button1, "entry_prenom") ; 
input3 = lookup_widget(button1, "entry_username") ; 
input4 = lookup_widget(button1, "entry_password") ; 
input5 = lookup_widget(button1, "entry_role") ;
strcpy(nom,gtk_entry_get_text(GTK_ENTRY(input1)));
strcpy(prenom,gtk_entry_get_text(GTK_ENTRY(input2)));
strcpy(username,gtk_entry_get_text(GTK_ENTRY(input3)));
strcpy(password,gtk_entry_get_text(GTK_ENTRY(input4)));
strcpy(role,gtk_entry_get_text(GTK_ENTRY(input5)));

ajouter(nom,prenom,username,password,role);


gtk_widget_show(dialog2);
gtk_widget_destroy(dialog1);

}
void
on_TEST_clicked                        (GtkWidget       *button2,
                                        gpointer         user_data)
{
GtkWidget *in,*in1,*window1,*dialog2,*test;

char T[10],A[10];
test=lookup_widget(button2,"labeltest");
dialog2=lookup_widget(button2,"dialog2");
in=lookup_widget(button2, "entry_id");
in1=lookup_widget (button2, "entry_pw");
strcpy (T,gtk_entry_get_text(GTK_ENTRY(in)));
strcpy (A,gtk_entry_get_text(GTK_ENTRY(in1)));
if (verif(T,A)==1)
{window1=create_window1();
gtk_widget_destroy(dialog2);
gtk_widget_show(window1);
}
else {

gtk_label_set_text(GTK_LABEL(test),"password or username erroné");


}
}

