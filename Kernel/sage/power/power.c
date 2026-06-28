#include "power.h"

#include "../sage.h"

#include "../../Headers/io.h"
#include "../../Headers/vga.h"
#include "../../Headers/cursor.h"


#include "../../Drivers/keyboard.h"

static void power_init() {
    OS_ACTIVE = false;
    disable_keyboard();
    clear_screen();
    cursor = 0;
    input_start = 20;
    update_cursor(cursor);
}

void shutdown() {
    power_init();
    print("Shutting down ...");

    // shutdown !
    outw(0x604, 0x2000);
}

void reboot() {
    power_init();
    print("Rebooting ...");
    while (inb(0x64) & 0x02);
    outb(0x64, 0xFE);
}
