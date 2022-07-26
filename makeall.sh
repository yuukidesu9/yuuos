#!/bin/bash

AS=nasm
ASFLAGS="-f elf"

CC=/mnt/hdd/i686-elf/bin/i686-elf-gcc
CCFLAGS="-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wextra -Werror -ffreestanding -c"

LD=/mnt/hdd/i686-elf/bin/i686-elf-ld
LDFLAGS="-T link.ld -melf_i386"

buildall() {
	echo "Looping through Assembly files..."
	for i in $(find . -type f -name "*.s")
	do
		echo $AS "$i" $ASFLAGS -o "${i%.*}.o" | bash
	done

	echo "Looping through C files..."
	for i in $(find . -type f -name "*.c")
	do
		echo $CC "$i" $CCFLAGS -o "${i%.*}.o" | bash
	done

	echo "Linking..."
	echo $LD $LDFLAGS boot/boot_entry.o kmain.o $(find . -type f -name "*.o" ! -path "./kmain.o" ! -path "./boot/boot_entry.o") -o build/iso/boot/kernel.elf | bash
	echo $LD $LDFLAGS boot/boot_entry.o kmain.o $(find . -type f -name "*.o" ! -path "./kmain.o" ! -path "./boot/boot_entry.o") -o build/iso/boot/kernel.elf
}

makeiso() {
	echo "Generating ISO image..."
	mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A yuuOS -input-charset iso8859-1 -boot-info-table -o build/yuuos_grub.iso build/iso
}

run-qemu() {
	qemu-system-i386 -cdrom build/yuuos_grub.iso -m 4 -monitor stdio
}

cleanup() {
	find . -type f -name "*.o" -delete
	rm build/iso/boot/kernel.elf
}

showhelp(){
	echo "Usage: ./makeall.sh -?habcir"
	echo "Build or cleanup the project."
	echo ""
	echo "  -a		builds the source code, creates the ISO file and runs it on QEMU"
	echo "  -b		only build the source code into object files and link it into an ELF file"
	echo "  -i		only create the ISO image file"
	echo "  -r		only run the built ISO on QEMU"
	echo "  -c		clean the project, removing all object files"
	echo "  -?, -h	show this help text"
}

echo "YuuOS build script -- version 1.0"
echo "because the Makefile keeps failing :c"
echo "====================================="

while getopts "\?habcir" opt; do
    case $opt in
        b)
          echo "Build option selected." >&2
          buildall
          ;;
        i)
          echo "ISO build option selected." >&2
          makeiso
          ;;
        r)
          echo "Run option selected." >&2
          run-qemu
          ;;
        c)
          echo "Cleanup option selected. Commencing cleanup..." >&2
          cleanup
          ;;
        a)
		  echo "Building everything." >&2
		  buildall
		  makeiso
		  run-qemu
		  ;;
        \? | h | *)
          showhelp
          ;;
    esac
    
done

if [ $# -eq 0 ]; then
	echo "Invalid usage -- no arguments"
	showhelp
fi
