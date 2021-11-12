#include "stdio.h"
#include "..\drivers\portbased\textmode.h"

void printf(char *message) {
    kprint_at(message, -1, -1);
}