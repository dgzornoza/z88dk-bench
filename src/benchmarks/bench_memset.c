#include <string.h>
#include "../lib/bench.h"
#include "bench_memset.h"

static unsigned char memset_buffer[BENCH_BUFFER_SIZE];
static volatile unsigned char memset_sink = 0;

void bench_memset(unsigned int iterations)
{
    for (unsigned int i = 0; i < iterations; ++i)
    {
        memset(memset_buffer, (unsigned char)i, BENCH_BUFFER_SIZE);
        memset_sink ^= memset_buffer[i % BENCH_BUFFER_SIZE];
    }
}
