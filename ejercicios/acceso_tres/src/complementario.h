//////////////////////////////////
#include <gtk/gtk.h>
//#include "complementario.h"

//#ifndef COMPLEMENTARIO_H
//#define COMPLEMENTARIO_H

typedef struct {
	int	clave[30];
	int	indice_lectura;
	int	indice_escritura;
	
}buffer;

static buffer buffer_clave;
//////////////////////////////////////////////////
typedef struct{
	char	name[30];
	int	password[30];
	int 	indice_lec;
	int	indice_esc;

}user;
static user usuario;
/////////////////////////////////////////////////
typedef struct {
    GtkWidget *lbl_clave;
    GtkWidget *label5;
    GtkWidget *label8;
    GtkWidget *rb1;
    GtkWidget *rb2;
    GtkWidget *lbl_name;
    GtkWidget *lbl_pass;
    
} app_widgets;
    
/////////////////////////////////////////////////
void escribir_buffer(void);

// #endif 
