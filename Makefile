CC     = x86_64-elf-gcc
AS     = nasm
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Iinclude -m32
LFLAGS = -ffreestanding -O2 -nostdlib -m32 -Wl,-melf_i386

OBJS = boot/boot.o \
       boot/gdt_flush.o \
       boot/idt_flush.o \
       boot/interrupt_stubs.o \
       kernel/kernel.o \
       kernel/terminal.o \
       kernel/gdt.o \
       kernel/idt.o \
       kernel/isr.o

.PHONY: all run clean

all: kernel.elf

kernel.elf: $(OBJS) linker.ld
	$(CC) -T linker.ld -o $@ $(LFLAGS) $(OBJS)

boot/boot.o: boot/boot.asm
	$(AS) -f elf32 $< -o $@

boot/gdt_flush.o: boot/gdt_flush.asm
	$(AS) -f elf32 $< -o $@

boot/idt_flush.o: boot/idt_flush.asm
	$(AS) -f elf32 $< -o $@

boot/interrupt_stubs.o: boot/interrupt_stubs.asm
	$(AS) -f elf32 $< -o $@

kernel/terminal.o: kernel/terminal.c
	$(CC) $(CFLAGS) -c $< -o $@

kernel/kernel.o: kernel/kernel.c
	$(CC) $(CFLAGS) -c $< -o $@

kernel/gdt.o: kernel/gdt.c
	$(CC) $(CFLAGS) -c $< -o $@

kernel/idt.o: kernel/idt.c
	$(CC) $(CFLAGS) -c $< -o $@

kernel/isr.o: kernel/isr.c
	$(CC) $(CFLAGS) -c $< -o $@

run: kernel.elf
	qemu-system-i386 -kernel kernel.elf

clean:
	rm -f $(OBJS) kernel.elf
