#include "Headers/vga.h"
#include "Headers/cursor.h"

#include "sage/sage.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

int cursor = 0;

void drawLine(){
    for (int i = 0; i < 80; i++) {
        putchar('-');
    }
}

void putchar(char c) {
    volatile char* vga = (volatile char*)0xB8000;

    if (c == '\n') {
        cursor = (cursor / VGA_WIDTH + 1) * VGA_WIDTH;
        update_cursor(cursor);
        return;
    } else if (c == '\t') {
        for (int i = 0; i < 5; i++) {
            putchar(' ');
        }
        cursor = cursor + 5;
        update_cursor(cursor);
        return;
    }

    int offset = cursor * 2;

    vga[offset] = c;
    vga[offset + 1] = 0x0F;

    cursor++;

    if (cursor >= VGA_WIDTH * VGA_HEIGHT)
        cursor = 0;

    update_cursor(cursor);
}

void print(const char* str) {
    while (*str) {
        putchar(*str);
        str++;
    }
}

void erase()
{
    if (cursor <= input_start)
        return;

    cursor--;

    volatile char* vga = (volatile char*)0xB8000;

    int offset = cursor * 2;

    vga[offset] = ' ';
    vga[offset + 1] = 0x0F;

    update_cursor(cursor);
}

void clear_screen() {
    volatile char* vga = (volatile char*)0xB8000;

    for (int i = 0; i < 80 * 25; i++) {
        vga[i * 2] = ' ';
        vga[i * 2 + 1] = 0x0F;
    }

    cursor = 0;
}