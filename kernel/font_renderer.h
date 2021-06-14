#ifndef __FONT_RENDERER_H__
#define __FONT_RENDERER_H__

#include "graphics_driver.h"

void print_string_exact(const char* msg, int len, int _x, int _y, u8 color);
void print_string(const char* msg, int len, u8 color);
int strlen(char* str);
#endif
