/* for communacating with the hardware directly eg: I/O operations, Eg. Disable/Enable Interrupts */

#ifndef __LOW_LEVEL_OP_H__
#define __LOW_LEVEL_OP_H__

#include "typedef.h"

/* Disables all interrupts */
static inline void disableInt() { __asm__("cli"); }

/* Enables interrupts */
static inline void enableInt() { __asm__("sti"); }

/* Write to the port */
static inline void outb(u16 port, u8 data) {
  __asm__ volatile("out %0, %1" : : "a"(data), "d"(port));
}
static inline void outw(u16 port, u16 data) {
  __asm__ volatile("out %0, %1" : : "a"(data), "d"(port));
}

/* Read from the port */
static inline u8 inb(u16 port) {
  u8 res;
  __asm__ volatile ("in %1, %0" : "=a"(res) : "d"(port));
  return res;
}
static inline u16 inw(u16 port) {
  u16 res;
  __asm__ volatile ("in %1, %0" : "=a"(res) : "d"(port));
  return res;
}

#endif
