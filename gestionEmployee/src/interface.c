/*
 * DO NOT EDIT THIS FILE - it is generated by Glade.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

#define GLADE_HOOKUP_OBJECT(component,widget,name) \
  g_object_set_data_full (G_OBJECT (component), name, \
    gtk_widget_ref (widget), (GDestroyNotify) gtk_widget_unref)

#define GLADE_HOOKUP_OBJECT_NO_REF(component,widget,name) \
  g_object_set_data (G_OBJECT (component), name, widget)

GtkWidget*
create_window1 (void)
{
  GtkWidget *window1;
  GtkWidget *notebook1;
  GtkWidget *fixed1;
  GtkWidget *entry16;
  GtkWidget *image10;
  GtkWidget *scrolledwindow5;
  GtkWidget *treeview5;
  GtkWidget *button7;
  GtkWidget *alignment7;
  GtkWidget *hbox7;
  GtkWidget *image11;
  GtkWidget *label37;
  GtkWidget *button8;
  GtkWidget *alignment8;
  GtkWidget *hbox8;
  GtkWidget *image12;
  GtkWidget *label38;
  GtkWidget *button9;
  GtkWidget *alignment9;
  GtkWidget *hbox9;
  GtkWidget *image13;
  GtkWidget *label39;
  GtkWidget *label36;
  GtkWidget *label1;
  GtkWidget *fixed5;
  GtkWidget *label66;
  GtkWidget *scrolledwindow6;
  GtkWidget *treeview6;
  GtkWidget *label67;
  GtkWidget *scrolledwindow7;
  GtkWidget *treeview7;
  GtkWidget *button14;
  GtkWidget *alignment14;
  GtkWidget *hbox14;
  GtkWidget *image18;
  GtkWidget *label68;
  GtkWidget *button15;
  GtkWidget *alignment15;
  GtkWidget *hbox15;
  GtkWidget *image19;
  GtkWidget *label69;
  GtkWidget *label2;

  window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_size_request (window1, 1024, 700);
  gtk_window_set_title (GTK_WINDOW (window1), _("window1"));

  notebook1 = gtk_notebook_new ();
  gtk_widget_show (notebook1);
  gtk_container_add (GTK_CONTAINER (window1), notebook1);
  gtk_widget_set_size_request (notebook1, 1024, 700);

  fixed1 = gtk_fixed_new ();
  gtk_widget_show (fixed1);
  gtk_container_add (GTK_CONTAINER (notebook1), fixed1);

  entry16 = gtk_entry_new ();
  gtk_widget_show (entry16);
  gtk_fixed_put (GTK_FIXED (fixed1), entry16, 145, 79);
  gtk_widget_set_size_request (entry16, 160, 27);
  gtk_entry_set_text (GTK_ENTRY (entry16), _("Recherche"));
  gtk_entry_set_invisible_char (GTK_ENTRY (entry16), 8226);

  image10 = gtk_image_new_from_stock ("gtk-find", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image10);
  gtk_fixed_put (GTK_FIXED (fixed1), image10, 120, 80);
  gtk_widget_set_size_request (image10, 21, 21);

  scrolledwindow5 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow5);
  gtk_fixed_put (GTK_FIXED (fixed1), scrolledwindow5, 120, 116);
  gtk_widget_set_size_request (scrolledwindow5, 784, 424);

  treeview5 = gtk_tree_view_new ();
  gtk_widget_show (treeview5);
  gtk_container_add (GTK_CONTAINER (scrolledwindow5), treeview5);

  button7 = gtk_button_new ();
  gtk_widget_show (button7);
  gtk_fixed_put (GTK_FIXED (fixed1), button7, 580, 550);
  gtk_widget_set_size_request (button7, 100, 30);
  gtk_container_set_border_width (GTK_CONTAINER (button7), 1);

  alignment7 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment7);
  gtk_container_add (GTK_CONTAINER (button7), alignment7);
  gtk_widget_set_size_request (alignment7, 75, -1);

  hbox7 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox7);
  gtk_container_add (GTK_CONTAINER (alignment7), hbox7);

  image11 = gtk_image_new_from_stock ("gtk-add", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image11);
  gtk_box_pack_start (GTK_BOX (hbox7), image11, FALSE, FALSE, 0);

  label37 = gtk_label_new_with_mnemonic (_("Ajouter"));
  gtk_widget_show (label37);
  gtk_box_pack_start (GTK_BOX (hbox7), label37, FALSE, FALSE, 0);

  button8 = gtk_button_new ();
  gtk_widget_show (button8);
  gtk_fixed_put (GTK_FIXED (fixed1), button8, 684, 550);
  gtk_widget_set_size_request (button8, 100, 30);
  gtk_container_set_border_width (GTK_CONTAINER (button8), 1);

  alignment8 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment8);
  gtk_container_add (GTK_CONTAINER (button8), alignment8);

  hbox8 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox8);
  gtk_container_add (GTK_CONTAINER (alignment8), hbox8);

  image12 = gtk_image_new_from_stock ("gtk-edit", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image12);
  gtk_box_pack_start (GTK_BOX (hbox8), image12, FALSE, FALSE, 0);

  label38 = gtk_label_new_with_mnemonic (_("Modifier"));
  gtk_widget_show (label38);
  gtk_box_pack_start (GTK_BOX (hbox8), label38, FALSE, FALSE, 0);

  button9 = gtk_button_new ();
  gtk_widget_show (button9);
  gtk_fixed_put (GTK_FIXED (fixed1), button9, 791, 550);
  gtk_widget_set_size_request (button9, 104, 30);

  alignment9 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment9);
  gtk_container_add (GTK_CONTAINER (button9), alignment9);
  gtk_widget_set_size_request (alignment9, 100, 30);

  hbox9 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox9);
  gtk_container_add (GTK_CONTAINER (alignment9), hbox9);

  image13 = gtk_image_new_from_stock ("gtk-delete", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image13);
  gtk_box_pack_start (GTK_BOX (hbox9), image13, FALSE, FALSE, 0);

  label39 = gtk_label_new_with_mnemonic (_("Supprimer"));
  gtk_widget_show (label39);
  gtk_box_pack_start (GTK_BOX (hbox9), label39, FALSE, FALSE, 0);

  label36 = gtk_label_new (_("Liste des employees :"));
  gtk_widget_show (label36);
  gtk_fixed_put (GTK_FIXED (fixed1), label36, 120, 56);
  gtk_widget_set_size_request (label36, 150, 19);

  label1 = gtk_label_new (_("Ajouter un employee"));
  gtk_widget_show (label1);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (notebook1), gtk_notebook_get_nth_page (GTK_NOTEBOOK (notebook1), 0), label1);

  fixed5 = gtk_fixed_new ();
  gtk_widget_show (fixed5);
  gtk_container_add (GTK_CONTAINER (notebook1), fixed5);

  label66 = gtk_label_new (_("Liste des demandes :"));
  gtk_widget_show (label66);
  gtk_fixed_put (GTK_FIXED (fixed5), label66, 120, 40);
  gtk_widget_set_size_request (label66, 152, 16);

  scrolledwindow6 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow6);
  gtk_fixed_put (GTK_FIXED (fixed5), scrolledwindow6, 128, 72);
  gtk_widget_set_size_request (scrolledwindow6, 760, 312);

  treeview6 = gtk_tree_view_new ();
  gtk_widget_show (treeview6);
  gtk_container_add (GTK_CONTAINER (scrolledwindow6), treeview6);

  label67 = gtk_label_new (_("Cong\303\251s approuv\303\251s :"));
  gtk_widget_show (label67);
  gtk_fixed_put (GTK_FIXED (fixed5), label67, 128, 432);
  gtk_widget_set_size_request (label67, 136, 16);

  scrolledwindow7 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow7);
  gtk_fixed_put (GTK_FIXED (fixed5), scrolledwindow7, 128, 464);
  gtk_widget_set_size_request (scrolledwindow7, 776, 168);

  treeview7 = gtk_tree_view_new ();
  gtk_widget_show (treeview7);
  gtk_container_add (GTK_CONTAINER (scrolledwindow7), treeview7);

  button14 = gtk_button_new ();
  gtk_widget_show (button14);
  gtk_fixed_put (GTK_FIXED (fixed5), button14, 672, 392);
  gtk_widget_set_size_request (button14, 100, 29);

  alignment14 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment14);
  gtk_container_add (GTK_CONTAINER (button14), alignment14);

  hbox14 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox14);
  gtk_container_add (GTK_CONTAINER (alignment14), hbox14);

  image18 = gtk_image_new_from_stock ("gtk-apply", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image18);
  gtk_box_pack_start (GTK_BOX (hbox14), image18, FALSE, FALSE, 0);

  label68 = gtk_label_new_with_mnemonic (_("Valider"));
  gtk_widget_show (label68);
  gtk_box_pack_start (GTK_BOX (hbox14), label68, FALSE, FALSE, 0);

  button15 = gtk_button_new ();
  gtk_fixed_put (GTK_FIXED (fixed5), button15, 784, 392);
  gtk_widget_set_size_request (button15, 100, 29);

  alignment15 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment15);
  gtk_container_add (GTK_CONTAINER (button15), alignment15);

  hbox15 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox15);
  gtk_container_add (GTK_CONTAINER (alignment15), hbox15);

  image19 = gtk_image_new_from_stock ("gtk-delete", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image19);
  gtk_box_pack_start (GTK_BOX (hbox15), image19, FALSE, FALSE, 0);

  label69 = gtk_label_new_with_mnemonic (_("R\303\251fuser"));
  gtk_widget_show (label69);
  gtk_box_pack_start (GTK_BOX (hbox15), label69, FALSE, FALSE, 0);

  label2 = gtk_label_new (_("Approuver les cong\303\251s"));
  gtk_widget_show (label2);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (notebook1), gtk_notebook_get_nth_page (GTK_NOTEBOOK (notebook1), 1), label2);

  g_signal_connect ((gpointer) button7, "clicked",
                    G_CALLBACK (on_button_ajouter_ouvrier_clicked),
                    NULL);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (window1, window1, "window1");
  GLADE_HOOKUP_OBJECT (window1, notebook1, "notebook1");
  GLADE_HOOKUP_OBJECT (window1, fixed1, "fixed1");
  GLADE_HOOKUP_OBJECT (window1, entry16, "entry16");
  GLADE_HOOKUP_OBJECT (window1, image10, "image10");
  GLADE_HOOKUP_OBJECT (window1, scrolledwindow5, "scrolledwindow5");
  GLADE_HOOKUP_OBJECT (window1, treeview5, "treeview5");
  GLADE_HOOKUP_OBJECT (window1, button7, "button7");
  GLADE_HOOKUP_OBJECT (window1, alignment7, "alignment7");
  GLADE_HOOKUP_OBJECT (window1, hbox7, "hbox7");
  GLADE_HOOKUP_OBJECT (window1, image11, "image11");
  GLADE_HOOKUP_OBJECT (window1, label37, "label37");
  GLADE_HOOKUP_OBJECT (window1, button8, "button8");
  GLADE_HOOKUP_OBJECT (window1, alignment8, "alignment8");
  GLADE_HOOKUP_OBJECT (window1, hbox8, "hbox8");
  GLADE_HOOKUP_OBJECT (window1, image12, "image12");
  GLADE_HOOKUP_OBJECT (window1, label38, "label38");
  GLADE_HOOKUP_OBJECT (window1, button9, "button9");
  GLADE_HOOKUP_OBJECT (window1, alignment9, "alignment9");
  GLADE_HOOKUP_OBJECT (window1, hbox9, "hbox9");
  GLADE_HOOKUP_OBJECT (window1, image13, "image13");
  GLADE_HOOKUP_OBJECT (window1, label39, "label39");
  GLADE_HOOKUP_OBJECT (window1, label36, "label36");
  GLADE_HOOKUP_OBJECT (window1, label1, "label1");
  GLADE_HOOKUP_OBJECT (window1, fixed5, "fixed5");
  GLADE_HOOKUP_OBJECT (window1, label66, "label66");
  GLADE_HOOKUP_OBJECT (window1, scrolledwindow6, "scrolledwindow6");
  GLADE_HOOKUP_OBJECT (window1, treeview6, "treeview6");
  GLADE_HOOKUP_OBJECT (window1, label67, "label67");
  GLADE_HOOKUP_OBJECT (window1, scrolledwindow7, "scrolledwindow7");
  GLADE_HOOKUP_OBJECT (window1, treeview7, "treeview7");
  GLADE_HOOKUP_OBJECT (window1, button14, "button14");
  GLADE_HOOKUP_OBJECT (window1, alignment14, "alignment14");
  GLADE_HOOKUP_OBJECT (window1, hbox14, "hbox14");
  GLADE_HOOKUP_OBJECT (window1, image18, "image18");
  GLADE_HOOKUP_OBJECT (window1, label68, "label68");
  GLADE_HOOKUP_OBJECT (window1, button15, "button15");
  GLADE_HOOKUP_OBJECT (window1, alignment15, "alignment15");
  GLADE_HOOKUP_OBJECT (window1, hbox15, "hbox15");
  GLADE_HOOKUP_OBJECT (window1, image19, "image19");
  GLADE_HOOKUP_OBJECT (window1, label69, "label69");
  GLADE_HOOKUP_OBJECT (window1, label2, "label2");

  return window1;
}

GtkWidget*
create_window2 (void)
{
  GtkWidget *window2;
  GtkWidget *fixed6;
  GtkWidget *entry17;
  GtkWidget *entry18;
  GtkWidget *entry19;
  GtkWidget *label40;
  GtkWidget *label41;
  GtkWidget *label42;
  GtkWidget *label43;
  GtkWidget *comboboxentry1;
  GtkWidget *comboboxentry2;
  GtkWidget *label44;
  GtkWidget *radiobutton1;
  GSList *radiobutton1_group = NULL;
  GtkWidget *comboboxentry3;
  GtkWidget *label45;
  GtkWidget *label46;
  GtkWidget *label47;
  GtkWidget *entry20;
  GtkWidget *comboboxentry4;
  GtkWidget *entry21;
  GtkWidget *label48;
  GtkWidget *label49;
  GtkWidget *button10;
  GtkWidget *alignment10;
  GtkWidget *hbox10;
  GtkWidget *image14;
  GtkWidget *label50;
  GtkWidget *button11;
  GtkWidget *alignment11;
  GtkWidget *hbox11;
  GtkWidget *image15;
  GtkWidget *label51;
  GtkWidget *entry22;
  GtkWidget *entry23;
  GtkWidget *radiobutton2;
  GSList *radiobutton2_group = NULL;
  GtkWidget *label52;

  window2 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_size_request (window2, 500, 550);
  gtk_window_set_title (GTK_WINDOW (window2), _("window3"));

  fixed6 = gtk_fixed_new ();
  gtk_widget_show (fixed6);
  gtk_container_add (GTK_CONTAINER (window2), fixed6);

  entry17 = gtk_entry_new ();
  gtk_widget_show (entry17);
  gtk_fixed_put (GTK_FIXED (fixed6), entry17, 200, 48);
  gtk_widget_set_size_request (entry17, 280, 27);
  gtk_entry_set_invisible_char (GTK_ENTRY (entry17), 8226);

  entry18 = gtk_entry_new ();
  gtk_widget_show (entry18);
  gtk_fixed_put (GTK_FIXED (fixed6), entry18, 200, 84);
  gtk_widget_set_size_request (entry18, 280, 28);
  gtk_entry_set_invisible_char (GTK_ENTRY (entry18), 8226);

  entry19 = gtk_entry_new ();
  gtk_widget_show (entry19);
  gtk_fixed_put (GTK_FIXED (fixed6), entry19, 200, 120);
  gtk_widget_set_size_request (entry19, 280, 28);
  gtk_entry_set_invisible_char (GTK_ENTRY (entry19), 8226);

  label40 = gtk_label_new (_("Nom :"));
  gtk_widget_show (label40);
  gtk_fixed_put (GTK_FIXED (fixed6), label40, 144, 56);
  gtk_widget_set_size_request (label40, 41, 17);

  label41 = gtk_label_new (_("Pr\303\251nom :"));
  gtk_widget_show (label41);
  gtk_fixed_put (GTK_FIXED (fixed6), label41, 120, 96);
  gtk_widget_set_size_request (label41, 72, 16);

  label42 = gtk_label_new (_("CIN :"));
  gtk_widget_show (label42);
  gtk_fixed_put (GTK_FIXED (fixed6), label42, 144, 128);
  gtk_widget_set_size_request (label42, 49, 17);

  label43 = gtk_label_new (_("Date de naissance :"));
  gtk_widget_show (label43);
  gtk_fixed_put (GTK_FIXED (fixed6), label43, 48, 168);
  gtk_widget_set_size_request (label43, 145, 16);

  comboboxentry1 = gtk_combo_box_entry_new_text ();
  gtk_widget_show (comboboxentry1);
  gtk_fixed_put (GTK_FIXED (fixed6), comboboxentry1, 200, 160);
  gtk_widget_set_size_request (comboboxentry1, 60, 29);

  comboboxentry2 = gtk_combo_box_entry_new_text ();
  gtk_widget_show (comboboxentry2);
  gtk_fixed_put (GTK_FIXED (fixed6), comboboxentry2, 272, 160);
  gtk_widget_set_size_request (comboboxentry2, 60, 29);

  label44 = gtk_label_new (_("Genre :"));
  gtk_widget_show (label44);
  gtk_fixed_put (GTK_FIXED (fixed6), label44, 136, 208);
  gtk_widget_set_size_request (label44, 49, 17);

  radiobutton1 = gtk_radio_button_new_with_mnemonic (NULL, _("Male"));
  gtk_widget_show (radiobutton1);
  gtk_fixed_put (GTK_FIXED (fixed6), radiobutton1, 200, 204);
  gtk_widget_set_size_request (radiobutton1, 116, 24);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton1), radiobutton1_group);
  radiobutton1_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton1));

  comboboxentry3 = gtk_combo_box_entry_new_text ();
  gtk_widget_show (comboboxentry3);
  gtk_fixed_put (GTK_FIXED (fixed6), comboboxentry3, 200, 235);
  gtk_widget_set_size_request (comboboxentry3, 189, 29);
  gtk_combo_box_append_text (GTK_COMBO_BOX (comboboxentry3), _("C\303\251l\303\251bataire"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (comboboxentry3), _("Mari\303\251"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (comboboxentry3), _("Divorc\303\251"));

  label45 = gtk_label_new (_("Etat civil :"));
  gtk_widget_show (label45);
  gtk_fixed_put (GTK_FIXED (fixed6), label45, 117, 246);
  gtk_widget_set_size_request (label45, 72, 16);

  label46 = gtk_label_new (_("Num\303\251ro de t\303\251l\303\251phone :"));
  gtk_widget_show (label46);
  gtk_fixed_put (GTK_FIXED (fixed6), label46, 24, 282);
  gtk_widget_set_size_request (label46, 168, 16);

  label47 = gtk_label_new (_("Adresse :"));
  gtk_widget_show (label47);
  gtk_fixed_put (GTK_FIXED (fixed6), label47, 112, 312);
  gtk_widget_set_size_request (label47, 81, 16);

  entry20 = gtk_entry_new ();
  gtk_widget_show (entry20);
  gtk_fixed_put (GTK_FIXED (fixed6), entry20, 200, 312);
  gtk_widget_set_size_request (entry20, 280, 64);
  gtk_entry_set_invisible_char (GTK_ENTRY (entry20), 8226);

  comboboxentry4 = gtk_combo_box_entry_new_text ();
  gtk_widget_show (comboboxentry4);
  gtk_fixed_put (GTK_FIXED (fixed6), comboboxentry4, 344, 160);
  gtk_widget_set_size_request (comboboxentry4, 90, 29);

  entry21 = gtk_entry_new ();
  gtk_widget_show (entry21);
  gtk_fixed_put (GTK_FIXED (fixed6), entry21, 201, 271);
  gtk_widget_set_size_request (entry21, 280, 28);
  gtk_entry_set_invisible_char (GTK_ENTRY (entry21), 8226);

  label48 = gtk_label_new (_("Email :"));
  gtk_widget_show (label48);
  gtk_fixed_put (GTK_FIXED (fixed6), label48, 134, 394);
  gtk_widget_set_size_request (label48, 56, 16);

  label49 = gtk_label_new (_("Secteur :"));
  gtk_widget_show (label49);
  gtk_fixed_put (GTK_FIXED (fixed6), label49, 128, 432);
  gtk_widget_set_size_request (label49, 56, 16);

  button10 = gtk_button_new ();
  gtk_widget_show (button10);
  gtk_fixed_put (GTK_FIXED (fixed6), button10, 384, 504);
  gtk_widget_set_size_request (button10, 100, 29);

  alignment10 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment10);
  gtk_container_add (GTK_CONTAINER (button10), alignment10);

  hbox10 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox10);
  gtk_container_add (GTK_CONTAINER (alignment10), hbox10);

  image14 = gtk_image_new_from_stock ("gtk-cancel", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image14);
  gtk_box_pack_start (GTK_BOX (hbox10), image14, FALSE, FALSE, 0);

  label50 = gtk_label_new_with_mnemonic (_("Annuler"));
  gtk_widget_show (label50);
  gtk_box_pack_start (GTK_BOX (hbox10), label50, FALSE, FALSE, 0);

  button11 = gtk_button_new ();
  gtk_widget_show (button11);
  gtk_fixed_put (GTK_FIXED (fixed6), button11, 280, 504);
  gtk_widget_set_size_request (button11, 100, 29);

  alignment11 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment11);
  gtk_container_add (GTK_CONTAINER (button11), alignment11);

  hbox11 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox11);
  gtk_container_add (GTK_CONTAINER (alignment11), hbox11);

  image15 = gtk_image_new_from_stock ("gtk-apply", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image15);
  gtk_box_pack_start (GTK_BOX (hbox11), image15, FALSE, FALSE, 0);

  label51 = gtk_label_new_with_mnemonic (_("Confirmer"));
  gtk_widget_show (label51);
  gtk_box_pack_start (GTK_BOX (hbox11), label51, FALSE, FALSE, 0);

  entry22 = gtk_entry_new ();
  gtk_widget_show (entry22);
  gtk_fixed_put (GTK_FIXED (fixed6), entry22, 200, 421);
  gtk_widget_set_size_request (entry22, 280, 28);
  gtk_entry_set_invisible_char (GTK_ENTRY (entry22), 8226);

  entry23 = gtk_entry_new ();
  gtk_widget_show (entry23);
  gtk_fixed_put (GTK_FIXED (fixed6), entry23, 200, 384);
  gtk_widget_set_size_request (entry23, 280, 28);
  gtk_entry_set_invisible_char (GTK_ENTRY (entry23), 8226);

  radiobutton2 = gtk_radio_button_new_with_mnemonic (NULL, _("Femelle"));
  gtk_widget_show (radiobutton2);
  gtk_fixed_put (GTK_FIXED (fixed6), radiobutton2, 322, 205);
  gtk_widget_set_size_request (radiobutton2, 115, 24);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton2), radiobutton2_group);
  radiobutton2_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton2));

  label52 = gtk_label_new (_("Modifier un employee :"));
  gtk_widget_show (label52);
  gtk_fixed_put (GTK_FIXED (fixed6), label52, 8, 8);
  gtk_widget_set_size_request (label52, 160, 24);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (window2, window2, "window2");
  GLADE_HOOKUP_OBJECT (window2, fixed6, "fixed6");
  GLADE_HOOKUP_OBJECT (window2, entry17, "entry17");
  GLADE_HOOKUP_OBJECT (window2, entry18, "entry18");
  GLADE_HOOKUP_OBJECT (window2, entry19, "entry19");
  GLADE_HOOKUP_OBJECT (window2, label40, "label40");
  GLADE_HOOKUP_OBJECT (window2, label41, "label41");
  GLADE_HOOKUP_OBJECT (window2, label42, "label42");
  GLADE_HOOKUP_OBJECT (window2, label43, "label43");
  GLADE_HOOKUP_OBJECT (window2, comboboxentry1, "comboboxentry1");
  GLADE_HOOKUP_OBJECT (window2, comboboxentry2, "comboboxentry2");
  GLADE_HOOKUP_OBJECT (window2, label44, "label44");
  GLADE_HOOKUP_OBJECT (window2, radiobutton1, "radiobutton1");
  GLADE_HOOKUP_OBJECT (window2, comboboxentry3, "comboboxentry3");
  GLADE_HOOKUP_OBJECT (window2, label45, "label45");
  GLADE_HOOKUP_OBJECT (window2, label46, "label46");
  GLADE_HOOKUP_OBJECT (window2, label47, "label47");
  GLADE_HOOKUP_OBJECT (window2, entry20, "entry20");
  GLADE_HOOKUP_OBJECT (window2, comboboxentry4, "comboboxentry4");
  GLADE_HOOKUP_OBJECT (window2, entry21, "entry21");
  GLADE_HOOKUP_OBJECT (window2, label48, "label48");
  GLADE_HOOKUP_OBJECT (window2, label49, "label49");
  GLADE_HOOKUP_OBJECT (window2, button10, "button10");
  GLADE_HOOKUP_OBJECT (window2, alignment10, "alignment10");
  GLADE_HOOKUP_OBJECT (window2, hbox10, "hbox10");
  GLADE_HOOKUP_OBJECT (window2, image14, "image14");
  GLADE_HOOKUP_OBJECT (window2, label50, "label50");
  GLADE_HOOKUP_OBJECT (window2, button11, "button11");
  GLADE_HOOKUP_OBJECT (window2, alignment11, "alignment11");
  GLADE_HOOKUP_OBJECT (window2, hbox11, "hbox11");
  GLADE_HOOKUP_OBJECT (window2, image15, "image15");
  GLADE_HOOKUP_OBJECT (window2, label51, "label51");
  GLADE_HOOKUP_OBJECT (window2, entry22, "entry22");
  GLADE_HOOKUP_OBJECT (window2, entry23, "entry23");
  GLADE_HOOKUP_OBJECT (window2, radiobutton2, "radiobutton2");
  GLADE_HOOKUP_OBJECT (window2, label52, "label52");

  return window2;
}

GtkWidget*
create_window3 (void)
{
  GtkWidget *window3;
  GtkWidget *fixed7;
  GtkWidget *entry24;
  GtkWidget *entry25;
  GtkWidget *entry26;
  GtkWidget *label54;
  GtkWidget *label55;
  GtkWidget *label56;
  GtkWidget *label57;
  GtkWidget *comboboxentry5;
  GtkWidget *comboboxentry6;
  GtkWidget *label58;
  GtkWidget *radiobutton3;
  GSList *radiobutton3_group = NULL;
  GtkWidget *radiobutton4;
  GSList *radiobutton4_group = NULL;
  GtkWidget *comboboxentry7;
  GtkWidget *label59;
  GtkWidget *label60;
  GtkWidget *label61;
  GtkWidget *entry27;
  GtkWidget *comboboxentry8;
  GtkWidget *entry28;
  GtkWidget *entry29;
  GtkWidget *label62;
  GtkWidget *label63;
  GtkWidget *entry30;
  GtkWidget *button12;
  GtkWidget *alignment12;
  GtkWidget *hbox12;
  GtkWidget *image16;
  GtkWidget *label64;
  GtkWidget *button13;
  GtkWidget *alignment13;
  GtkWidget *hbox13;
  GtkWidget *image17;
  GtkWidget *label65;
  GtkWidget *label53;

  window3 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_size_request (window3, 550, 550);
  gtk_window_set_title (GTK_WINDOW (window3), _("window3"));

  fixed7 = gtk_fixed_new ();
  gtk_widget_show (fixed7);
  gtk_container_add (GTK_CONTAINER (window3), fixed7);
  gtk_widget_set_size_request (fixed7, 0, -1);

  entry24 = gtk_entry_new ();
  gtk_widget_show (entry24);
  gtk_fixed_put (GTK_FIXED (fixed7), entry24, 200, 48);
  gtk_widget_set_size_request (entry24, 280, 27);
  gtk_entry_set_invisible_char (GTK_ENTRY (entry24), 8226);

  entry25 = gtk_entry_new ();
  gtk_widget_show (entry25);
  gtk_fixed_put (GTK_FIXED (fixed7), entry25, 200, 84);
  gtk_widget_set_size_request (entry25, 280, 28);
  gtk_entry_set_invisible_char (GTK_ENTRY (entry25), 8226);

  entry26 = gtk_entry_new ();
  gtk_widget_show (entry26);
  gtk_fixed_put (GTK_FIXED (fixed7), entry26, 200, 120);
  gtk_widget_set_size_request (entry26, 280, 28);
  gtk_entry_set_invisible_char (GTK_ENTRY (entry26), 8226);

  label54 = gtk_label_new (_("Nom :"));
  gtk_widget_show (label54);
  gtk_fixed_put (GTK_FIXED (fixed7), label54, 144, 56);
  gtk_widget_set_size_request (label54, 41, 17);

  label55 = gtk_label_new (_("Pr\303\251nom :"));
  gtk_widget_show (label55);
  gtk_fixed_put (GTK_FIXED (fixed7), label55, 120, 96);
  gtk_widget_set_size_request (label55, 72, 16);

  label56 = gtk_label_new (_("CIN :"));
  gtk_widget_show (label56);
  gtk_fixed_put (GTK_FIXED (fixed7), label56, 144, 128);
  gtk_widget_set_size_request (label56, 49, 17);

  label57 = gtk_label_new (_("Date de naissance :"));
  gtk_widget_show (label57);
  gtk_fixed_put (GTK_FIXED (fixed7), label57, 48, 168);
  gtk_widget_set_size_request (label57, 145, 16);

  comboboxentry5 = gtk_combo_box_entry_new_text ();
  gtk_widget_show (comboboxentry5);
  gtk_fixed_put (GTK_FIXED (fixed7), comboboxentry5, 200, 160);
  gtk_widget_set_size_request (comboboxentry5, 60, 29);

  comboboxentry6 = gtk_combo_box_entry_new_text ();
  gtk_widget_show (comboboxentry6);
  gtk_fixed_put (GTK_FIXED (fixed7), comboboxentry6, 272, 160);
  gtk_widget_set_size_request (comboboxentry6, 60, 29);

  label58 = gtk_label_new (_("Genre :"));
  gtk_widget_show (label58);
  gtk_fixed_put (GTK_FIXED (fixed7), label58, 136, 208);
  gtk_widget_set_size_request (label58, 49, 17);

  radiobutton3 = gtk_radio_button_new_with_mnemonic (NULL, _("Male"));
  gtk_widget_show (radiobutton3);
  gtk_fixed_put (GTK_FIXED (fixed7), radiobutton3, 200, 204);
  gtk_widget_set_size_request (radiobutton3, 116, 24);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton3), radiobutton3_group);
  radiobutton3_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton3));

  radiobutton4 = gtk_radio_button_new_with_mnemonic (NULL, _("Femelle"));
  gtk_widget_show (radiobutton4);
  gtk_fixed_put (GTK_FIXED (fixed7), radiobutton4, 322, 205);
  gtk_widget_set_size_request (radiobutton4, 115, 24);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton4), radiobutton4_group);
  radiobutton4_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton4));

  comboboxentry7 = gtk_combo_box_entry_new_text ();
  gtk_widget_show (comboboxentry7);
  gtk_fixed_put (GTK_FIXED (fixed7), comboboxentry7, 200, 235);
  gtk_widget_set_size_request (comboboxentry7, 189, 29);
  gtk_combo_box_append_text (GTK_COMBO_BOX (comboboxentry7), _("C\303\251l\303\251bataire"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (comboboxentry7), _("Mari\303\251"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (comboboxentry7), _("Divorc\303\251"));

  label59 = gtk_label_new (_("Etat civil :"));
  gtk_widget_show (label59);
  gtk_fixed_put (GTK_FIXED (fixed7), label59, 117, 246);
  gtk_widget_set_size_request (label59, 72, 16);

  label60 = gtk_label_new (_("Num\303\251ro de t\303\251l\303\251phone :"));
  gtk_widget_show (label60);
  gtk_fixed_put (GTK_FIXED (fixed7), label60, 24, 282);
  gtk_widget_set_size_request (label60, 168, 16);

  label61 = gtk_label_new (_("Adresse :"));
  gtk_widget_show (label61);
  gtk_fixed_put (GTK_FIXED (fixed7), label61, 112, 312);
  gtk_widget_set_size_request (label61, 81, 16);

  entry27 = gtk_entry_new ();
  gtk_widget_show (entry27);
  gtk_fixed_put (GTK_FIXED (fixed7), entry27, 200, 312);
  gtk_widget_set_size_request (entry27, 280, 64);
  gtk_entry_set_invisible_char (GTK_ENTRY (entry27), 8226);

  comboboxentry8 = gtk_combo_box_entry_new_text ();
  gtk_widget_show (comboboxentry8);
  gtk_fixed_put (GTK_FIXED (fixed7), comboboxentry8, 344, 160);
  gtk_widget_set_size_request (comboboxentry8, 90, 29);

  entry28 = gtk_entry_new ();
  gtk_widget_show (entry28);
  gtk_fixed_put (GTK_FIXED (fixed7), entry28, 201, 271);
  gtk_widget_set_size_request (entry28, 280, 28);
  gtk_entry_set_invisible_char (GTK_ENTRY (entry28), 8226);

  entry29 = gtk_entry_new ();
  gtk_widget_show (entry29);
  gtk_fixed_put (GTK_FIXED (fixed7), entry29, 201, 385);
  gtk_widget_set_size_request (entry29, 280, 28);
  gtk_entry_set_invisible_char (GTK_ENTRY (entry29), 8226);

  label62 = gtk_label_new (_("Email :"));
  gtk_widget_show (label62);
  gtk_fixed_put (GTK_FIXED (fixed7), label62, 134, 394);
  gtk_widget_set_size_request (label62, 56, 16);

  label63 = gtk_label_new (_("Secteur :"));
  gtk_widget_show (label63);
  gtk_fixed_put (GTK_FIXED (fixed7), label63, 128, 432);
  gtk_widget_set_size_request (label63, 56, 16);

  entry30 = gtk_entry_new ();
  gtk_widget_show (entry30);
  gtk_fixed_put (GTK_FIXED (fixed7), entry30, 201, 421);
  gtk_widget_set_size_request (entry30, 280, 28);
  gtk_entry_set_invisible_char (GTK_ENTRY (entry30), 8226);

  button12 = gtk_button_new ();
  gtk_widget_show (button12);
  gtk_fixed_put (GTK_FIXED (fixed7), button12, 384, 504);
  gtk_widget_set_size_request (button12, 100, 29);

  alignment12 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment12);
  gtk_container_add (GTK_CONTAINER (button12), alignment12);

  hbox12 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox12);
  gtk_container_add (GTK_CONTAINER (alignment12), hbox12);

  image16 = gtk_image_new_from_stock ("gtk-cancel", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image16);
  gtk_box_pack_start (GTK_BOX (hbox12), image16, FALSE, FALSE, 0);

  label64 = gtk_label_new_with_mnemonic (_("Annuler"));
  gtk_widget_show (label64);
  gtk_box_pack_start (GTK_BOX (hbox12), label64, FALSE, FALSE, 0);

  button13 = gtk_button_new ();
  gtk_widget_show (button13);
  gtk_fixed_put (GTK_FIXED (fixed7), button13, 280, 504);
  gtk_widget_set_size_request (button13, 100, 29);

  alignment13 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment13);
  gtk_container_add (GTK_CONTAINER (button13), alignment13);

  hbox13 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox13);
  gtk_container_add (GTK_CONTAINER (alignment13), hbox13);

  image17 = gtk_image_new_from_stock ("gtk-apply", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image17);
  gtk_box_pack_start (GTK_BOX (hbox13), image17, FALSE, FALSE, 0);

  label65 = gtk_label_new_with_mnemonic (_("Confirmer"));
  gtk_widget_show (label65);
  gtk_box_pack_start (GTK_BOX (hbox13), label65, FALSE, FALSE, 0);

  label53 = gtk_label_new (_("Ajouter un Employee :"));
  gtk_widget_show (label53);
  gtk_fixed_put (GTK_FIXED (fixed7), label53, 8, 8);
  gtk_widget_set_size_request (label53, 152, 24);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (window3, window3, "window3");
  GLADE_HOOKUP_OBJECT (window3, fixed7, "fixed7");
  GLADE_HOOKUP_OBJECT (window3, entry24, "entry24");
  GLADE_HOOKUP_OBJECT (window3, entry25, "entry25");
  GLADE_HOOKUP_OBJECT (window3, entry26, "entry26");
  GLADE_HOOKUP_OBJECT (window3, label54, "label54");
  GLADE_HOOKUP_OBJECT (window3, label55, "label55");
  GLADE_HOOKUP_OBJECT (window3, label56, "label56");
  GLADE_HOOKUP_OBJECT (window3, label57, "label57");
  GLADE_HOOKUP_OBJECT (window3, comboboxentry5, "comboboxentry5");
  GLADE_HOOKUP_OBJECT (window3, comboboxentry6, "comboboxentry6");
  GLADE_HOOKUP_OBJECT (window3, label58, "label58");
  GLADE_HOOKUP_OBJECT (window3, radiobutton3, "radiobutton3");
  GLADE_HOOKUP_OBJECT (window3, radiobutton4, "radiobutton4");
  GLADE_HOOKUP_OBJECT (window3, comboboxentry7, "comboboxentry7");
  GLADE_HOOKUP_OBJECT (window3, label59, "label59");
  GLADE_HOOKUP_OBJECT (window3, label60, "label60");
  GLADE_HOOKUP_OBJECT (window3, label61, "label61");
  GLADE_HOOKUP_OBJECT (window3, entry27, "entry27");
  GLADE_HOOKUP_OBJECT (window3, comboboxentry8, "comboboxentry8");
  GLADE_HOOKUP_OBJECT (window3, entry28, "entry28");
  GLADE_HOOKUP_OBJECT (window3, entry29, "entry29");
  GLADE_HOOKUP_OBJECT (window3, label62, "label62");
  GLADE_HOOKUP_OBJECT (window3, label63, "label63");
  GLADE_HOOKUP_OBJECT (window3, entry30, "entry30");
  GLADE_HOOKUP_OBJECT (window3, button12, "button12");
  GLADE_HOOKUP_OBJECT (window3, alignment12, "alignment12");
  GLADE_HOOKUP_OBJECT (window3, hbox12, "hbox12");
  GLADE_HOOKUP_OBJECT (window3, image16, "image16");
  GLADE_HOOKUP_OBJECT (window3, label64, "label64");
  GLADE_HOOKUP_OBJECT (window3, button13, "button13");
  GLADE_HOOKUP_OBJECT (window3, alignment13, "alignment13");
  GLADE_HOOKUP_OBJECT (window3, hbox13, "hbox13");
  GLADE_HOOKUP_OBJECT (window3, image17, "image17");
  GLADE_HOOKUP_OBJECT (window3, label65, "label65");
  GLADE_HOOKUP_OBJECT (window3, label53, "label53");

  return window3;
}
