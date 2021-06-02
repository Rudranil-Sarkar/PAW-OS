/*
 * the most basic graphics driver implementaion ever
 * TODO get_pixel color from a given coordinate
*/

#ifndef __GRAPHICS_DRIVER_H__
#define __GRAPHICS_DRIVER_H__

#define video_memory_address	0xA0000			// in graphics mode our memory mapped video memory starts at this location in memory
#define MAX_WIDTH							320
#define MAX_HEIGHT						200

#include "typedef.h"

void put_pixel(u8 color, int x, int y);
#endif
