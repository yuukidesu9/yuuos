#ifndef ATA_H
#define ATA_H
#include "../cpu/type.h"

void PIO_readsec(u32 targetaddr, u32 lba, u8 sector_count);
void PIO_writesec(u32 lba, u8 sector_count, u32* bytes);

#endif