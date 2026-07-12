#ifndef BENCHMARKS_BENCH_MEMCPY_H
#define BENCHMARKS_BENCH_MEMCPY_H

/*
 * Memory copy workload.
 * Repeatedly copies `size` bytes from a source buffer to a destination buffer.
 * Buffer size is capped by BENCH_BUFFER_SIZE.
 * @param iterations Number of memcpy operations to perform.
 */
void bench_memcpy(unsigned int iterations);

#endif /* BENCHMARKS_BENCH_MEMCPY_H */
