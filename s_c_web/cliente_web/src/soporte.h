#ifndef __SUPPORT_H__
#define __SUPPORT_H__

#include <gtk/gtk.h>

void prueba(void);
void pagina_accesoBio(void);
void pagina_accesoPass(void);
void pagina_configuraciones(void);

void MoveCursor(int x, int y);
void HideCursor(GtkWidget *window);

/* Main data structure definition */
typedef struct _ChData ChData;
struct _ChData
{
    /* Widgets */
    //GtkWidget *main_window;  /* Main application window */
    //GtkWidget *chart_area;   /* Chart drawing area */
};

static int var=0;

#endif /* __SUPPORT_H__ */
