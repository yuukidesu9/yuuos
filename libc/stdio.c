#include "stdio.h"
#include "../drivers/screen.h"

void printf(char *message) {
    kprint_at(message, -1, -1);
}