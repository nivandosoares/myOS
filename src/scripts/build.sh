#!/bin/bash
export PATH=$PATH:/usr/local/i386elfgcc/bin

# Ensure Binaries directory exists
mkdir -p src/bin

# Compile assembly code
nasm "src/boot.asm" -f bin -o "src/bin/boot.bin"
nasm "src/kernel_entry.asm" -f elf -o "src/bin/kernel_entry.o"

# Compile C++ code for kernel and drivers
i386-elf-gcc -ffreestanding -m32 -g -c "src/kernel.cpp" -o "src/bin/kernel.o" -I"src/drivers" -I"src/include"
i386-elf-gcc -ffreestanding -m32 -g -c "src/drivers/vga.cpp" -o "src/bin/vga.o" -I"src/include"
i386-elf-gcc -ffreestanding -m32 -g -c "src/drivers/keyboard.cpp" -o "src/bin/keyboard.o" -I"src/include"
i386-elf-gcc -ffreestanding -m32 -g -c "src/menu.cpp" -o "src/bin/menu.o" -I"src/drivers" -I"src/include"

# Link all object files together
i386-elf-ld -o "src/bin/full_kernel.bin" -Ttext 0x1000 "src/bin/kernel_entry.o" "src/bin/kernel.o" "src/bin/vga.o" "src/bin/keyboard.o" "src/bin/menu.o" --oformat binary

# Combine into final OS binary
cat "src/bin/boot.bin" "src/bin/full_kernel.bin" > "src/bin/OS.bin"

# Run in QEMU
qemu-system-x86_64 -drive format=raw,file="src/bin/OS.bin",index=0,if=floppy, -m 128M
