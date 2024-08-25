#include <stdio.h>
#include <gtk/gtk.h>

#include "interface.h"

#include <stdio.h>

void drawing_area_on_press(GtkGestureSingle *gesture, gdouble x, gdouble y, gpointer user_data) {
	tab_context *tab = (tab_context*)user_data;
	view_pos = tab->view_pos;
	
    printf("Press: x = %f, y = %f\n", x, y);
}

void drawing_area_on_release(GtkGestureSingle *gesture, gdouble x, gdouble y, gpointer user_data) {
	tab_context *tab = (tab_context*)user_data;
	view_pos = tab->view_pos;
	
    printf("Release: x = %f, y = %f\n", x, y);
}

void on_drag_update(GtkGestureDrag *gesture, gdouble offset_x, gdouble offset_y, gpointer user_data) {
	tab_context *tab = (tab_context*)user_data;
	view_pos = tab->view_pos;
	
    printf("Drag update: offset_x = %f, offset_y = %f\n", offset_x, offset_y);
}

void on_scroll(GtkEventControllerScroll *controller, gdouble delta_x, gdouble delta_y, gpointer user_data) {
	tab_context *tab = (tab_context*)user_data;
	view_pos = tab->view_pos;
	
    printf("Scroll: delta_x = %f, delta_y = %f\n", delta_x, delta_y);
}

void undo_action_callback(GSimpleAction *action, 
		                  GVariant *parameter, 
		                  gpointer user_draw_parts_data) {
	printf("Undo button clicked\n");
}

void redo_action_callback(GSimpleAction *action, 
						  GVariant *parameter, 
						  gpointer user_draw_parts_data) {
	printf("Redo button clicked\n");
}

/*
 * filles assets_list_box
 */
void equtys_list_refresh(GtkWidget *box) {
	// добавить когда разберемся с API
}

// Holds pointers to the popover and its results box for use in the search callback.
typedef struct {
    GtkWidget *popover;
    GtkWidget *results_box;
} search_cb_data;

void on_search_activated(GtkEntry *entry, gpointer user_data) {

	search_cb_data *data = (search_cb_data *)user_data;

	GtkWidget *popover = data->popover;

	GtkWidget* results_box = data->results_box;

	// get text buffer from entry
	GtkEntryBuffer *buffer = gtk_entry_buffer_new(NULL, -1);
    buffer =  gtk_entry_get_buffer(entry);

    // if there is some text in the search bar
    if (g_strcmp0(gtk_entry_buffer_get_text(buffer), "") != 0) {
    	// show the popover
		gtk_widget_set_visible(popover, true);

		// api call for getting search data

		// json into array of structures that have info about matches to show

		// make widgets for matches
    }

}


/*
 * window
 *    -main vertical box
 * 	    - toolbar
 * 	    - tabs
 * 	    - workspace
 * 	       - assets
 * 	       - candles
 * 
 * Окно с инструментами потом добавить либо как отдельные окно, 
 * либо самостоятельно отрисовывать с помошью cairo
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
	gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Search...");

	// popover that will show search results
	GtkWidget *search_popover = gtk_popover_new();
	gtk_popover_set_has_arrow(GTK_POPOVER(search_popover), FALSE);
	gtk_popover_set_position(GTK_POPOVER(search_popover), GTK_POS_BOTTOM);

	// 1st box in the popover that has a label and scrolled window
	GtkWidget *search_popover_label = gtk_label_new("Search results:");
	GtkWidget *search_popover_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_box_append(GTK_BOX(search_popover_box), search_popover_label);
	gtk_popover_set_child(GTK_POPOVER(search_popover), search_popover_box);

	// scrolled window
	GtkWidget *search_popover_scrolled = gtk_scrolled_window_new();
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(search_popover_scrolled), 
	                               GTK_POLICY_AUTOMATIC, 
	                               GTK_POLICY_AUTOMATIC);

	// 2nd box in scrolled window that will have search results
	GtkWidget *search_results_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(search_popover_scrolled), search_results_box);
	gtk_box_append(GTK_BOX(search_popover_box), search_popover_scrolled);

	// pin popover to search bar
	gtk_widget_set_parent(search_popover, GTK_WIDGET(entry));

	// Создаем и инициализируем структуру данных
	search_cb_data *search_data = g_new(search_cb_data, 1);
	search_data->popover = search_popover;
	search_data->results_box = search_results_box;

	// Подключаем сигнал activate к обработчику, передавая структуру данных
	g_signal_connect(entry, "activate", G_CALLBACK(on_search_activated), search_data);

	// Остальная часть кода
	GtkWidget *search_bar = gtk_search_bar_new();
	gtk_search_bar_connect_entry(GTK_SEARCH_BAR(search_bar), GTK_EDITABLE(GTK_ENTRY(entry)));

	gtk_box_append(GTK_BOX(sidebar_box), search_bar);
	gtk_box_append(GTK_BOX(sidebar_box), entry);

	// scrolled window for assets list in sidebar
	GtkWidget *sidebar_scrolled = gtk_scrolled_window_new();
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sidebar_scrolled), 
	                                                   GTK_POLICY_AUTOMATIC, 
	                                                   GTK_POLICY_AUTOMATIC);
	gtk_widget_set_vexpand(sidebar_scrolled, TRUE);
	gtk_widget_set_hexpand(sidebar_scrolled, TRUE);
	gtk_box_append(GTK_BOX(sidebar_box), sidebar_scrolled);


	// attets list box
	/* в box будут помещаться фреймы в которых будут название актива, его цена, 
	 * и возможно что то еще.
	 * если ничего особенного не понадобится (Ну например стрелочка зеленого или 
	 * красного цвета, обозначающая рост или падение актива) заменим на простые gtkButtons
	 */
	GtkWidget *assets_list_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(sidebar_scrolled), assets_list_box);

	equtys_list_refresh(assets_list_box);



	// *** candles drawing area (cairo) ***

	/* Важно: эта структура это просто временное решение. 
	 * Позже, когда уже реализуеим работу с вкладками, 
	 * надо добавить возможность использовать разные вкладки*/
	tab_context *tab_context = malloc( sizeof(tab_context) );

	// init tab context
	tab_context->current_asset = "\0";
	tab_context->view_pos = (position){0, 0};

	gpointer tab_context_gpointer = tab_context;

	// make drawing area widget
	GtkWidget *drawing_area = gtk_drawing_area_new();
	gtk_drawing_area_set_content_width(GTK_DRAWING_AREA(drawing_area), 500);
	gtk_drawing_area_set_content_height(GTK_DRAWING_AREA(drawing_area), 500);
	gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(drawing_area), 
	                               draw_function, 
	                               NULL,
	                               tab_context_gpointer);
	gtk_widget_set_vexpand(drawing_area, TRUE);
	gtk_widget_set_hexpand(drawing_area, TRUE);
	gtk_frame_set_child(GTK_FRAME(candles_frame), drawing_area);



	// *** Gestures ***
	GtkGesture *click_gesture;
	GtkGesture *drag_gesture;

	// press
	click_gesture = gtk_gesture_click_new ();
	gtk_gesture_single_set_button (GTK_GESTURE_SINGLE (click_gesture), GDK_BUTTON_PRIMARY);
	g_signal_connect (click_gesture, "pressed", G_CALLBACK (drawing_area_on_press), tab_context_gpointer);
	g_signal_connect (click_gesture, "released", G_CALLBACK (drawing_area_on_release), tab_context_gpointer);
	gtk_widget_add_controller (drawing_area, GTK_EVENT_CONTROLLER (click_gesture));

	// drag
	drag_gesture = gtk_gesture_drag_new ();
	g_signal_connect (drag_gesture, "drag-update", G_CALLBACK (on_drag_update), tab_context_gpointer);
	gtk_widget_add_controller (drawing_area, GTK_EVENT_CONTROLLER (drag_gesture));

	// scroll
	GtkEventController *scroll_controller = gtk_event_controller_scroll_new(GTK_EVENT_CONTROLLER_SCROLL_VERTICAL);
	g_signal_connect(scroll_controller, "scroll", G_CALLBACK(on_scroll), tab_context_gpointer);
	gtk_widget_add_controller(drawing_area, scroll_controller);

	// // mouse motion callback
	// GtkEventController *mouse_controller = gtk_event_controller_motion_new();
	// g_signal_connect(mouse_controller, "motion", G_CALLBACK(on_motion_in_draw_area), pointer_pos);
	// gtk_widget_add_controller(drawing_area, mouse_controller);


	// *** Show all ***
	gtk_window_present(GTK_WINDOW(window));

}