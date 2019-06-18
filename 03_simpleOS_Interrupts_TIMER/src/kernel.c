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
int fps;

void timer_handler (registers *reg) {

    timer_ticks++;
    fps++;

    if (timer_ticks % CLOCKS_PER_SEC == 0) {
        display_time (fps);
        fps = 0;
    }
}

void init_timer (int hz) {
    int divisor = PIT_HZ / hz;
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
    init_timer (CLOCKS_PER_SEC);

    //-------------------------------------------

    puts ("Kernel Init ...\n");
    return 1;
}

void kernel_finalize (void) {
    puts ("Kernel Finalize ...\n");
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

void kernel_main_loop (void) {

    puts ("\nKernel Interrups Example | TIMER\n\n");
    puts ("To exit type: 'quit'\n");
    puts (SHELL_PROMPT);

    for (;;) {

        keyboard_wait ();

        switch (GetCommandLine(string_command, STR_CMD_SIZE)) {
        case KEY_ENTER:
            if (!strcmp(string_command, "quit")) {
                puts ("\n");
                return;
            }
            puts("\nCommand Not Found: '"); puts(string_command); puts("'");
            puts (SHELL_PROMPT);
            break;
        }// switch (GetCommandLine(...))

    }// for (;;)

}// kernel_main_loop()

void kernel_main (struct multiboot_info * mbi) {
    if (!kernel_init(mbi))
  return;
    kernel_main_loop ();
    kernel_finalize ();
}

