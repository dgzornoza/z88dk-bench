/*
 * Function Call Benchmark
 *
 * Measures the overhead of repeatedly calling a small function.
 * Uses __z88dk_fastcall to exercise the fastcall calling convention.
 */

#include "../lib/bench.h"
#include "bench_call.h"

/* Volatile sink ensures calls are not optimized away. */
static volatile unsigned int call_sink = 0;

/*
 * Target function called in the tight loop.
 * @param value Input value accumulated into the sink.
 */
static void bench_target(unsigned int value) __z88dk_fastcall
{
    call_sink += value;
}

/*
 * Run the function call workload.
 * @param iterations Number of calls to perform.
 */
void bench_call(unsigned int iterations) __z88dk_fastcall
{
    for (unsigned int i = 0; i < iterations; ++i)
    {
        bench_target(i);
    }
}
