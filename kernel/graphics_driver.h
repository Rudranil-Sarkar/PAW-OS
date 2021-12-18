/*
 * the most basic graphics driver implementaion ever
*/

#ifndef __GRAPHICS_DRIVER_H__
#define __GRAPHICS_DRIVER_H__

/* #define video_memory_address 0x07FFFF // in graphics mode our memory mapped video memory starts at this location in memory */
#define MAX_WIDTH  1024
#define MAX_HEIGHT 768
#define GRAPHICS_MEMORY_BASE 0x0FFC

#include "typedef.h"

static char* video_memory_base = (char *) GRAPHICS_MEMORY_BASE;

/* char* video_memory = (char*) 0xFD000000; */
static char* video_memory;

void graphics_init();
void set_bg(u8 color);
void put_pixel(u8 color, int x, int y);
u8 get_pixel (int x, int y);
u8 get_bg_color();
#endif
