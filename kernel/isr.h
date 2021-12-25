#ifndef __ISR_H__
#define __ISR_H__

#include "font_renderer.h"
#include "low-level-op.h"
#include "pic.h"
#include "keyboard.h"
#include "vga_colors.h"

/******************************************************************************/
/* According to gcc manual this the correct way to declare interrupt routines */
/* I personaly found this the easier way to write ISRs than writing assembly  */
/* routines for every interrupt                                               */
/******************************************************************************/

struct interrupt_frame {
  u32 ip;
  u32 cs;
  u32 flags;
  u32 sp;
  u32 ss;
} __attribute__((packed));

/* A generic exception handler that just completely hanges the computer */
static __attribute__((interrupt))
void exception_handler(struct interrupt_frame *frame) {
  print_string("error", 5, 0x5B, FONT_DEFAULT_BG_COLOR);
  __asm__("cli\n\thlt");
  while (1) {}
}

__attribute__((interrupt))
void irq0(struct interrupt_frame *frame) {reset_irq(0); }

__attribute__((interrupt))
void irq1(struct interrupt_frame *frame) {
  u8 scancode = read_data();
  char a = decode_scancode(scancode);

  /* switch (a) { */
  /*   case KEY_PAGE_UP: */
  /*     break; */

  /* } */

  // A switch case will be better I know but this section is marked for removal
  if (a == KEY_PAGE_UP)
    print_string("Page up", strlen("page up"), 0x0F, FONT_DEFAULT_BG_COLOR);

  else if(a != -0x02 && a != -0x03)
  {
    char str[1] = {a};
    print_string(str, 1, 0x0F, FONT_DEFAULT_BG_COLOR);
  }

  reset_irq(1);
}

#endif // __ISR_H__
