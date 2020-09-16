C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)
# Nice syntax for file extension replacement
OBJ = ${C_SOURCES:.c=.o}

# Change this if your cross-compiler is somewhere else
CC = /c/i686-elf/bin/i686-elf-gcc
# -g: Use debugging symbols in gcc
CFLAGS = -g

# First rule is run by default
os_image.img: boot/bootsect.bin kernel.bin
	cat $^ > build/os_image.img

# '--oformat binary' deletes all symbols as a collateral, so we don't need
# to 'strip' them manually on this case
kernel.bin: boot/kernel_entry.o ${OBJ}
	i686-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

# Used for debugging purposes
kernel.elf: boot/kernel_entry.o ${OBJ}
	i686-elf-ld -o $@ -Ttext 0x1000 $^ 

run: os_image.img
	qemu-system-i386 -fda build/os_image.img

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
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o
