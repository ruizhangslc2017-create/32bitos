#include "isr.h"
#include "terminal.h"

static const char* exception_names[] = {
    "Division By Zero",
    "Debug",
    "Non-Maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "Reserved",
    "x87 FPU Exception",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
};

void isr_handler(registers_t* regs)
{
    if (regs->int_no < 21) {
        terminal_writestring("INTERRUPT: ");
        terminal_writestring(exception_names[regs->int_no]);
        terminal_writestring("\n");
    } else {
        terminal_writestring("INTERRUPT: unknown\n");
    }
}
