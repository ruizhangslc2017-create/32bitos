Notes for the IDT 


Next milestone: minimal IDT


Load an IDT
Trigger a breakpoint interrupt
Print something like "Interrupt received"

The next files will probably be:

include/idt.h
kernel/idt.c
boot/idt_flush.asm
boot/interrupt_stubs.asm

And later:

kernel/isr.c
include/isr.h
What IDT does

The IDT is basically a table saying:

If interrupt 0 happens, go to handler A
If interrupt 1 happens, go to handler B
If interrupt 3 happens, go to breakpoint handler
If interrupt 14 happens, go to page fault handler

The simplest test is interrupt 3, the breakpoint interrupt:

int 3

Eventually my kernel should be able to do:

idt_initialize();
terminal_writestring("IDT loaded\n");

asm volatile("int $3");

terminal_writestring("Still alive after interrupt\n");

Expected idea:

IDT loaded
Interrupt received
Still alive after interrupt
But before coding IDT

so rn i have
[T] Boot kernel
[T] VGA terminal
[T] GDT
[IP] IDT
[ ] ISRs / exception handlers
[ ] IRQs / PIC remap
[ ] PIT timer
[ ] keyboard input
[ ] physical memory manager
[ ] paging
[ ] heap
[ ] simple shell

