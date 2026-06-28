CC=i686-elf-gcc
LD=i686-elf-ld

CFLAGS=-m32 -ffreestanding -Wall -Wextra
LDFLAGS=-m elf_i386 -T linker.ld


SRCS = \
Kernel/Kernel.c \
Kernel/vga.c \
Kernel/cursor.c \
\
Kernel/gdt.c \
Kernel/idt.c \
Kernel/io.c \
Kernel/pic.c \
Kernel/isr.c \
Kernel/irq.c \
\
Kernel/Drivers/keyboard.c \
\
Kernel/Libraires/memory.c \
Kernel/Libraires/strcmp.c \
\
Kernel/Syscalls/FaultHandlers.c \
Kernel/Syscalls/SageAPI.c \
\
Kernel/Power/power.c \
\
User/SageShell/SageShell.c \
User/SageShell/command.c \

OBJS = $(SRCS:.c=.o)

all: iso

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

boot.o: boot.s 
	$(CC) -m32 -c boot.s -o boot.o

gdt.o: gdt.s
	nasm -f elf32 gdt.s -o gdt.o
idt.o: idt.s
	nasm -f elf32 idt.s -o idt.o

isr.o: isr.s
	nasm -f elf32 isr.s -o isr.o
irq.o: irq.s
	nasm -f elf32 irq.s -o irq.o


kernel.bin: boot.o gdt.o idt.o isr.o irq.o $(OBJS)
	$(LD) $(LDFLAGS) -o $@ boot.o gdt.o idt.o isr.o irq.o $(OBJS)
iso: kernel.bin
	mkdir -p iso/boot
	cp kernel.bin iso/boot/kernel.bin
	grub-mkrescue -o SageOS.iso iso

run: iso
	qemu-system-i386 -cdrom SageOS.iso

clean:
	rm -f *.o kernel.bin SageOS.iso
	rm -f iso/boot/kernel.bin
	rm -f \
		Kernel/*.o \
		Kernel/Drivers/*.o \
		Kernel/Libraires/*.o \
		Kernel/Syscalls/*.o \
		Kernel/Power/*.o \
		User/SageShell/*.o \

		2>/dev/null || true
