C_SOURCES = $(wildcard loader/*.c drivers/*.c cpu/*.c libc/*.c)
HEADERS = $(wildcard loader/*.h drivers/*.h cpu/*.h libc/*.h)
# Nice syntax for file extension replacement
OBJ = ${C_SOURCES:.c=.o cpu/interrupt.o}

AS = nasm
CC = /c/i686-elf/bin/i686-elf-gcc
LD = /c/i686-elf/bin/i686-elf-ld

CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -ffreestanding -c
LDFLAGS = -T link.ld -melf_i386


# First rule is run by default
#os_image.img: boot/bootsect.bin kernel.bin
	#cat $^ > build/os_image.img
	#$(info Image created.)

# some variables to build the ISO.
FILESIZE = $(shell stat -c%s "build/os_image.img")
SECTORSIZE = 512
DIVIDED = $(shell echo $$(($(FILESIZE) / $(SECTORSIZE))))
FLOPPYSECS = 2876
FILLERSIZE = $(shell echo $$(($(FLOPPYSECS) - $(DIVIDED))))

os_boot.iso: _floppy.img _floppy.catalog
	rm "build/os_boot.iso"
	mkisofs -r -b "build/_floppy.img" -c "build/_floppy.catalog" -o "build/os_boot.iso" .

yuuos_grub.iso: kernel.elf
	mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A yuuOS -input-charset iso8859-1 -boot-info-table -o $@ build/iso
	mv yuuos_grub.iso build/yuuos_grub.iso

_floppy.catalog: _floppy.img
	touch build/_floppy.catalog
	$(info Catalog file built.)
    
_floppy.img: os_image.img
	$(info Filesize: $(FILESIZE), No. of sectors: $(DIVIDED))
	dd if="/dev/zero" bs=$(SECTORSIZE) count=$(FILLERSIZE) of="build/_filler.img"
	$(info Filler created.)
	cat build/os_image.img build/_filler.img > build/_floppy.img
	$(info Secondary image created.)

# '--oformat binary' deletes all symbols as a collateral, so we don't need
# to 'strip' them manually on this case

kernel.bin: boot/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^ --oformat binary

help:
	$(info Commands of this makefile:)
	$(info make: builds a standalone 1.44MB floppy image)
	$(info make qemu-old-floppy: builds and runs a 1.44MB floppy image on QEMU)
	$(info make qemu-old-iso: builds and runs an ISO image on QEMU)
	$(info make qemu-iso: builds and runs an ISO image on QEMU - New format)
	$(info make vbox-iso: builds and runs an ISO image on VirtualBox)
	$(info make vmware-iso: builds and runs an ISO image on VMWare Player)
	$(info make clean: cleans up the build environment)
	$(info make help: this command)

kernel.elf: boot/loader_entry.o kernel/kernel.o ${OBJ}
	${LD} ${LDFLAGS} $^ -o build/iso/boot/$@
	$(info File kernel.elf generated successfully.)

qemu-old-floppy: os_image.img
	qemu-system-i386 -fda build/os_image.img
    
qemu-old-iso: os_boot.iso
	qemu-system-i386 -cdrom build/os_boot.iso
    
qemu-iso: yuuos_grub.iso
	qemu-system-i386 -cdrom build/yuuos_grub.iso
    
vbox-old-iso: os_boot.iso
	VBoxManage startvm "yuuOS"

vmware-iso: os_boot.iso
	vmrun start "../../Virtual Machines/yuuOS/yuuOS.vmx"

# Generic rules for wildcards
# To make an object, always compile from its .c
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} $< -o $@

%.o: %.asm
	${AS} $< -f elf -o $@

%.bin: %.asm
	${AS} $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o *.elf
	rm -rf loader/*.o boot/*.bin drivers/*.o boot/*.o cpu/*.o libc/*.o
