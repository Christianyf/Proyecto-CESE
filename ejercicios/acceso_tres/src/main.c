#include <gtk/gtk.h>
#include <stdio.h>
#include "complementario.h"
#include <stdlib.h>


/*typedef struct {
    GtkWidget *lbl_clave;
    GtkWidget *label5;
} app_widgets;*/

///////////////////////////////Funciones locales///////////////////////////////////// 
//static buffer buffer_clave;

    void cubrir_clave(void);
   
    char str_count[30];

//////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
    GtkBuilder      *builder; 
    GtkWidget       *window;
    
    buffer_clave.indice_escritura = 0;  
    // instantiate structure, allocating memory for it
    app_widgets     *widgets = g_slice_new(app_widgets);
    
    //buffer_clave.indice_lectura=5;//uso para probar escritura en buffer
 
    gtk_init(&argc, &argv);
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/menu.glade", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(builder,"window1"));
    // get pointers to the label
    widgets->lbl_clave = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_clave"));
    widgets->label8 = GTK_WIDGET(gtk_builder_get_object(builder, "label8"));
    widgets->lbl_name = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_name"));
    widgets->lbl_pass = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_pass"));
    widgets->rb1 = GTK_WIDGET(gtk_builder_get_object(builder, "rb1"));
    widgets->rb2 = GTK_WIDGET(gtk_builder_get_object(builder, "rb2"));
    
    // widgets pointer will be passed to all widget handler functions as the user_data parameter
    gtk_builder_connect_signals(builder,widgets);
 
    g_object_unref(builder);
 
    gtk_widget_show(window);                
    
    gtk_main();
   // escribir_buffer();
    
    
    // reclaim memory from application after it exits
    g_slice_free(app_widgets, widgets);
    while(1)
    {
    	printf("Proces 1\r\n"); 
    
    }
 
    return 0;
}

void on_button1_clicked(GtkButton *button1,app_widgets *app_wdgts)
{
   
   //gtk_label_set_text(GTK_LABEL(app_wdgts->lbl_clave),str_count);
   buffer_clave.clave[buffer_clave.indice_escritura]=1;
   buffer_clave.indice_escritura++;
   cubrir_clave();
   gtk_label_set_text(GTK_LABEL(app_wdgts->lbl_clave),str_count);
   
   //sprintf(str_count, "%d", buffer_clave.indice_escritura);
   

   
   printf("%d\r\n",buffer_clave.indice_escritura);//para probar escritura en buffer
   
   escribir_buffer();//no hace nada
}
///////////////////////////////////////////////////////////////////
void on_button2_clicked(GtkButton *button2,app_widgets *app_wdgts)
{
	//gtk_label_set_text(GTK_LABEL(app_wdgts->lbl_clave),"2");
	buffer_clave.clave[buffer_clave.indice_escritura]=2;
   	buffer_clave.indice_escritura++;
   	cubrir_clave();
  	gtk_label_set_text(GTK_LABEL(app_wdgts->lbl_clave),str_count);

}
//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
void on_button3_clicked(GtkButton *button3,app_widgets *app_wdgts)
{
	//gtk_label_set_text(GTK_LABEL(app_wdgts->lbl_clave),"3");
	buffer_clave.clave[buffer_clave.indice_escritura]=3;
   	buffer_clave.indice_escritura++;
   	cubrir_clave();
   	gtk_label_set_text(GTK_LABEL(app_wdgts->lbl_clave),str_count);

}
//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
void on_button4_clicked(GtkButton *button4,app_widgets *app_wdgts)
{
	//gtk_label_set_text(GTK_LABEL(app_wdgts->lbl_clave),"4");
	buffer_clave.clave[buffer_clave.indice_escritura]=4;
   	buffer_clave.indice_escritura++;
   	cubrir_clave();
   	gtk_label_set_text(GTK_LABEL(app_wdgts->lbl_clave),str_count);

}
//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
void on_button5_clicked(GtkButton *button5,app_widgets *app_wdgts)
{
	//gtk_label_set_text(GTK_LABEL(app_wdgts->lbl_clave),"5");
	buffer_clave.clave[buffer_clave.indice_escritura]=5;
   	buffer_clave.indice_escritura++;
   	cubrir_clave();
   	gtk_label_set_text(GTK_LABEL(app_wdgts->lbl_clave),str_count);

}
//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
void on_button6_clicked(GtkButton *button6,app_widgets *app_wdgts)
{
	//gtk_label_set_text(GTK_LABEL(app_wdgts->lbl_clave),"6");
	buffer_clave.clave[buffer_clave.indice_escritura]=6;
   	buffer_clave.indice_escritura++;
   	cubrir_clave();
   	gtk_label_set_text(GTK_LABEL(app_wdgts->lbl_clave),str_count);

}
//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
void on_button7_clicked(GtkButton *button7,app_widgets *app_wdgts)
{
	//gtk_label_set_text(GTK_LABEL(app_wdgts->lbl_clave),"7");
	buffer_clave.clave[buffer_clave.indice_escritura]=7;
   	buffer_clave.indice_escritura++;
   	cubrir_clave();
   	gtk_label_set_text(GTK_LABEL(app_wdgts->lbl_clave),str_count);

}
//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
void on_button8_clicked(GtkButton *button8,app_widgets *app_wdgts)
{
	//gtk_label_set_text(GTK_LABEL(app_wdgts->lbl_clave),"8");
	buffer_clave.clave[buffer_clave.indice_escritura]=8;
   	buffer_clave.indice_escritura++;
   	cubrir_clave();
   	gtk_label_set_text(GTK_LABEL(app_wdgts->lbl_clave),str_count);

}
//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
void on_button9_clicked(GtkButton *button9,app_widgets *app_wdgts)
{
	//gtk_label_set_text(GTK_LABEL(app_wdgts->lbl_clave),"9");
	buffer_clave.clave[buffer_clave.indice_escritura]=9;
   	buffer_clave.indice_escritura++;
   	cubrir_clave();
   	gtk_label_set_text(GTK_LABEL(app_wdgts->lbl_clave),str_count);

}
//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
void on_button_0_clicked(GtkButton *button_0,app_widgets *app_wdgts)
{
	//gtk_label_set_text(GTK_LABEL(app_wdgts->lbl_clave),"0");
	buffer_clave.clave[buffer_clave.indice_escritura]=0;
   	buffer_clave.indice_escritura++;
   	cubrir_clave();
   	gtk_label_set_text(GTK_LABEL(app_wdgts->lbl_clave),str_count);

}
//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
void on_button_borrar_clicked(GtkButton *button_borrar,app_widgets *app_wdgts)
{
	//gtk_label_set_text(GTK_LABEL(app_wdgts->lbl_clave),"borrar");
	if(buffer_clave.indice_escritura > 0)
	{
		buffer_clave.indice_escritura--;
	}
	else
	{
		buffer_clave.indice_escritura = 0;
	}
	
	cubrir_clave();
   	gtk_label_set_text(GTK_LABEL(app_wdgts->lbl_clave),str_count);

}
//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
void on_button_entrar_clicked(GtkButton *button_entrar,app_widgets *app_wdgts)
{
	gtk_label_set_text(GTK_LABEL(app_wdgts->lbl_clave),"entrar");

}
//////////////////////////////////////////////////////////////////
void cubrir_clave(void)
{
	int i;
	for (i=0;i<buffer_clave.indice_escritura;i++)
	{
		str_count[i]='*';
	}
	str_count[buffer_clave.indice_escritura]='\0';
	
}
/////////////////////////////////////////////////////////////////
// called when window is closed
void on_window1_destroy()
{
    gtk_main_quit();
}
/////////////////////////////////////////////////////////////////




