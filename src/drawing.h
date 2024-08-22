#ifndef DRAWING_H
#define DRAWING_H

typedef struct {
	int x, y;	
}position;

typedef struct {
	int r, g, b;	
}color;

void draw_function(GtkDrawingArea *area, 
                   cairo_t *cr, 
                   int width, 
                   int height, 
                   gpointer user_data);

#endif
