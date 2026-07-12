#ifndef BENCHMARKS_BENCH_FPMARK_H
#define BENCHMARKS_BENCH_FPMARK_H

/*
 * FPMark Benchmark
 * ----------------
 * A compact floating-point benchmark designed for 8-bit systems with
 * software floating-point support. The workload exercises:
 * - Multiply-add sequences (vector style operations)
 * - A small IIR-like filter update
 * - Division and normalization
 * - Accumulation to prevent dead-code elimination
 *
 * @param iterations Number of full FPMark iterations to run.
 */
void bench_fpmark(unsigned int iterations);

#endif /* BENCHMARKS_BENCH_FPMARK_H */
