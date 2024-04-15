#include "vga.h"
// Function to clear the screen
void clear_screen() {
    unsigned short* vga_buffer = (unsigned short*) VGA_ADDRESS;
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; ++i) {
        vga_buffer[i] = (unsigned short)(' ' | (GREEN_ON_BLACK << 8));
    }
}

// Function to print a string at a specific location
void print_string(int row, int col, const char* str) {
    unsigned short* vga_buffer = (unsigned short*) VGA_ADDRESS;
    int offset = row * VGA_WIDTH + col;
    while (*str) {
        vga_buffer[offset++] = (unsigned short)(*str | (GREEN_ON_BLACK << 8));
        str++;
    }
}


// Function to calculate the length of a string
int strlen(const char* str) {
    int length = 0;
    while (str[length])
        length++;
    return length;
}

// Function to print a string centered on a specific row
void print_centered(int row, const char* str) {
    int length = strlen(str);
    int col = (VGA_WIDTH - length) / 2;  // Calculate the starting column
    print_string(row, col, str);
}
