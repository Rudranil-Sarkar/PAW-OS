CC=gcc
CCFLAGS= -m32 --std=c11 -O2 -g -Wall -Wextra -Wpedantic -Wstrict-aliasing -Wno-pointer-arith
CCFLAGS+= -Wno-unused-parameter -nostdlib -nostdinc -ffreestanding
CCFLAGS+= -fno-pie -fno-stack-protector -fno-builtin-function -fno-builtin -c



NASMFLAGS=-f bin
asm_files=$(wildcard ./*.asm)

kernel_src=kernel
kernel_files_h=$(wildcard $(kernel_src)/*.h)
kernel_files_c=$(wildcard $(kernel_src)/*.c)

output_folder=objs

all: os_image

os_image: $(output_folder)/boot_loader.bin $(output_folder)/kernel.bin
	cat $^ > $@

$(output_folder)/boot_loader.bin: $(asm_files) directory
	nasm stage_0.asm $(NASMFLAGS) -o $@

$(output_folder)/kernel_loader.o: ./kernel/kernel_loader.asm directory
	nasm $< -f elf -o $@

$(output_folder)/kernel.o: $(kernel_files_c) $(kernel_files_h) directory
	$(CC) $(CCFLAGS) $< -o $@

$(output_folder)/kernel.bin: $(output_folder)/kernel_loader.o $(output_folder)/kernel.o
	ld -o $@ -m elf_i386 --oformat binary -Ttext 0x10000 $^

run: os_image
	qemu-system-x86_64 -drive format=raw,file=$<

directory:
	mkdir -p $(output_folder)

