/*
 * main.c
 * 
 * Copyright 2018 christian <christian@home>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <stdio.h>
#include <gtk/gtk.h>

int main(int argc, char **argv)
{
	GtkBuilder *builder;
	GtkWidget  *window;
	
	gtk_init(&argc,&argv);
	
	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder,"window1.glade",NULL); 
	
	window = GTK_WIDGET(gtk_builder_get_object(builder,"window1"));
	gtk_builder_connect_signals(builder, NULL);
	
	g_object_unref(builder);
	
	gtk_widget_show(window);
	gtk_main();
	
	return 0;
}
void on_window1_destroy()
{
	gtk_main_quit();
}

