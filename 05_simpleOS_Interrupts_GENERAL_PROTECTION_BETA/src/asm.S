//-------------------------------------------------------------------
//
// THIS FILE IS PART OF SIMPLE OPERATING SYSTEM:
//
//   The Interrupt API.
//
// FILE:
//   asm.S
//
// This API is based in this:
//
// REFERENCE:
//   http://www.osdever.net/bkerndev/index.php
//   https://sourceforge.net/projects/flick/
//   https://github.com/ketanhwr/exylus
//
// START DATE: 16/06/2019 - 10:40
//
//-------------------------------------------------------------------
//
.code32    

#ifdef WIN32
.globl _gdt_flush

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
#endif
#ifdef __linux__
.globl gdt_flush

.globl isr0
.globl isr1
.globl isr2
.globl isr3
.globl isr4
.globl isr5
.globl isr6
.globl isr7
.globl isr8
.globl isr9
.globl isr10
.globl isr11
.globl isr12
.globl isr13
.globl isr14
.globl isr15
.globl isr16
.globl isr17
.globl isr18
.globl isr19
.globl isr20
.globl isr21
.globl isr22
.globl isr23
.globl isr24
.globl isr25
.globl isr26
.globl isr27
.globl isr28
.globl isr29
.globl isr30
.globl isr31
#endif

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
.extern _fault_handler
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
.extern fault_handler
#endif

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

//-----------------------------------------------
// ISR CALLBACK:
//-----------------------------------------------
//
//
//  0: Divide By Zero Exception
//		pushl $0
//		pushl $0
#ifdef WIN32
_isr0:
#endif
#ifdef __linux__
isr0:
#endif
    cli
    pushl $0
    pushl $0
    jmp isr_common_stub

//  1: Debug Exception
#ifdef WIN32
_isr1:
#endif
#ifdef __linux__
isr1:
#endif
    cli
    pushl $0
    pushl $1
    jmp isr_common_stub

//  2: Non Maskable Interrupt Exception
#ifdef WIN32
_isr2:
#endif
#ifdef __linux__
isr2:
#endif
    cli
    pushl $0
    pushl $2
    jmp isr_common_stub

//  3: Int 3 Exception
#ifdef WIN32
_isr3:
#endif
#ifdef __linux__
isr3:
#endif
    cli
    pushl $0
    pushl $3
    jmp isr_common_stub

//  4: INTO Exception
#ifdef WIN32
_isr4:
#endif
#ifdef __linux__
isr4:
#endif
    cli
    pushl $0
    pushl $4
    jmp isr_common_stub

//  5: Out of Bounds Exception
#ifdef WIN32
_isr5:
#endif
#ifdef __linux__
isr5:
#endif
    cli
    pushl $0
    pushl $5
    jmp isr_common_stub

//  6: Invalid Opcode Exception
#ifdef WIN32
_isr6:
#endif
#ifdef __linux__
isr6:
#endif
    cli
    pushl $0
    pushl $6
    jmp isr_common_stub

//  7: Coprocessor Not Available Exception
#ifdef WIN32
_isr7:
#endif
#ifdef __linux__
isr7:
#endif
    cli
    pushl $0
    pushl $7
    jmp isr_common_stub

//  8: Double Fault Exception (With Error Code!)
#ifdef WIN32
_isr8:
#endif
#ifdef __linux__
isr8:
#endif
    cli
    pushl $8
    jmp isr_common_stub

//  9: Coprocessor Segment Overrun Exception
#ifdef WIN32
_isr9:
#endif
#ifdef __linux__
isr9:
#endif
    cli
    pushl $0
    pushl $9
    jmp isr_common_stub

// 10: Bad TSS Exception (With Error Code!)
#ifdef WIN32
_isr10:
#endif
#ifdef __linux__
isr10:
#endif
    cli
    pushl $10
    jmp isr_common_stub

// 11: Segment Not Present Exception (With Error Code!)
#ifdef WIN32
_isr11:
#endif
#ifdef __linux__
isr11:
#endif
    cli
    pushl $11
    jmp isr_common_stub

// 12: Stack Fault Exception (With Error Code!)
#ifdef WIN32
_isr12:
#endif
#ifdef __linux__
isr12:
#endif
    cli
    pushl $12
    jmp isr_common_stub

// 13: General Protection Fault Exception (With Error Code!)
#ifdef WIN32
_isr13:
#endif
#ifdef __linux__
isr13:
#endif
    cli
    pushl $13
    jmp isr_common_stub

// 14: Page Fault Exception (With Error Code!)
#ifdef WIN32
_isr14:
#endif
#ifdef __linux__
isr14:
#endif
    cli
    pushl $14
    jmp isr_common_stub

// 15: Reserved Exception
#ifdef WIN32
_isr15:
#endif
#ifdef __linux__
isr15:
#endif
    cli
    pushl $0
    pushl $15
    jmp isr_common_stub

// 16: Floating Point Exception
#ifdef WIN32
_isr16:
#endif
#ifdef __linux__
isr16:
#endif
    cli
    pushl $0
    pushl $16
    jmp isr_common_stub

// 17: Alignment Check Exception
#ifdef WIN32
_isr17:
#endif
#ifdef __linux__
isr17:
#endif
    cli
    pushl $0
    pushl $17
    jmp isr_common_stub

// 18: Machine Check Exception
#ifdef WIN32
_isr18:
#endif
#ifdef __linux__
isr18:
#endif
    cli
    pushl $0
    pushl $18
    jmp isr_common_stub

// 19: Reserved
#ifdef WIN32
_isr19:
#endif
#ifdef __linux__
isr19:
#endif
    cli
    pushl $0
    pushl $19
    jmp isr_common_stub

// 20: Reserved
#ifdef WIN32
_isr20:
#endif
#ifdef __linux__
isr20:
#endif
    cli
    pushl $0
    pushl $20
    jmp isr_common_stub

// 21: Reserved
#ifdef WIN32
_isr21:
#endif
#ifdef __linux__
isr21:
#endif
    cli
    pushl $0
    pushl $21
    jmp isr_common_stub

// 22: Reserved
#ifdef WIN32
_isr22:
#endif
#ifdef __linux__
isr22:
#endif
    cli
    pushl $0
    pushl $22
    jmp isr_common_stub

// 23: Reserved
#ifdef WIN32
_isr23:
#endif
#ifdef __linux__
isr23:
#endif
    cli
    pushl $0
    pushl $23
    jmp isr_common_stub

// 24: Reserved
#ifdef WIN32
_isr24:
#endif
#ifdef __linux__
isr24:
#endif
    cli
    pushl $0
    pushl $24
    jmp isr_common_stub

// 25: Reserved
#ifdef WIN32
_isr25:
#endif
#ifdef __linux__
isr25:
#endif
    cli
    pushl $0
    pushl $25
    jmp isr_common_stub

// 26: Reserved
#ifdef WIN32
_isr26:
#endif
#ifdef __linux__
isr26:
#endif
    cli
    pushl $0
    pushl $26
    jmp isr_common_stub

// 27: Reserved
#ifdef WIN32
_isr27:
#endif
#ifdef __linux__
isr27:
#endif
    cli
    pushl $0
    pushl $27
    jmp isr_common_stub

// 28: Reserved
#ifdef WIN32
_isr28:
#endif
#ifdef __linux__
isr28:
#endif
    cli
    pushl $0
    pushl $28
    jmp isr_common_stub

// 29: Reserved
#ifdef WIN32
_isr29:
#endif
#ifdef __linux__
isr29:
#endif
    cli
    pushl $0
    pushl $29
    jmp isr_common_stub

// 30: Reserved
#ifdef WIN32
_isr30:
#endif
#ifdef __linux__
isr30:
#endif
    cli
    pushl $0
    pushl $30
    jmp isr_common_stub

// 31: Reserved
#ifdef WIN32
_isr31:
#endif
#ifdef __linux__
isr31:
#endif
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
    #ifdef WIN32
    movl $_fault_handler, %eax
    #endif
    #ifdef __linux__
    movl $fault_handler, %eax
    #endif
    call *%eax
    popl %eax
    popl %gs
    popl %fs
    popl %es
    popl %ds
    popa
    addl $8,%esp
    iret


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



