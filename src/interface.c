#include <stdio.h>
#include <gtk/gtk.h>

void activate(GtkApplication *app, gpointer user_draw_parts_data) {
	// *** Main window ***
	GtkWidget *window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Window");
	gtk_window_set_default_size(GTK_WINDOW(window), 800, 400);

	// code

	// *** Show all ***
	gtk_window_present(GTK_WINDOW(window));
}