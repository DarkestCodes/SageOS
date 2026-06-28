#include <stdbool.h>

#include "SageShell.h"
#include "command.h"

#include "../../Kernel/Syscalls/Headers/SageAPI.h"


int input_start = 0;
int cmd_index = 0;
int cmd_cursor = 0;

uint8_t real_fg_color = 0x3;
uint8_t real_bg_color = 0x0;

char command[128];


bool OS_ACTIVE = true;

void newLine();

void SAGE_START() {
    sage.display.changeFG("cyan");
    sage.display.print("\t\t\t    Sage OS\n");
    sage.display.resetFBG();
    newLine();
}

int shell_change_fg(const char *color)
{
    int result = sage.display.changeFG(color);

    if(result == 0)
        real_fg_color = sage.display.getFGcolor();

    return result;
}

int shell_change_bg(const char *color)
{
    int result = sage.display.changeBG(color);

    if(result == 0)
        real_bg_color = sage.display.getBGcolor();

    return result;
}

void redraw_command()
{
    static int previous_length = 0;

    sage.cursor.update(input_start);

    // Draw new command
    for(int i = 0; i < cmd_index; i++)
    {
        char c[2] = {command[i], 0};
        sage.display.print(c);
    }

    // Remove leftover characters
    for(int i = cmd_index; i < previous_length; i++)
    {
        sage.display.print(" ");
    }

    previous_length = cmd_index;

    // Restore editing position
    sage.cursor.update(input_start + cmd_cursor);
}

void shell_add_char(char c)
{
    sage.display.changeFG(sage.display.getColorName(real_fg_color));
    sage.display.changeBG(sage.display.getColorName(real_bg_color));

    MagicKeys keys = sageShell.keyboard.getMagicKeys();

    if(cmd_index >= 127)
        return;


    if(c >= 'a' && c <= 'z')
    {
        if(keys.shift ^ keys.caps)
            c -= 32;
    }


    for(int i = cmd_index; i > cmd_cursor; i--)
    {
        command[i] = command[i-1];
    }


    command[cmd_cursor] = c;

    cmd_index++;
    cmd_cursor++;

    redraw_command();
}

void shell_backspace()
{
    if(cmd_cursor <= 0)
        return;


    for(int i = cmd_cursor-1; i < cmd_index-1; i++)
    {
        command[i] = command[i+1];
    }


    cmd_cursor--;
    cmd_index--;

    command[cmd_index] = '\0';

    redraw_command();
}

void shell_enter() {
    real_fg_color = sage.display.getFGcolor();
    real_bg_color = sage.display.getBGcolor();
    
    sage.display.changeFG("cyan");
    sage.display.resetBG();
    sage.display.print("\n");
    
    command[cmd_index] = 0;
    
    execute(command);
    sage.display.resetFBG();
    newLine();
}


void newLine() {
    if (OS_ACTIVE){
        sage.display.print("\n!#Sage>");
        
        sage.display.changeFG(sage.display.getColorName(real_fg_color));
        sage.display.changeBG(sage.display.getColorName(real_bg_color));

        input_start = sage.cursor.getCursorIndex();
        cmd_index = 0;
        cmd_cursor = 0;
        
        command[0]= '\0';
    }
}

void shell_move_cursor(int direction)
{
    if(direction == 0) // left
    {
        if(cmd_cursor > 0)
        {
            cmd_cursor--;
            sage.cursor.update(input_start + cmd_cursor);
        }
    }


    if(direction == 1) // right
    {
        if(cmd_cursor < cmd_index)
        {
            cmd_cursor++;
            sage.cursor.update(input_start + cmd_cursor);
        }
    }
}
