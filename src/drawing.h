#ifndef DRAWING_H
#define DRAWING_H

typedef struct {
	int x, y;	
}position;

typedef struct {
	int r, g, b;	
}color;

typedef struct {
    position position;
    int width, height;
}rectangle;

typedef struct {
    rectangle *candles;
    color *candles_colors;
    int candles_num;
}draw_data;


void draw_function(GtkDrawingArea *area, 
                   cairo_t *cr, 
                   int width, 
                   int height, 
                   gpointer user_data);

#endif
