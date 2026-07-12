/*
 * Benchmark harness entry point.
 * Runs a set of modular benchmarks located in src/benchmarks, using
 * common timing helpers from src/lib/bench.*.
 * Add new benchmarks by creating a module and invoking it between
 * bench_start("name") and bench_end().
 */
#include "z88dk_headers.h"
#include "lib/io.h"
#include "lib/bench.h"
#include "benchmarks/bench_add.h"
#include "benchmarks/bench_memcpy.h"
#include "benchmarks/bench_memset.h"
#include "benchmarks/bench_call.h"

#define BENCH_ARITHMETIC_ITERATIONS 40000
#define BENCH_CALL_ITERATIONS 100000
#define BENCH_MEM_ITERATIONS 1000

int main(void)
{
    enable_ei();

    bench_start("bench_add");
    bench_add(BENCH_ARITHMETIC_ITERATIONS);
    bench_end();

    bench_start("bench_memcpy");
    bench_memcpy(BENCH_MEM_ITERATIONS);
    bench_end();

    bench_start("bench_memset");
    bench_memset(BENCH_MEM_ITERATIONS);
    bench_end();

    bench_start("bench_call");
    bench_call(BENCH_CALL_ITERATIONS);
    bench_end();

    return 0;
}
