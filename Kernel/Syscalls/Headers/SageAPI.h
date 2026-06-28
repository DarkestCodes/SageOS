#ifndef SAGEAPI_H
#define SAGEAPI_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

// Magic Keys
typedef struct {
    bool caps;
    bool fn;
    bool shift;
    bool alt;
    bool ctrl;
} MagicKeys;


// Memory
typedef struct {
    void *(*malloc)(size_t);
    void (*free)(void *);
} MemoryAPI;


// Power
typedef struct {
    void (*shutdown)();
    void (*reboot)();
} PowerAPI;

// VGA
typedef struct {
    void (*erase)(int);
    void (*print)(const char *);
    void (*printf)(const char *, ...);
    void (*drawLine)();
    void (*clean)();
    void (*resetFBG)();
    void (*resetFG)();
    void (*resetBG)();
    
    int (*changeFG)(const char *);
    int (*changeBG)(const char *);
    
    uint8_t (*getFGcolor)();
    uint8_t (*getBGcolor)();

    const char *(*getColorName)(unsigned char);
    unsigned char (*getColorHex)(const char *);
    
} DisplayAPI;

// Cursor

typedef struct {
    void (*update)(int);
    int (*getCursorIndex)();
} Cursor;



typedef struct {
    MemoryAPI memory;
    PowerAPI power;
    DisplayAPI display;
    Cursor cursor;

} SageAPI;


// Sage Shell API





typedef struct {
    void (*shell_backspace)();
    void (*shell_enter)();
    void (*shell_add_char)(char);
    void (*shell_move_cursor)(int);
    
    MagicKeys (*getMagicKeys)();
} Keyboard;




typedef struct 
{
    Keyboard keyboard;
} SageShellAPI;

extern SageAPI sage;
extern SageShellAPI sageShell;

#endif