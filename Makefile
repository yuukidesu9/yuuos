rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

C_SRCS = $(call rwildcard,backbone boot cpu drivers memory libc .,*.c)
HEADERS = $(call rwildcard,backbone cpu drivers memory libc .,*.h)
ASM_SRCS = $(call rwildcard,boot cpu drivers memory libc,*.s)
OBJFILES = $(call rwildcard,backbone boot cpu drivers memory libc modules .,*.o)

AS = nasm
ASFLAGS = -f elf
CC = /c/i686-elf/bin/i686-elf-gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wextra -Werror -ffreestanding -c
LD = /c/i686-elf/bin/i686-elf-ld
LDFLAGS = -T link.ld -melf_i386

all: kernel.elf

kernel.elf: boot/boot_entry.o kmain.o $(OBJFILES)
	$(LD) $(LDFLAGS) $^ -o build/iso/boot/$@

yuuos_grub.iso: kernel.elf
	mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A yuuOS -input-charset iso8859-1 -boot-info-table -o $@ build/iso
	mv yuuos_grub.iso build/yuuos_grub.iso

qemu-iso: yuuos_grub.iso
	qemu-system-i386 -cdrom build/yuuos_grub.iso -m 4 -monitor stdio

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o kernel.elf 