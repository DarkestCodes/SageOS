# SageOS

![SageOS](https://img.shields.io/badge/status-active%20development-blue)

SageOS is an operating system built from scratch, featuring an interactive command-line environment called **Sage Shell**. The project is an exploration of bare-metal programming, low-level systems development, and the fundamentals of operating system design.

SageOS is actively developed and will continue to receive updates as new features, improvements, and experiments are added.

SageOS has been tested in Virtual Box and Qemu-i386 both works.
SageOS couldn't shutdown in Virtual Box but did in Qemu-i386.
---

## Features

Current features:

- Custom boot process
- VGA text-mode graphics
- Hardware cursor support
- Keyboard interrupt handling
- Interactive Sage Shell
- Command execution system
- Basic command-line editing
- Shift and Caps Lock support
- Cursor movement with arrow keys

---

## Screenshots
<img width="1920" height="1080" alt="Screenshot_2026-07-01_07_47_06" src="https://github.com/user-attachments/assets/bb620bb3-57b5-4076-b5ec-57129c27d99e" />

<img width="1920" height="1080" alt="Screenshot_2026-07-01_07_47_25" src="https://github.com/user-attachments/assets/6bd90876-b9d0-49f1-b820-a21071a2304f" />

---

## Building

### Requirements

- ! GCC cross compiler (i686-elf-gcc)
- ! Linker LD (i686-elf-ld)
- ! NASM
- ! Make
- QEMU-i386 (Recommended)

### Build

Clone the repository:

```bash
git clone https://github.com/DarkestCodes/SageOS.git
cd SageOS
```

Build the operating system:

```bash
make
```

Run with QEMU:

```bash
qemu-system-i386 -cdrom SageOS.iso
```

Complete Command:

```bash
make clean && make && clear && qemu-system-i386 -cdrom SageOS.iso && make clean
```

---

## Sage Shell

Sage Shell is the interactive command-line interface of SageOS.

Example:

```
!#Sage>help
!#Sage>clear
!#Sage>info
```

The shell is continuously being improved with features such as:

- Better command editing
- Command history
- More built-in commands
- File system integration
- Allow app dev

---

## Roadmap

Planned features:
- [ ] Move from kernel ring (Avoid FULL system crash)
- [ ] Better memory management
- [ ] More shell commands
- [ ] File system support
- [ ] Program loading
- [ ] Improved keyboard support
- [ ] User applications
- [ ] Multitasking
- [ ] Custom Nano
- [ ] Custom Programming Language
- [ ] Port C Language
---

## About

SageOS is a personal learning project focused on understanding how computers work at a lower level.

The goal is not only to build an operating system, but also to explore:

- Hardware interaction
- Interrupt handling
- Memory management
- Kernel design
- Computer architecture

---

## License

SageOS is licensed under the Apache License 2.0.

You are free to use, modify, and distribute this software under the terms of the license.

See the [LICENSE](LICENSE) file for the full license text.
