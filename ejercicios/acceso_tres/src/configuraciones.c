#include <gtk/gtk.h>
#include <stdio.h>
#include "complementario.h"
#include <stdlib.h>



int flag =0;

int configuraciones(int argc, char *argv[])
{
    usuario.indice_esc=0;

 
    return 0;
}

void on_button11_clicked(GtkButton *button11,app_widgets *app_wdgts)
{
   
   if(flag==1)
   {
   	gtk_label_set_text(GTK_LABEL(app_wdgts->lbl_pass),"1");
   }
   
   //sprintf(str_count, "%d", buffer_clave.indice_escritura);
   printf("%d\r\n",buffer_clave.indice_escritura);//para probar escritura en buffer
}
/////////////////////////////////////////////////////////////////////////
void on_buttonq_clicked(GtkButton *buttonq,app_widgets *app_wdgts)
{
	
	if(flag==0)
	{
		//gtk_label_set_text(GTK_LABEL(app_wdgts->lbl_name),"Q");
		usuario.name[usuario.indice_esc]='Q';
		usuario.indice_esc++;
		usuario.name[usuario.indice_esc]='\0';
		gtk_label_set_text(GTK_LABEL(app_wdgts->lbl_name),usuario.name);
			
	}
	else if (flag==1)
	{
		gtk_label_set_text(GTK_LABEL(app_wdgts->lbl_pass),"1");
	}

}
////////////////////////////////////////////////////////////////////////
// handle radio button toggle events
void on_radiobutton_toggled (GtkToggleButton *togglebutton, app_widgets *app_wdgts)
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(app_wdgts->rb1))) {
        gtk_label_set_text(GTK_LABEL(app_wdgts->label8), "NOMBRE");     // update label
        //g_print("Toggled 1\n");
        flag=0;
    }
    else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(app_wdgts->rb2))) {
        gtk_label_set_text(GTK_LABEL(app_wdgts->label8), "CONTRASEÑA");     // update label
        //g_print("Toggled 2\n");
        flag=1;
    }
    
}
   
////////////////////////////////////////////////////////////////////////
void on_button_borr_clicked(GtkButton *button_borr,app_widgets *app_wdgts)
{
	if(usuario.indice_esc > 0)
	{
		usuario.indice_esc--;
		usuario.name[usuario.indice_esc]='\0';
	}
	else
	{
		usuario.indice_esc = 0;
	}
	gtk_label_set_text(GTK_LABEL(app_wdgts->lbl_name),usuario.name);	

}




