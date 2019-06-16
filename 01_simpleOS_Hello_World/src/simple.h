//-------------------------------------------------------------------
//
// THIS FILE IS PART OF SIMPLE OPERATING SYSTEM:
//
//   The Main Header:
//
// FILE:
//   simple.h
//
// START DATE: 16/06/2019 - 10:40
//
//-------------------------------------------------------------------
//
#ifndef _SIMPLE_H_
#define _SIMPLE_H_

//-----------------------------------------------
//------------------  INCLUDE  ------------------
//-----------------------------------------------
//
#include "multiboot.h"

//-----------------------------------------------
//---------------  DEFINE / ENUM  ---------------
//-----------------------------------------------
//
#define TXT_COLOR             7

enum {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

//-----------------------------------------------
//------------------  TYPEDEF  ------------------
//-----------------------------------------------
//
typedef unsigned char         uchar;
typedef unsigned short        ushort;
typedef unsigned int          uint;
typedef unsigned long         ulong;

// kernel.c
//
extern void   kernel_main     (struct multiboot_info * mbi);

// libc.c
//
extern uchar  inb             (ushort port);
extern ushort inw             (ushort port);
extern void   outb            (ushort port, uchar value);
//
extern void   video_clear     (void);
extern void   video_set_color (unsigned char c);
extern void   puts            (const char *s);

#endif // ! _SIMPLE_H_

