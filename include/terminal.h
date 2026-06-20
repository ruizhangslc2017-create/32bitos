#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdint.h>

void terminal_initialize(void);
void terminal_clear(void);
void terminal_putchar(char c);
void terminal_writestring(const char* s);
void terminal_writedec(uint32_t n);
void terminal_writehex(uint32_t n);

#endif