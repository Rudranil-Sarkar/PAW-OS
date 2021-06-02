[bits 32]
[extern _main]
global _start

_start:
call _main
jmp Hang_up

Hang_up: jmp $
