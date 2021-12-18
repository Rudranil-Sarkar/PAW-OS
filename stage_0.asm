[org 0x7c00]

;; Setting the segment registers to their defaults

	cli							; This is important to disable interrupts
	xor ax, ax					; 0 out the register

	mov ds, ax
	mov es, ax

	mov ss, ax
	mov sp, 0x9000
	mov bp, sp
	mov [boot_drive], dl		; the bios stroes our boot drive in dl better to store it
	sti

modeblock:	times 256 db 0  	; For setting the framebuffer address

main
	mov di, Welcome_msg
	call print_string
	;; Get the VESA info and store it in modeblock buffer
	mov ax, 0x4F01				; The actual function we want to call to get the info
	mov cx, 0x4105				; The mode number for display mode we want
	mov di, modeblock			; The pointer for storing the VBE info structure
	int 0x10

	;; Read the hard drive and load the kernel into memory
	call read_disk

	;; set the screen mode to 1024x768 with 8bit colors (256 possible colors)
	mov ax, 0x4F02
	mov bx, 0x4105
	int 0x10

	;; Time to make it big prepering for the switch to 32 bit

	cli							; disable interrupts
	lgdt [GDT_DESCRIPTOR]

	;; stage 0 complete and let's switch to 32 bit

	;; to switch to 32bit we need to set the first bit of special CPU control register named cr0
	mov eax, cr0
	or eax, 0x1
	mov cr0, eax

	jmp CODE_SEG:protected_mode_setup

read_disk:
	mov ah, 0x08				; read the drive parameters to get the num of sectors in a track
	mov dl, [boot_drive]
	int 0x13

	and cl, 0x3f				; get the number of sectors per track
	mov [drive_sectors], cl
	mov [sector_read], cl
	
	;; now attempt to read the sectors of the disk
	mov ah, 0x02
	mov al, [sector_read]
	mov ch, [drive_cylynder]
	mov cl, 0x02				; read from the 2nd sector (skip the bootloader)
	mov dh, [drive_head]
	mov dl, [boot_drive]
	mov bx, kernel_offset
	mov es, bx
	mov bx, 0x0000

	;; Todo auto increament the head, cyclinder to read the whole disk

	int 0x13
	jc Disk_error
	ret

Disk_error:
	mov di, disk_error_msg
	call print_string
	jmp $

%include "print_string.asm"

;; varaibles -------------------------

Welcome_msg: db "welcome to pawos", 0
disk_error_msg: db "Disk Error", 0

boot_drive: db 0x00
track_num: db 0x00
drive_head: db 0x0
drive_cylynder: db 0x0
drive_sectors: db 0x00
sector_read: db 0x0f
kernel_offset equ 0x1000  		; we are gonna load the kernel at 0x10000

;; The most hard and annoying part of the whole thing YES the GDT

;; GDT (Global Descripter Table) indicates the cpu the properties of the segments, privilage level of the segments etc
;; here we are defining the simplest possible segments called the flat model that allows us to use the whole 4GB of memory

;; Two overlapping code and data sectors

	ALIGN 16
GDT_START:
GDT_NULL:
	dd 0x00
	dd 0x00

GDT_CODE:
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 10011010b
	db 11001111b
	db 0x0

GDT_DATA:
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 10010010b
	db 11001111b
	db 0x0

GDT_END:

	ALIGN 16
GDT_DESCRIPTOR:
	dw GDT_END - GDT_START - 1
	dd GDT_START

	CODE_SEG equ GDT_CODE - GDT_START
	DATA_SEG equ GDT_DATA - GDT_START

[bits 32]
protected_mode_setup:

;; We are in 32 bit world now

;; Reinitialize the segment registers and stack
	mov ax, DATA_SEG
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	mov esp, 0x3000
	mov ebp, esp

	mov eax, 0x10000
	mov esi, modeblock
	jmp 0x10000								; go and start execute the kernel code

times 510 - ($ - $$) db 0					; fill the void
dw 0xaa55									; The bootable flag
