#include "command.h"

#include "power/power.h"

#include "../Headers/vga.h"

#include "../Libraires/strcmp.h"

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

void c_info() {
    putchar('\n');
    drawLine();
    print("SageOS v1.0\tKernel v1.0\tSage $hell v1.0\n");
    drawLine();
    print("Mode: 32-bit x86\n");
    drawLine();
    print("Developer DarkestCodes\n");
    print("Github\tTiktok\n");
    print("@darkestcodes   @darkestcodes\n");
    drawLine();
}

void show_commands() {
    putchar('\n');
    print("     |-| Help Menu |+|\n");
    print("         - help\n");
    print("         - clear    | clears the screen\n");
    print("         - echo     | echos words back\n");
    print("         - info     | shows system info\n");
    print("     [+] Power\n");
    print("         - shutdown | shuts down your device\n");
    print("         - reboot   | reboots your device\n");
}

void execute(char* command) {
    command = trim_left(command);
    command = trim_right(command);

    if (command[0] == 0)
        return;
    // for now only change when filesystem is integrated!
    if (strcmp(command, "help") == 0) {
        show_commands();
        return;
    }
    if (strcmp(command, "clear") == 0) {
        clear_screen();
        return;
    }

    if (strncmp(command, "echo ", 5) == 0) {
        print(command + 5);
        print("\n");
        return;
    }

    if (strcmp(command, "info") == 0){
        c_info();
        return;
    }

    if (strcmp(command, "shutdown") == 0) {
        shutdown();
        return;
    }

    if (strcmp(command, "reboot") == 0) {
        reboot();
        return;
    }

    print("\nUnknown command!\n");
}