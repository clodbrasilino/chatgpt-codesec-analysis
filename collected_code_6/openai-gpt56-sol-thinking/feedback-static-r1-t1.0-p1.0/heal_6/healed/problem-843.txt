#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <ctype.h>
#include <stddef.h>

typedef struct {
    uint64_t value;
    uint64_t prime;
    size_t index;
} HeapNode;

typedef struct {
    FILE *stream;
    unsigned char buffer[4096];
    size_t position;
    size_t length;
    bool error;
} InputReader;

static int input_reader_get(InputReader *reader)
{
    if (reader == NULL || reader->stream == NULL || reader->error) {
        return EOF;
    }

    if (reader->position >= reader->length) {
        reader->length = fread(reader->buffer, 1,
                               sizeof(reader->buffer), reader->stream);
        reader->position = 0;

        if (reader->length == 0) {
            if (ferror(reader->stream)) {
                reader->error = true;
            }
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
    } while (isspace((unsigned char)character));

    while (character != EOF && !isspace((unsigned char)character)) {
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

    if (reader->error || !valid || !has_digit) {
        return false;
    }

    *result = value;
    return true;
}

static void heap_sift_down(HeapNode *heap, size_t size, size_t index)
{
    if (heap == NULL || size < 2 || index >= size) {
        return;
    }

    while (index < size / 2) {
        size_t left = index * 2 + 1;
        size_t right = left + 1;
        size_t smallest = left;

        if (right < size && heap[right].value < heap[left].value) {
            smallest = right;
        }

        if (heap[index].value <= heap[smallest].value) {
            break;
        }

        HeapNode temporary = heap[index];
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

    for (size_t i = size / 2; i > 0; --i) {
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

    if (n == 0 || prime_count == 0 || primes == NULL || result == NULL) {
        return false;
    }

    for (size_t i = 0; i < prime_count; ++i) {
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

    for (size_t i = 0; i < prime_count; ++i) {
        heap[i].value = primes[i];
        heap[i].prime = primes[i];
        heap[i].index = 0;
    }

    heap_build(heap, heap_size);

    for (size_t i = 1; i < n; ++i) {
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
    InputReader reader = {
        .stream = stdin,
        .position = 0,
        .length = 0,
        .error = false
    };
    uintmax_t n_input;
    uintmax_t prime_count_input;
    uint64_t *primes = NULL;
    uint64_t result;

    if (!read_uintmax_value(&reader, (uintmax_t)SIZE_MAX, &n_input) ||
        !read_uintmax_value(&reader, (uintmax_t)SIZE_MAX,
                            &prime_count_input) ||
        n_input == 0 || prime_count_input == 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    size_t n = (size_t)n_input;
    size_t prime_count = (size_t)prime_count_input;

    if (prime_count > SIZE_MAX / sizeof(*primes)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    primes = malloc(prime_count * sizeof(*primes));
    if (primes == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < prime_count; ++i) {
        uintmax_t prime_input;

        if (!read_uintmax_value(&reader, (uintmax_t)UINT64_MAX,
                                &prime_input) ||
            prime_input < UINT64_C(2)) {
            fputs("Invalid prime list\n", stderr);
            free(primes);
            return EXIT_FAILURE;
        }

        primes[i] = (uint64_t)prime_input;
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