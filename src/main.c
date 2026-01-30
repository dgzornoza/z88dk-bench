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
#include "benchmarks/bench_coremark.h"
#include "benchmarks/bench_fpmark.h"
#include "benchmarks/bench_malloc.h"

#define BENCH_ARITHMETIC_ITERATIONS 100000
#define BENCH_CALL_ITERATIONS 100000
#define BENCH_MEM_ITERATIONS 2000
#define BENCH_COREMARK_ITERATIONS 25
#define BENCH_FPMARK_ITERATIONS 50
#define BENCH_MALLOC_ITERATIONS 2000

int main(void)
{
    enable_ei();

    // standard benchmarks
    bench_start("bench_coremark");
    bench_coremark(BENCH_COREMARK_ITERATIONS);
    bench_end();

    bench_start("bench_fpmark");
    bench_fpmark(BENCH_FPMARK_ITERATIONS);
    bench_end();

    // custom benchmarks
    bench_start("bench_add");
    bench_add(BENCH_ARITHMETIC_ITERATIONS);
    bench_end();

    bench_start("bench_call");
    bench_call(BENCH_CALL_ITERATIONS);
    bench_end();

    bench_start("bench_memcpy");
    bench_memcpy(BENCH_MEM_ITERATIONS);
    bench_end();

    bench_start("bench_memset");
    bench_memset(BENCH_MEM_ITERATIONS);
    bench_end();

    bench_start("bench_malloc");
    bench_malloc(BENCH_MALLOC_ITERATIONS);
    bench_end();

    print_string(FONT_CONTROL_CRLF "All benchmarks completed." FONT_CONTROL_CRLF);

    return 0;
}
