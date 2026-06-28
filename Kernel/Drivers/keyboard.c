#include "../Headers/irq.h"
#include "../Headers/io.h"

#include "keyboard.h"

#include <stdint.h>
#include <stdbool.h>

#include "../Syscalls/Headers/SageAPI.h"

bool caps_on = false;
bool shift_pressed = false;

bool ctrl_hold = false;
bool alt_hold = false;
bool fn_hold = false;


static char keyboard_map[128] =
{
    0,
    27,
    '1','2','3','4','5','6','7','8','9','0',
    '-','=',
    '\b',
    '\t',
    'q','w','e','r','t','y','u','i','o','p',
    '[',']',
    '\n',
    0,
    'a','s','d','f','g','h','j','k','l',
    ';','\'','`',
    0,
    '\\',
    'z','x','c','v','b','n','m',
    ',','.','/',
    0,
    '*',
    0,
    ' ',
};


static char keyboard_shift_map[128] =
{
    0,
    27,
    '!', '@', '#', '$', '%', '^', '&', '*', '(', ')',
    '_', '+',
    '\b',
    '\t',
    'Q','W','E','R','T','Y','U','I','O','P',
    '{','}',
    '\n',
    0,
    'A','S','D','F','G','H','J','K','L',
    ':','"','~',
    0,
    '|',
    'Z','X','C','V','B','N','M',
    '<','>','?',
    0,
    '*',
    0,
    ' ',
};

static void keyboard_handler(registers_t* regs) {
    (void)regs;
    
    uint8_t scancode = inb(0x60);
    uint8_t key = scancode & 0x7F;
    bool released = scancode & 0x80;
    
    // if key released
    if (released){
        switch (key) {
            case 0x2A: // Lshift    
            case 0x36: // Rshift  
            shift_pressed = false;    
            break;
            
            case 0x1D: // Ctrl
            ctrl_hold = false;
            break;
            
            case 0x38: // Alt
            alt_hold = false;
            break;
            
            
        }
        return;
    }


    switch (key) {
        
        case 0x48: // up key
            return;
        
        case 0x50: // down key
            return;

        case 0x4B: // left
            sageShell.keyboard.shell_move_cursor(0);
            return;

        case 0x4D: // right
            sageShell.keyboard.shell_move_cursor(1);
            return;

        case 0x2A: // Lshift
        case 0x36: // Rshift
            shift_pressed = true;
            return;
        
        case 0x1D: // Ctrl
            ctrl_hold = true;
            return;
        
        case 0x38: // Alt
            alt_hold = true;
            return;
        
        case 0x3A: // Caps
            caps_on = !caps_on;
            return;
    }

    char c;

    if (shift_pressed)
        c = keyboard_shift_map[key];
    else
        c = keyboard_map[key];
    
    if (caps_on) {
        if (c >= 'a' && c <= 'z')
            c -= 32; // lowercase -> uppercase

        else if (c >= 'A' && c <= 'Z')
            c += 32; // uppercase -> lowercase
    }

    if (c == 0) {
        return;
    }

    if (c == '\b'){
        sageShell.keyboard.shell_backspace();
        return;
    }

    if (c == '\n') {
        sageShell.keyboard.shell_enter();
        return;
    }

    if (c == '\t') {
        sageShell.keyboard.shell_add_char('\t');
        return;
    }

    sageShell.keyboard.shell_add_char(c);
}

void keyboard_install() {
    irq_register_handler(1, keyboard_handler);
}

void disable_keyboard() {
    outb(0x64, 0xAD);
    __asm__ volatile ("cli");
}

void enable_keyboard() {
    __asm__ volatile ("sti");
}