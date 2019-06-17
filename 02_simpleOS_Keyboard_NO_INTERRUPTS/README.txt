

 SIMPLE OPERATING SYSTEM:

 A x86 (32 bits) Operating System in C.

 <<<<<<<<<<  THIS COMPILE ONLY TO 32 BITS  >>>>>>>>>>

 TO COMPILE TYPE:
   make clean
   make


 TO TEST WITH QEMU:
   qemu -kernel simpleOS_kernel
 OR
   qemu-system-i386 -kernel simpleOS_kernel


 TO TEST WITH GRUB( 1.x ):
 ----------------------------
 title SIMPLE OS
   kernel /simpleOS_kernel
 ----------------------------


 BY: Francisco - gokernel@hotmail.com
