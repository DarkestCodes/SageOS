extern isr_handler

global isr0

isr0:
    cli

    push dword 0
    push dword 0

    pusha

    push esp
    call isr_handler

    add esp, 4

    popa

    add esp, 8

    iret