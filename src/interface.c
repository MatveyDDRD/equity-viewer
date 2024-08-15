#include <stdio.h>
#include <gtk/gtk.h>

void undo_action_callback(GSimpleAction *action, GVariant *parameter, gpointer user_draw_parts_data) {printf("Undo button clicked\n");}

void redo_action_callback(GSimpleAction *action, GVariant *parameter, gpointer user_draw_parts_data) {printf("Redo button clicked\n");}


/*
 * window
 *    -main vertical box
 * 	    - toolbar
 * 	    - tabs
 * 	    - workspace
 * 	       - equity's
 * 	       - candels
 * 
 * Окно с инструментами потом добавить либо как отдельные окно, либо самостоятельно отрисовывать с помошью cairo
 */
void activate(GtkApplication *app, gpointer user_draw_parts_data) {
	// *** Main window ***
	GtkWidget *window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Window");
	gtk_window_set_default_size(GTK_WINDOW(window), 800, 400);


	GtkWidget *main_vertical_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_window_set_child(GTK_WINDOW(window), main_vertical_box);

	// пока добавил просто пример меню, чтобы потом проще было проще создавать его, 
	// и не надо было долго копаться в документации

	// Create the main menu
	GMenu *menu_bar = g_menu_new();

	// Create the "File" submenu
	GMenu *file_menu = g_menu_new();
	g_menu_append_submenu(menu_bar,"File", G_MENU_MODEL(file_menu));

	// Create the "Edit" submenu
	GMenu *edit_menu = g_menu_new();
	g_menu_append_submenu(menu_bar,"Edit", G_MENU_MODEL(edit_menu));

	// Create the "example_submenu" within the "File" submenu
	GMenu *example_submenu = g_menu_new();
	g_menu_append_submenu(file_menu,"example_submenu", G_MENU_MODEL(example_submenu));

	// Create "Undo" and "Redo" actions
	GSimpleAction *act_undo = g_simple_action_new("undo", NULL);
	GSimpleAction *act_redo = g_simple_action_new("redo", NULL);

	// Add actions to the application's action map
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(act_undo));
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(act_redo));

	// Connect activation signals to actions
	g_signal_connect(act_undo,"activate", G_CALLBACK(undo_action_callback), NULL);
	g_signal_connect(act_redo,"activate", G_CALLBACK(redo_action_callback), NULL);

	// Create the "Undo" menu item and add it to the "Edit" submenu
	GMenuItem *menu_item_undo = g_menu_item_new("Undo", "app.undo");
	g_menu_append_item(edit_menu, menu_item_undo);

	// Create the "Redo" menu item and add it to the "Edit" submenu
	GMenuItem *menu_item_redo = g_menu_item_new("Redo", "app.redo");
	g_menu_append_item(edit_menu, menu_item_redo);

	// Set the main menu for the application and display it
	gtk_application_set_menubar(GTK_APPLICATION(app), G_MENU_MODEL(menu_bar));
	gtk_application_window_set_show_menubar(GTK_APPLICATION_WINDOW(window), TRUE);

	GtkWidget *butt = gtk_button_new();
	gtk_button_set_label(GTK_BUTTON(butt), "button");



	// *** Make tabs switcher ***
	GtkWidget *notebook = gtk_notebook_new();

	GtkWidget *label = gtk_label_new("main tab");

	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), butt, label);

	gtk_box_append(GTK_BOX(main_vertical_box), notebook);



	// *** Show all ***
	gtk_window_present(GTK_WINDOW(window));
}