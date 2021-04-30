# yuuOS - My hobby operating system
An operating system, made by me, in my programming journey. It's in its very early development stages.

**Current status:** Very early alpha version.
I'm rewriting some of the code for compatibility reasons.

## Roadmap
### Basic Features
- DOS-like system shell - OK!
- Keyboard input - OK! (sort of)
- Memory page allocation - OK! (sort of)
- COM1 debugging - Planned
- Kernel event logging - Planned
- Command arguments - Planned

### File Systems
- USTAR filesystem support - WIP/Planned
- FAT32 filesystem support - Planned
- BTRFS filesystem support - Planned
- EXT2/3/4 filesystem support - Planned

### Devices
- CGA/EGA/VGA text-mode driver - OK!
- CGA/EGA/VGA graphics-mode driver - OK!
- PS/2 Keyboard driver - WIP/OK
- CMOS/RTC driver - Planned
- PCI device drivers - Planned
- Basic network device drivers - Planned
- USB device enumerators and drivers - Planned
- Other device drivers - Planned

### Boot and Launch
- Migration from BIOS to UEFI - Planned
- Port VGA code to GOP - Planned
- 32-bit-compatible kernel - WIP
- 64-bit-compatible kernel - Planned

### Graphics
- Mouse support - Planned
- GUI - Planned
- Window management and GUI API - Planned

### Multitasking and Apps
- Preemptive multitasking - Planned
- Package management - Planned
- Userland C library porting - Planned

## Known errors

- When interrupts are received, the kernel doesn't print a description. Just a "S".
- The CPUID function is hardcoded, since I was lazy and a bit dumb.
- I know how USTAR filesystem works, but I couldn't implement it yet because I'm being a lazy-ass motherfucker.
- Same for FAT32.
