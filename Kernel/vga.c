#include <stdarg.h>
#include <stdint.h>

#include "Headers/vga.h"
#include "Headers/cursor.h"

#include "Libraires/strcmp.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define INVALID_COLOR 0xFF

Color colors[] = {
    {"black",          0x0},
    {"blue",           0x1},
    {"green",          0x2},
    {"cyan",           0x3},
    {"red",            0x4},
    {"magenta",        0x5},
    {"brown",          0x6},
    {"light gray",     0x7},
    {"dark gray",      0x8},
    {"light blue",     0x9},
    {"light green",    0xA},
    {"light cyan",     0xB},
    {"light red",      0xC},
    {"light magenta",  0xD},
    {"yellow",         0xE},
    {"white",          0xF}
};

int color_count = sizeof(colors) / sizeof(Color);

int cursor = 0;

uint8_t text_color = 0xF;
uint8_t bg_color = 0x0;

unsigned char get_color(const char *name)
{
    for(int i = 0; i < color_count; i++)
    {
        if(strcmp(name, colors[i].name) == 0)
            return colors[i].value;
    }

    return INVALID_COLOR;
}

const char *get_color_name(unsigned char value)
{
    for(int i = 0; i < color_count; i++)
    {
        if(colors[i].value == value)
            return colors[i].name;
    }

    return "unknown";
}

void reset_colors(){
    text_color = 0xF;
    bg_color = 0x00;
}

void reset_fg(){
    text_color = 0xF;
}

void reset_bg(){
    bg_color = 0x00;
}

int change_fg(const char *arg)
{
    uint8_t fg = get_color(arg);

    if(fg == INVALID_COLOR)
        return 1;

    text_color = fg;
    return 0;
}


int change_bg(const char *arg)
{
    uint8_t bg = get_color(arg);

    if(bg == INVALID_COLOR)
        return 1;

    bg_color = bg;
    return 0;
}

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

        cursor += 5;
        update_cursor(cursor);
        return;
    }

    int offset = cursor * 2;

    vga[offset] = c;
    vga[offset + 1] = text_color | (bg_color << 4);

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



void print_int(int n)
{
    char buf[12];
    int i = 0;

    if (n == 0) {
        putchar('0');
        return;
    }

    if (n < 0) {
        putchar('-');
        n = -n;
    }

    while (n > 0) {
        buf[i++] = '0' + (n % 10);
        n /= 10;
    }

    while (i > 0) {
        putchar(buf[--i]);
    }
}

void print_uint(unsigned int n)
{
    char buf[11];
    int i = 0;

    if (n == 0) {
        putchar('0');
        return;
    }

    while (n > 0) {
        buf[i++] = '0' + (n % 10);
        n /= 10;
    }

    while (i > 0) {
        putchar(buf[--i]);
    }
}

void print_hex(unsigned long long n)
{
    char hex[] = "0123456789ABCDEF";

    if (n == 0) {
        putchar('0');
        return;
    }

    char buf[32];
    int i = 0;

    while (n > 0) {
        buf[i++] = hex[n & 0xF];
        n >>= 4;
    }

    while (i > 0) {
        putchar(buf[--i]);
    }
}

void print_double(double num)
{
    if (num < 0) {
        putchar('-');
        num = -num;
    }

    int whole = (int)num;
    print_int(whole);

    putchar('.');

    double frac = num - whole;

    for (int i = 0; i < 6; i++) {
        frac *= 10;
        int digit = (int)frac;
        putchar('0' + digit);
        frac -= digit;
    }
}


void vprintf(const char *fmt, va_list args)
{
    va_list copy;
    va_copy(copy, args);
    
    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            
            switch (*fmt) {
                
                case 'd':
                case 'i':
                print_int(va_arg(copy, int));
                break;
                
                case 'u':
                print_uint(va_arg(copy, unsigned int));
                break;
                
                case 'x':
                case 'X':
                print_hex(va_arg(copy, unsigned int));
                break;
                
                case 'c':
                putchar((char)va_arg(copy, int));
                break;
                
                case 's': {
                    char *str = va_arg(copy, char *);
                    print(str ? str : "(null)");
                    break;
                }
                
                case 'p': {
                    void *ptr = va_arg(copy, void *);
                    print("0x");
                    print_hex((uintptr_t)ptr);
                    break;
                }
                
                case 'f':
                print_double(va_arg(copy, double));
                break;
                
                case '%':
                putchar('%');
                break;
                
                default:
                putchar('%');
                putchar(*fmt);
                break;
            }
            
        } else {
            putchar(*fmt);
        }
        
        fmt++;
    }
    
    va_end(copy);
}





void printf(const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);

    vprintf(fmt, args);

    va_end(args);
}


void erase(int input_start)
{
    if (cursor <= input_start)
        return;

    cursor--;

    volatile char* vga = (volatile char*)0xB8000;

    int offset = cursor * 2;

    vga[offset] = ' ';
    vga[offset + 1] = text_color | (bg_color << 4);

    update_cursor(cursor);
}

void clear_screen() {
    volatile char* vga = (volatile char*)0xB8000;

    for (int i = 0; i < 80 * 25; i++) {
        vga[i * 2] = ' ';
        vga[i * 2 + 1] = text_color | (bg_color << 4);
    }

    cursor = 0;
}