#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"


void
on_button_login_close_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_main_quit();
}

