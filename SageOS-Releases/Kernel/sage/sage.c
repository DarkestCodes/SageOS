#include <stdbool.h>

#include "sage.h"
#include "command.h"

#include "../Headers/vga.h"
#include "../Headers/cursor.h"

#include "../Drivers/keyboard.h"


int input_start = 0;
int cmd_index = 0;
int cmd_cursor = 0;

char command[128];

bool OS_ACTIVE = true;

void newLine();


void SAGE_START() {
    print("\t\t\t    Sage OS\n");

    newLine();
}

void shell_add_char(char c) {
    if (cmd_index >= 127) 
        return;
    if (c >= 'a' && c <= 'z') {

        if (shift_pressed ^ caps_on) {
            c -= 32; // make upper
        }

    }
    for (int i = cmd_index; i > cmd_cursor; i--) {
        command[i] = command[i - 1];
    }

    command[cmd_cursor] = c;
    
    cmd_cursor++;
    cmd_index++;
    char str[2] = {c, 0};
    print(str);
}

void shell_backspace() {
    if (cmd_cursor <= 0) 
        return;
    
    for (int i = cmd_cursor - 1; i < cmd_index - 1; i++) {
        command[i] = command[i+1];
    }

    cmd_cursor--;
    cmd_index--;
    command[cmd_index] = 0;

    erase();
}

void shell_enter() {
    print("\n");
    
    command[cmd_index] = 0;

    execute(command);
    newLine();
}
    

void newLine() {
    if (OS_ACTIVE){
        print("\n!#Sage>");
        input_start = cursor;
        cmd_index = 0;
        cmd_cursor = 0;

        command[0]= '\0';
    }
}

void shell_move_cursor(int direction) {
    // LEFT
    if (direction == 0) {
        if (cursor > input_start) {
            cursor--;
            cmd_cursor--;
            update_cursor(cursor);
        }
        return;
    }

    // RIGHT
    if (direction == 1) {
        if (cursor < input_start + cmd_index) {
            cursor++;
            cmd_cursor++;
            update_cursor(cursor);
        }
        return;
    }
}
