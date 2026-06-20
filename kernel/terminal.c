#include <stdint.h>
#include <stddef.h>

#define VGA_WIDTH  80
#define VGA_HEIGHT 25
#define VGA_MEM    ((uint16_t *)0xB8000)

static size_t col = 0;
static size_t row = 0;
static uint8_t color = 0x0F;
static uint16_t* buffer = VGA_MEM;

static inline uint16_t vga_entry(char c, uint8_t color) {
    return (uint16_t)c | ((uint16_t)color << 8);
} 


void terminal_clear(void) {
    for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
        buffer[i] = vga_entry(' ', color);
    col = 0; 
    row = 0;
}

void terminal_initialize(void) {
    col = 0;
    row = 0;
    color = 0x0F;
    buffer = VGA_MEM;
    terminal_clear();
}

// terminal_putchar:
// Input: one character.
// Behavior:
// - if the character is '\n':
//     - set column to 0
//     - move row down by 1
//     - if row reaches VGA_HEIGHT, wrap to 0 for now
//     - return
// - otherwise:
//     - compute index = row * VGA_WIDTH + column
//     - write the character/color VGA entry into the buffer at that index
//     - move column forward by 1
//     - if column reaches VGA_WIDTH:
//         - set column to 0
//         - move row down by 1
//         - if row reaches VGA_HEIGHT, wrap to 0 for now

void terminal_putchar(char c) {
    if (c == '\n') {
        col = 0;
        row += 1;

        if (row >= VGA_HEIGHT) {
            row = 0;
        }

        return;
    }

    size_t index = row * VGA_WIDTH + col;
    buffer[index] = vga_entry(c, color);

    col += 1;

    if (col >= VGA_WIDTH) {
        col = 0;
        row += 1;

        if (row >= VGA_HEIGHT) {
            row = 0;
        }
    }
}


// terminal_writestring:
// Input: null-terminated C string.
// Behavior:
// - loop while current character is not '\0'
// - call terminal_putchar on current character
// - advance to the next character

void terminal_writestring(const char* s) {
    while (*s != '\0') {
        terminal_putchar(*s);
        s++;
    }
}


// terminal_writedec:
// Input: uint32_t number.
// Behavior:
// - if number is 0, print '0' and return
// - create a small char buffer large enough for 10 decimal digits
// - repeatedly:
//     - digit = number % 10
//     - store '0' + digit in bufferthen low byte is 0x05, which is not the printable character '5'. It is a control-ish character code, so it may display weirdly or not visibly.


//     - number = number / 10
// - digits are stored backwards, so print them from the end back to the start

void terminal_writedec(uint32_t n) {
    if (n == 0) {
        terminal_putchar('0');
        return;
    }

    char buf[10];
    size_t len = 0;

    while (n > 0) {
        uint32_t digit = n % 10;
        buf[len] = '0' + digit;
        len++;
        n /= 10;
    }

    while (len > 0) {
        len--;
        terminal_putchar(buf[len]);
    }
}

// terminal_writehex:
// Input: uint32_t number.
// Behavior:
// - print "0x"
// - for shifts 28, 24, 20, 16, 12, 8, 4, ; shift -= 4) {
//     - isolate the current 4-bit nibble using shift and mask
//     - if nibble is 0-9, convert to '0' through '9'
//     - if nibble is 10-15, convert to 'A' through 'F'
//     - print that character

void terminal_writehex(uint32_t n) {
    terminal_writestring("0x");

    for (int shift = 28; shift >= 0; shift -= 4) {
        uint32_t nibble = (n >> shift) & 0xF;

        char c;

        if (nibble <= 9) {
            c = '0' + nibble;
        } else {
            c = 'A' + (nibble - 10);
        }

        terminal_putchar(c);
    }
}
