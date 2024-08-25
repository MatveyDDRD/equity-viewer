#ifndef INTERFACE_H
#define INTERFACE_H

#include "drawing.h"

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
		printf("allocation error in function __func__\n");                \
		exit(EXIT_FAILURE);												  \
	}																	  \
	ALLOC_CHECK(pointer);												  \



typedef struct{
	char* current_asset;
	position view_pos;
}tab_context;

void activate(GtkApplication *app, gpointer user_data);

#endif