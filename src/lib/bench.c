#include "bench.h"

static unsigned long bench_start_tick = 0;

void bench_start(const char *name)
{
    print_string(FONT_CONTROL_CRLF "bench-");
    print_string((char *)name);
    print_string(": ");

    bench_start_tick = zx_clock();
}

unsigned long bench_end(void)
{
    // zx spectrum 50 Hz frame counter (1 tick = 20 ms)
    unsigned long end_tick = zx_clock();
    unsigned long elapsed_ms = (end_tick - bench_start_tick) * 20UL; // 1 tick = 20ms (50Hz)

    char buf[32];
    ultoa(elapsed_ms, buf, 10);
    print_string(buf);
    print_string(" ms");

    return elapsed_ms;
}
