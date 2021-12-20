CC=gcc
CCFLAGS= -m32 --std=c11 -O2 -g -Wall -Wextra -Wpedantic -Wstrict-aliasing -Wno-pointer-arith
CCFLAGS+= -Wno-unused-parameter -nostdlib -nostdinc -ffreestanding
CCFLAGS+= -fno-pie -fno-stack-protector -fno-builtin-function -fno-builtin -mgeneral-regs-only -c

NASMFLAGS=-f bin
asm_files=$(wildcard ./*.asm)

kernel_src=kernel
kernel_files_c=$(wildcard $(kernel_src)/*.c)
kernel_objs=$(patsubst $(kernel_src)/%.c, $(output_folder)/%.o, $(kernel_files_c))
isoname=image.iso

output_folder=objs

os_image: $(output_folder)/boot_loader.bin $(output_folder)/kernel.bin
	cat $^ > $@

$(output_folder)/boot_loader.bin: $(asm_files) directory
	nasm stage_0.asm $(NASMFLAGS) -o $@

$(output_folder)/kernel_loader.o: ./kernel/kernel_loader.asm directory
	nasm $< -f elf -o $@

$(output_folder)/%.o: $(kernel_src)/%.c $(kernel_src)/%.h directory
	$(CC) $(CCFLAGS) $< -o $@

$(output_folder)/%.o: $(kernel_src)/%.c directory
	$(CC) $(CCFLAGS) $< -o $@

$(output_folder)/kernel.bin: $(output_folder)/kernel_loader.o $(kernel_objs)
	ld -o $@ -m elf_i386 --oformat binary -Ttext 0x10000 $^

run: os_image
	qemu-system-x86_64 -drive format=raw,file=$<

directory:
	mkdir -p $(output_folder)

blank_iso:
	dd if=/dev/zero of=$(isoname) iflag=fullblock bs=1M count=300
	fdisk $(isoname) < fdisk_input

iso: blank_iso os_image
	dd if=objs/boot_loader.bin of=$(isoname) conv=notrunc bs=440 count=1 # Skip the mbr partitiom
	dd if=objs/boot_loader.bin of=$(isoname) conv=notrunc bs=1 count=2 skip=510 seek=510 # The preserve the magic number
	dd if=objs/kernel.bin 	   of=$(isoname) conv=notrunc bs=1 seek=512 status=progress  # Add the kernel
