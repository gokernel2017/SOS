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

#define SHELL_PROMPT    "\nshell > "

static char
    string_command [100]
    ;

int kernel_init (struct multiboot_info * mbi) {
    video_clear ();
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
        char buf [10] = { 0 };

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
            string [pos++] = k;
            buf [0] = k;
            buf [1] = 0;
            puts (buf);
        } else {
            //return key;
        }
    }

    return 0;
}

void kernel_main_loop (void) {

    puts ("\nKeyboard loop example ... NO INTERRUPTS\n");
    puts ("To exit type: 'quit'\n");
    puts (SHELL_PROMPT);

    for (;;) {

        keyboard_wait ();

        switch (GetCommandLine(string_command, sizeof(string_command)-1 )) {
        case KEY_ENTER:
            if (!strcmp(string_command, "quit")) {
                puts ("\n");
                return;
            }
            puts("\nCommand Not Found: '"); puts(string_command); puts("'");
            puts (SHELL_PROMPT);
            break;
        }
    }
}

void kernel_main (struct multiboot_info * mbi) {
    if (!kernel_init(mbi))
  return;
    kernel_main_loop ();
    kernel_finalize ();
}

