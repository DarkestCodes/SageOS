#include <stdint.h>

#include "command.h"
#include "SageShell.h"


#include "../../Kernel/Syscalls/Headers/SageAPI.h"

static char* trim_left(char* str) {
    while (*str == ' ' || *str == '\t')
        str++;
    return str;
}

static char* trim_right(char* str) {
    char* end = str;

    while (*end)
        end++;

    end--;

    while (end > str && (*end == ' ' || *end == '\t'))
        end--;

    *(end + 1) = '\0';

    return str;
}

void help(char *func_name){
    sage.display.printf("\nHelp? Incorrect usage for '%s'! Try ' help %s '\n", func_name, func_name);
}

void c_info() {
    sage.display.changeFG("magenta");
    sage.display.print("\n");
    sage.display.drawLine();
    sage.display.print("SageOS v1.0\tKernel v1.0\tSage $hell v1.0\n");
    sage.display.drawLine();
    sage.display.changeFG("yellow");
    sage.display.print("Arch: 32-bit x86\n");
    sage.display.drawLine();
    sage.display.changeFG("green");
    sage.display.print("Developer       DarkestCodes\n");
    sage.display.print("Github\tTiktok\n");
    sage.display.print("@darkestcodes   @darkestcodes\n");
    sage.display.drawLine();
    sage.display.resetFG();
}

void show_commands() {
    sage.display.print("\n");
    sage.display.print("     |-| Help Menu |+|\n");
    sage.display.print("         - help\n");
    sage.display.print("         - clear    | clears the screen\n");
    sage.display.print("         - echo     | echos words back\n");
    sage.display.print("         - info     | shows system info\n");
    sage.display.print("         - color    | changes shell color\n");
    sage.display.print("     [+] Power\n");
    sage.display.print("         - shutdown | shuts down your device\n");
    sage.display.print("         - reboot   | reboots your device\n");
}

void execute(char* command) {
    command = trim_left(command);
    command = trim_right(command);

    if (command[0] == 0)
        return;

        // for now only change when filesystem is integrated!
    if (strncmp(command, "help", 4) == 0) {
        memmove(command,0,5);

        if (strcmp(command, "color") == 0){
            sage.display.print("\tcolor foreground 'brown/black/etc'\n\tcolor background 'brown/black/etc'");
            return;
            
        } else {
            show_commands();
            return;
        }
    }

    if (strcmp(command, "clear") == 0) {
        sage.display.clean();
        return;
    }

    if (strncmp(command, "echo", 4) == 0) {
        sage.display.print(command + 5);
        sage.display.print("\n");
        return;
    }

    if (strcmp(command, "info") == 0){
        c_info();
        return;
    }

    /*                      Power                           */
    if (strcmp(command, "shutdown") == 0) {
        sage.power.shutdown();
        return;
    }

    if (strcmp(command, "reboot") == 0) {
        sage.power.reboot();
        return;
    }

    /*                      Display                         */
    if(strncmp(command, "color", 5) == 0) {
        memmove(command, 0, 6);
        if (strncmp(command, "foreground ", 11) == 0) {
            memmove(command, 0, 11);
            if (shell_change_fg(command) == 0) return;
            sage.display.print("\nInvalid color!\n");
            return;
        } else if (strncmp(command, "background ", 11) == 0) {
            memmove(command, 0, 11);
            if (shell_change_bg(command) == 0) return;
            sage.display.print("\nInvalid color!\n");
            return;
        }
        help("color");
        return;
    }

    sage.display.changeFG("yellow");
    sage.display.print("\nUnknown command!\n");
    sage.display.resetFG();
}
