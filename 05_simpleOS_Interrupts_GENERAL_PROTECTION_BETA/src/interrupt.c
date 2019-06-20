//-------------------------------------------------------------------
//
// THIS FILE IS PART OF SIMPLE OPERATING SYSTEM:
//
//   The Interrupt API.
//
// FILE:
//   interrupt.c
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
#include "simple.h"

struct gdt_entry {
    unsigned short limit;
    unsigned short base;
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((packed)); // prevents compiler any "optimization" on structure

struct gdt_ptr {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct idt_entry {
    unsigned short base_lo;
    unsigned short sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_hi;
} __attribute__((packed));

struct idt_ptr {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));


struct gdt_entry  GDT_ENTRY [5];
struct gdt_ptr    GDT_PTR;

struct idt_entry  IDT_ENTRY [256];
struct idt_ptr    IDT_PTR;

void * irq_routines [16] = { NULL };

// This is in ( asm.S ) We use this to properly reload
extern void gdt_flush (unsigned int);
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
//
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();


// Setup a descriptor in the Global Descriptor Table
static void gdt_set_gate (int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran) {
    // Setup the descriptor base address
    GDT_ENTRY[num].base = (base & 0xFFFF);
    GDT_ENTRY[num].base_middle = (base >> 16) & 0xFF;
    GDT_ENTRY[num].base_high = (base >> 24) & 0xFF;

    // Setup the descriptor limits
    GDT_ENTRY[num].limit = (limit & 0xFFFF);
    GDT_ENTRY[num].granularity = ((limit >> 16) & 0x0F);

    // Finally, set up the granularity and access flags
    GDT_ENTRY[num].granularity |= (gran & 0xF0);
    GDT_ENTRY[num].access = access;
}

/* Should be called by main. This will setup the special GDT
*  pointer, set up the first 3 entries in our GDT, and then
*  finally call gdt_flush() in our assembler file in order
*  to tell the processor where the new GDT is and update the
*  new segment registers */
static void install_gdt (void) {
    // Setup the GDT pointer and limit
    GDT_PTR.limit = (sizeof(struct gdt_entry) * 5) - 1;
    GDT_PTR.base = (uint)&GDT_ENTRY;

/*
    // Our NULL descriptor
    gdt_set_gate (0, 0, 0, 0, 0);

    // The second entry is our Code Segment. The base address
    // is 0, the limit is 4GBytes, it uses 4KByte granularity,
   //  uses 32-bit opcodes, and is a Code Segment descriptor.
   //  Please check the table above in the tutorial in order
   //  to see exactly what each value means 
    gdt_set_gate (1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    // The third entry is our Data Segment. It's EXACTLY the
    //  same as our code segment, but the descriptor type in
    //  this entry's access byte says it's a Data Segment
    gdt_set_gate (2, 0, 0xFFFFFFFF, 0x92, 0xCF);
*/
    gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

    // Flush out the old GDT and install the new changes!
    gdt_flush((uint)&GDT_PTR);
}

static void idt_set_gate (uchar num, uint base, ushort sel, uchar flags) {
    IDT_ENTRY[num].base_lo = base & 0xFFFF;
    IDT_ENTRY[num].base_hi = (base >> 16) & 0xFFFF;
    IDT_ENTRY[num].sel = sel;
    IDT_ENTRY[num].always0 = 0;
    IDT_ENTRY[num].flags = flags;
}

static void install_idt (void) {
    IDT_PTR.limit = sizeof(struct idt_entry) * 256 -1;
    IDT_PTR.base = (uint)&IDT_ENTRY;

    memset (&IDT_ENTRY, 0, sizeof(struct idt_entry)*256);


	idt_set_gate(0, (uint)isr0, 0x08, 0x8E);
	idt_set_gate(1, (uint)isr1, 0x08, 0x8E);
	idt_set_gate(2, (uint)isr2, 0x08, 0x8E);
	idt_set_gate(3, (uint)isr3, 0x08, 0x8E);
	idt_set_gate(4, (uint)isr4, 0x08, 0x8E);
	idt_set_gate(5, (uint)isr5, 0x08, 0x8E);
	idt_set_gate(6, (uint)isr6, 0x08, 0x8E);
	idt_set_gate(7, (uint)isr7, 0x08, 0x8E);
	idt_set_gate(8, (uint)isr8, 0x08, 0x8E);
	idt_set_gate(9, (uint)isr9, 0x08, 0x8E);
	idt_set_gate(10, (uint)isr10, 0x08, 0x8E);
	idt_set_gate(11, (uint)isr11, 0x08, 0x8E);
	idt_set_gate(12, (uint)isr12, 0x08, 0x8E);
	idt_set_gate(13, (uint)isr13, 0x08, 0x8E);
	idt_set_gate(14, (uint)isr14, 0x08, 0x8E);
	idt_set_gate(15, (uint)isr15, 0x08, 0x8E);
	idt_set_gate(16, (uint)isr16, 0x08, 0x8E);
	idt_set_gate(17, (uint)isr17, 0x08, 0x8E);
	idt_set_gate(18, (uint)isr18, 0x08, 0x8E);
	idt_set_gate(19, (uint)isr19, 0x08, 0x8E);
	idt_set_gate(20, (uint)isr20, 0x08, 0x8E);
	idt_set_gate(21, (uint)isr21, 0x08, 0x8E);
	idt_set_gate(22, (uint)isr22, 0x08, 0x8E);
	idt_set_gate(23, (uint)isr23, 0x08, 0x8E);
	idt_set_gate(24, (uint)isr24, 0x08, 0x8E);
	idt_set_gate(25, (uint)isr25, 0x08, 0x8E);
	idt_set_gate(26, (uint)isr26, 0x08, 0x8E);
	idt_set_gate(27, (uint)isr27, 0x08, 0x8E);
	idt_set_gate(28, (uint)isr28, 0x08, 0x8E);
	idt_set_gate(29, (uint)isr29, 0x08, 0x8E);
	idt_set_gate(30, (uint)isr30, 0x08, 0x8E);
	idt_set_gate(31, (uint)isr31, 0x08, 0x8E);

    #ifdef WIN32
    asm volatile ("lidt _IDT_PTR");
    #endif
    #ifdef __linux__
    asm volatile ("lidt IDT_PTR");
    #endif
}

// IRQ:

static void irq_remap (void) {
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}

static void install_irq (void) {
    irq_remap();

    idt_set_gate(32, (uint)irq0, 0x08, 0x8E);
    idt_set_gate(33, (uint)irq1, 0x08, 0x8E);
    idt_set_gate(34, (uint)irq2, 0x08, 0x8E);
    idt_set_gate(35, (uint)irq3, 0x08, 0x8E);
    idt_set_gate(36, (uint)irq4, 0x08, 0x8E);
    idt_set_gate(37, (uint)irq5, 0x08, 0x8E);
    idt_set_gate(38, (uint)irq6, 0x08, 0x8E);
    idt_set_gate(39, (uint)irq7, 0x08, 0x8E);
    idt_set_gate(40, (uint)irq8, 0x08, 0x8E);
    idt_set_gate(41, (uint)irq9, 0x08, 0x8E);
    idt_set_gate(42, (uint)irq10, 0x08, 0x8E);
    idt_set_gate(43, (uint)irq11, 0x08, 0x8E);
    idt_set_gate(44, (uint)irq12, 0x08, 0x8E);
    idt_set_gate(45, (uint)irq13, 0x08, 0x8E);
    idt_set_gate(46, (uint)irq14, 0x08, 0x8E);
    idt_set_gate(47, (uint)irq15, 0x08, 0x8E);

    asm volatile ("sti");
}

void Intr_Init (void) {
    install_gdt();
    install_idt();
    install_irq();
}

void Intr_SetHandler (int irq, void (*handler)(registers *r)) {
    irq_routines[irq] = handler;
}



/* Each of the IRQ ISRs point to this function, rather than
*  the 'fault_handler' in 'isrs.c'. The IRQ Controllers need
*  to be told when you are done servicing them, so you need
*  to send them an "End of Interrupt" command (0x20). There
*  are two 8259 chips: The first exists at 0x20, the second
*  exists at 0xA0. If the second controller (an IRQ from 8 to
*  15) gets an interrupt, you need to acknowledge the
*  interrupt at BOTH controllers, otherwise, you only send
*  an EOI command to the first controller. If you don't send
*  an EOI, you won't raise any more IRQs */
//
void irq_handler (registers *r) {
    // This is a blank function pointer
    void (*handler)(registers *r);

    /* Find out if we have a custom handler to run for this
    *  IRQ, and then finally, run it */
    handler = irq_routines[r->int_no - 32];
    if (handler) {
        handler(r);
    }

    /* If the IDT entry that was invoked was greater than 40
    *  (meaning IRQ8 - 15), then we need to send an EOI to
    *  the slave controller */
    if (r->int_no >= 40)
    {
        outb(0xA0, 0x20);
    }

    /* In either case, we need to send an EOI to the master
    *  interrupt controller too */
    outb(0x20, 0x20);
}



// This is a simple string array. It contains the message that
// corresponds to each and every exception. We get the correct
//  message by accessing like:
//  exception_message[interrupt_number] 
char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

// All of our Exception handling Interrupt Service Routines will
//  point to this function. This will tell us what exception has
//  happened! Right now, we simply halt the system by hitting an
//  endless loop. All ISRs disable interrupts while they are being
//  serviced as a 'locking' mechanism to prevent an IRQ from
//  happening and messing up kernel data structures
void fault_handler (registers *r) {
    if (r->int_no < 32) {
        puts (exception_messages[r->int_no]);
        puts("\nException. System Halted!\n");
//        puts ("<<<<<<<<<< POR ESSA VEZ PASSA >>>>>>>>>>\n");
        asm volatile ("cli");
        asm volatile ("hlt");
        for (;;);
    }
}



