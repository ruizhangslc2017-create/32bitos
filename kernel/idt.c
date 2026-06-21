#include "idt.h"

idt_entry_t idt[256];
idt_ptr_t idtp;

extern void idt_flush(idt_ptr_t*);

extern void isr0(void);  extern void isr1(void);  extern void isr2(void);
extern void isr3(void);  extern void isr4(void);  extern void isr5(void);
extern void isr6(void);  extern void isr7(void);  extern void isr8(void);
extern void isr9(void);  extern void isr10(void); extern void isr11(void);
extern void isr12(void); extern void isr13(void); extern void isr14(void);
extern void isr15(void); extern void isr16(void); extern void isr17(void);
extern void isr18(void); extern void isr19(void); extern void isr20(void);

static void set_gate(int n, uint32_t handler)
{
    idt[n].base_low  = handler & 0xFFFF;
    idt[n].base_high = (handler >> 16) & 0xFFFF;
    idt[n].sel       = 0x08;   // kernel code segment
    idt[n].always0   = 0;
    idt[n].flags     = 0x8E;   // present, ring 0, 32-bit interrupt gate
}

void idt_init(void)
{
    idtp.limit = sizeof(idt) - 1;
    idtp.base  = (uint32_t)&idt;

    set_gate(0,  (uint32_t)isr0);
    set_gate(1,  (uint32_t)isr1);
    set_gate(2,  (uint32_t)isr2);
    set_gate(3,  (uint32_t)isr3);
    set_gate(4,  (uint32_t)isr4);
    set_gate(5,  (uint32_t)isr5);
    set_gate(6,  (uint32_t)isr6);
    set_gate(7,  (uint32_t)isr7);
    set_gate(8,  (uint32_t)isr8);
    set_gate(9,  (uint32_t)isr9);
    set_gate(10, (uint32_t)isr10);
    set_gate(11, (uint32_t)isr11);
    set_gate(12, (uint32_t)isr12);
    set_gate(13, (uint32_t)isr13);
    set_gate(14, (uint32_t)isr14);
    set_gate(15, (uint32_t)isr15);
    set_gate(16, (uint32_t)isr16);
    set_gate(17, (uint32_t)isr17);
    set_gate(18, (uint32_t)isr18);
    set_gate(19, (uint32_t)isr19);
    set_gate(20, (uint32_t)isr20);

    idt_flush(&idtp);
}
