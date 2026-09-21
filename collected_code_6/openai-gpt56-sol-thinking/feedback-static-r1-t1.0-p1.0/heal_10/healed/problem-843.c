#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <ctype.h>
#include <stddef.h>

#define INPUT_BUFFER_SIZE 4096U

typedef struct {
    uint64_t value;
    uint64_t prime;
    size_t index;
} HeapNode;

typedef struct {
    FILE *stream;
    unsigned char buffer[INPUT_BUFFER_SIZE];
    size_t position;
    size_t length;
    bool exhausted;
    bool failed;
} InputReader;

static void input_reader_init(InputReader *reader, FILE *stream)
{
    if (reader == NULL) {
        return;
    }

    reader->stream = stream;
    reader->position = 0;
    reader->length = 0;
    reader->exhausted = false;
    reader->failed = false;
}

static int input_reader_get(InputReader *reader)
{
    if (reader == NULL || reader->stream == NULL ||
        reader->failed || reader->exhausted) {
        return EOF;
    }

    if (reader->position == reader->length) {
        reader->length = fread(reader->buffer, 1,
                               sizeof(reader->buffer), reader->stream);
        reader->position = 0;

        if (reader->length == 0) {
            if (ferror(reader->stream)) {
                reader->failed = true;
            }

            reader->exhausted = true;
            return EOF;
        }
    }

    return (int)reader->buffer[reader->position++];
}

static bool read_uintmax_value(InputReader *reader, uintmax_t limit,
                               uintmax_t *result)
{
    uintmax_t value = 0;
    bool valid = true;
    bool has_digit = false;
    int character;

    if (reader == NULL || result == NULL) {
        return false;
    }

    do {
        character = input_reader_get(reader);
        if (character == EOF) {
            return false;
        }
    } while (isspace((unsigned char)character) != 0);

    while (character != EOF &&
           isspace((unsigned char)character) == 0) {
        if (character >= '0' && character <= '9') {
            uintmax_t digit = (uintmax_t)(character - '0');

            has_digit = true;

            if (valid) {
                if (value > limit / UINTMAX_C(10) ||
                    (value == limit / UINTMAX_C(10) &&
                     digit > limit % UINTMAX_C(10))) {
                    valid = false;
                } else {
                    value = value * UINTMAX_C(10) + digit;
                }
            }
        } else {
            valid = false;
        }

        character = input_reader_get(reader);
    }

    if (reader->failed || !valid || !has_digit) {
        return false;
    }

    *result = value;
    return true;
}

static bool input_has_only_whitespace(InputReader *reader)
{
    int character;

    if (reader == NULL) {
        return false;
    }

    while ((character = input_reader_get(reader)) != EOF) {
        if (isspace((unsigned char)character) == 0) {
            return false;
        }
    }

    return !reader->failed;
}

static void heap_sift_down(HeapNode *heap, size_t size, size_t index)
{
    if (heap == NULL || index >= size) {
        return;
    }

    for (;;) {
        size_t left;
        size_t right;
        size_t smallest;
        HeapNode temporary;

        if (index >= size / 2) {
            break;
        }

        left = index * 2 + 1;
        right = left + 1;
        smallest = left;

        if (right < size && heap[right].value < heap[left].value) {
            smallest = right;
        }

        if (heap[index].value <= heap[smallest].value) {
            break;
        }

        temporary = heap[index];
        heap[index] = heap[smallest];
        heap[smallest] = temporary;
        index = smallest;
    }
}

static void heap_build(HeapNode *heap, size_t size)
{
    size_t i;

    if (heap == NULL) {
        return;
    }

    for (i = size / 2; i > 0; --i) {
        heap_sift_down(heap, size, i - 1);
    }
}

static bool nth_super_ugly_number(size_t n, const uint64_t *primes,
                                  size_t prime_count, uint64_t *result)
{
    uint64_t *numbers = NULL;
    HeapNode *heap = NULL;
    size_t heap_size;
    bool success = false;
    size_t i;

    if (n == 0 || prime_count == 0 || primes == NULL || result == NULL) {
        return false;
    }

    for (i = 0; i < prime_count; ++i) {
        if (primes[i] < UINT64_C(2)) {
            return false;
        }
    }

    if (n == 1) {
        *result = UINT64_C(1);
        return true;
    }

    if (n > SIZE_MAX / sizeof(*numbers) ||
        prime_count > SIZE_MAX / sizeof(*heap)) {
        return false;
    }

    numbers = malloc(n * sizeof(*numbers));
    if (numbers == NULL) {
        return false;
    }

    heap = malloc(prime_count * sizeof(*heap));
    if (heap == NULL) {
        free(numbers);
        return false;
    }

    numbers[0] = UINT64_C(1);
    heap_size = prime_count;

    for (i = 0; i < prime_count; ++i) {
        heap[i].value = primes[i];
        heap[i].prime = primes[i];
        heap[i].index = 0;
    }

    heap_build(heap, heap_size);

    for (i = 1; i < n; ++i) {
        uint64_t next;

        if (heap_size == 0) {
            goto cleanup;
        }

        next = heap[0].value;
        numbers[i] = next;

        if (i == n - 1) {
            break;
        }

        while (heap_size > 0 && heap[0].value == next) {
            HeapNode node = heap[0];

            if (node.index >= i) {
                goto cleanup;
            }

            ++node.index;

            if (numbers[node.index] > UINT64_MAX / node.prime) {
                --heap_size;

                if (heap_size > 0) {
                    heap[0] = heap[heap_size];
                    heap_sift_down(heap, heap_size, 0);
                }
            } else {
                node.value = node.prime * numbers[node.index];
                heap[0] = node;
                heap_sift_down(heap, heap_size, 0);
            }
        }
    }

    *result = numbers[n - 1];
    success = true;

cleanup:
    free(heap);
    free(numbers);
    return success;
}

int main(void)
{
    InputReader reader;
    uintmax_t n_input;
    uintmax_t prime_count_input;
    uint64_t *primes;
    uint64_t result;
    size_t n;
    size_t prime_count;
    size_t i;

    input_reader_init(&reader, stdin);

    if (!read_uintmax_value(&reader, (uintmax_t)SIZE_MAX, &n_input) ||
        !read_uintmax_value(&reader, (uintmax_t)SIZE_MAX,
                            &prime_count_input) ||
        n_input == 0 ||
        prime_count_input == 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    n = (size_t)n_input;
    prime_count = (size_t)prime_count_input;

    if (prime_count > SIZE_MAX / sizeof(*primes)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    primes = malloc(prime_count * sizeof(*primes));
    if (primes == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < prime_count; ++i) {
        uintmax_t prime_input;

        if (!read_uintmax_value(&reader, (uintmax_t)UINT64_MAX,
                                &prime_input) ||
            prime_input < UINTMAX_C(2)) {
            fputs("Invalid prime list\n", stderr);
            free(primes);
            return EXIT_FAILURE;
        }

        primes[i] = (uint64_t)prime_input;
    }

    if (!input_has_only_whitespace(&reader)) {
        fputs("Unexpected trailing input\n", stderr);
        free(primes);
        return EXIT_FAILURE;
    }

    if (!nth_super_ugly_number(n, primes, prime_count, &result)) {
        fputs("Unable to compute the requested value\n", stderr);
        free(primes);
        return EXIT_FAILURE;
    }

    free(primes);

    if (printf("%" PRIu64 "\n", result) < 0) {
        fputs("Output error\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}