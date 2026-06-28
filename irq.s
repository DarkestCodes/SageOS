extern irq_handler

global irq0
global irq1

irq0:
    cli

    push dword 0
    push dword 32

    pusha

    push esp
    call irq_handler

    add esp, 4

    popa

    add esp, 8

    iret


irq1:
    cli

    push dword 0
    push dword 33

    pusha

    push esp
    call irq_handler

    add esp, 4

    popa

    add esp, 8

    iret