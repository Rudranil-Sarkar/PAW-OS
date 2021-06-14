#include "pic.h"

void reset_irq(u8 irq)
{
    if (irq >=8)
        outb(PIC2_COMMAND, PIC_EOI);
    outb(PIC1_COMMAND, PIC_EOI);
}

void disable_pic()
{
   outb(PIC2_DATA, 0xFF);
   outb(PIC1_DATA, 0xFF);
}

void init_pic(u8 offset1, u8 offset2)
{
    /* Tell the master and slave pic to begin initializing process */

    outb(PIC1_COMMAND, 0x11);
    outb(PIC2_COMMAND, 0x11);

    /* Set the offset for the isr table */
    outb(PIC1_DATA, offset1);
    outb(PIC2_DATA, offset2);

    /* Telling the PIC it's configuration */
    outb(PIC1_DATA, 0x04);  // tell the master PIC that it has a slave PIC connected on IRQ2
    outb(PIC2_DATA, 0x02);  // tell the slave PIC that it is connected to the master PIC throught IRQ2

    /* Tell the PIC to run in 8086 mode */
    outb(PIC1_DATA, 0x01);
    outb(PIC2_DATA, 0x01);
}
