#pragma once

#include "../Framebuffer/kPrintf.h"
// Exceptions
void interrupt_print_alert();
void interrupt_print_page_fault();

extern void interupt_general_handler();

extern void interrupt_page_fault_handler();