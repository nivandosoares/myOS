#include "drivers/vga.h"
#include "drivers/keyboard.h"
#include "menu.h"

extern "C" void main() {
    clear_screen();
    print_string(12, 34, "Welcome to RobCo OS");
    print_string(13, 28, "Press any key to continue...");
    wait_for_keypress();
    clear_screen();
    print_string(12, 34, "See You Space Cowboy");
}
