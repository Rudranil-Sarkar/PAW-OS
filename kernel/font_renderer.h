#ifndef __FONT_RENDERER_H__
#define __FONT_RENDERER_H__

#define FONT_DEFAULT_BG_COLOR get_bg_color()

#include "typedef.h"
#include "graphics_driver.h"

void print_string(const char* msg, int len, u8 color, u8 bg_color);
void print_hex_byte(u8 num, u8 color, u8 bg_color);
void print_hex_word(u16 num, u8 color, u8 bg_color);
void print_hex_dword(u32 num, u8 color, u8 bg_color);
void print_char(const char chr, u8 color, u8 bg_color);
void setCursor(u16 x, u16 y);
int strlen(char* str);
static u8 font_bg_color;
#endif
