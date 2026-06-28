#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdbool.h>

extern bool caps_on;
extern bool shift_pressed;

extern bool ctrl_hold;
extern bool alt_hold;
extern bool fn_hold;


void keyboard_install();

void enable_keyboard();
void disable_keyboard();

#endif