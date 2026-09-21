#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    INPUT_BUFFER_SIZE = 4096
};

typedef struct {
    FILE *stream;
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

static bool input_reader_init(InputReader *reader, FILE *stream)
{
    if (reader == NULL || stream == NULL) {
        return false;
    }

    reader->stream = stream;
    reader->position = 0U;
    reader->length = 0U;
    reader->error = false;

    return true;
}

static int input_reader_get(InputReader *reader)
{
    if (reader == NULL || reader->stream == NULL) {
        return EOF;
    }

    if (reader->position == reader->length) {
        reader->length = fread(reader->buffer, 1U,
                               sizeof(reader->buffer), reader->stream);
        reader->position = 0U;

        if (reader->length == 0U) {
            if (ferror(reader->stream) != 0) {
                reader->error = true;
            }

            return EOF;
        }
    }

    return (int)reader->buffer[reader->position++];
}

static bool read_uint64(InputReader *reader, uint64_t *result)
{
    uint64_t value = UINT64_C(0);
    int character;

    if (reader == NULL || result == NULL) {
        return false;
    }

    do {
        character = input_reader_get(reader);
    } while (character != EOF &&
             isspace((unsigned char)character) != 0);

    if (character == EOF || character < '0' || character > '9') {
        return false;
    }

    do {
        const uint64_t digit = (uint64_t)(character - '0');

        if (value > (UINT64_MAX - digit) / UINT64_C(10)) {
            do {
                character = input_reader_get(reader);
            } while (character >= '0' && character <= '9');

            return false;
        }

        value = value * UINT64_C(10) + digit;
        character = input_reader_get(reader);
    } while (character >= '0' && character <= '9');

    if (character == EOF) {
        if (reader->error) {
            return false;
        }
    } else if (isspace((unsigned char)character) == 0) {
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
    } while (character != EOF &&
             isspace((unsigned char)character) != 0);

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
        size_t left;
        size_t right;
        size_t smallest = index;

        if (index > (heap_size - 1U) / 2U) {
            return;
        }

        left = index * 2U + 1U;

        if (left >= heap_size) {
            return;
        }

        right = left + 1U;

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

    while (index > 0U) {
        const size_t parent = (index - 1U) / 2U;

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

    for (index = heap_size / 2U; index > 0U; --index) {
        sift_down(heap, heap_size, index - 1U);
    }
}

static bool heap_pop(HeapNode *heap, size_t *heap_size, HeapNode *node)
{
    if (heap == NULL || heap_size == NULL || node == NULL ||
        *heap_size == 0U) {
        return false;
    }

    *node = heap[0];
    --(*heap_size);

    if (*heap_size > 0U) {
        heap[0] = heap[*heap_size];
        sift_down(heap, *heap_size, 0U);
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

    if (n == 0U || primes == NULL || prime_count == 0U ||
        result == NULL) {
        return false;
    }

    for (index = 0U; index < prime_count; ++index) {
        if (primes[index] < UINT64_C(2)) {
            return false;
        }
    }

    if (n == 1U) {
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

    for (index = 0U; index < prime_count; ++index) {
        heap[index].value = primes[index];
        heap[index].prime = primes[index];
        heap[index].index = 0U;
    }

    heap_size = prime_count;
    count = 1U;
    build_heap(heap, heap_size);

    while (count < n) {
        uint64_t next_value;
        HeapNode node;

        if (heap_size == 0U) {
            goto cleanup;
        }

        next_value = heap[0].value;
        ugly[count] = next_value;
        ++count;

        while (heap_size > 0U && heap[0].value == next_value) {
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

    *result = ugly[n - 1U];
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

    if (!input_reader_init(&reader, stdin)) {
        fprintf(stderr, "Unable to initialize input reader\n");
        return EXIT_FAILURE;
    }

    if (!read_uint64(&reader, &n_input) ||
        !read_uint64(&reader, &prime_count_input)) {
        fprintf(stderr, "Invalid input\n");
        goto cleanup;
    }

    if (n_input == UINT64_C(0) ||
        prime_count_input == UINT64_C(0)) {
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

    for (index = 0U; index < prime_count; ++index) {
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