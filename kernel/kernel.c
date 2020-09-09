/* Naka-chan - The OS kernel!
   --------------------------------
   Finally, the heart of our OS!
   I present you... Naka-chan!
   Code: Yuuki Sanada
*/
// Here we'll use a dummy function, just to
// avoid loading kernel.c:0x00
void dummy_test_entrypoint() {
}
// And here's our main function!
// Don't mind, it's still barebones by now.
void kernel_main() {
    char* video_memory = (char*) 0xb8000;
    *video_memory = 'h';
}