/*
 * FPMark Benchmark Implementation
 *
 * A deterministic floating-point workload intended for small embedded
 * targets. The test uses only basic arithmetic so it can run on
 * software floating-point runtimes without relying on libm.
 */

#include "bench_fpmark.h"
#include "../lib/bench.h"

/* Size of the working vectors (small enough for 8-bit targets). */
#define FPMARK_VECTOR_SIZE 32

/* Coefficients for IIR-like update and normalization. */
#define FPMARK_ALPHA 0.75f
#define FPMARK_BETA  0.25f
#define FPMARK_DECAY 0.999f
#define FPMARK_BIAS  0.001f

/* Working buffers and sink to prevent optimization. */
static float fpmark_vector[FPMARK_VECTOR_SIZE];
static float fpmark_coeffs[FPMARK_VECTOR_SIZE];
static volatile float fpmark_sink = 0.0f;

/*
 * Initialize the working vectors with deterministic values.
 * A simple linear congruential generator (LCG) avoids lib dependencies.
 */
static void fpmark_init(void)
{
    unsigned int seed = 0x1234u;

    for (unsigned int i = 0; i < FPMARK_VECTOR_SIZE; ++i) {
        seed = (seed * 1103515245u + 12345u);
        fpmark_vector[i] = (float)(seed & 0xFF) / 255.0f;   /* 0.0 .. 1.0 */

        seed = (seed * 1103515245u + 12345u);
        fpmark_coeffs[i] = ((float)(seed & 0x7F) / 127.0f) - 0.5f; /* -0.5 .. 0.5 */
    }
}

/*
 * Run the FPMark benchmark workload.
 *
 * The workload contains:
 * - A multiply-add loop over a small vector
 * - An IIR-like filter update (depends on previous value)
 * - A division-based normalization step
 * - A decay step to keep values bounded
 */
void bench_fpmark(unsigned int iterations)
{
    float accumulator = 0.0f;
    float prev = 0.0f;

    fpmark_init();

    for (unsigned int iter = 0; iter < iterations; ++iter) {
        for (unsigned int i = 0; i < FPMARK_VECTOR_SIZE; ++i) {
            float x = fpmark_vector[i];
            float c = fpmark_coeffs[i];

            /* Multiply-add sequence and simple IIR-like update. */
            float y = (c * x) + (FPMARK_ALPHA * prev);
            prev = (FPMARK_BETA * y);

            /* Update working vector to avoid trivial optimization. */
            fpmark_vector[i] = x + (FPMARK_BETA * y);

            /* Accumulate with a shifted coefficient to vary access. */
            accumulator += y * fpmark_coeffs[(i + 7u) % FPMARK_VECTOR_SIZE];
        }

        /* Normalize with a division step to stress FP division. */
        {
            float denom = 1.0f + (float)(iter & 7u) * 0.125f;
            accumulator += fpmark_vector[iter % FPMARK_VECTOR_SIZE] / denom;
        }

        /* Apply a small decay to keep values in range. */
        accumulator = (accumulator * FPMARK_DECAY) + FPMARK_BIAS;
    }

    /* Make sure the compiler cannot remove the computations. */
    fpmark_sink = accumulator + prev;
}
