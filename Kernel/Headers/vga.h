#ifndef VGA_H
#define VGA_H

#include <stdarg.h>
#include <stdint.h>

extern uint8_t text_color;
extern uint8_t bg_color;


typedef struct {
    const char *name;
    unsigned char value;
} Color;

unsigned char get_color(const char* name);
const char *get_color_name(unsigned char value);

int change_fg(const char* color);
int change_bg(const char* color);

void reset_colors();

void reset_fg();
void reset_bg();

void putchar(char c);

void print(const char *str);

void vprintf(const char *fmt, va_list args);
void printf(const char *fmt, ...);

void erase(int input_start);
void drawLine();
void clear_screen();

#endif