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

#define NULL                  ((void*)0)
#define TXT_COLOR             7
#define MAXLEN                1024

#define PIT_HZ                1193182
#define CLOCKS_PER_SEC        1000
#define IRQ_TIMER             0
#define IRQ_KEYBOARD          1

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

typedef char                  * va_list;

/* Amount of space required in an argument list for an arg of type TYPE.
   TYPE may alternatively be an expression whose type is used.  */

#define __va_rounded_size(TYPE)  \
  (((sizeof (TYPE) + sizeof (int) - 1) / sizeof (int)) * sizeof (int))

#define va_start(AP, LASTARG) \
 (AP = ((char *) &(LASTARG) + __va_rounded_size(LASTARG)))

extern void va_end (va_list);
#define va_end(AP) /* Nothing */

#define va_arg(AP, TYPE) (AP += __va_rounded_size (TYPE), \
  *((TYPE *) (AP - __va_rounded_size (TYPE))))

typedef struct { // IRQ HANDLER CALLBACK ARGUENT
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;
} registers;

extern int fps;

// kernel.c
//
extern void   kernel_main     (struct multiboot_info * mbi);

// keyboard.c
//
extern int		keyboard_getkey	(void);
extern void   keyboard_wait   (void);

// interrupt.c
//
extern void   Intr_Init       (void);
extern void   Intr_SetHandler (int irq, void (*handler)(registers *r));

// libc.c
//
extern uchar  inb             (ushort port);
extern ushort inw             (ushort port);
extern void   outb            (ushort port, uchar value);
extern void   display_time    (int value);
//
extern void   video_clear     (void);
extern void   video_put       (void);
extern void   video_set_color (unsigned char c);
extern void		video_backspace	(void);
//
extern int    strlen          (const char *str);
extern char	*	strcat					(char *dest, const char *src);
extern char	*	strcpy					(char *dest, const char *src);
extern int    strcmp          (const char *s1, const char *s2);
extern void * memset          (void *s, int c, unsigned int n);
extern void   itoa            (unsigned long n, unsigned char *s, char base);
//
extern void   puts            (const char *s);
extern void   printk          (const char *format, ...);
extern void		sprintk					(char *str, const char *format, ...);
extern void		vsprintk				(char *str, const char *format, va_list ap);

extern void   Console_Format  (const char *fmt, ...);

#endif // ! _SIMPLE_H_
