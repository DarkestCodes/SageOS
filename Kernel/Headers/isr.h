#ifndef ISR_H
#define ISR_H

#include <stdint.h>

#define KERNEL_CODE_SEGMENT 0x08
#define IDT_FLAGS 0x8E

typedef struct registers
{
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;

    uint32_t int_no;
    uint32_t err_code;

    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
} registers_t;

void isr_install();

#endif