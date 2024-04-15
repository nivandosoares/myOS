#include "menu.h"
#include "./drivers/vga.h"


#define MENU_ITEMS 3
const char* menu_options[MENU_ITEMS] = {
    "Program 1",
    "Program 2",
    "Program 3"
};

int current_selection = 0;

void print_menu() {
    clear_screen();
    int start_row = (VGA_HEIGHT - MENU_ITEMS) / 2; // Center menu vertically

    for (int i = 0; i < MENU_ITEMS; i++) {
        int row = start_row + i; // Calculate row position for each item
        int col_prefix = (VGA_WIDTH - strlen(menu_options[i]) - 2) / 2;
        int col_text = (VGA_WIDTH - strlen(menu_options[i])) / 2;
        
        if (i == current_selection) {
            print_string(row, col_prefix, "> "); // Show a cursor for the selected item
        } else {
            print_string(row, col_prefix, "  "); // Space for non-selected items
        }
        print_string(row, col_text, menu_options[i]);
    }
}

void run_selected_program() {
    clear_screen();
    print_string(12, (VGA_WIDTH - 20) / 2, "Running: ");
    print_string(12, (VGA_WIDTH - 20) / 2 + 9, menu_options[current_selection]);
    // Placeholder for program execution
}

void handle_menu_navigation() {
    unsigned char key;
    do {
        key = read_keyboard_encoder();  // Implement this function based on your system

        switch (key) {
            case 0x48: // Scan code for UP arrow
                if (current_selection > 0) {
                    current_selection--;
                    print_menu();
                }
                break;
            case 0x50: // Scan code for DOWN arrow
                if (current_selection < MENU_ITEMS - 1) {
                    current_selection++;
                    print_menu();
                }
                break;
            case 0x1C: // Scan code for Enter key
                run_selected_program();
                return;
        }
    } while (key != 0x1C); // Continue until Enter is pressed
}

