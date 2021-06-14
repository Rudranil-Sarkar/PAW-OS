#ifndef __PIC_H__
#define __PIC_H__

#define PIC1         0x20
#define PIC2         0xA0
#define PIC1_COMMAND PIC1
#define PIC1_DATA    (PIC1+1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA    (PIC2+1)

#define PIC_EOI 0x20

#include "typedef.h"
#include "low-level-op.h"

void init_pic(u8 offset1, u8 offset2);
void reset_irq(u8 irq);
void disable_pic();

#endif // __PIC_H__
