#ifndef INTERFACE_H
#define INTERFACE_H

#include "drawing.h"

void activate(GtkApplication *app, gpointer user_data);

typedef struct {
	/* first dimention array elements are a closed shape made up of connected points.
	 One element represents a single component in the drawing.
	second dimention is a points of a component */
	position** points;
	int *points_num;
	int elements_num;

	color *elements_colors;
}draw_data;

#endif