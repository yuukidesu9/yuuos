#include "../cpu/ports.h"
#include "ata.h"

#define STATUS_BSY 0x80
#define STATUS_RDY 0x40
#define STATUS_DRQ 0x08
#define STATUS_DF 0x20
#define STATUS_ERR 0x01

static void ATA_wait_BSY();
static void ATA_wait_DRQ();

void PIO_readsec(u32 targetaddr, u32 lba, u8 sector_count)
{

	ATA_wait_BSY();
	outb(0x1F6,0xE0 | ((lba >>24) & 0xF));
	outb(0x1F2,sector_count);
	outb(0x1F3, (u8) lba);
	outb(0x1F4, (u8)(lba >> 8));
	outb(0x1F5, (u8)(lba >> 16)); 
	outb(0x1F7,0x20); //Send read command

	u16 *target = (u16*) targetaddr;
    int i, j;
	for (j=0;j<sector_count;j++)
	{
		ATA_wait_BSY();
		ATA_wait_DRQ();
		for(i=0;i<256;i++)
			target[i] = inw(0x1F0);
		target+=256;
	}
}

void PIO_writesec(u32 lba, u8 sector_count, u32* bytes)
{
	ATA_wait_BSY();
	outb(0x1F6,0xE0 | ((lba >>24) & 0xF));
	outb(0x1F2,sector_count);
	outb(0x1F3, (u8) lba);
	outb(0x1F4, (u8)(lba >> 8));
	outb(0x1F5, (u8)(lba >> 16)); 
	outb(0x1F7,0x30); //Send write command
    int i, j;
	for (j=0;j<sector_count;j++)
	{
		ATA_wait_BSY();
		ATA_wait_DRQ();
		for(i=0;i<256;i++)
		{
			outdw(0x1F0, bytes[i]);
		}
	}
}

static void ATA_wait_BSY()   //Wait for ATA interface to be free (BSY = 0)
{
	while(inb(0x1F7)&STATUS_BSY);
}

static void ATA_wait_DRQ()  //Wait fot DRQ to be 1
{
	while(!(inb(0x1F7)&STATUS_RDY));
}