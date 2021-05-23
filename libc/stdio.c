#include "stdio.h"
#include "../drivers/textmode.h"

void printf(char *message) {
    kprint_at(message, -1, -1);
}