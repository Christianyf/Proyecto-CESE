#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

#include <X11/Xlib.h>
#include <glib.h>

#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringSerial.h>
#include "soporte.h"

void pagina_accesoPass(void)
{
    GtkBuilder      *builder;
    GtkWidget       *window;
    
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/clave_numerica.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "pagina_clave"));
    gtk_builder_connect_signals(builder, NULL);
    
    //label2 = GTK_WIDGET(gtk_builder_get_object(builder, "label2"));
    

    g_object_unref(builder);

    // prevent cursor from briefly appearing between screen changes
    MoveCursor(800, 480);	// move cursor off screen
    gtk_widget_show(window);
    
    HideCursor(window);
}
