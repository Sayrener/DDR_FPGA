#pragma once

#include "drawings.h"

// BUTTONS
#define BUTTON_UP               0x10
#define BUTTON_DOWN             0x02
#define BUTTON_RIGHT            0x08
#define BUTTON_LEFT             0x04
#define BUTTON_CENTER           0x01
#define BUTTON_NONE             0x00
#define BUTTON_ALL_BUT_MID      0x1E

void ddr(void);

void timer0_init(void);

void timer0_isr(void);

void setup_timer0(void);

typedef struct {
    int x;
    int y;
    Direction direction;
} ActiveArrow;



