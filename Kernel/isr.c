#include "Headers/vga.h"
#include "Headers/isr.h"
#include "Headers/idt.h"

extern void isr0();

void isr_handler(registers_t* regs)
{
    print("EXCEPTION: ");

    if(regs->int_no == 0)
    {
        print("\n\nDIVIDE BY ZERO");
    }

    print("\n");

    for(;;)
    {
        __asm__ volatile("hlt");
    }
}

void isr_install()
{
    idt_set_gate(
        0,
        (uint32_t)isr0,
        0x08,
        0x8E
    );
}