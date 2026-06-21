#pragma once
#include <stdint.h>

// Stack layout built by isr_common (low address first, matches push order):
//   gs, fs, es, ds          <- segment registers (pushed last → lowest addr)
//   edi,esi,ebp,esp,ebx,edx,ecx,eax  <- pusha (EDI pushed last)
//   int_no                  <- stub pushed this
//   err_code                <- stub dummy or CPU error code
//   eip, cs, eflags         <- CPU-pushed interrupt frame
typedef struct {
    uint32_t gs, fs, es, ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags;
} registers_t;

void isr_handler(registers_t* regs);
