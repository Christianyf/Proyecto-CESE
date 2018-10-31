//---------------------------------------------------------------------
//  Program:      rpi_gtk_kiosk
//
//  Description:  Raspberry PI Shopping Mall Information Kiosk
//                - Displays a main window with mall map and buttons
//                - Clicking any button opens a corresponding window
//                  with information on a shop in the mall
//                - Each shop window has a back button that closes the
//                  window reverting back to the main mall window
//
//  Build info:   Built using Glade and GTK+ 3
//                Compiled using GCC
//
//  Date:         25 November 2016      Author: W.A. Smith
//                http://startingelectronics.org
//---------------------------------------------------------------------
#include <gtk/gtk.h>
#include <X11/Xlib.h>
#include <glib.h>
#include <wiringPi.h>
#include "soporte.h"



GtkWidget* win_new_glade(char *glade_file, char *win_name);
void HideCursor(GtkWidget *window);
void MoveCursor(int x, int y);
void mainWindowInit();

static GThread   *thread_finger_print; 
static GThread   *thread_finger_config; 
static int flag=0,flag2=0;

int main(int argc, char *argv[])
{

    gtk_init(&argc, &argv);
	
    mainWindowInit();
    
    gtk_main();

    return 0;

}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
void mainWindowInit()
{
    GtkBuilder      *builder; 
    GtkWidget       *window;

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);

    gtk_window_fullscreen(GTK_WINDOW(window));
	
    MoveCursor(800, 480);	// move cursor off screen
    gtk_widget_show(window);                

    HideCursor(window);
    
    return;
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
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
//-------------------------------------------------------------------------
void *fingerprintService()
{
	//g_print("Inside thread...\n");
	printf("dentro de la tarea fingerPrint\r\n");
	var=1;
	printf("%d\r\n",var);
	//progress=0.00;
	while(flag==0)
	{
		// Questa funzione viene eseguita compatibilmente
		// le esigenze del ciclo principale delle Gtk
		g_idle_add ((GSourceFunc) verificarSignal, NULL   );
		//sleep(1);

        		
	}
	printf("Thread fingerprint completed...\r\n");
	prueba();
	g_thread_exit(thread_finger_print);
	return FALSE;

}
//------------------------------------------------------------------------
void *fingerprintConfig()
{
	//g_print("Inside thread...\n");
	printf("dentro de la tarea fingerConfig\r\n");
	//progress=0.00;
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
//------------------------------------------------------------------------
//------------------------------------------------------------------------

//------------------------------------------------------------------------
//------------------------------------------------------------------------
// button click handlers for the shops
void on_btn_shop1_clicked(GtkWidget *widget, gpointer data)
{
	win_new_glade("glade/acceso_biometrico.glade", "pagina_biometrico");
	flag=0;
	//GThread   *myThread; 
	//myThread= g_thread_new(NULL,(GThreadFunc)fingerprintService,data);
	thread_finger_print=g_thread_new(NULL,(GThreadFunc)fingerprintService,data);
	//gtk_widget_set_sensitive(widget, FALSE) ;

}

void on_btn_shop2_clicked()
{
	win_new_glade("glade/clave_numerica.glade", "pagina_clave");
	//g_thread_exit(myThread); 
}

void on_btn_shop3_clicked(GtkWidget *widget, gpointer data)
{
	flag2=0;
	win_new_glade("glade/configuraciones.glade", "pagina_configuraciones");
	thread_finger_config=g_thread_new(NULL,(GThreadFunc)fingerprintConfig,data);
}



// close window when back button is clicked in  window 1
void on_btn_back_pg1_clicked(GtkWidget *widget, gpointer data)
{
	flag=1;
	gtk_widget_destroy(data);
}
//close window when back button is clicked in  window 2
void on_btn_back_pg2_clicked(GtkWidget *widget, gpointer data)
{
	gtk_widget_destroy(data);
}
//close window when back button is clicked in  window 3
void on_btn_back_pg3_clicked(GtkWidget *widget, gpointer data)
{
	flag2=1;
	gtk_widget_destroy(data);
}
// close the main window when Alt + F4 pressed - needed during development
void on_window_main_destroy()
{
    gtk_main_quit();
}

// window creation utility function
// creates a window from a glade file and displays the selected image in the window
GtkWidget* win_new_glade(char *glade_file, char *win_name)
{
    GtkBuilder      *builder;
    GtkWidget       *window;
    
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, glade_file, NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, win_name));
    gtk_builder_connect_signals(builder, NULL);
    

    g_object_unref(builder);

	// prevent cursor from briefly appearing between screen changes
	MoveCursor(800, 480);	// move cursor off screen
    gtk_widget_show(window);
    
    HideCursor(window);
    
    return window;
}

void HideCursor(GtkWidget *window)
{
    GdkDisplay		*display;
    GdkCursor		*hideCursor = NULL;
    GdkWindow		*gdk_window;
    
	// hide cursor
	display = gdk_display_get_default();
	hideCursor = gdk_cursor_new_for_display(display, GDK_BLANK_CURSOR);
	gdk_window = gtk_widget_get_window(window);
	gdk_window_set_cursor(gdk_window, hideCursor);
}

void MoveCursor(int x, int y)
{
	Display *dpy;
	Window root_window;
	
	dpy = XOpenDisplay(0);
	root_window = XRootWindow(dpy, 0);
	XSelectInput(dpy, root_window, KeyReleaseMask);
	XWarpPointer(dpy, None, root_window, 0, 0, 0, 0, x, y);
	XFlush(dpy);
}
