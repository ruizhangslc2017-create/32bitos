#include "terminal.h"
#include "gdt.h"
#include "idt.h"

void kernel_main(void) {
    terminal_initialize();
    terminal_writestring("ruios kernel booted\n");
    terminal_writestring("VGA terminal online\n");

    gdt_initialize();
    terminal_writestring("GDT loaded\n");

    idt_init();
    terminal_writestring("IDT loaded\n");

    asm volatile("int $3");
    terminal_writestring("Back from INT 3\n");
}
