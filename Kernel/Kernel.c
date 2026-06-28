#include "Headers/Kernel.h"

#include "Headers/vga.h"

#include "Headers/gdt.h"
#include "Headers/idt.h"

#include "Headers/pic.h"
#include "Headers/isr.h"
#include "Headers/irq.h"
#include "Drivers/keyboard.h"

#include "Libraires/memory.h"

#include "../User/SageShell/SageShell.h"

void initialize() {
    change_fg("cyan");
    clear_screen();
    drawLine();
    
    // Memory init
    kinit_memory();
    
    // INTRUPPTS
    gdt_init();
    print("GDT OK\t");
    
    idt_init();
    print("IDT OK\t");
    
    // KEYBOARD
    
    pic_remap();
    print("PIC OK\t");
    
    isr_install();
    print("\nISR OK\t");
    
    irq_install();
    print("IRQ OK\t"); 
    
    keyboard_install();
    print("KEYBOARD OK\n");
    drawLine();
    reset_colors();
}

void kernel_panic(const char *reason) {
    change_bg("blue");
    change_fg("red");
    clear_screen();
    disable_keyboard();
    printf("\nKernel PANIC: %s\n", reason);
    while(1);
}

void kernel_main(void) {
    // initilize before system runs
    initialize();

    enable_keyboard();

    // Open COMMAND PROMPT (SAGE)
    SAGE_START();

    // HALT
    for (;;) {
        __asm__ volatile ("hlt");
    }
}