C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c libc/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h libc/*.h)
# Nice syntax for file extension replacement
OBJ = ${C_SOURCES:.c=.o cpu/interrupt.o}

# Change this if your cross-compiler is somewhere else
CC = /c/i686-elf/bin/i686-elf-gcc

# -g: Use debugging symbols in gcc
CFLAGS = -g -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra



# First rule is run by default
os_image.img: boot/bootsect.bin kernel.bin
	cat $^ > build/os_image.img
	echo "Image created."

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
	echo "Catalog file built."
    
_floppy.img: os_image.img
	echo "Filesize: $(FILESIZE), No. of sectors: $(DIVIDED)"
	dd if="/dev/zero" bs=$(SECTORSIZE) count=$(FILLERSIZE) of="build/_filler.img"
	echo "Filler created."
	cat build/os_image.img build/_filler.img > build/_floppy.img
	echo "Secondary image created."

# '--oformat binary' deletes all symbols as a collateral, so we don't need
# to 'strip' them manually on this case

kernel.bin: boot/kernel_entry.o ${OBJ}
	i686-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

run: os_image.img
	qemu-system-i386 -fda build/os_image.img
    
runiso: os_boot.iso
	qemu-system-i386 -cdrom build/os_boot.iso

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
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o cpu/*.o libc/*.o
