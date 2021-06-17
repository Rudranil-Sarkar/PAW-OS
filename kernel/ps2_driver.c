#include "ps2_driver.h"

void send_command(u8 opcode)
{
    outb(COMMAND_PORT, opcode);
}

u8 read_data()
{
    u8 res;
    res = inb(DATA_PORT);
    return res;
}

void send_data_to_device(u8 opcode)
{
    outb(DATA_PORT, opcode);
}

u8 read_status()
{
    u8 res;
    res = inb(STATUS_PORT);
    return res;
}

void send_data_to_second_port(u8 data)
{
    outb(COMMAND_PORT, 0xD4);
    outb(DATA_PORT, data);
}
