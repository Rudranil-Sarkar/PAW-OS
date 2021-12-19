#include "font_renderer.h"
#include "font.h"

u32 cursorX = 0;
u32 cursorY = 0;

void setCursor(u16 x, u16 y) {
  cursorX = x;
  cursorY = y;
}

int strlen(char* str)
{
  int res = 0;
  for (int i = 0; str[i] != '\0'; i++)
    res++;
  return res;
}

void print_char(const char chr, u8 color, u8 bg_color) {
  if (chr == '\n') {
    cursorX = 0;
    cursorY += 8;
  }
  u8 *fontbitmap = font8x8_basic[(u8)chr]; // choose the right bitmap set for our character
  for (int fonty = 0; fonty < 8; fonty++) {
    for (int fontx = 0; fontx < 8; fontx++) {
      u8 set = (fontbitmap[fonty] >> fontx) & 0x01;
      put_pixel(set ? color : bg_color, (cursorX + fontx), cursorY + fonty);
    }
  }
  cursorX += 8;
  if (cursorX >= 1024) {
    cursorX = 0;
    cursorY += 8;
  }
}

void print_string(const char* msg, int len, u8 color, u8 bg_color)
{
  for (int i = 0; i < len; i++) {
    print_char(msg[i], color, bg_color);
  }
}

void print_hex(u8 num, u8 color, u8 bg_color)
{
  char* hex = "0x00";
  for(int i = 0; i < 2; i++)
  {
    u8 temp = num >> (i * 4);
    temp = temp & 0x0F;

    if (temp <= 9)
    {
      // Print 0-9
      hex[3 - i] += temp;
    }
    else
    {
      // Print A-F
      hex[3 - i] += temp + 7;
    }
  }
  print_string(hex, 4, color, bg_color);
}
