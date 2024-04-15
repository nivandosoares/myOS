// File: src/drivers/keyboard.h
// I/O port operations
unsigned char read_status();
unsigned char read_keyboard_encoder();
void wait_for_keypress();

#ifndef KEYBOARD_H
#define KEYBOARD_H

inline void outb(unsigned short port, unsigned char val) {
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

inline unsigned char inb(unsigned short port) {
    unsigned char ret;
    asm volatile ("inb %1, %0"
                  : "=a"(ret)
                  : "Nd"(port));
    return ret;
}

// Other declarations and definitions

#endif // KEYBOARD_H
