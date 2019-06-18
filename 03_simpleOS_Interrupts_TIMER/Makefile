#------------------------------------------------
#
# Project: Simple Operating System
#
#------------------------------------------------
#

CC = gcc
LD = ld
OBJCOPY = objcopy
RM = rm -f

OBJ         = obj/boot.o obj/asm.o obj/libc.o obj/keyboard.o obj/interrupt.o obj/kernel.o
BIN         = obj/kernel.bin
KERNEL_NAME = simpleOS_kernel

CFLAGS = -m32 -s -O2 -U_WIN32 -Wall -nostdinc -fno-exceptions -nostartfiles -ffreestanding -fno-builtin
LDFLAGS = -T src/link.ld -nostdlib

.PHONY: all all-before all-after clean clean-custom

all: $(KERNEL_NAME)

clean: clean-custom
	${RM} $(OBJ) $(BIN) $(KERNEL_NAME)

#################################################
$(KERNEL_NAME): $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o $(BIN)
	$(OBJCOPY) -O binary $(BIN) $(KERNEL_NAME)
#################################################

obj/boot.o: src/boot.S
	$(CC) -c src/boot.S -o obj/boot.o $(CFLAGS)

obj/asm.o: src/asm.S
	$(CC) -c src/asm.S -o obj/asm.o $(CFLAGS)

obj/libc.o: src/libc.c
	$(CC) -c src/libc.c -o obj/libc.o $(CFLAGS)

obj/keyboard.o: src/keyboard.c
	$(CC) -c src/keyboard.c -o obj/keyboard.o $(CFLAGS)

obj/interrupt.o: src/interrupt.c
	$(CC) -c src/interrupt.c -o obj/interrupt.o $(CFLAGS)

obj/kernel.o: src/kernel.c
	$(CC) -c src/kernel.c -o obj/kernel.o $(CFLAGS)
