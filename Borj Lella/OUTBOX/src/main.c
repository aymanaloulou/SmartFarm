/*
 * Initial main.c file generated by Glade. Edit as required.
 * Glade will not overwrite this file.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "interface.h"
#include "support.h"

int
main (int argc, char *argv[])
{
GtkWidget *window_employee_space;

#ifdef ENABLE_NLS
  bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
  bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
  textdomain (GETTEXT_PACKAGE);
#endif

  gtk_set_locale ();
  gtk_init (&argc, &argv);

  add_pixmap_directory ("../pixmaps");
  GtkWidget *window_gest_ouvrier;
  window_gest_ouvrier = create_window_gest_ouvrier ();
  gtk_widget_show (window_gest_ouvrier);

  GtkWidget *window_gest_emp,*window_employee_space1;
  window_gest_emp = create_window_gest_emp ();
  gtk_widget_show (window_gest_emp);
  window_employee_space=create_window_espace_admin();
gtk_widget_show(window_employee_space);
window_employee_space1=create_window_employee_space();
gtk_widget_show(window_employee_space1);

  /*
   * The following code was added by Glade to create one of each component
   * (except popup menus), just so that you see something after building
   * the project. Delete any components that you don't want shown initially.
   */

  gtk_main ();
  return 0;
}

