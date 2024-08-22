#include <gtk/gtk.h>

#include "drawing.h"
#include "interface.h"

void draw_function(GtkDrawingArea *area, 
                   cairo_t *cr, 
                   int width, 
                   int height, 
                   gpointer user_data) {
	draw_data *data = (draw_data*)user_data;

	// background
	cairo_set_source_rgb(cr, 0.15, 0.15, 0.15);
	cairo_paint(cr);
}
