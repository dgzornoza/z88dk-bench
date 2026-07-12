#ifndef BENCHMARKS_BENCH_MEMSET_H
#define BENCHMARKS_BENCH_MEMSET_H

/*
 * Memory fill workload.
 * Repeatedly fills a buffer with a changing byte value.
 * Buffer size is capped by BENCH_BUFFER_SIZE.
 * @param iterations Number of fill operations to perform.
 */
void bench_memset(unsigned int iterations);

#endif /* BENCHMARKS_BENCH_MEMSET_H */
