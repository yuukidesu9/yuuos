#ifndef MEM_H
#define MEM_H

void memcpy(unsigned char *source, unsigned char *dest, int nbytes);
void memset(unsigned char *dest, unsigned char val, unsigned int len);

// At this stage there is a 'free' implemented.
// In a very clumsy way, but it's there.
unsigned int malloc(unsigned int size, int align, unsigned int *phys_addr);

#endif
