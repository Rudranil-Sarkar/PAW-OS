#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include "ps2_driver.h"

#define ACK_BYTE 0xFA
#define RESEND_BYTE 0xFE


static s8* keycode_table[] = {
"nill", "ESC",   "1",      "2",     // 0x00
"3",    "4",     "5",      "6",     // 0x04
"7",    "8",     "9",      "0",     // 0x08
"-",    "=",     "BSP",    "TAB",   // 0x0C
"q",    "w",     "e",      "r",     // 0x10
"t",    "y",     "u",      "i",     // 0x14
"o",    "p",     "[",      "]",     // 0x18
"RET",  "LCTRL", "a",      "s",     // 0x1C
"d",    "f",     "g",      "h",     // 0x20
"j",    "k",     "l",      ";",     // 0x24
"'",    "`",     "LSHIFT", "\\",    // 0x28
"z",    "x",     "c",      "v",     // 0x2C
"b",    "n",     "m",      ",",     // 0x30
".",    "/",     "RSHIFT", "*",     // 0x34
"LALT", " ",     "CAPS"    "F1",    // 0x38
"F2",   "F3",    "F4",     "F5",    // 0x3C
"F6",   "F7",    "F8",     "F9",    // 0x40
"F10",  "NUML",  "SCRLL",  "K7",    // 0x44
"K8",   "K9",    "K-",     "K4",    // 0x48
"K5",   "K6",    "K+",     "K1",    // 0x4C
"K2",   "K3",    "K0",     "K.",    // 0x50
"nill", "nill",  "nill",   "F11",   // 0x54
"F12",  "nill",  "nill",   "nill",  // 0x58

/*******************************************************************/
/* These are the release codes for the all the previouse scancodes */
/*******************************************************************/

"nill",         "RELEASE-ESC",   "RELEASE-1",      "RELEASE-2",    // 0x5C
"RELEASE-3",    "RELEASE-4",     "RELEASE-5",      "RELEASE-6",    // 0x60
"RELEASE-7",    "RELEASE-8",     "RELEASE-9",      "RELEASE-0",    // 0x64
"RELEASE--",    "RELEASE-=",     "RELEASE-BSP",    "RELEASE-TAB",  // 0x68
"RELEASE-q",    "RELEASE-w",     "RELEASE-e",      "RELEASE-r",    // 0x6C
"RELEASE-t",    "RELEASE-y",     "RELEASE-u",      "RELEASE-i",    // 0x70
"RELEASE-o",    "RELEASE-p",     "RELEASE-[",      "RELEASE-]",    // 0x74
"RELEASE-RET",  "RELEASE-LCTRL", "RELEASE-a",      "RELEASE-s",    // 0x7C
"RELEASE-d",    "RELEASE-f",     "RELEASE-g",      "RELEASE-h",    // 0x80
"RELEASE-j",    "RELEASE-k",     "RELEASE-l",      "RELEASE-;",    // 0x84
"RELEASE-'",    "RELEASE-`",     "RELEASE-LSHIFT", "RELEASE-\\",   // 0x88
"RELEASE-z",    "RELEASE-x",     "RELEASE-c",      "RELEASE-v",    // 0x8C
"RELEASE-b",    "RELEASE-n",     "RELEASE-m",      "RELEASE-,",    // 0x90
"RELEASE-.",    "RELEASE-/",     "RELEASE-RSHIFT", "RELEASE-*",    // 0x94
"RELEASE-LALT", "RELEASE- ",     "RELEASE-CAPS"    "RELEASE-F1",   // 0x98
"RELEASE-F2",   "RELEASE-F3",    "RELEASE-F4",     "RELEASE-F5",   // 0x9C
"RELEASE-F6",   "RELEASE-F7",    "RELEASE-F8",     "RELEASE-F9",   // 0xA0
"RELEASE-F10",  "RELEASE-NUML",  "RELEASE-SCRLL",  "RELEASE-K7",   // 0xA4
"RELEASE-K8",   "RELEASE-K9",    "RELEASE-K-",     "RELEASE-K4",   // 0xA8
"RELEASE-K5",   "RELEASE-K6",    "RELEASE-K+",     "RELEASE-K1",   // 0xAC
"RELEASE-K2",   "RELEASE-K3",    "RELEASE-K0",     "RELEASE-K.",   // 0xB0
"nill",         "nill",          "nill",           "RELEASE-F11",  // 0xB4
"RELEASE-F12",  "nill",          "nill",           "nill",         // 0xB8
};

char decode_scancode(u8 scancode);

#endif // __KEYBOARD_H__
