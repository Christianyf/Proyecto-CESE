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

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

GtkWidget *label2;
extern int flag;
extern int s;
extern struct sockaddr_in serveraddr;

static GThread   *thread_finger_print; 

struct {
	int dat1;
	char dat2;
	int dat3[3]; 
}ejemplo;
//--------------------------------------------------------------------------
void *verificarSig()
{		    
	while (gtk_events_pending())
	{
		//printf("dentro...\r\n");
		gtk_main_iteration();
		//sleep(1);
	}
	return FALSE;
}
//--------------------------------------------------------------------------
void *fingerprintService()
{
	printf("dentro de la tarea fingerPrint\r\n");
	gtk_label_set_text(GTK_LABEL(label2), "Hello, world!");
	var=1;
	printf("%d\r\n",var);
	ejemplo.dat1=1;
	//int n = write(s,"tareadedo",10);
	int n = write(s,&ejemplo,sizeof(ejemplo));
	printf ("El tamaño es %d\n", sizeof(ejemplo)); 
	
	if(n<=0)
    	{
        	fprintf(stderr,"ERROR sending command\r\n");
        	close(s);
        	exit(EXIT_FAILURE);
    	}

	while(flag==0)
	{
		// Questa funzione viene eseguita compatibilmente
		// le esigenze del ciclo principale delle Gtk
		g_idle_add ((GSourceFunc) verificarSig, NULL   );
		//sleep(1);
	}
	printf("Thread fingerprint completed...\r\n");
	prueba();
	//close(s);
	g_thread_exit(thread_finger_print);
	return FALSE;

}
//--------------------------------------------------------------------------
void pagina_accesoBio(void)
{
    GtkBuilder      *builder;
    GtkWidget       *window;
    
    builder = gtk_builder_new();
     gtk_builder_add_from_file (builder, "glade/acceso_biometrico.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "pagina_biometrico"));
    gtk_builder_connect_signals(builder, NULL);
    
    label2 = GTK_WIDGET(gtk_builder_get_object(builder, "label2"));
    

    g_object_unref(builder);

    // prevent cursor from briefly appearing between screen changes
    MoveCursor(800, 480);	// move cursor off screen
    gtk_widget_show(window);
    
    HideCursor(window);
    
    thread_finger_print=g_thread_new(NULL,(GThreadFunc)fingerprintService,NULL);

}

void prueba(void)
{
	var=2;
	printf("%d\r\n",var);
}
//-----------------------------------------------------------------------------





