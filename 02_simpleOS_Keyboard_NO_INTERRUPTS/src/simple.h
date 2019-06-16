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
#define MAXLEN                1024

// keys:
#define KEY_BACKSPACE         8
#define KEY_TAB               9
#define KEY_ENTER             13
#define KEY_ESC               27
#define KEY_CTRL              29
#define KEY_SPACE             32
#define KEY_LSHIFT            42
#define KEY_RSHIFT            54
#define KEY_ALT               56

#define KEY_F1                128
#define KEY_F2                129
#define KEY_F3                130
#define KEY_F4                131
#define KEY_F5                132
#define KEY_F6                133
#define KEY_F7                134
#define KEY_F8                135
#define KEY_F9                136
#define KEY_F10               137

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

// keyboard.c
//
extern int		keyboard_getkey	(void);
extern void   keyboard_wait   (void);

// libc.c
//
extern uchar  inb             (ushort port);
extern ushort inw             (ushort port);
extern void   outb            (ushort port, uchar value);
//
extern void   video_clear     (void);
extern void   video_set_color (unsigned char c);
extern void		video_backspace	(void);
extern void   puts            (const char *s);
extern int    strcmp          (const char *s1, const char *s2);

#endif // ! _SIMPLE_H_

