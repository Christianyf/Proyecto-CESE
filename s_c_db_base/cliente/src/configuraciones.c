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

extern int flag2;
static GThread   *thread_finger_config; 

extern int s;
extern struct sockaddr_in serveraddr;

//-------------------------------------------------------------------------------
void *verificarSignal()
{		    
	while (gtk_events_pending())
	{
		//printf("dentro...\r\n");
		gtk_main_iteration();
		//sleep(1);
	}
	return FALSE;
}
//-------------------------------------------------------------------------------
void *fingerprintConfig()
{
	printf("dentro de la tarea fingerConfig\r\n");
	int n = write(s,"hola",5);
	while(flag2==0)
	{
		// Questa funzione viene eseguita compatibilmente
		// le esigenze del ciclo principale delle Gtk
		g_idle_add ((GSourceFunc) verificarSignal, NULL   );
		//sleep(1);	
	}
	printf("Thread fingerconfig completed...\r\n");
	g_thread_exit(thread_finger_config);
	return FALSE;

}
//--------------------------------------------------------------------------------
void pagina_configuraciones(void)
{
    GtkBuilder      *builder;
    GtkWidget       *window;
    
    builder = gtk_builder_new();
     gtk_builder_add_from_file (builder, "glade/configuraciones.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "pagina_configuraciones"));
    gtk_builder_connect_signals(builder, NULL);
    
    //label2 = GTK_WIDGET(gtk_builder_get_object(builder, "label2"));
    

    g_object_unref(builder);

    // prevent cursor from briefly appearing between screen changes
    MoveCursor(800, 480);	// move cursor off screen
    gtk_widget_show(window);
    
    HideCursor(window);
    
    thread_finger_config=g_thread_new(NULL,(GThreadFunc)fingerprintConfig,NULL);
}

