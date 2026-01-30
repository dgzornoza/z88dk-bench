#ifndef BENCHMARKS_BENCH_COREMARK_H
#define BENCHMARKS_BENCH_COREMARK_H

/**
 * CoreMark Benchmark - Embedded Performance Benchmark
 *
 * CoreMark is a standard benchmark that measures the performance of embedded
 * processors by executing a set of core operations commonly found in embedded
 * applications:
 *
 * - List Processing: Linked list manipulation (search, insert, delete)
 * - Matrix Operations: 2D matrix math (multiply, transpose)
 * - State Machine: Finite state machine simulation
 * - CRC: Cyclic redundancy check calculations
 *
 * This implementation provides a condensed CoreMark suite optimized for
 * resource-constrained environments like the Sinclair ZX Spectrum.
 *
 * @param iterations Number of times to run the complete CoreMark workload.
 */
void bench_coremark(unsigned int iterations);

#endif /* BENCHMARKS_BENCH_COREMARK_H */
