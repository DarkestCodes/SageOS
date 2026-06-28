#include "Headers/FaultHandlers.h"

#include "../Headers/Kernel.h"

#include "../Headers/vga.h"

const char *exception_names[] =
{
    "Divide By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "Reserved",
    "x87 Floating Point",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating Point",
    "Virtualization Exception",
    "Control Protection Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Security Exception",
    "Reserved"
};


void exception_handler(registers_t *regs)
{
    if (regs->int_no < 20)
    {
        clear_screen();
        kernel_panic(exception_names[regs->int_no]);
        while(1);
    }
    else
    {
        print("UNKNOWN EXCEPTION");
    }

    kernel_panic("CPU Exception");
}