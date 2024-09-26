#include <gtk/gtk.h>
#include <stdio.h>
#include <time.h>

#include "drawing.h"
#include "interface.h"
#include "api_client.h"

// позже это надо реализовать через настройки
#define CANDLE_WIDTH_DEFAULT 6 //  при zoom = 0
#define CANDLE_DISTANCE_DEFAULT 10 //  при zoom = 0
#define CANDLE_COLOR_DEFAULT_UP ((color){0, 255, 0})
#define CANDLE_COLOR_DEFAULT_DOWN ((color){255, 0, 0})
#define CANDLE_LINE_COLOR_DEFAULT ((color){150, 150, 150})

draw_data prepare_draw_data(position view_pos, bar *candles, int candles_num, position window_size)
{
	draw_data self;

	self.candles_num = candles_num;
	self.candles = malloc( sizeof(rectangle) * candles_num);
	self.candles_colors = malloc( sizeof(color) * candles_num );

	for (int i = 0; i < candles_num; ++i)
	{
		// rectangle transform
		self.candles[i].position.x = CANDLE_DISTANCE_DEFAULT * i;
		self.candles[i].width = CANDLE_WIDTH_DEFAULT;

		self.candles[i].position.y = window_size.y / 2;
		self.candles[i].height = (rand() % 100) - 50;

		// add color to candles
		if(candles[i].open > candles[i].close) {
			self.candles_colors[i] = CANDLE_COLOR_DEFAULT_UP;
		} 
        else {
			self.candles_colors[i] = CANDLE_COLOR_DEFAULT_DOWN;
		}
	}

	return self;
}

// это временная функция которая поможет в отладке
void print_draw_data(const draw_data *data) {
    printf("Number of candles: %d\n", data->candles_num);

    for (int i = 0; i < data->candles_num; i++) {
        rectangle *candle = &data->candles[i];
        color *candle_color = &data->candles_colors[i];

        // printf("Candle %d:\n", i + 1);
        // printf("Position: (%d, %d)\n", candle->position.x, candle->position.y);
        // printf("Size: %d x %d\n", candle->width, candle->height);
        // printf("Color: (R: %d, G: %d, B: %d)\n", candle_color->r, candle_color->g, candle_color->b);
    }
}

// временная функция которая создает массив bars с рандомными значениями, для отладки
bar* create_bars() {
    bar* array = (bar*)malloc(20 * sizeof(bar));
    srand(time(NULL));

    for (int i = 0; i < 20; i++) {
        array[i].open = (float)(rand() % 100);
        array[i].high = (float)(rand() % 100);
        array[i].low = (float)(rand() % 100);
        array[i].close = (float)(rand() % 100);
        array[i].volume = 0;
        
        printf("%.2f\n", array[i].open);
    }

    return array;
}

void draw_function(GtkDrawingArea *area,
                   cairo_t *cr,
                   int width,
                   int height,
                   gpointer user_data) {
    // tab_context *tab = (tab_context*)user_data;

    bar* bars = create_bars();

    position pos = (position){0, 0};

    position window_size = (position){width, height};
    draw_data data = prepare_draw_data(pos, bars, 20, window_size);

    print_draw_data(&data);

    // for (int i = 0; i < 20; i++) {
    //     printf("Bar %d:\n", i);
    //     printf("  open: %.2f\n", bars[i].open);
    //     printf("  high: %.2f\n", bars[i].high);
    //     printf("  low: %.2f\n", bars[i].low);
    //     printf("  close: %.2f\n", bars[i].close);
    //     printf("  volume: %.2f\n", bars[i].volume);
    // }

    // Background
    cairo_set_source_rgb(cr, 0.15, 0.15, 0.15);
    cairo_paint(cr);

    // Set the color for the candles
    for (int i = 0; i < data.candles_num; i++) {
        rectangle *candle = &data.candles[i];
        color candle_color = data.candles_colors[i];

        // Set candle color
        cairo_set_source_rgb(cr, candle_color.r / 255.0, candle_color.g / 255.0, candle_color.b / 255.0);

        // Draw the candle
        cairo_rectangle(cr, candle->position.x, candle->position.y, candle->width, candle->height);
        cairo_fill(cr);
    }
}
