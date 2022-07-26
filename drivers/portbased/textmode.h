#ifndef TEXTMODE_H
#define TEXTMODE_H

#define VIDEO_ADDRESS 0x000b8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define COLOR_BLACK 0
#define COLOR_BLUE 1
#define COLOR_GREEN 2
#define COLOR_RED 4
#define COLOR_DARKGRAY 8
#define COLOR_WHITE 15

/* Screen i/o ports */
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

/* Screen byte commands */
#define FB_HIGHBYTE_CMD 14
#define FB_LOWBYTE_CMD 15



/* Public kernel API */
void clear_screen();
void move_cursor(unsigned short pos);
void writechar(unsigned int index, char chr, unsigned char fore, unsigned char back);
void writesimple();
int writestring(char *buffer, unsigned int length);
//void kprint_at(char *message, int col, int row);
//void kprint_backspace();

#endif
