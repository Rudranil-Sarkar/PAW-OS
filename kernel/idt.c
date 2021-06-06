#include "idt.h"
#include "font_renderer.h"

__attribute__((aligned(0x10)))
static idt_table_entry idt_table[MAX_ENTRIES];

static idt_info idt;

/* A generic exception handler that just completely hanges the computer */
__attribute__((noreturn))
void exception_handler(void);
void exception_handler() { print_string("error", 5, 0, 0, 0x5B); __asm__("cli\n\thlt"); while(1) {} }

/* So this is the way we have to define interrupt and exception routines in gcc */
struct interrupt_frame {
    u32 ip;
    u32 cs;
    u32 flags;
    u32 sp;
    u32 ss;
} __attribute__((packed));

__attribute__((interrupt))
void int20 (struct interrupt_frame * frame)
{
    print_string("Testing Interrupt", 17, 0, 100, 0x5B);
}

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
        add_entry(vector, exception_handler, 0x8E);

     add_entry(0x20, int20, 0x8E);
    __asm__ volatile ("lidt %0": : "memory"(idt));
    __asm__ volatile ("movb $0xff, %al; outb %al, $0xa1; outb %al, $0x21");         // Disabling the PIC chip
    __asm__ volatile ("sti");
}

