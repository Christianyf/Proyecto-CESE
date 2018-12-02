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
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <gtk/gtk.h>
#include <X11/Xlib.h>
#include <glib.h>
#include <wiringPi.h>
#include "soporte.h"


void mainWindowInit();

int flag=0,flag2=0;

extern GtkWidget *label2;

        struct sockaddr_in serveraddr;
	int s;
	
typedef struct UnaEstructura
{
    int idproceso;
    int idsensor;
    char name[20];
    int pass[4];
} UnaEstructura; 


int main(int argc, char *argv[])
{
        //struct sockaddr_in serveraddr;
	//char buf[128];
	//int s;

	// Creamos socket
	s = socket(PF_INET,SOCK_STREAM, 0);

	// Cargamos datos de direccion de server
    	bzero((char *) &serveraddr, sizeof(serveraddr));
    	serveraddr.sin_family = AF_INET;
    	serveraddr.sin_port = htons(4096);
    	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    	if(serveraddr.sin_addr.s_addr==INADDR_NONE)
    	{
        	fprintf(stderr,"ERROR invalid server IP\r\n");
        	return 1;
    	}

	// Ejecutamos connect()
    	if (connect(s, (const struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
    	{
        	fprintf(stderr,"ERROR connecting\r\n");
        	close(s);
        	exit(EXIT_FAILURE);
    	}
	
	printf("Conectado\r\n");
	
//printf ("El tamaño es %d\n", sizeof(UnaEstructura)); 
	// Enviamos mensaje a server
    	//printf("Ingrese un mensaje:\r\n");
    	//fgets(buf,sizeof(buf),stdin);
    	//printf("envio:%s",buf);

    	//int n = write(s, buf, strlen(buf));
    	//int n = write(s,"principal", 10);
	//printf("Envie %d bytes\n",n);
	// prueba server desconectado. Al enviar por segunda vez se recibe SIGPIPE********
    	//n = write(s, buf, strlen(buf));************
	//__________________________

    	/*if(n<=0)
    	{
        	fprintf(stderr,"ERROR sending command\r\n");
        	close(s);
        	exit(EXIT_FAILURE);
    	}*/

	// Leemos respuesta de server
    	/*n = read(s, buf, sizeof(buf));
	printf("Recibi %d bytes\n",n);
    	if(n>0)
    	{
        	printf("Recibi:'%s'\r\n",buf);
    	}
	close(s);*/
    gtk_init(&argc, &argv);	
    mainWindowInit();    
    gtk_main();
    
    close(s);

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

// button click handlers for the shops
void on_btn_shop1_clicked(GtkWidget *widget, gpointer data)
{
	pagina_accesoBio();
	flag=0;
}

void on_btn_shop2_clicked()
{
	pagina_accesoPass();
}

void on_btn_shop3_clicked(GtkWidget *widget, gpointer data)
{
	pagina_configuraciones();
	flag2=0;
	//thread_finger_config=g_thread_new(NULL,(GThreadFunc)fingerprintConfig,data);
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
