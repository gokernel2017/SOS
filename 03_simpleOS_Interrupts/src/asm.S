//-------------------------------------------------------------------
//
// THIS FILE IS PART OF SIMPLE OPERATING SYSTEM:
//
//   The Interrupt API.
//
// FILE:
//   asm.S
//
// START DATE: 16/06/2019 - 10:40
//
//-------------------------------------------------------------------
//
.code32    

#ifdef WIN32
.globl _gdt_flush
.globl _idt_flush
#endif
#ifdef __linux__
.globl gdt_flush
.globl idt_flush
#endif

/*
.globl _isr0
.globl _isr1
.globl _isr2
.globl _isr3
.globl _isr4
.globl _isr5
.globl _isr6
.globl _isr7
.globl _isr8
.globl _isr9
.globl _isr10
.globl _isr11
.globl _isr12
.globl _isr13
.globl _isr14
.globl _isr15
.globl _isr16
.globl _isr17
.globl _isr18
.globl _isr19
.globl _isr20
.globl _isr21
.globl _isr22
.globl _isr23
.globl _isr24
.globl _isr25
.globl _isr26
.globl _isr27
.globl _isr28
.globl _isr29
.globl _isr30
.globl _isr31
*/

#ifdef WIN32
.globl _irq0
.globl _irq1
.globl _irq2
.globl _irq3
.globl _irq4
.globl _irq5
.globl _irq6
.globl _irq7
.globl _irq8
.globl _irq9
.globl _irq10
.globl _irq11
.globl _irq12
.globl _irq13
.globl _irq14
.globl _irq15
.extern _irq_handler
#endif

#ifdef __linux__
.globl irq0
.globl irq1
.globl irq2
.globl irq3
.globl irq4
.globl irq5
.globl irq6
.globl irq7
.globl irq8
.globl irq9
.globl irq10
.globl irq11
.globl irq12
.globl irq13
.globl irq14
.globl irq15
.extern irq_handler
#endif

//.extern _fault_handler

#ifdef WIN32
_gdt_flush:
#endif
#ifdef __linux__
gdt_flush:
#endif
    mov 4(%esp), %eax
    lgdt (%eax)
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %ss

    jmp $0x08, $.flush
    .flush:
    ret

#ifdef WIN32
_idt_flush:
#endif
#ifdef __linux__
idt_flush:
#endif
    mov 4(%esp), %eax
    lidt (%eax)
    ret

/*
//-----------------------------------------------
// ISR CALLBACK:
//-----------------------------------------------
//
//
//  0: Divide By Zero Exception
//		pushl $0
//		pushl $0
_isr0:
    cli
    pushl $0
    pushl $0
    jmp isr_common_stub

//  1: Debug Exception
_isr1:
    cli
    pushl $0
    pushl $1
    jmp isr_common_stub

//  2: Non Maskable Interrupt Exception
_isr2:
    cli
    pushl $0
    pushl $2
    jmp isr_common_stub

//  3: Int 3 Exception
_isr3:
    cli
    pushl $0
    pushl $3
    jmp isr_common_stub

//  4: INTO Exception
_isr4:
    cli
    pushl $0
    pushl $4
    jmp isr_common_stub

//  5: Out of Bounds Exception
_isr5:
    cli
    pushl $0
    pushl $5
    jmp isr_common_stub

//  6: Invalid Opcode Exception
_isr6:
    cli
    pushl $0
    pushl $6
    jmp isr_common_stub

//  7: Coprocessor Not Available Exception
_isr7:
    cli
    pushl $0
    pushl $7
    jmp isr_common_stub

//  8: Double Fault Exception (With Error Code!)
_isr8:
    cli
    pushl $8
    jmp isr_common_stub

//  9: Coprocessor Segment Overrun Exception
_isr9:
    cli
    pushl $0
    pushl $9
    jmp isr_common_stub

// 10: Bad TSS Exception (With Error Code!)
_isr10:
    cli
    pushl $10
    jmp isr_common_stub

// 11: Segment Not Present Exception (With Error Code!)
_isr11:
    cli
    pushl $11
    jmp isr_common_stub

// 12: Stack Fault Exception (With Error Code!)
_isr12:
    cli
    pushl $12
    jmp isr_common_stub

// 13: General Protection Fault Exception (With Error Code!)
_isr13:
    cli
    pushl $13
    jmp isr_common_stub

// 14: Page Fault Exception (With Error Code!)
_isr14:
    cli
    pushl $14
    jmp isr_common_stub

// 15: Reserved Exception
_isr15:
    cli
    pushl $0
    pushl $15
    jmp isr_common_stub

// 16: Floating Point Exception
_isr16:
    cli
    pushl $0
    pushl $16
    jmp isr_common_stub

// 17: Alignment Check Exception
_isr17:
    cli
    pushl $0
    pushl $17
    jmp isr_common_stub

// 18: Machine Check Exception
_isr18:
    cli
    pushl $0
    pushl $18
    jmp isr_common_stub

// 19: Reserved
_isr19:
    cli
    pushl $0
    pushl $19
    jmp isr_common_stub

// 20: Reserved
_isr20:
    cli
    pushl $0
    pushl $20
    jmp isr_common_stub

// 21: Reserved
_isr21:
    cli
    pushl $0
    pushl $21
    jmp isr_common_stub

// 22: Reserved
_isr22:
    cli
    pushl $0
    pushl $22
    jmp isr_common_stub

// 23: Reserved
_isr23:
    cli
    pushl $0
    pushl $23
    jmp isr_common_stub

// 24: Reserved
_isr24:
    cli
    pushl $0
    pushl $24
    jmp isr_common_stub

// 25: Reserved
_isr25:
    cli
    pushl $0
    pushl $25
    jmp isr_common_stub

// 26: Reserved
_isr26:
    cli
    pushl $0
    pushl $26
    jmp isr_common_stub

// 27: Reserved
_isr27:
    cli
    pushl $0
    pushl $27
    jmp isr_common_stub

// 28: Reserved
_isr28:
    cli
    pushl $0
    pushl $28
    jmp isr_common_stub

// 29: Reserved
_isr29:
    cli
    pushl $0
    pushl $29
    jmp isr_common_stub

// 30: Reserved
_isr30:
    cli
    pushl $0
    pushl $30
    jmp isr_common_stub

// 31: Reserved
_isr31:
    cli
    pushl $0
    pushl $31
    jmp isr_common_stub


isr_common_stub:
    pusha
    push %ds
    push %es
    push %fs
    push %gs
    movw $0x10,%ax
    movw %ax,%ds
    movw %ax,%es
    movw %ax,%fs
    movw %ax,%gs
    movl %esp,%eax
    pushl %eax
    movl $_fault_handler, %eax
    call *%eax
    popl %eax
    popl %gs
    popl %fs
    popl %es
    popl %ds
    popa
    addl $8,%esp
    iret
*/

#ifdef WIN32
//-----------------------------------------------
// IRQ CALLBACK:
//-----------------------------------------------
//
//
// 32: IRQ0
_irq0:
    cli
		pushl $0
		pushl $32
    jmp irq_common_stub

// 33: IRQ1
_irq1:
    cli
		pushl $0
		pushl $33
    jmp irq_common_stub

// 34: IRQ2
_irq2:
    cli
		pushl $0
		pushl $34
    jmp irq_common_stub

// 35: IRQ3
_irq3:
    cli
		pushl $0
		pushl $35
    jmp irq_common_stub

// 36: IRQ4
_irq4:
   cli
		pushl $0
		pushl $36
    jmp irq_common_stub

// 37: IRQ5
_irq5:
   cli
		pushl $0
		pushl $37
    jmp irq_common_stub

// 38: IRQ6
_irq6:
   cli
		pushl $0
		pushl $38
    jmp irq_common_stub

// 39: IRQ7
_irq7:
   cli
		pushl $0
		pushl $39
    jmp irq_common_stub

// 40: IRQ8
_irq8:
   cli
		pushl $0
		pushl $40
    jmp irq_common_stub

// 41: IRQ9
_irq9:
   cli
		pushl $0
		pushl $41
    jmp irq_common_stub

// 42: IRQ10
_irq10:
   cli
		pushl $0
		pushl $42
    jmp irq_common_stub

// 43: IRQ11
_irq11:
   cli
		pushl $0
		pushl $43
    jmp irq_common_stub

// 44: IRQ12
_irq12:
   cli
		pushl $0
		pushl $44
    jmp irq_common_stub

// 45: IRQ13
_irq13:
   cli
		pushl $0
		pushl $45
    jmp irq_common_stub

// 46: IRQ14
_irq14:
   cli
		pushl $0
		pushl $46
    jmp irq_common_stub

// 47: IRQ15
_irq15:
   cli
		pushl $0
		pushl $47
    jmp irq_common_stub

irq_common_stub:
    pusha
    push %ds
    push %es
    push %fs
    push %gs
    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movl %esp, %eax
    pushl %eax
    movl $_irq_handler, %eax
    call *%eax
    popl %eax
    popl %gs
    popl %fs
    popl %es
    popl %ds
    popa
    addl $8, %esp
    iret

#endif // WIN32








#ifdef __linux__
//-----------------------------------------------
// IRQ CALLBACK:
//-----------------------------------------------
//
//
// 32: IRQ0
irq0:
    cli
		pushl $0
		pushl $32
    jmp irq_common_stub

// 33: IRQ1
irq1:
    cli
		pushl $0
		pushl $33
    jmp irq_common_stub

// 34: IRQ2
irq2:
    cli
		pushl $0
		pushl $34
    jmp irq_common_stub

// 35: IRQ3
irq3:
    cli
		pushl $0
		pushl $35
    jmp irq_common_stub

// 36: IRQ4
irq4:
    cli
		pushl $0
		pushl $36
    jmp irq_common_stub

// 37: IRQ5
irq5:
    cli
		pushl $0
		pushl $37
    jmp irq_common_stub

// 38: IRQ6
irq6:
    cli
		pushl $0
		pushl $38
    jmp irq_common_stub

// 39: IRQ7
irq7:
    cli
		pushl $0
		pushl $39
    jmp irq_common_stub

// 40: IRQ8
irq8:
    cli
		pushl $0
		pushl $40
    jmp irq_common_stub

// 41: IRQ9
irq9:
    cli
		pushl $0
		pushl $41
    jmp irq_common_stub

// 42: IRQ10
irq10:
    cli
		pushl $0
		pushl $42
    jmp irq_common_stub

// 43: IRQ11
irq11:
    cli
		pushl $0
		pushl $43
    jmp irq_common_stub

// 44: IRQ12
irq12:
    cli
		pushl $0
		pushl $44
    jmp irq_common_stub

// 45: IRQ13
irq13:
    cli
		pushl $0
		pushl $45
    jmp irq_common_stub

// 46: IRQ14
irq14:
    cli
		pushl $0
		pushl $46
    jmp irq_common_stub

// 47: IRQ15
irq15:
    cli
		pushl $0
		pushl $47
    jmp irq_common_stub

irq_common_stub:
    pusha
    push %ds
    push %es
    push %fs
    push %gs
    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movl %esp, %eax
    pushl %eax
    movl $irq_handler, %eax
    call *%eax
    popl %eax
    popl %gs
    popl %fs
    popl %es
    popl %ds
    popa
    addl $8, %esp
    iret

#endif // __linux__



