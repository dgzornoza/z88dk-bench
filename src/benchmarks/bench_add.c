#include "../lib/bench.h"
#include "bench_add.h"

static volatile unsigned int add_accumulator = 0;

void bench_add(unsigned int iterations)
{
    for (unsigned int i = 0; i < iterations; ++i)
    {
        add_accumulator += 1;
        add_accumulator += 2;
        add_accumulator += 3;
        add_accumulator += 4;
        add_accumulator += 5;
    }
}
