#include "font_renderer.h"
#include "font.h"

u16 x = 0;
u16 y = 0;

int strlen(char* str)
{
  int res = 0;
  for (int i = 0; str[i] != '\0'; i++)
    res++;
  return res;
}

void print_string(const char* msg, int len, u8 color)
{
      print_string_exact(msg, len, x, y, color);
      x += len * 8;
}

void print_string_exact(const char* msg, int len, int _x, int _y, u8 color)
{
    /* each font is 8x8 in size so after we render our font we need to move to 8 pixels */

    for (int l = 0; l < len; l++)           // looping over the string to print the each character
    {
        u8 *chr = font8x8_basic[msg[l]];    // choose the right bitmap set for our character
        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                u8 set = (chr[y] >> x) & 0x01;
                put_pixel(set ? color: get_bg_color(), (_x + x) + (l * 8), _y + y);
            }
        }
    }
}
