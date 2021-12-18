[bits 32]
[extern _main]
global _start

_start:
    mov edi, [esi + 0x28]
    mov dword [0x0FFC], edi
call _main
jmp Hang_up

Hang_up: jmp $
