### PAW OS
![screen](https://github.com/Rudranil-Sarkar/PAW-OS/blob/master/Screenshots/screen.png)
##### This is demo operating system that boots up and displays a logo and a message to the screen. Nothing usefull for now.
Currently the project is targeted for old BIOS style boot systems not UEFI/EFI.

List of work currently done:
 - Switch to graphics mode
 - Jump to protected 32bit mode
 - Bitmap font rendering

I highly recommend to run it in qemu as it may not work in all real hardware.

#### Dependencies
 - nasm (assembler)
 - gcc (C compiler)
 - ld (linker)
    

#### Buid Instructions
Just use `make`. It will generate a file named `os_image`. Use it on qemu to run.
