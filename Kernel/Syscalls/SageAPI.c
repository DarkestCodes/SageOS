#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>

#include "Headers/SageAPI.h"

#include "../Headers/vga.h"
#include "../Headers/cursor.h"

#include "../Drivers/keyboard.h"

#include "../Libraires/memory.h"

#include "../Power/power.h"

#include "../../User/SageShell/SageShell.h"

/*                  Power                    */

void power_shutdown(){
    shutdown();
}

void power_reboot() {
    reboot();
}


/*                  Memory                   */

void *memory_malloc(size_t size) {
    return kmalloc(size);
}

void memory_free(void *ptr) {
    (void)kfree(ptr);
}




/*                  VGA                      */

int vga_fg_color(const char *color){
    return change_fg(color);
}

int vga_bg_color(const char *color){
    return change_bg(color);
}

void vga_reset_FBG(){
    reset_colors();
}

void vga_reset_fg(){
    reset_fg();
}

void vga_reset_bg(){
    reset_bg();
}

uint8_t vga_return_fg(){
    return text_color;
}

uint8_t vga_return_bg(){
    return bg_color;
}

const char *vga_get_color_name(unsigned char value) { 
    return get_color_name(value);
}

unsigned char vga_get_color_hex(const char* name) {
    return get_color(name);
}

void vga_erase(int input_start){
    erase(input_start);
}

void vga_print(const char *str){
    print(str);
}

void vga_printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

void vga_drawLine() {
    drawLine();
}

void vga_clear_screen() {
    clear_screen();
}

/*                  Cursor                  */

void vga_cursor_update(int pos){
    update_cursor(pos);
}

int vga_getCursorIndex() {
    return cursor;
}

SageAPI sage = {
// power
    .power = {
        .shutdown = power_shutdown,
        .reboot = power_reboot,
        
    },
    
// memory
    .memory = {
        .malloc = memory_malloc,
        .free = memory_free,
    },

// VGA
    .display = {
        .erase = vga_erase,
        .print = vga_print,
        .printf = vga_printf,
        .drawLine = vga_drawLine,
        .clean = vga_clear_screen,
        .changeFG = vga_fg_color,
        .changeBG = vga_bg_color,
        .resetFBG = vga_reset_FBG,
        .resetFG = vga_reset_fg,
        .resetBG = vga_reset_bg,
        .getFGcolor = vga_return_fg,
        .getBGcolor = vga_return_bg,

        .getColorName = vga_get_color_name,
        .getColorHex = vga_get_color_hex,
    },
    
    // Cursor
    .cursor = {
        .update = vga_cursor_update,
        .getCursorIndex = vga_getCursorIndex,
    }
};



// keyboard


void SageShell_add_char(char c){
    shell_add_char(c);
}

void SageShell_backspace(){
    shell_backspace();
}

void SageShell_enter(){
    shell_enter();
}

void SageShell_move(int direction){
    shell_move_cursor(direction);
}



MagicKeys SageShell_getMagicKeys()
{
    MagicKeys keys = {
        .caps  = caps_on,
        .fn    = fn_hold,
        .shift = shift_pressed,
        .alt   = alt_hold,
        .ctrl  = ctrl_hold
    };

    return keys;
}


SageShellAPI sageShell = {
    .keyboard = {
        .shell_add_char = SageShell_add_char,
        .shell_backspace = SageShell_backspace,
        .shell_enter = SageShell_enter,
        .shell_move_cursor = SageShell_move,
        .getMagicKeys = SageShell_getMagicKeys,
    },
};