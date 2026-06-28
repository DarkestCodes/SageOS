.section .multiboot
.align 8

.long 0xE85250D6
.long 0
.long 24
.long -(0xE85250D6 + 0 + 24)

.short 0
.short 0
.long 8

.section .text
.global _start
.extern kernel_main

_start:
    mov $stack_top, %esp
    call kernel_main
hang:
    hlt
    jmp hang
    