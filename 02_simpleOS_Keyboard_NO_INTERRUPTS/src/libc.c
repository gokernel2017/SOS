//-------------------------------------------------------------------
//
// THIS FILE IS PART OF SIMPLE OPERATING SYSTEM:
//
//   LibC Implementation.
//
// FILE:
//   libc.c
//
// START DATE: 16/06/2019 - 10:40
//
//-------------------------------------------------------------------
//
#include "simple.h"

#define VIDEO_SIZE        4000  // 80 * 25 * 2
#define REG_SCREEN_CTRL   0x3D4
#define REG_SCREEN_DATA   0x3D5

static char *video = (char*)0xb8000; // video memory begins at address 0xb8000

static int
    text_color = 7,
    pos,
    line
    ;

uchar inb (ushort port) {
    uchar result;
    asm volatile ("inb %1, %0" : "=a" (result) : "d" (port));
    return result;
}

ushort inw (ushort port) {
    ushort ret;
    asm volatile ("inw %1, %0" : "=a" (ret) : "d" (port));
    return ret;
}

// Write a byte into the specified port
void outb (ushort port, uchar value) {
    asm volatile ("outb %0, %1" : :"a" (value), "d" (port)); //: metalkit
}

// Set cursor position
// The same implementation as in get_cursor_offset()
// Write to CTRL register 14 (0xE) and write Hi byte to DATA register
// Write to CTRL register 15 (0xF) and write Lo byte to DATA register
static void set_cursor_position (int offset) {
    outb (REG_SCREEN_CTRL, 14);
    outb (REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    outb (REG_SCREEN_CTRL, 15);
    outb (REG_SCREEN_DATA, (unsigned char)(offset & 0xFF));
}

void video_scroll (void) {
    register int i = 160;

    while (i < VIDEO_SIZE) {
        video [i-160] = video[i];
        i++;
    }

    // clear the last line
    i = (24*80*2);
    while (i < VIDEO_SIZE) {
        video [i] = ' ';
        video [i+1] = TXT_COLOR;
        i += 2;
    }
}

void video_backspace (void) {
    if (pos >= 2) {
        pos -= 2;
        video [pos] = ' ';
        video [pos+1] = TXT_COLOR;
        set_cursor_position (pos/2);
    }
}

void video_clear (void) {
    register int i = 0;
    while (i < VIDEO_SIZE) {
        video [i++] = ' ';
        video [i++] = TXT_COLOR;
    }
    pos = 0;
    line = 0;
}

void video_set_color (unsigned char c) {
    text_color = c;
}

void video_putchar (char c) {
    if (pos < VIDEO_SIZE) {
        video [pos] = c;
        video [pos+1] = text_color;
        pos += 2;
    } else {
        line = 24;
        video_scroll ();
        pos = (line*80*2);
        video_putchar (c);
    }
}

void puts (const char *s) {
    while (*s) {
        if (*s == '\n') {
            line++;
            pos = (line*80*2);
        } else {
            video_putchar (*s);
        }
        s++;
    }
    set_cursor_position (pos/2);
}

int strcmp (const char *s1, const char *s2) {
    for (; *s1 == *s2; s1++, s2++)
        if (*s1 == '\0')
            return 0;	/* equal */
    return *s1 - *s2;
}

