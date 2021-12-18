#include "graphics_driver.h"
u8 bg_color = 0x00;


void graphics_init() {
	u32* address = (u32*)GRAPHICS_MEMORY_BASE;
	u32 a = *address;
	video_memory = (char*) a;
}
void put_pixel(u8 color, int x, int y)
{
	video_memory[MAX_WIDTH * y + x] = color;
}

u8 get_pixel(int x, int y) {
	u8 color = video_memory[MAX_WIDTH * y + x];
	return color;
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
