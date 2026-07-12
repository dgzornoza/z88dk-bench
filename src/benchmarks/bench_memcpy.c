/*
 * Memory Copy Benchmark
 *
 * Measures the throughput of block memory copies. The benchmark
 * initializes a source buffer once, then repeatedly copies it into
 * a destination buffer while sampling a byte to avoid optimization.
 */

#include <string.h>
#include "../lib/bench.h"
#include "bench_memcpy.h"

/* Static buffers avoid heap usage and keep the test deterministic. */
static unsigned char memcpy_src[BENCH_BUFFER_SIZE];
static unsigned char memcpy_dst[BENCH_BUFFER_SIZE];
static volatile unsigned char memcpy_sink = 0;

/*
 * Run the memcpy workload.
 * @param iterations Number of copy iterations to execute.
 */
void bench_memcpy(unsigned int iterations)
{
    /* Initialize the source buffer with a simple pattern. */
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
