bits 32

extern isr_handler

; ISR_NOERR: CPU does NOT push an error code for this interrupt.
; We push a dummy 0 so the stack layout is always identical when
; we reach isr_common, regardless of which interrupt fired.
%macro ISR_NOERR 1
global isr%1
isr%1:
    push dword 0
    push dword %1
    jmp isr_common
%endmacro

; ISR_ERR: CPU already pushed an error code before jumping here.
; We only need to push the interrupt number on top of it.
%macro ISR_ERR 1
global isr%1
isr%1:
    push dword %1
    jmp isr_common
%endmacro

ISR_NOERR 0   ; Division By Zero
ISR_NOERR 1   ; Debug
ISR_NOERR 2   ; Non-Maskable Interrupt
ISR_NOERR 3   ; Breakpoint
ISR_NOERR 4   ; Overflow
ISR_NOERR 5   ; Bound Range Exceeded
ISR_NOERR 6   ; Invalid Opcode
ISR_NOERR 7   ; Device Not Available
ISR_ERR   8   ; Double Fault          (CPU pushes error code)
ISR_NOERR 9   ; Coprocessor Segment Overrun (legacy, no error code)
ISR_ERR   10  ; Invalid TSS           (CPU pushes error code)
ISR_ERR   11  ; Segment Not Present   (CPU pushes error code)
ISR_ERR   12  ; Stack-Segment Fault   (CPU pushes error code)
ISR_ERR   13  ; General Protection Fault (CPU pushes error code)
ISR_ERR   14  ; Page Fault            (CPU pushes error code)
ISR_NOERR 15  ; Reserved
ISR_NOERR 16  ; x87 FPU Exception
ISR_ERR   17  ; Alignment Check       (CPU pushes error code)
ISR_NOERR 18  ; Machine Check
ISR_NOERR 19  ; SIMD Floating-Point Exception
ISR_NOERR 20  ; Virtualization Exception

global isr_common
isr_common:
    ; At entry, stack (top to bottom):
    ;   int_no   <- pushed by stub
    ;   err_code <- pushed by stub (dummy 0) or CPU
    ;   EIP      <- pushed by CPU when interrupt fired
    ;   CS       <- pushed by CPU
    ;   EFLAGS   <- pushed by CPU

    pusha           ; pushes EAX,ECX,EDX,EBX,ESP,EBP,ESI,EDI (EDI now at top)

    push ds
    push es
    push fs
    push gs

    ; ESP now points to the bottom of our registers_t struct.
    ; Pass it as the argument to isr_handler(registers_t*).
    push esp
    call isr_handler
    add esp, 4      ; pop the esp argument

    pop gs
    pop fs
    pop es
    pop ds

    popa
    add esp, 8      ; discard int_no and err_code
    iret
