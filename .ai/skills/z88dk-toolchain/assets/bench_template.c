#include "benchmarks/bench_template.h"

/*
 * Minimal benchmark skeleton.
 *
 * - Use `volatile unsigned int accumulator` and `(void)accumulator;`
 *   to defeat dead-code elimination.
 * - The harness already starts/stops the clock via bench_start/bench_end.
 * - Keep all work inside the `iterations` loop; do not allocate per-iteration.
 */

void bench_template(unsigned int iterations)
{
    volatile unsigned int accumulator = 0;
    unsigned int i;

    for (i = 0; i < iterations; ++i) {
        /* TODO: replace with the operation under measurement */
        accumulator += i;
    }

    (void)accumulator;
}