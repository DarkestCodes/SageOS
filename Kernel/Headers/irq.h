#ifndef IRQ_H
#define IRQ_H

#include "isr.h"

typedef void (*irq_handler_t)(registers_t*);

void irq_install();


void irq_register_handler(
    int irq,
    irq_handler_t handler
);

#endif