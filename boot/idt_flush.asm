bits 32

global idt_flush

; void idt_flush(idt_ptr_t* ptr)
; Loads the IDTR register using the pointer passed on the stack.
idt_flush:
    mov eax, [esp+4]    ; first argument: pointer to idt_ptr_t
    lidt [eax]
    ret

