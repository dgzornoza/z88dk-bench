/*
 * Integer Addition Benchmark
 *
 * A tiny arithmetic workload that performs repeated integer additions.
 * The goal is to measure ALU throughput and loop overhead using a
 * predictable sequence of operations.
 */

#include "../lib/bench.h"
#include "bench_add.h"

/* Volatile accumulator prevents the compiler from removing the loop. */
static volatile unsigned int add_accumulator = 0;

/*
 * Run the integer addition workload.
 * @param iterations Number of loop iterations to execute.
 */
void bench_add(unsigned int iterations)
{
    for (unsigned int i = 0; i < iterations; ++i)
    {
        add_accumulator += 1;
        add_accumulator += 2;
        add_accumulator += 3;
        add_accumulator += 4;
        add_accumulator += 5;
    }
}
