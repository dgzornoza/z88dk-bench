#ifndef LIB_BENCH_H
#define LIB_BENCH_H

/*
 * Benchmark timing helpers for z88dk.
 *
 * Overview
 * --------
 * These helpers provide a simple, consistent way to time benchmarks.
 * Use `bench_start(name)` to announce and start timing, run your benchmark workload, then call
 * `bench_end()` to print and return the elapsed time in milliseconds.
 *
 * Example
 * -------
 *   bench_start("bench_add");
 *   bench_add(BENCH_ITERATIONS);
 *   (void)bench_end();
 *
 * Tunables
 * --------
 * - BENCH_ITERATIONS:       Default loop count for light workloads
 * - BENCH_MEMCPY_SIZE:      Default byte size for memory tests
 * - BENCH_CALL_ITERATIONS:  Default loop count for call overhead
 * - BENCH_BUFFER_SIZE:      Shared scratch buffer capacity
 */

#include "io.h"
#include "zx_clock.h"
#include <stdlib.h>

/** Large buffer for various tests */
#define BENCH_BUFFER_SIZE 512

/**
 * Start a benchmark and announce its name.
 * @param name Null-terminated label printed before timing begins.
 */
void bench_start(const char *name);

/**
 * End a benchmark and print elapsed time in milliseconds.
 * @return Elapsed time in milliseconds.
 */
unsigned long bench_end(void);

#endif /* LIB_BENCH_H */
