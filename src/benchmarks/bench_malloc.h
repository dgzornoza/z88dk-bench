#ifndef BENCHMARKS_BENCH_MALLOC_H
#define BENCHMARKS_BENCH_MALLOC_H

/*
 * Malloc Benchmark
 * ----------------
 * Exercises dynamic allocation and deallocation overhead using a
 * small set of fixed sizes. Designed for constrained systems with
 * limited heap memory.
 *
 * @param iterations Number of allocation/free cycles to run.
 */
void bench_malloc(unsigned int iterations);

#endif /* BENCHMARKS_BENCH_MALLOC_H */
