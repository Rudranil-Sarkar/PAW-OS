#include "idt.h"
#include "font_renderer.h"
#include "pic.h"
#include "isr.h"

__attribute__((aligned(0x10)))
static idt_table_entry idt_table[MAX_ENTRIES];

static idt_info idt;

void add_entry(u8 vector, void (*isr)(), u8 flags)
{
    idt_table_entry* entry = &idt_table[vector];
    entry->offset_low = (u32)isr & 0xFFFF;
    entry->selector = 0x08;
    entry->padding = 0x00;
    entry->type_flag = flags;
    entry->offset_high = (u32)isr >> 16;
}

void idt_init(void)
{
    idt.limit = (u16) sizeof(idt_table_entry) * MAX_ENTRIES - 1;
    idt.base = (u32) &idt_table[0];
    /* The first 32 entries are reserved by the cpu used for exceptions */
     for (u8 vector = 0; vector < 32; vector++)
        add_entry(vector, exception_handler, 0x8F);

     add_entry(0x20, irq0, 0x8E);
     add_entry(0x21, irq1, 0x8E);

    __asm__ volatile ("lidt %0": : "memory"(idt));
    disable_pic();
    __asm__ volatile ("sti");
}

