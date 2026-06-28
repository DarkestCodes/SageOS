#ifndef SAGE_H
#define SAGE_H

#include <stdbool.h>

extern int input_start;
extern int cmd_index;

extern char command[128];

extern bool OS_ACTIVE;

void SAGE_START();

void shell_add_char(char c);
void shell_backspace();
void shell_enter();

void shell_move_cursor(int direction);


#endif