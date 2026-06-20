CC     = i686-elf-gcc
AS     = nasm
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Iinclude
LFLAGS = -ffreestanding -O2 -nostdlib -lgcc

OBJS = boot/boot.o kernel/kernel.o kernel/terminal.o

.PHONY: all run clean

all: kernel.elf

kernel.elf: $(OBJS) linker.ld
	$(CC) -T linker.ld -o $@ $(LFLAGS) $(OBJS)

boot/boot.o: boot/boot.asm
	$(AS) -f elf32 $< -o $@

kernel/terminal.o: kernel/terminal.c
	$(CC) $(CFLAGS) -c $< -o $@

kernel/kernel.o: kernel/kernel.c
	$(CC) $(CFLAGS) -c $< -o $@

run: kernel.elf
	qemu-system-i386 -kernel kernel.elf

clean:
	rm -f $(OBJS) kernel.elf