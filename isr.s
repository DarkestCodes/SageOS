extern isr_handler

global isr_common

; Common ISR handler

isr_common:
    cli

    pusha

    ; pass registers_t pointer
    push esp
    call isr_handler
    add esp, 4

    popa

    ; remove int number + error code
    add esp, 8

    sti
    iretd



; Macros


%macro ISR_NOERR 1
global isr%1

isr%1:
    push dword 0        ; fake error code
    push dword %1       ; interrupt number
    jmp isr_common
%endmacro


%macro ISR_ERR 1
global isr%1

isr%1:
    push dword %1       ; interrupt number
    jmp isr_common
%endmacro



; Exceptions 32 from 0 - 31


ISR_NOERR 0     ; Divide Error
ISR_NOERR 1     ; Debug
ISR_NOERR 2     ; NMI
ISR_NOERR 3     ; Breakpoint
ISR_NOERR 4     ; Overflow
ISR_NOERR 5     ; Bound Range Exceeded
ISR_NOERR 6     ; Invalid Opcode
ISR_NOERR 7     ; Device Not Available

ISR_ERR 8       ; Double Fault

ISR_NOERR 9     ; Coprocessor Segment Overrun

ISR_ERR 10      ; Invalid TSS
ISR_ERR 11      ; Segment Not Present
ISR_ERR 12      ; Stack Fault
ISR_ERR 13      ; General Protection Fault
ISR_ERR 14      ; Page Fault

ISR_NOERR 15     ; Reserved

ISR_NOERR 16     ; x87 Floating Point Exception

ISR_ERR 17      ; Alignment Check

ISR_NOERR 18     ; Machine Check
ISR_NOERR 19     ; SIMD Floating Point Exception
ISR_NOERR 20     ; Virtualization Exception
ISR_NOERR 21     ; Control Protection Exception

ISR_NOERR 22
ISR_NOERR 23
ISR_NOERR 24
ISR_NOERR 25
ISR_NOERR 26
ISR_NOERR 27
ISR_NOERR 28
ISR_NOERR 29
ISR_NOERR 30
ISR_NOERR 31