#pragma once

#include <stdint.h>
#include "ddr.h"
#include "drawings.h"

// Définition de la structure
typedef struct {
    uint32_t time;
    Direction direction;
} ArrowEvent;

ArrowEvent getArrowEvents(int currentTime);

int numEvents(void);

extern ArrowEvent arrowEvents[];