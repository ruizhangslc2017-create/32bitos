#include <stdint.h>
#include <stddef.h>

#define VGA_WIDTH  80
#define VGA_HEIGHT 25
#define VGA_MEM    ((uint16_t *)0xB8000)
/*
two byte structure to create a basic cell with char and then color*/
static inline uint16_t vga_entry(char c, uint8_t color) {
    return (uint16_t)c | ((uint16_t)color << 8);
}

static size_t col = 0, row = 0;
static uint8_t color = 0x0F; /* white on black */

static void vga_putchar(char c) {
    if (c == '\n') {
        col = 0;
        if (++row == VGA_HEIGHT) row = 0;
        return;
    }
    VGA_MEM[row * VGA_WIDTH + col] = vga_entry(c, color);
    if (++col == VGA_WIDTH) {
        col = 0;
        if (++row == VGA_HEIGHT) row = 0;
    }
}

static void vga_puts(const char *s) {
    while (*s) vga_putchar(*s++);
}

static void vga_clear(void) {
    for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
        VGA_MEM[i] = vga_entry(' ', color);
    col = row = 0;
}

void kernel_main(void) {
    vga_clear();
    vga_puts("ruios kernel booted\n");
    vga_puts("Hello from kernel_main!\n");
}
