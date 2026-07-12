/*
 * Memory Set Benchmark
 *
 * Measures the throughput of filling memory buffers with a byte value.
 * A rolling value is used to vary the fill pattern between iterations.
 */

#include <string.h>
#include "../lib/bench.h"
#include "bench_memset.h"

/* Static buffer ensures deterministic behavior without heap usage. */
static unsigned char memset_buffer[BENCH_BUFFER_SIZE];
static volatile unsigned char memset_sink = 0;

/*
 * Run the memset workload.
 * @param iterations Number of fill iterations to execute.
 */
void bench_memset(unsigned int iterations)
{
    for (unsigned int i = 0; i < iterations; ++i)
    {
        memset(memset_buffer, (unsigned char)i, BENCH_BUFFER_SIZE);
        memset_sink ^= memset_buffer[i % BENCH_BUFFER_SIZE];
    }
}
