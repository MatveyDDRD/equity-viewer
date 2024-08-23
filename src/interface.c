#include <stdio.h>
#include <gtk/gtk.h>

#include "interface.h"

#define ALLOC_CHECK(pointer) \
    if (pointer == NULL) { \
        printf("Fatal error: allocation error in function %s\n", __func__); \
        exit(EXIT_FAILURE); \
    }

#define ALLOC(pointer, type, elements_num, elements_add_num).             \
	if (elements_num == 0)												  \
	{																	  \
		pointer = malloc( sizeof(type) * elements_add_num );			  \
	}else if( elements_num > 0) {										  \
		pointer = realloc(pointer, sizeof(type) * elements_add_num );	  \
	}else{																  \
		printf("trying to allocate memory for negative number of elements in function __func__\n"); \
		exit(EXIT_FAILURE);												  \
	}																	  \
	ALLOC_CHECK(pointer);												  \


void undo_action_callback(GSimpleAction *action, GVariant *parameter, gpointer user_draw_parts_data) {
	printf("Undo button clicked\n");
}

void redo_action_callback(GSimpleAction *action, GVariant *parameter, gpointer user_draw_parts_data) {
	printf("Redo button clicked\n");
}

/*
 * filles eqiuty_list_box
 */
void equtys_list_refresh(GtkWidget *box) {
	// добавить когда разберемся с API
}

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
void activate(GtkApplication *app, gpointer user_data) {
	// *** Main window ***
	GtkWidget *window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Window");
	gtk_window_set_default_size(GTK_WINDOW(window), 800, 400);


	GtkWidget *main_vertical_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_window_set_child(GTK_WINDOW(window), main_vertical_box);

	/* пока добавил просто пример меню, чтобы потом проще было проще создавать его, 
	и не надо было долго копаться в документации */

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

	// test button
	GtkWidget *butt = gtk_button_new();
	gtk_button_set_label(GTK_BUTTON(butt), "button");
	GtkWidget *butt2 = gtk_button_new();
	gtk_button_set_label(GTK_BUTTON(butt2), "button2");



	// *** Paned ***
	GtkWidget *main_frame = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL); // sidebar | candles
	GtkWidget *sidebar_frame = gtk_frame_new(NULL);
	GtkWidget *candles_frame = gtk_frame_new(NULL);

	// gtk_box_append(GTK_BOX(main_vertical_box), main_frame);

	gtk_paned_set_start_child(GTK_PANED(main_frame), sidebar_frame);
	gtk_paned_set_resize_start_child(GTK_PANED(main_frame), TRUE);
	gtk_paned_set_shrink_start_child(GTK_PANED(main_frame), FALSE);
	gtk_widget_set_size_request(sidebar_frame, 50, -1);

	gtk_paned_set_end_child(GTK_PANED(main_frame), candles_frame);
	gtk_paned_set_resize_end_child(GTK_PANED(main_frame), TRUE);
	gtk_paned_set_shrink_end_child(GTK_PANED(main_frame), FALSE);
	gtk_widget_set_size_request(candles_frame, 50, -1);


	/* Сейчас здесь просто вкладка с воркспейсом, и вкладка с кнопкой, 
	 * позже надо будет реализовать создание и удаление вкладок, 
	 * но сейчас это не в приоритете*/

	// *** Make tabs switcher ***
	GtkWidget *notebook = gtk_notebook_new();

	GtkWidget *label = gtk_label_new("main tab");
	GtkWidget *label2 = gtk_label_new("second tab");

	// GtkWidget *sidebar_frame = gtk_frame_new(NULL);

	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), main_frame, label);
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), butt2, label2);

	gtk_box_append(GTK_BOX(main_vertical_box), notebook);


	// *** Sidebar ***
	// box in sidebar
	GtkWidget *sidebar_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_frame_set_child(GTK_FRAME(sidebar_frame), sidebar_box);


	// *** Search bar ***
	GtkWidget *entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Search");

	GtkWidget *search_bar = gtk_search_bar_new();
	gtk_search_bar_connect_entry(GTK_SEARCH_BAR(search_bar), GTK_EDITABLE(GTK_ENTRY(entry)));

	gtk_box_append(GTK_BOX(sidebar_box), search_bar);
	gtk_box_append(GTK_BOX(sidebar_box), entry);


	// scrolled window for equity's list in sidebar
	GtkWidget *sidebar_scrolled = gtk_scrolled_window_new();
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sidebar_scrolled), 
	                                                   GTK_POLICY_AUTOMATIC, 
	                                                   GTK_POLICY_AUTOMATIC);
	gtk_widget_set_vexpand(sidebar_scrolled, TRUE);
	gtk_widget_set_hexpand(sidebar_scrolled, TRUE);
	gtk_box_append(GTK_BOX(sidebar_box), sidebar_scrolled);


	// eqiuty's list box
	/* в box будут помещаться фреймы в которых будут название актива, его цена, и возможно что то еще.
	 * если ничего особенного не понадобится (Ну например стрелочка зеленого или красного цвета, 
	 * обозначающая рост или падение актива) заменим на простые gtkButtons
	 */
	GtkWidget *eqiuty_list_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(sidebar_scrolled), eqiuty_list_box);

	equtys_list_refresh(eqiuty_list_box);


	// *** Candels drawing area (cairo) ***
	// structure that contains data that cairo should draw
	draw_data *draw_data = malloc(sizeof(draw_data));
	gpointer draw_data_gpointer = draw_data;


	// make drawing area widget
	GtkWidget *drawing_area = gtk_drawing_area_new();
	gtk_drawing_area_set_content_width(GTK_DRAWING_AREA(drawing_area), 500);
	gtk_drawing_area_set_content_height(GTK_DRAWING_AREA(drawing_area), 500);
	gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(drawing_area), 
	                               draw_function, 
	                               NULL,
	                               draw_data_gpointer);
	gtk_widget_set_vexpand(drawing_area, TRUE);
	gtk_widget_set_hexpand(drawing_area, TRUE);
	gtk_frame_set_child(GTK_FRAME(candles_frame), drawing_area);


	// *** Show all ***
	gtk_window_present(GTK_WINDOW(window));
}