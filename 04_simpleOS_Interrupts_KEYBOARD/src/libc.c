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

int seconds, minutes, hours, video_count;

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

void video_put (void) {
    video [0] = 'A';
    video [1] = TXT_COLOR;
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

//-------------------------------------------------------------------

int strlen (const char *str) {
    register char *s = (char*)str;
    while (*++s) ;
    return s - str;
}

char *strcat (char *dest, const char *src) {
    char *s = dest;
	
    for (; *s != '\0'; s++); // go through dest until we reach a NUL

    while (*src != '\0')
        *(s++) = *(src++);
    *s = '\0';
	
    return dest;
}

char *strcpy (char *dest, const char *src) {
		while (*src != '\0')
				*(dest++) = *(src++);
		return dest;
}

int strcmp (const char *s1, const char *s2) {
    for (; *s1 == *s2; s1++, s2++)
        if (*s1 == '\0')
            return 0;
    return *s1 - *s2;
}

void * memset (void *s, int c, unsigned int n) {
    char *to = (char*) s;
    while (n-- > 0)
        *(to++) = c;
    return s;
}

void itoa (unsigned long n, unsigned char *s, char base) {
    unsigned long i, j;
    unsigned char tmp[20], digit;

    i = 0;
    do {
        j = n;
        n /= base;	// divide num by base
        n *= base;	// multiply num by b to isolate the digit
        digit = j - n;
		
        // change the numerical digit to printable ASCII value
        if (digit <= 9) {
            tmp[i] = digit + '0';
        } else {
            tmp[i] = digit - 0x0A + 'A';
        }
        n /= base;	// divide num by b again to get to the next digit
        i++;
    } while (n != 0);
	
    tmp[i] = '\0'; // add the terminator
	
    // reverse string
    j = strlen(tmp) - 1;
    for (i = 0; i < strlen(tmp); i++) {
        s[i] = tmp[j];
        j--;
    }
    s[i] = '\0';
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

void printk (const char *format, ...) {
    unsigned int *argp = (void *)&format;
    char buf[20];

    while (1) {

        switch (*format) {
        case '\0':
            return;

        case '\n':
            puts ("\n");
            break;
        case '%':
            format++; argp++;
            switch (*format) {
            case '%': video_putchar ('%'); argp--; break;
            case 'd': itoa (*argp, buf, 10); puts (buf); break;
//            case 'x': /* falling through */
//            case 'p': vga_put_unsigned_num (*argp, 16);         break;
            case 'c': video_putchar (*argp); break;
            case 's': puts ((char *)*argp); break;
            //default:  panic ("printk");                         break;
            }
            break;
        default:
            video_putchar (*format);
            break;
        }//: switch (*fmt)

        if (format[0] == '\\' && format[1] == 'n') { // new line
            puts ("\n");
            format++;
        }

        format++;

    }//: while (1)

}//: void printk (const char *format, ...)

void vsprintk (char *str, const char *format, va_list ap) {
	char *p = str;
	char *s; int d; char c; char buf[MAXLEN];
	int i = 0;
	
	*p = '\0';
	/* go through format until we reach a % */
	while (*format != '\0')
	{
		if (*format != '%') {	/* ordinary character */
			i = strlen(p);
			p[i] = *format;
			p[i + 1] = '\0';
		}
		
		else {
			switch (*(format + 1)) {
				case 'c':	/* char */
					c = (char) va_arg(ap, int);
					i = strlen(p);
					p[i] = c;
					p[i + 1]  = '\0';
					break;		
				case 's':	/* string */
					s = va_arg(ap, char *);
					strcat(p, s);
					break;
				case 'd':	/* integer */
				case 'i':
					d = va_arg(ap, int);
					itoa(d, buf, 10);	/* convert to string */
					strcat(p, buf);
					break;
				case 'x':	/* hexa-decimal */
					d = va_arg(ap, int);
					itoa(d, buf, 16);
					strcat(p, buf);
					break;
				default:
					/* print the % and the following character */
					i = strlen(p);
					p[i]  = *format;
					p[i + 1]  = *(format + 1);
					p[i + 2]  = '\0';
					break;
			}
			format++;
		}
		format++;
	}
}


void sprintk (char *str, const char *format, ...) {
    va_list ap;
    va_start (ap, format);
    vsprintk (str, format, ap);
    va_end (ap);
    //return strlen (str);
}


char buf[100];
void display_time (int value) {
    int save_line = line;
    int save_pos = pos;

    asm volatile ("mov $0, %al");    // 0 = seconds
    asm volatile ("out %al, $0x70");
    asm volatile ("in $0x71, %al");
    #ifdef WIN32
    asm volatile ("mov %al, _seconds");  // copy ( %al ) in var ( seg )
    #endif
    #ifdef __linux__
    asm volatile ("mov %al, seconds");  // copy ( %al ) in var ( seg )
    #endif

    asm volatile ("mov $2, %al");    // 2 = minutes
    asm volatile ("out %al, $0x70");
    asm volatile ("in $0x71, %al");
    #ifdef WIN32
    asm volatile ("mov %al, _minutes");  // copy ( %al ) in var ( seg )
    #endif
    #ifdef __linux__
    asm volatile ("mov %al, minutes");  // copy ( %al ) in var ( seg )
    #endif

    asm volatile ("mov $4, %al");    // 2 = hours
    asm volatile ("out %al, $0x70");
    asm volatile ("in $0x71, %al");
    #ifdef WIN32
    asm volatile ("mov %al, _hours");  // copy ( %al ) in var ( seg )
    #endif
    #ifdef __linux__
    asm volatile ("mov %al, hours");  // copy ( %al ) in var ( seg )
    #endif

    text_color = VGA_COLOR_LIGHT_GREEN;

    pos = 0;
    line = 0;
//		sprintk (buf, "%s: %d", "FPS", value);
    printk ("Time: %d:%d:%d | %d | FPS %d ",
        ((hours   & 0x0F) + ((hours   / 16) * 10)),
        ((minutes & 0x0F) + ((minutes / 16) * 10)),
        ((seconds & 0x0F) + ((seconds / 16) * 10)),
        video_count++,
        value
        );
//    puts (buf);
    line = save_line;
    pos = save_pos;
    set_cursor_position (pos/2);

    text_color = TXT_COLOR;
}

