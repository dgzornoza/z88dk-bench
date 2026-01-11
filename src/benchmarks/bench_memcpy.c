#include <string.h>
#include "../lib/bench.h"
#include "bench_memcpy.h"

static unsigned char memcpy_src[BENCH_BUFFER_SIZE];
static unsigned char memcpy_dst[BENCH_BUFFER_SIZE];
static volatile unsigned char memcpy_sink = 0;

void bench_memcpy(unsigned int iterations)
{
    for (unsigned int i = 0; i < BENCH_BUFFER_SIZE; ++i)
    {
        memcpy_src[i] = (unsigned char)(i & 0xFF);
    }

    for (unsigned int i = 0; i < iterations; ++i)
    {
        memcpy(memcpy_dst, memcpy_src, BENCH_BUFFER_SIZE);
        memcpy_sink ^= memcpy_dst[i % BENCH_BUFFER_SIZE];
    }
}
