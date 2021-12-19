#include "graphics_driver.h"
#include "paw_bitmap.h"
#include "font_renderer.h"
#include "idt.h"
#include "pic.h"

void _main()
{
	graphics_init();
	idt_init();
	init_pic(0x20, 0x28);

	u8 startx = 0;
	u8 starty = 0;
	for (int i = 0; i < 100; i++)
	{
		for(int j = 0; j < 100; j++)
		{
			put_pixel(paw[i][j], startx + i, starty + j);
		}
	}

	char* paw_os = "PAW OS";
	setCursor(138, 120);
	print_string(paw_os, strlen(paw_os), 0x5B, FONT_DEFAULT_BG_COLOR);
}
