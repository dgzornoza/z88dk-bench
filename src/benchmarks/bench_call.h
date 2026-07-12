#ifndef BENCHMARKS_BENCH_CALL_H
#define BENCHMARKS_BENCH_CALL_H

/*
 * Function-call overhead benchmark.
 * Repeatedly calls a small __z88dk_fastcall function to measure call cost.
 * @param iterations Number of invocations to perform.
 */
void bench_call(unsigned int iterations) __z88dk_fastcall;

#endif /* BENCHMARKS_BENCH_CALL_H */
