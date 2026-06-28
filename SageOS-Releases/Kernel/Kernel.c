#include "Headers/vga.h"

#include "Headers/gdt.h"
#include "Headers/idt.h"

#include "Headers/pic.h"
#include "Headers/isr.h"
#include "Headers/irq.h"
#include "Drivers/keyboard.h"

#include "sage/sage.h"

void initialize() {
    clear_screen();
    drawLine();
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