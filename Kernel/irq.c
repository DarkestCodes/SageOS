#include "Headers/vga.h"
#include "Headers/irq.h"
#include "Headers/idt.h"
#include "Headers/pic.h"

static irq_handler_t handlers[16];

extern void irq0();
extern void irq1();

void irq_register_handler(int irq, irq_handler_t handler) {
    handlers[irq] = handler;
}


void irq_handler(registers_t* regs) {
    int irq = regs->int_no - 32;

    if (handlers[irq]) {
        handlers[irq](regs);
    }

    pic_send_eoi(irq);
}

void irq_install() {
    idt_set_gate(32, (uint32_t)irq0, 0x08, 0x8E);
    idt_set_gate(33, (uint32_t)irq1, 0x08, 0x8E);
}