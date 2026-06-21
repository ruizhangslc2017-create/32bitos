

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


idt notes: 
this is the full run through of what happens:
CPU triggers interrupt 3
→ CPU saves minimal state
→ CPU jumps to IDT[3]
→ ASM stub runs
→ ASM pushes “3”
→ ASM saves registers
→ ASM calls isr_handler(regs)
→ C reads regs->int_no = 3
→ prints "Breakpoint" 
