#include "graphics_driver.h"
char* video_memory = (char*) video_memory_address;
u8 bg_color = 0x00;

void put_pixel(u8 color, int x, int y) 
{
	video_memory[MAX_WIDTH * y + x] = color;
}

void set_bg(u8 color)
{
	bg_color = color;
	for	(int y = 0; y < MAX_HEIGHT; y++)
	{
		for (int x = 0; x < MAX_WIDTH; x++)
			put_pixel(color, x, y);
	}
}

u8 get_bg_color() { return bg_color; }
