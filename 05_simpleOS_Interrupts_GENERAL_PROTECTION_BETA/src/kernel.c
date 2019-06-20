//-------------------------------------------------------------------
//
// THIS FILE IS PART OF SIMPLE OPERATING SYSTEM:
//
//   The Kernel Core.
//
// MAIN FUNCTION:
//
//   void kernel_main ( struct multiboot_info * mbi );
//
// FILE:
//   kernel.c
//
// START DATE: 16/06/2019 - 10:40
//
//-------------------------------------------------------------------
//
#include "simple.h"

#define STR_CMD_SIZE    255
#define SHELL_PROMPT    "\nshell > "

static char
    string_command [ STR_CMD_SIZE + 1 ]
    ;

unsigned long timer_ticks = 0;

static int
    quit // for exit of main loop
    ;

int fps;

void call_hello (void);

void timer_handler (registers *reg) {

    timer_ticks++;

}

int GetCommandLine (char *string, int len) {
    static int pos = 0;
    int k;

    k = keyboard_getkey ();

    if (k > 0) {
        if (k == KEY_ENTER) {
            string [pos] = 0;
            pos = 0;
            return KEY_ENTER;
        } else if (k == KEY_BACKSPACE) {
            if (pos > 0) {
                pos--;
                video_backspace ();
            }
        } else if (k == KEY_TAB || k == KEY_ALT) {

            return k;

        } else if (pos < len && (k >= KEY_SPACE && k <= 126)) { //  126 = ( ~ )
            char buf [5] = { 0, 0, 0, 0 };
            string [pos++] = k;
            buf [0] = k;
            buf [1] = 0;
            puts (buf);
        } else {
            //return key;
        }
    }

    return 0;

}// GetCommandLine()

void keyboard_handler (registers *reg) {

    switch (GetCommandLine(string_command, STR_CMD_SIZE)) {
    case KEY_ENTER:
        if (!strcmp(string_command, "quit")) {
            puts ("\n");
            quit = 1;
            return;
        }
        //
        // "General Protection Fault",
        //
        if (!strcmp(string_command, "call_hello")) { // only for testing  ...
            call_hello();
            puts ("--- \n ---");
            puts (SHELL_PROMPT);
            return;
        }

        puts("\nCommand Not Found: '"); puts(string_command); puts("'");
        puts (SHELL_PROMPT);
        break;
    }// switch (GetCommandLine(...))

}// keyboard_handler ()

void init_timer (void) {
    int divisor = PIT_HZ / CLOCKS_PER_SEC;
    outb(0x43, 0x36);
    outb(0x40, divisor & 0xFF);
    outb(0x40, divisor >> 8);
    Intr_SetHandler (IRQ_TIMER, timer_handler);
}

int kernel_init (struct multiboot_info * mbi) {
    video_clear ();

    //-------------------------------------------
    // INTERRUPTS API:
    //-------------------------------------------
    //
    // interrupts API ( asm.S, interrupt.c ):
    //
    Intr_Init ();
    init_timer ();
    Intr_SetHandler (IRQ_KEYBOARD, keyboard_handler);

    //-------------------------------------------

    puts ("Kernel Init Keyboard INTERRUPTS...\n");
    return 1;
}

void kernel_finalize (void) {
    puts ("Kernel Finalize ...\n");
}

void kernel_wait (void) {
    asm volatile ("hlt");
}

static inline void iEnable (void) {
    asm volatile ("sti");
}

static inline void iDisable (void) {
    asm volatile ("cli");
}


void hello (int i) {
    printk ("\nMy Hello(%d): testing\n\n", i);
}


#define LONG_TO_BYTE(l) l, (l >> 8), (l >> 16), (l >> 24)
void call_hello (void) {
    long l = &hello;

    unsigned char code[] = {
    0x55,         // push  %ebp
    0x89, 0xe5,   // mov   %esp,%ebp
    // ... no setup %esp stack ...

    // PASS ARGUMENT ... QUEBRA ...
    //
    // c7 04 24 dc 05 00 00 	movl   $0x5dc,(%esp)
    0xc7, 0x04, 0x24, 0xdc, 0x05, 0x00, 0x00,

    // call hello()
    //-----------------------------
    0xb8, LONG_TO_BYTE(l),
    0xff, 0xd0,
    //-----------------------------

    0xc9,         // leave
    0xc3          // ret
    };

    ( (void(*)()) code ) ();

}

void kernel_main_loop (void) {
    puts ("To test <<<<< General Protection >>>>>>  type: 'call_hello'\n");
    puts ("To exit type: 'quit'\n");
    puts (SHELL_PROMPT);

    quit = 0;
    while (!quit) {

        fps++;

        if (timer_ticks % CLOCKS_PER_SEC == 0) {
            display_time (fps);
            fps = 0;
        }

        //
        // wait for the next interrupt
        //
        kernel_wait ();

    }// while (!quit)

}// kernel_main_loop()

void kernel_main (struct multiboot_info * mbi) {
    if (!kernel_init(mbi))
  return;
    kernel_main_loop ();
    kernel_finalize ();
}

