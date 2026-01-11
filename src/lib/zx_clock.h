#ifndef ZX_CLOCK_H
#define ZX_CLOCK_H

/*
 * Returns a value representing the number of ticks since first call to clock.
 * ZX Spectrum: 50Hz interrupt, so 1 tick = 20ms.
 * Returns: unsigned long representing ticks since first call to clock.
 */
unsigned long zx_clock(void);

#endif // ZX_CLOCK_H
