#include "zx_clock.h"
#include <arch/zx.h>

static unsigned long _zx_start_tick = 0;

/*
 * Reads the current tick count from the ZX Spectrum system variable FRAMES (0x5C78),
 * which increments at 50Hz (every 20ms).
 * Clock is in addressess: * 23672 (LSB) * 23673 * 23674 (MSB)
 * Returns a 32-bit unsigned long with the 24-bit value.
 */
unsigned long zx_read_frames(void)
{
    volatile unsigned char *frames = (volatile unsigned char *)0x5C78;
    return (unsigned long)frames[0] | ((unsigned long)frames[1] << 8) | ((unsigned long)frames[2] << 16);
}

unsigned long zx_clock(void)
{
    if (_zx_start_tick == 0)
    {
        _zx_start_tick = zx_read_frames();
    }

    return zx_read_frames() - _zx_start_tick;
}
