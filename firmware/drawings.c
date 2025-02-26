#include "drawings.h"


// Fonction pour effacer l'écran
void clear_screen(unsigned char* buffer_base) 
{
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) 
    {
        buffer_base[i] = 0x00; // Noir
    }
}

// CARRE
void draw_square(unsigned char* buffer_base, int x, int y, unsigned char color)
{
    // Calculer les coordonnées des bords du carré
    int half_size = SQUARE_SIZE / 2;

    for (int i = -half_size; i < half_size + 1; i++)
    {
        for (int t = 0; t < SQUARE_BORDER_THICKNESS; t++)
        {
            // Tracer le côté supérieur (ligne horizontale)
            buffer_base[(y + i) * SCREEN_WIDTH + (x - half_size + t)] = color;

            // Tracer le côté inférieur (ligne horizontale)
            buffer_base[(y + i) * SCREEN_WIDTH + (x + half_size - t)] = color;

            // Tracer le côté gauche (ligne verticale)
            buffer_base[(y - half_size + t) * SCREEN_WIDTH + (x + i)] = color;

            // Tracer le côté droit (ligne verticale)
            buffer_base[(y + half_size - t) * SCREEN_WIDTH + (x + i)] = color;
        }
    }
}

// FLECHES
void draw_arrow(unsigned char* buffer_base, int x, int y, unsigned char color, Direction direction)
{
    if(direction == UP)
    {
        // Dessiner le corps de la flèche (rectangle)
        for (int i = 0; i < RECTANGLE_HEIGHT; i++)
        {
            for (int j = 0; j < RECTANGLE_WIDTH; j++)
            {
                buffer_base[(y + i) * SCREEN_WIDTH + (x + j)] = color;
            }
        }

        // Dessiner la pointe de la flèche (triangle)
        for (int i = 0; i < TRIANGLE_HEIGHT; i++)
        {
            for (int j = -i; j <= i; j++)
            {
                buffer_base[(y - TRIANGLE_HEIGHT + i) * SCREEN_WIDTH + (x + RECTANGLE_WIDTH / 2 + j)] = color;
            }
        }
    }

    if(direction == DOWN)
    {
        // Dessiner le corps de la flèche (rectangle)
        for (int i = 0; i < RECTANGLE_HEIGHT; i++)
        {
            for (int j = 0; j < RECTANGLE_WIDTH; j++)
            {
                buffer_base[(y + i) * SCREEN_WIDTH + (x + j)] = color;
            }
        }

        // Dessiner la pointe de la flèche (triangle)
        for (int i = 0; i < TRIANGLE_HEIGHT; i++)
        {
            for (int j = -(TRIANGLE_HEIGHT - i); j <= (TRIANGLE_HEIGHT - i); j++)
            {
                buffer_base[(y + RECTANGLE_HEIGHT + i) * SCREEN_WIDTH + (x + RECTANGLE_WIDTH / 2 + j)] = color;
            }
        }
    }

    if(direction == LEFT)
    {
        // Dessiner le corps de la flèche (rectangle horizontal)
        for (int i = 0; i < RECTANGLE_WIDTH; i++)
        {
            for (int j = 0; j < RECTANGLE_HEIGHT; j++)
            {
                buffer_base[(y + i) * SCREEN_WIDTH + (x + j)] = color;
            }
        }

        // Dessiner la pointe de la flèche (triangle pointant vers la gauche)
        for (int i = 0; i < TRIANGLE_HEIGHT; i++) 
        {
            for (int j = 0; j <= i; j++) 
            {
                buffer_base[(y - 6 + i) * SCREEN_WIDTH + (x - i + j)] = color;
                buffer_base[(y + 12 - i) * SCREEN_WIDTH + (x - i + j)] = color;
            }
        }
    }

    if(direction == RIGHT)
    {
        // Dessiner le corps de la flèche (rectangle horizontal)
        for (int i = 0; i < RECTANGLE_WIDTH; i++)
        {
            for (int j = 0; j < RECTANGLE_HEIGHT; j++)
            {
                buffer_base[(y + i) * SCREEN_WIDTH + (x + j)] = color;
            }
        }

        // Dessiner la pointe de la flèche (triangle pointant vers la droite)
        for (int i = 0; i < TRIANGLE_HEIGHT; i++) 
        {
            for (int j = 0; j <= i; j++) 
            {
                buffer_base[(y - 6 + i) * SCREEN_WIDTH + (x + i - (j - RECTANGLE_HEIGHT))] = color;
                buffer_base[(y + 12 - i) * SCREEN_WIDTH + (x + i - (j - RECTANGLE_HEIGHT))] = color;
            }
        }
    }
    
}