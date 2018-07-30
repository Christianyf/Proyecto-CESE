#include <gtk/gtk.h>
 
//GtkWidget *g_lbl_hello;
//GtkWidget *g_lbl_count;
 
int main(int argc, char *argv[])
{
    GtkBuilder      *builder; 
    GtkWidget       *window;
 
    gtk_init(&argc, &argv);
 
    builder = gtk_builder_new();
   // gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);
    gtk_builder_add_from_file (builder, "glade/window.glade", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
    gtk_builder_connect_signals(builder, NULL);
    
    // get pointers to the two labels
    //g_lbl_hello = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_hello"));
    //g_lbl_count = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_count"));
 
    g_object_unref(builder);
 
    gtk_widget_show(window);                
    gtk_main();
 
    return 0;
}
 
// called when button is clicked
void on_button2_clicked(int argc, char *argv[])
{
    GtkBuilder      *builder; 
    GtkWidget       *window;
 
    gtk_init(&argc, &argv);
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);
    
    g_object_unref(builder);
 
    gtk_widget_show(window);                
    
    gtk_main();
    

  

}
 
// called when window is closed
void on_window1_destroy()
{
    gtk_main_quit();
}

// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}
