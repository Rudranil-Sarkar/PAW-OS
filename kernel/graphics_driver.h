/*
 * the most basic graphics driver implementaion ever
*/

#ifndef __GRAPHICS_DRIVER_H__
#define __GRAPHICS_DRIVER_H__

#define video_memory_address	0xA0000			// in graphics mode our memory mapped video memory starts at this location in memory
#define MAX_WIDTH							320
#define MAX_HEIGHT						200

#include "typedef.h"


void set_bg(u8 color);
void put_pixel(u8 color, int x, int y);
u8 get_pixel (int x, int y);
u8 get_bg_color();
#endif
