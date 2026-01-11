#ifndef BENCHMARKS_BENCH_ADD_H
#define BENCHMARKS_BENCH_ADD_H

/*
 * Integer addition workload.
 * Performs repeated unsigned 16-bit additions to exercise ALU ops.
 * @param iterations Number of loop iterations to run.
 */
void bench_add(unsigned int iterations);

#endif /* BENCHMARKS_BENCH_ADD_H */
