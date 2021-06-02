print_string:
	mov ah, 0x0e  ; teltype terminal (Move the cursor automatically) less hassle than 0x09 interrupt
	mov bh, 0x00
	.loop:
		cmp byte[di], 0
		je return
		mov al, byte[di]
		inc di
		int 0x10
		jmp .loop
