/**
 * CoreMark Benchmark Implementation
 *
 * A modular implementation of CoreMark, divided into four core workloads:
 * 1. List Processing - Linked list operations
 * 2. Matrix Operations - Linear algebra computations
 * 3. State Machine - FSM state transitions
 * 4. CRC Calculation - Checksum computation
 */

#include "../lib/bench.h"
#include "bench_coremark.h"

/* ============================================================================
 * List Processing Workload
 * ============================================================================
 * Exercises linked list traversal, insertion, and deletion.
 * Common in embedded systems for data structure management.
 */

#define LIST_SIZE 32

/**
 * Linked list node structure containing both data and pointer.
 */
typedef struct coremark_list_node {
    unsigned int data;
    struct coremark_list_node *next;
} list_node_t;

/**
 * Static list node storage to avoid dynamic allocation.
 * Each node contains an integer payload for processing.
 */
static list_node_t list_nodes[LIST_SIZE];

/**
 * Initialize the linked list with sequential data values.
 * Creates a chain of nodes where each points to the next.
 *
 * @return Pointer to the head of the initialized list.
 */
static list_node_t *coremark_list_init(void)
{
    for (unsigned int i = 0; i < LIST_SIZE - 1; ++i) {
        list_nodes[i].data = i;
        list_nodes[i].next = &list_nodes[i + 1];
    }
    list_nodes[LIST_SIZE - 1].data = LIST_SIZE - 1;
    list_nodes[LIST_SIZE - 1].next = NULL;

    return &list_nodes[0];
}

/**
 * Traverse a linked list, accumulating data values.
 * This operation exercises memory access patterns and pointer dereferencing.
 *
 * @param head Pointer to the list head.
 * @return Sum of all node data values.
 */
static unsigned int coremark_list_traverse(list_node_t *head)
{
    unsigned int sum = 0;
    list_node_t *current = head;

    while (current != NULL) {
        sum += current->data;
        current = current->next;
    }

    return sum;
}

/* ============================================================================
 * Matrix Operations Workload
 * ============================================================================
 * Performs matrix multiplication and operations.
 * Represents numerical computation common in signal processing.
 */

#define MATRIX_SIZE 8

/**
 * Small matrix for multiplication workload.
 * Each element is an 8-bit value to conserve memory on embedded systems.
 */
typedef struct {
    unsigned char data[MATRIX_SIZE][MATRIX_SIZE];
} coremark_matrix_t;

/**
 * Static matrices used for benchmark operations.
 */
static coremark_matrix_t matrix_a;
static coremark_matrix_t matrix_b;
static coremark_matrix_t matrix_result;

/**
 * Initialize matrices with test data.
 * Each matrix is filled with sequential values to create predictable computations.
 */
static void coremark_matrix_init(void)
{
    for (unsigned int i = 0; i < MATRIX_SIZE; ++i) {
        for (unsigned int j = 0; j < MATRIX_SIZE; ++j) {
            matrix_a.data[i][j] = (i + j) % 256;
            matrix_b.data[i][j] = (i * j) % 256;
            matrix_result.data[i][j] = 0;
        }
    }
}

/**
 * Multiply two matrices using standard row-by-column dot products.
 * This is compute-intensive and exercises the CPU's arithmetic units.
 * Result is stored modulo 256 to prevent overflow.
 */
static void coremark_matrix_multiply(void)
{
    for (unsigned int i = 0; i < MATRIX_SIZE; ++i) {
        for (unsigned int j = 0; j < MATRIX_SIZE; ++j) {
            unsigned int sum = 0;
            for (unsigned int k = 0; k < MATRIX_SIZE; ++k) {
                sum += (unsigned int)matrix_a.data[i][k] *
                       (unsigned int)matrix_b.data[k][j];
            }
            matrix_result.data[i][j] = sum % 256;
        }
    }
}

/* ============================================================================
 * State Machine Workload
 * ============================================================================
 * Simulates a finite state machine processing an input stream.
 * Models embedded systems that respond to external events.
 */

#define STATE_COUNT 8
#define STATE_INPUT_SIZE 64

/**
 * State machine state enumeration.
 */
typedef enum {
    STATE_IDLE = 0,
    STATE_ACTIVE = 1,
    STATE_PROCESSING = 2,
    STATE_WAIT = 3,
    STATE_ERROR = 4,
    STATE_RESET = 5,
    STATE_SUSPEND = 6,
    STATE_SHUTDOWN = 7
} coremark_state_t;

/**
 * State transition table: next_state[current_state][input]
 * Each state has a defined next state based on the input value.
 */
static const coremark_state_t state_transitions[STATE_COUNT][4] = {
    { STATE_ACTIVE,    STATE_IDLE,    STATE_RESET,   STATE_IDLE      }, /* From IDLE */
    { STATE_PROCESSING,STATE_WAIT,    STATE_ERROR,   STATE_ACTIVE    }, /* From ACTIVE */
    { STATE_WAIT,      STATE_IDLE,    STATE_RESET,   STATE_PROCESSING}, /* From PROCESSING */
    { STATE_PROCESSING,STATE_ACTIVE,  STATE_ERROR,   STATE_WAIT      }, /* From WAIT */
    { STATE_RESET,     STATE_RESET,   STATE_RESET,   STATE_RESET     }, /* From ERROR */
    { STATE_IDLE,      STATE_IDLE,    STATE_IDLE,    STATE_IDLE      }, /* From RESET */
    { STATE_IDLE,      STATE_ACTIVE,  STATE_SUSPEND, STATE_SUSPEND   }, /* From SUSPEND */
    { STATE_RESET,     STATE_RESET,   STATE_RESET,   STATE_RESET     }, /* From SHUTDOWN */
};

/**
 * Simulate a state machine processing input stream.
 * Exercises branching and indirect memory access patterns.
 *
 * @return Final state accumulator (for verification).
 */
static unsigned int coremark_state_machine(void)
{
    coremark_state_t state = STATE_IDLE;
    unsigned int result = 0;

    /* Process a stream of input values */
    for (unsigned int i = 0; i < STATE_INPUT_SIZE; ++i) {
        unsigned char input = i % 4;
        state = state_transitions[state][input];
        result += (unsigned int)state;
    }

    return result;
}

/* ============================================================================
 * CRC Calculation Workload
 * ============================================================================
 * Performs CRC-16 checksum calculation over a data buffer.
 * Represents data validation and error detection in embedded systems.
 */

#define CRC_DATA_SIZE 256

/**
 * Static data buffer for CRC computation.
 */
static unsigned char crc_data_buffer[CRC_DATA_SIZE];

/**
 * Initialize CRC data buffer with test pattern.
 */
static void coremark_crc_init(void)
{
    for (unsigned int i = 0; i < CRC_DATA_SIZE; ++i) {
        crc_data_buffer[i] = (unsigned char)((i ^ (i >> 4)) & 0xFF);
    }
}

/**
 * Compute CRC-16 checksum using polynomial x^16 + x^15 + x^2 + 1.
 * This is a standard CRC used in many embedded protocols.
 *
 * @return Computed CRC-16 value.
 */
static unsigned int coremark_crc_calculate(void)
{
    unsigned int crc = 0xFFFF;

    for (unsigned int i = 0; i < CRC_DATA_SIZE; ++i) {
        unsigned char byte = crc_data_buffer[i];

        for (unsigned int bit = 0; bit < 8; ++bit) {
            unsigned int feedback = (crc ^ byte) & 1;
            crc >>= 1;

            if (feedback) {
                crc ^= 0xA001;  /* CRC-16-IBM polynomial */
            }

            byte >>= 1;
        }
    }

    return crc;
}

/* ============================================================================
 * Main CoreMark Benchmark Driver
 * ============================================================================
 */

/**
 * Run the complete CoreMark benchmark suite.
 *
 * The benchmark executes four distinct workloads multiple times:
 * 1. List Processing - Linked list traversal and manipulation
 * 2. Matrix Operations - Floating-point like computations
 * 3. State Machine - Control flow and branching patterns
 * 4. CRC Calculation - Bit manipulation and checksums
 *
 * Each iteration of the suite exercises different aspects of the CPU:
 * - Memory bandwidth (lists, matrices)
 * - Branch prediction (state machine)
 * - Arithmetic units (matrix multiply, CRC)
 * - Load/store pipelines (all workloads)
 *
 * @param iterations Number of complete CoreMark suite iterations.
 */
void bench_coremark(unsigned int iterations)
{
    volatile unsigned int accumulator = 0;

    /* Initialize static data structures */
    list_node_t *list_head = coremark_list_init();
    coremark_matrix_init();
    coremark_crc_init();

    /* Execute the complete CoreMark suite */
    for (unsigned int iter = 0; iter < iterations; ++iter) {

        /* List Processing Workload */
        accumulator += coremark_list_traverse(list_head);

        /* Matrix Multiplication Workload */
        coremark_matrix_multiply();
        accumulator += matrix_result.data[0][0];

        /* State Machine Workload */
        accumulator += coremark_state_machine();

        /* CRC Calculation Workload */
        accumulator += coremark_crc_calculate();
    }

    /* Use accumulator to prevent compiler optimization */
    (void)accumulator;
}
