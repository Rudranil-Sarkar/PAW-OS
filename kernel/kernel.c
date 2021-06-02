#include "graphics_driver.h"
#include "paw_bitmap.h"
#include "font_renderer.h"

int strlen(char* str)
{
	int res = 0;
	for (int i = 0; str[i] != '\0'; i++)
		res++;
	return res;
}

void _main()
{
	u8 startx = 110;
	u8 starty = 30;
	for (int i = 0; i < 100; i++)
	{
		for(int j = 0; j < 100; j++)
		{
			put_pixel(paw[i][j], startx + i, starty + j);
		}
	}
	char* paw_os = "PAW OS";
	print_string(paw_os, strlen(paw_os), 138, 120, 0x5B);
}
