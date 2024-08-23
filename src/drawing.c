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

    cairo_set_source_rgb(cr, 0.514, 0.302, 1.0);

    cairo_rectangle(cr, 50, 50, 100, 100);
    cairo_fill(cr);

}
