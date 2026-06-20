#include <stdint.h>
#include "gdt.h"

// Include stdint.h for uint8_t, uint16_t, uint32_t.
// Include gdt.h.
// Include terminal.h only if you want to debug-print from inside gdt_initialize.

// Define a packed struct for one GDT entry.
// A GDT entry is exactly 8 bytes.
// It contains:
// - limit low 16 bits
// - base low 16 bits
// - base middle 8 bits
// - access byte
// - granularity byte
// - base high 8 bits

// Define a packed struct for the GDT pointer.
// The CPU's lgdt instruction expects:
// - limit: size of GDT in bytes minus 1
// - base: address of the GDT table

// Create a static array of 3 GDT entries.
// gdt[0] = null
// gdt[1] = kernel code
// gdt[2] = kernel data

// Create a static GDT pointer.

// Declare external assembly function:
// extern void gdt_flush(uint32_t gdt_ptr_address);


struct __attribute__((packed)) gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t  base_middle;
    uint8_t  access;
    uint8_t  granularity;
    uint8_t  base_high;
};

/*
 * This is the 6-byte descriptor passed to lgdt.
 * It tells the CPU where the GDT starts and how large it is.
 */
struct __attribute__((packed)) gdt_ptr {
    uint16_t limit;
    uint32_t base;
};

static struct gdt_entry gdt[3];
static struct gdt_ptr gp;

extern void gdt_flush(uint32_t gdt_ptr_address);

// gdt_set_entry:
// Inputs:
// - index
// - base
// - limit
// - access
// - granularity
// Behavior:
// - split base into low/middle/high parts
// - split limit into low part and upper 4 bits
// - combine granularity flags with upper limit bits
// - set access byte

static void gdt_set_entry(int index,
                          uint32_t base,
                          uint32_t limit,
                          uint8_t access,
                          uint8_t granularity) {
    gdt[index].base_low = base & 0xFFFF;
    gdt[index].base_middle = (base >> 16) & 0xFF;
    gdt[index].base_high = (base >> 24) & 0xFF;

    gdt[index].limit_low = limit & 0xFFFF;
    gdt[index].granularity = (limit >> 16) & 0x0F;

    gdt[index].granularity |= granularity & 0xF0;
    gdt[index].access = access;
}

// gdt_initialize:
// Behavior:
// - set GDT pointer limit = sizeof(gdt) - 1
// - set GDT pointer base = address of gdt
// - set null descriptor
// - set kernel code descriptor
// - set kernel data descriptor
// - call gdt_flush with address of the pointer
/*
 * One GDT entry is exactly 8 bytes.
 * The CPU expects this exact byte layout.
 */

void gdt_initialize(void) {
    gp.limit = sizeof(gdt) - 1;
    gp.base = (uint32_t)&gdt;

    // Null descriptor. Required because selector 0x00 means "invalid."
    gdt_set_entry(0, 0, 0, 0, 0);

    // Kernel code segment.
    // base = 0, limit = 4GB, access = 0x9A, granularity = 0xCF
    gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    // Kernel data segment.
    // base = 0, limit = 4GB, access = 0x92, granularity = 0xCF
    gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    gdt_flush((uint32_t)&gp);
}