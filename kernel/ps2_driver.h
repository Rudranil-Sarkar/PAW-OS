#ifndef __PS2_DRIVER_H__
#define __PS2_DRIVER_H__

#include "typedef.h"
#include "low-level-op.h"
#include "font_renderer.h"

#define DATA_PORT 0x60
#define STATUS_PORT 0x64
#define COMMAND_PORT 0x64

void send_command(u8 opcode);
u8 read_data();
u8 read_status();

void send_data_to_second_port(u8 data);

#endif // __PS2_DRIVER_H__
