#ifndef VGA_H
#define VGA_H

extern int cursor;

void putchar(char c);
void print(const char* str);

void drawLine();
void erase();
void clear_screen();

#endif