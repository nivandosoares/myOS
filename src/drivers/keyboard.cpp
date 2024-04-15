#include "keyboard.h"

// Function to read status from keyboard controller
unsigned char read_status() {
    return inb(0x64);
}

// Function to read data from keyboard encoder
unsigned char read_keyboard_encoder() {
    return inb(0x60);
}

// Function to wait for a key press
void wait_for_keypress() {
    unsigned char status;
    // Loop until the keyboard buffer is empty and a key is pressed
    do {
        status = read_status();
        // If the lowest bit is set, a key has been pressed
        if (status & 0x01) {
            // Discard the key (for now)
            (void)read_keyboard_encoder();
        }
    } while (!(status & 0x01));
}