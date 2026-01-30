/*
 * Malloc Benchmark Implementation
 *
 * Measures the overhead of repeated malloc/free cycles while touching
 * allocated memory to ensure the work is not optimized away.
 */

#include "bench_malloc.h"
#include "../lib/bench.h"
#include <stdlib.h>

/* Keep sizes modest to fit typical 8-bit heap constraints. */
#define MALLOC_SIZES_COUNT 5
static const unsigned int malloc_sizes[MALLOC_SIZES_COUNT] = { 16u, 24u, 32u, 48u, 64u };

/* Volatile sink to prevent the compiler from removing memory writes. */
static volatile unsigned char malloc_sink = 0;

/*
 * Run the malloc benchmark workload.
 * - Allocate a small block.
 * - Touch memory to simulate real use.
 * - Free the block.
 */
void bench_malloc(unsigned int iterations)
{
    for (unsigned int iter = 0; iter < iterations; ++iter) {
        unsigned int size = malloc_sizes[iter % MALLOC_SIZES_COUNT];
        unsigned char *buffer = (unsigned char *)malloc(size);

        if (buffer != NULL) {
            /* Write a simple pattern to the buffer. */
            for (unsigned int i = 0; i < size; ++i) {
                buffer[i] = (unsigned char)(i + (iter & 0xFFu));
            }

            /* Read back one byte to keep the writes observable. */
            malloc_sink ^= buffer[size - 1u];

            free(buffer);
        } else {
            /* If allocation fails, still perturb the sink to keep timing stable. */
            malloc_sink ^= (unsigned char)(size & 0xFFu);
        }
    }
}
