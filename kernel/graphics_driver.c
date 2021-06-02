#include "graphics_driver.h"
char* video_memory = (char*) video_memory_address;

void put_pixel(u8 color, int x, int y) 
{
	video_memory[MAX_WIDTH * y + x] = color;
}
