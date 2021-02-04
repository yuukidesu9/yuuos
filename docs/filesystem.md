# Musings about my Operating System #2 - Filesystem and Disk Management
Well, I gotta be real here: if I'm building an operating system, I need to have access to devices. Mainly, disk devices, such as floppies and HDDs.

My idea was making an installer or live distro that would fit a CD, without using the current floppy emulation shenanigans from GRUB's 'El Torito' boot scheme. But, oh well, we gotta work with what we have, right?

So, my new idea: using a basic filesystem inside the floppy image, and starting it right after the kernel. Since the kernel would have the necessary disk and filesystem modules, it'd be a little easier to implement the actual FS with the kernel outside, IMO.

### Disk Structure
The disk structure would be as follows, with each sector having 512 bytes in size:

- Sector 0 contains the boootloader.
- Sector 1 onwards contains the kernel.
- The final kernel sector would be filled with zeros, just for the sake of completion.
- The sector right after it would contain the string SYSSTART, and later some user settings in bytes, then finishing with the string SYSEND on the final 6 bytes of the sector.
- The next sector can contain the filesystem. I'm thinking about using USTAR (basically the TAR filesystem), since it's easier to port it to a floppy image.

### About the USTAR (TAR) filesystem
Every file has a 512-byte header (basically a sector-sized header), then the file *per se*.

If the file is a directory, then there's no file after it; instead, there's another header in the sector right after it.

If the file doesn't fill a sector, it's filled with NUL bytes(0x00) at the ending.

### Directory structure
I decided to go a little Linux-y here and keep a simple directory structure.

- / - root directory
- /bin/ - binaries and applications
- /dsk/ - devices and drives
- /etc/ - configuration files
- /home/ - user directory
- /lib/ - binary libraries
- /mem/ - virtual memory shenanigans (for future usage)
- /sys/ - system binaries
