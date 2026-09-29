#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_BUFFER_SIZE 4096U

typedef struct {
    FILE *stream;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[INPUT_BUFFER_SIZE];
    size_t position;
    size_t length;
    bool error;
} InputReader;

typedef struct {
    uint64_t value;
    uint64_t prime;
    size_t index;
} HeapNode;

static void input_reader_init(InputReader *reader, FILE *stream)
{
    if (reader == NULL) {
        return;
    }

    reader->stream = stream;
    reader->position = 0;
    reader->length = 0;
    reader->error = false;
}

static int input_reader_get(InputReader *reader)
{
    if (reader == NULL || reader->stream == NULL) {
        return EOF;
    }

    if (reader->position >= reader->length) {
        reader->length = fread(reader->buffer, 1, sizeof(reader->buffer),
                               reader->stream);
        reader->position = 0;

        if (reader->length == 0) {
            reader->error = ferror(reader->stream) != 0;
            return EOF;
        }
    }

    return (int)reader->buffer[reader->position++];
}

static bool read_uint64(InputReader *reader, uint64_t *result)
{
    uint64_t value = 0;
    bool overflow = false;
    int character;

    if (reader == NULL || result == NULL) {
        return false;
    }

    do {
        character = input_reader_get(reader);
    } while (character != EOF && isspace((unsigned char)character));

    if (character == EOF || character < '0' || character > '9') {
        return false;
    }

    do {
        uint64_t digit = (uint64_t)(character - '0');

        if (!overflow) {
            if (value > (UINT64_MAX - digit) / UINT64_C(10)) {
                overflow = true;
            } else {
                value = value * UINT64_C(10) + digit;
            }
        }

        character = input_reader_get(reader);
    } while (character >= '0' && character <= '9');

    if (character == EOF) {
        if (reader->error) {
            return false;
        }
    } else if (!isspace((unsigned char)character)) {
        return false;
    }

    if (overflow) {
        return false;
    }

    *result = value;
    return true;
}

static bool input_reader_at_end(InputReader *reader)
{
    int character;

    if (reader == NULL) {
        return false;
    }

    do {
        character = input_reader_get(reader);
    } while (character != EOF && isspace((unsigned char)character));

    return character == EOF && !reader->error;
}

static void swap_nodes(HeapNode *left, HeapNode *right)
{
    HeapNode temporary;

    if (left == NULL || right == NULL) {
        return;
    }

    temporary = *left;
    *left = *right;
    *right = temporary;
}

static void sift_down(HeapNode *heap, size_t heap_size, size_t index)
{
    if (heap == NULL || index >= heap_size) {
        return;
    }

    for (;;) {
        size_t smallest;
        size_t left;
        size_t right;

        if (index > (heap_size - 1) / 2 ||
            index * 2 + 1 >= heap_size) {
            return;
        }

        smallest = index;
        left = index * 2 + 1;
        right = left + 1;

        if (heap[left].value < heap[smallest].value) {
            smallest = left;
        }

        if (right < heap_size &&
            heap[right].value < heap[smallest].value) {
            smallest = right;
        }

        if (smallest == index) {
            return;
        }

        swap_nodes(&heap[index], &heap[smallest]);
        index = smallest;
    }
}

static void sift_up(HeapNode *heap, size_t index)
{
    if (heap == NULL) {
        return;
    }

    while (index > 0) {
        size_t parent = (index - 1) / 2;

        if (heap[parent].value <= heap[index].value) {
            return;
        }

        swap_nodes(&heap[parent], &heap[index]);
        index = parent;
    }
}

static void build_heap(HeapNode *heap, size_t heap_size)
{
    size_t index;

    if (heap == NULL) {
        return;
    }

    for (index = heap_size / 2; index > 0; --index) {
        sift_down(heap, heap_size, index - 1);
    }
}

static bool heap_pop(HeapNode *heap, size_t *heap_size, HeapNode *node)
{
    if (heap == NULL || heap_size == NULL || node == NULL ||
        *heap_size == 0) {
        return false;
    }

    *node = heap[0];
    --(*heap_size);

    if (*heap_size > 0) {
        heap[0] = heap[*heap_size];
        sift_down(heap, *heap_size, 0);
    }

    return true;
}

static bool heap_push(HeapNode *heap, size_t *heap_size, size_t capacity,
                      HeapNode node)
{
    size_t index;

    if (heap == NULL || heap_size == NULL || *heap_size >= capacity) {
        return false;
    }

    index = *heap_size;
    heap[index] = node;
    ++(*heap_size);
    sift_up(heap, index);

    return true;
}

static bool nth_super_ugly_number(size_t n, const uint64_t *primes,
                                  size_t prime_count, uint64_t *result)
{
    uint64_t *ugly = NULL;
    HeapNode *heap = NULL;
    size_t heap_size;
    size_t count;
    size_t index;
    bool success = false;

    if (n == 0 || primes == NULL || prime_count == 0 || result == NULL) {
        return false;
    }

    for (index = 0; index < prime_count; ++index) {
        if (primes[index] < UINT64_C(2)) {
            return false;
        }
    }

    if (n == 1) {
        *result = UINT64_C(1);
        return true;
    }

    if (n > SIZE_MAX / sizeof(*ugly) ||
        prime_count > SIZE_MAX / sizeof(*heap)) {
        return false;
    }

    ugly = malloc(n * sizeof(*ugly));
    if (ugly == NULL) {
        goto cleanup;
    }

    heap = malloc(prime_count * sizeof(*heap));
    if (heap == NULL) {
        goto cleanup;
    }

    ugly[0] = UINT64_C(1);

    for (index = 0; index < prime_count; ++index) {
        heap[index].value = primes[index];
        heap[index].prime = primes[index];
        heap[index].index = 0;
    }

    heap_size = prime_count;
    count = 1;
    build_heap(heap, heap_size);

    while (count < n) {
        uint64_t next_value;
        HeapNode node;

        if (heap_size == 0) {
            goto cleanup;
        }

        next_value = heap[0].value;
        ugly[count++] = next_value;

        while (heap_size > 0 && heap[0].value == next_value) {
            if (!heap_pop(heap, &heap_size, &node)) {
                goto cleanup;
            }

            if (node.index == SIZE_MAX) {
                goto cleanup;
            }

            ++node.index;

            if (node.index >= count) {
                goto cleanup;
            }

            if (ugly[node.index] > UINT64_MAX / node.prime) {
                continue;
            }

            node.value = ugly[node.index] * node.prime;

            if (!heap_push(heap, &heap_size, prime_count, node)) {
                goto cleanup;
            }
        }
    }

    *result = ugly[n - 1];
    success = true;

cleanup:
    free(heap);
    free(ugly);
    return success;
}

int main(void)
{
    InputReader reader;
    uint64_t n_input;
    uint64_t prime_count_input;
    uint64_t *primes = NULL;
    uint64_t result;
    size_t n;
    size_t prime_count;
    size_t index;
    int exit_status = EXIT_FAILURE;

    input_reader_init(&reader, stdin);

    if (!read_uint64(&reader, &n_input) ||
        !read_uint64(&reader, &prime_count_input)) {
        fprintf(stderr, "Invalid input\n");
        goto cleanup;
    }

    if (n_input == 0 || prime_count_input == 0) {
        fprintf(stderr, "Input values are out of range\n");
        goto cleanup;
    }

#if SIZE_MAX < UINT64_MAX
    if (n_input > (uint64_t)SIZE_MAX ||
        prime_count_input > (uint64_t)SIZE_MAX) {
        fprintf(stderr, "Input values are out of range\n");
        goto cleanup;
    }
#endif

    n = (size_t)n_input;
    prime_count = (size_t)prime_count_input;

    if (prime_count > SIZE_MAX / sizeof(*primes)) {
        fprintf(stderr, "Prime list is too large\n");
        goto cleanup;
    }

    primes = malloc(prime_count * sizeof(*primes));
    if (primes == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        goto cleanup;
    }

    for (index = 0; index < prime_count; ++index) {
        if (!read_uint64(&reader, &primes[index]) ||
            primes[index] < UINT64_C(2)) {
            fprintf(stderr, "Invalid prime list\n");
            goto cleanup;
        }
    }

    if (!input_reader_at_end(&reader)) {
        fprintf(stderr, "Unexpected trailing input\n");
        goto cleanup;
    }

    if (!nth_super_ugly_number(n, primes, prime_count, &result)) {
        fprintf(stderr, "Unable to compute the requested value\n");
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        fprintf(stderr, "Output error\n");
        goto cleanup;
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    free(primes);
    return exit_status;
}