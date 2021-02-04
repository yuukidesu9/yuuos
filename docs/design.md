# Musings about my Operating System #1 - Design Ideas
I've been thinking about implementing some stuff onto the OS. My first idea on a long term would be to run Windows applications.

But hey, I gotta start small, so I think running DOS applications would be a nice grounding for it. Maybe I can even run DOOM!

The DOS EXE format is kinda simple, because it already contains a header and memory addresses ready, right out of the box.

Now the difficult thing would be emulating the DOS system calls. Ain't gonna be easy, but I think I can pull it off.

But, there's a catch to all this: I gotta have a filesystem and drivers ready, right?

Also, there's the thing about a package management system. I'll go with the proven GZIP packaging (.gz), or maybe TAR (.tar) to make it easier.

I also gotta have a cross-compiler to compile yuuOS-ready binaries.

And, since we're not in 2010 anymore, a 64-bit kernel, with 64-bit system calls and everything.