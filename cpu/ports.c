#include "ports.h"

// Here we have our port-handling... erm, thing.
// We can see it's using inline Assembly instructions.
// Some OOP programmers would call it 'cheating',
// but I'd call this a clear technical advantage.

// We can use IN and OUT assembly instructions,
// which basically tells the CPU to grab and put
// things into processor ports.
// Now, to the proper instructions:
u8 inb (u16 port) {
    // First, we have our inb (which stands for INput Byte),
    // which grabs data from a processor port,
    // so we can use it on our program.
    // Rather, our kernel.
    
    // But we have to store the data as a byte, right?
    u8 result;
    
    // IN AL, DX (Intel syntax)
    // also known as IN DX, AL (AT&T syntax)
    
    // (what it means: pick the data from DX and store into AL.)
    
    // AL stands for Address Low. It's used since Intel's 
    // 16-bit era to store the lower parts of addresses.
    // (More on registers later.)
    
    // DX stands for Data eXtension. It's used to store data.
    // The DX register stores 8, 16 and 32-bit values.
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    
    // Then we return our result as a byte.
    return result;
}

void outb (u16 port, u8 data) {
    // Here's our outb (or OUTput Byte, for the more intimates),
    // which (opposing the inb function) puts a byte into a
    // port.
    
    // OUT DX, AL (Intel syntax)
    // also known as OUT AL, DX (AT&T syntax)
    
    // (what it means: pick the data from AL and store it into DX.)
    
    // You know the drill.
    __asm__ __volatile__("out %%al, %%dx" : : "a" (data), "d" (port));
}

u16 inw (u16 port) {
    // Now, stepping up the game a little, we have our inw function
    // (which stands for INput Word, being word a 16-bit value).
    // You know the drill, right? But in this case, we use a different
    // register.
    
    // But before, store our result as a word.
    u16 result;
    
    // NEW CHALLENGER APPROACHING!
    // Now, we have a new register to play with: the AX register.
    // AX stands for Address eXtension. It stores 16-bit addresses,
    // if you will.
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
    
    // Return our result and done!
    return result;
}

void outw (u16 port, u16 data) {
    // Same thing as always: outw means OUTput Word.
    __asm__ __volatile__("out %%ax, %%dx" : : "a" (data), "d" (port));
}

u32 indw (u32 port) {
    // And now, to top it all, we have the indw function!
    // The indw (INput Double-Word) now handles 32-bit values!
    // This is gonna be important, since we'll want to handle 32-bit
    // values from CPU ports.
    
    // First, store our result as a double-word.
    u32 result;
    
    // EAX JOINS THE BRAWL!
    // Now, since we're entering 32-bit territory, we need
    // a new companion: the EAX register!
    // EAX stands for Expanded Address eXtension. Same as always,
    // but
    // *slaps CPU register*
    // this baby can fit so much 32-bit data!
    __asm__("in %%dx, %%eax" : "=a" (result) : "d" (port));
    
    // Return our thingie, and done!
    return result;
}

void outdw (u32 port, u32 data) {
    // Now let's put some 32-bit values, baby!
    __asm__ __volatile__("out %%eax, %%dx" : : "a" (data), "d" (port));
}