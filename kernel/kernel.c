#include "terminal.h"

void kernel_main(void) {
    terminal_initialize();

    terminal_writestring("ruios kernel booted\n");
    terminal_writestring("VGA terminal online\n");

    terminal_writestring("hex test: ");
    terminal_writehex(0xB8000);
    terminal_putchar('\n');

    terminal_writestring("dec test: ");
    terminal_writedec(12345);
    terminal_putchar('\n');
}