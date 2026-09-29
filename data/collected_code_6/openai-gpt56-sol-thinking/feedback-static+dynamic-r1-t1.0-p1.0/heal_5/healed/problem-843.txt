#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <ctype.h>
#include <stddef.h>

typedef struct {
    FILE *stream;
    bool end_of_file;
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
    reader->end_of_file = false;
    reader->error = false;
    return true;
}

static int input_reader_get(InputReader *reader)
{
    int character;

    if (reader == NULL || reader->stream == NULL) {
        if (reader != NULL) {
            reader->error = true;
        }
        return EOF;
    }

    if (reader->error || reader->end_of_file) {
        return EOF;
    }

    character = fgetc(reader->stream);

    if (character == EOF) {
        if (ferror(reader->stream)) {
            reader->error = true;
        } else {
            reader->end_of_file = true;
        }
    }

    return character;
}

static bool read_uintmax_bounded(InputReader *reader, uintmax_t limit,
                                 uintmax_t *result)
{
    int character;
    uintmax_t value = 0;
    bool overflow = false;

    if (reader == NULL || result == NULL) {
        return false;
    }

    do {
        character = input_reader_get(reader);
    } while (character != EOF && isspace((unsigned char)character));

    if (character == '+') {
        character = input_reader_get(reader);
    }

    if (character == EOF || !isdigit((unsigned char)character)) {
        return false;
    }

    do {
        uintmax_t digit = (uintmax_t)(character - '0');

        if (!overflow) {
            if (digit > limit ||
                value > (limit - digit) / UINTMAX_C(10)) {
                overflow = true;
            } else {
                value = value * UINTMAX_C(10) + digit;
            }
        }

        character = input_reader_get(reader);
    } while (character != EOF && isdigit((unsigned char)character));

    if (character != EOF && !isspace((unsigned char)character)) {
        return false;
    }

    if (reader->error || overflow) {
        return false;
    }

    *result = value;
    return true;
}

static bool input_finished(InputReader *reader)
{
    int character;

    if (reader == NULL) {
        return false;
    }

    while ((character = input_reader_get(reader)) != EOF) {
        if (!isspace((unsigned char)character)) {
            return false;
        }
    }

    return !reader->error;
}

static void heap_sift_down(HeapNode *heap, size_t size, size_t index)
{
    if (heap == NULL || size < 2 || index >= size) {
        return;
    }

    while (index <= (size - 2) / 2) {
        size_t left = index * 2 + 1;
        size_t right = left + 1;
        size_t smallest = left;
        HeapNode temporary;

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
    if (heap == NULL) {
        return;
    }

    for (size_t index = size / 2; index > 0; --index) {
        heap_sift_down(heap, size, index - 1);
    }
}

static bool nth_super_ugly_number(size_t n, const uint64_t *primes,
                                  size_t prime_count, uint64_t *result)
{
    uint64_t *numbers = NULL;
    HeapNode *heap = NULL;
    size_t heap_size;
    bool success = false;

    if (n == 0 || prime_count == 0 || primes == NULL || result == NULL) {
        return false;
    }

    for (size_t index = 0; index < prime_count; ++index) {
        if (primes[index] < UINT64_C(2)) {
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

    for (size_t index = 0; index < prime_count; ++index) {
        heap[index].value = primes[index];
        heap[index].prime = primes[index];
        heap[index].index = 0;
    }

    heap_build(heap, heap_size);

    for (size_t index = 1; index < n; ++index) {
        uint64_t next;

        if (heap_size == 0) {
            goto cleanup;
        }

        next = heap[0].value;
        numbers[index] = next;

        if (index == n - 1) {
            break;
        }

        while (heap_size > 0 && heap[0].value == next) {
            HeapNode node = heap[0];

            if (node.index == SIZE_MAX) {
                goto cleanup;
            }

            ++node.index;

            if (node.index > index ||
                numbers[node.index] > UINT64_MAX / node.prime) {
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
    uintmax_t parsed_n;
    uintmax_t parsed_prime_count;
    size_t n;
    size_t prime_count;
    uint64_t *primes = NULL;
    uint64_t result;
    int exit_status = EXIT_FAILURE;

    if (!input_reader_init(&reader, stdin)) {
        fputs("Input initialization failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (!read_uintmax_bounded(&reader, (uintmax_t)SIZE_MAX, &parsed_n) ||
        !read_uintmax_bounded(&reader, (uintmax_t)SIZE_MAX,
                              &parsed_prime_count) ||
        parsed_n == 0 || parsed_prime_count == 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    n = (size_t)parsed_n;
    prime_count = (size_t)parsed_prime_count;

    if (prime_count > SIZE_MAX / sizeof(*primes)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    primes = malloc(prime_count * sizeof(*primes));
    if (primes == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t index = 0; index < prime_count; ++index) {
        uintmax_t prime;

        if (!read_uintmax_bounded(&reader, (uintmax_t)UINT64_MAX, &prime) ||
            prime < UINTMAX_C(2)) {
            fputs("Invalid prime list\n", stderr);
            goto cleanup;
        }

        primes[index] = (uint64_t)prime;
    }

    if (!input_finished(&reader)) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    if (!nth_super_ugly_number(n, primes, prime_count, &result)) {
        fputs("Unable to compute the requested value\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        fputs("Output error\n", stderr);
        goto cleanup;
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    free(primes);
    return exit_status;
}