#include "interrupts.h"

void interrupt_print_alert()
{
    kPrintf("Interrupt triggered!!\n");
}

void interrupt_print_page_fault()
{
    kPrintf("Page fault!\n");
}