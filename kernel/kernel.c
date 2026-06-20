#include "terminal.h"
#include "gdt.h"

void kernel_main(void) {
    terminal_initialize();

    terminal_writestring("ruios kernel booted\n");
    terminal_writestring("VGA terminal online\n");

    gdt_initialize();
    terminal_writestring("GDT loaded\n");
}

/* 
compile time:
  gdt_flush.asm -> gdt_flush.o
  just converted into machine code, not executed

link time:
  gdt_flush.o gets put into kernel.elf

runtime:
  QEMU runs kernel.elf
  kernel_main calls gdt_initialize()
  gdt_initialize calls gdt_flush()
  now the assembly instructions actually execute on the CPU

*/