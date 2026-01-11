#ifndef __Z88DK_HEADERS_H__
#define __Z88DK_HEADERS_H__

#include <arch/zx.h>

/**
 * Enable interrupts for ensure clocked sections work correctly.
 */
void enable_ei(void)
{
#asm
    ei
#endasm;
}

#endif // __Z88DK_HEADERS_H__
