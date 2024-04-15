#define VGA_ADDRESS 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define GREEN_ON_BLACK 0x02 // Green text on black background

void clear_screen();
void print_string(int row, int col, const char* str);
void print_centered(int row, const char* str);
int strlen(const char* str);
