#ifndef __IDT_H__
#define __IDT_H__

#include "typedef.h"

#define MAX_ENTRIES 256

/* This struct will be used to load our idt into the cpu register */
typedef struct {
	u16 limit;															// The size of our idt ( sizeof each table entry * total number - 1)
	u32 base;															// The address of our table
} __attribute__((packed)) idt_info;			// __attribute__((packed)) tells gcc to not to shrink/grow the size of our struct for speed

typedef struct {
	u16 offset_low;			// The first 16 bits of the address of isr
	u16 selector;				// The code segment from gdt
	u8	padding;				// Reserved filled with zeros
	u8	type_flag;			// Flags
	u16	offset_high;		// The rest of the 16 bits of the isr routines address
} __attribute__((packed)) idt_table_entry;

void add_entry(u8 vector, void (* isr)(), u8 flags);
void idt_init(void);

#endif
