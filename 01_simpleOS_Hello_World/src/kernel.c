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

int kernel_init (struct multiboot_info * mbi) {
    video_clear ();
    puts ("Kernel Init ...\n");
    return 1;
}

void kernel_finalize (void) {
    puts ("Kernel Finalize ...\n");
}

void kernel_main_loop (void) {
    video_set_color (VGA_COLOR_LIGHT_GREEN);
    puts ("... Kernel Main Loop ...\n");
    video_set_color (TXT_COLOR);
}

void kernel_main (struct multiboot_info * mbi) {
    if (!kernel_init(mbi))
  return;
    kernel_main_loop ();
    kernel_finalize ();
}

