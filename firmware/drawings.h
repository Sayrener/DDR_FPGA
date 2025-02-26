#pragma once

// SCREEN RESOLUTION
#define SCREEN_WIDTH            800
#define SCREEN_HEIGHT           600

// SQUARE DIMENSIONS
#define SQUARE_SIZE             40
#define SQUARE_BORDER_THICKNESS 3

// ARROW DIMENSIONS
#define RECTANGLE_HEIGHT        16
#define RECTANGLE_WIDTH         8
#define TRIANGLE_HEIGHT         10

// Définition des directions comme énumération
typedef enum {
    UP      = 0,
    DOWN    = 1,
    LEFT    = 2,
    RIGHT   = 3
} Direction;

void clear_screen(unsigned char* buffer_base);

void draw_square(unsigned char* buffer_base, int x, int y, unsigned char color);

void draw_arrow(unsigned char* buffer_base, int x, int y, unsigned char color, Direction direction);

