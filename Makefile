C_SOURCES = $(wildcard loader/*.c drivers/*.c cpu/*.c libc/*.c)
HEADERS = $(wildcard loader/*.h drivers/*.h cpu/*.h libc/*.h)
# Nice syntax for file extension replacement
OBJ = ${C_SOURCES:.c=.o cpu/interrupt.o}

# Change this if your cross-compiler is somewhere else
CC = /c/i686-elf/bin/i686-elf-gcc

# -g: Use debugging symbols in gcc
CFLAGS = -g -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra



# First rule is run by default
os_image.img: boot/bootsect.bin kernel.bin
	cat $^ > build/os_image.img
	$(info Image created.)

# some variables to build the ISO.
FILESIZE = $(shell stat -c%s "build/os_image.img")
SECTORSIZE = 512
DIVIDED = $(shell echo $$(($(FILESIZE) / $(SECTORSIZE))))
FLOPPYSECS = 2876
FILLERSIZE = $(shell echo $$(($(FLOPPYSECS) - $(DIVIDED))))

os_boot.iso: _floppy.img _floppy.catalog
	mkisofs -r -b "build/_floppy.img" -c "build/_floppy.catalog" -o "build/os_boot.iso" .

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
	i686-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

help:
	$(info Commands of this makefile:)
	$(info make: builds a standalone 1.44MB floppy image)
	$(info make qemu-floppy: builds and runs a 1.44MB floppy image on QEMU)
	$(info make qemu-iso: builds and runs an ISO image on QEMU)
	$(info make vbox-iso: builds and runs an ISO image on VirtualBox)
	$(info make vmware-iso: builds and runs an ISO image on VMWare Player)
	$(info make clean: cleans up the build environment)
	$(info make help: this command)

qemu-floppy: os_image.img
	qemu-system-i386 -fda build/os_image.img
    
qemu-iso: os_boot.iso
	qemu-system-i386 -cdrom build/os_boot.iso
    
vbox-iso: os_boot.iso
	VBoxManage startvm "yuuOS"

vmware-iso: os_boot.iso
	vmrun start "../../Virtual Machines/yuuOS/yuuOS.vmx"

# Generic rules for wildcards
# To make an object, always compile from its .c
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o *.elf
	rm -rf loader/*.o boot/*.bin drivers/*.o boot/*.o cpu/*.o libc/*.o
