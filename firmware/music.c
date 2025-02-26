#include <stdio.h>

#include "music.h"

// Tableau des événements
ArrowEvent arrowEvents[] = {
    {0.93, DOWN},
    {1.39, LEFT},
    {2.32, DOWN},
    {3.25, DOWN},
    {3.74, RIGHT},
    {4.23, UP},
    {4.71, RIGHT},
    {5.20, LEFT},
    {6.25, LEFT},
    {7.05, DOWN},
    {7.85, UP},
    {8.65, RIGHT},
    {10.00, LEFT},
    {10.00, DOWN},
    {10.00, UP},
    {10.00, RIGHT}
};

int numEvents(void)
{
    return sizeof(arrowEvents) / sizeof(arrowEvents[0]);
}

ArrowEvent getArrowEvents(int currentTime)
{
    return arrowEvents[currentTime]; 
}