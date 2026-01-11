#include "../lib/bench.h"
#include "bench_call.h"

static volatile unsigned int call_sink = 0;

static void bench_target(unsigned int value) __z88dk_fastcall
{
    call_sink += value;
}

void bench_call(unsigned int iterations) __z88dk_fastcall
{
    for (unsigned int i = 0; i < iterations; ++i)
    {
        bench_target(i);
    }
}
