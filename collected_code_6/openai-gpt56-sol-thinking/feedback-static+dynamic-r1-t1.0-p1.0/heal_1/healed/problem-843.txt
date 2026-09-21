#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <ctype.h>

typedef struct {
    uint64_t value;
    uint64_t prime;
    size_t index;
} HeapNode;

static bool read_uintmax_bounded(FILE *stream, uintmax_t limit,
                                 uintmax_t *result)
{
    int character;
    uintmax_t value = 0;
    bool overflow = false;

    do {
        character = fgetc(stream);
    } while (character != EOF && isspace((unsigned char)character));

    if (character == '+') {
        character = fgetc(stream);
    }

    if (character == EOF || !isdigit((unsigned char)character)) {
        return false;
    }

    do {
        uintmax_t digit = (uintmax_t)(character - '0');

        if (digit > limit || value > (limit - digit) / 10) {
            overflow = true;
        } else if (!overflow) {
            value = value * 10 + digit;
        }

        character = fgetc(stream);
    } while (character != EOF && isdigit((unsigned char)character));

    if (character != EOF && !isspace((unsigned char)character)) {
        return false;
    }

    if (ferror(stream) || overflow) {
        return false;
    }

    *result = value;
    return true;
}

static bool input_finished(FILE *stream)
{
    int character;

    while ((character = fgetc(stream)) != EOF) {
        if (!isspace((unsigned char)character)) {
            return false;
        }
    }

    return !ferror(stream);
}

static void heap_sift_down(HeapNode *heap, size_t size, size_t index)
{
    if (size < 2) {
        return;
    }

    while (index <= (size - 2) / 2) {
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
    for (size_t index = size / 2; index > 0; --index) {
        heap_sift_down(heap, size, index - 1);
    }
}

bool nth_super_ugly_number(size_t n, const uint64_t *primes,
                           size_t k, uint64_t *result)
{
    uint64_t *numbers = NULL;
    HeapNode *heap = NULL;
    size_t heap_size;
    bool success = false;

    if (n == 0 || k == 0 || primes == NULL || result == NULL) {
        return false;
    }

    for (size_t index = 0; index < k; ++index) {
        if (primes[index] < 2) {
            return false;
        }
    }

    if (n == 1) {
        *result = 1;
        return true;
    }

    if (n > SIZE_MAX / sizeof(*numbers) ||
        k > SIZE_MAX / sizeof(*heap)) {
        return false;
    }

    numbers = malloc(n * sizeof(*numbers));
    if (numbers == NULL) {
        return false;
    }

    heap = malloc(k * sizeof(*heap));
    if (heap == NULL) {
        free(numbers);
        return false;
    }

    numbers[0] = 1;
    heap_size = k;

    for (size_t index = 0; index < k; ++index) {
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
    uintmax_t parsed_n;
    uintmax_t parsed_k;
    size_t n;
    size_t k;
    uint64_t *primes = NULL;
    uint64_t result;

    if (!read_uintmax_bounded(stdin, (uintmax_t)SIZE_MAX, &parsed_n) ||
        !read_uintmax_bounded(stdin, (uintmax_t)SIZE_MAX, &parsed_k) ||
        parsed_n == 0 || parsed_k == 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    n = (size_t)parsed_n;
    k = (size_t)parsed_k;

    if (k > SIZE_MAX / sizeof(*primes)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    primes = malloc(k * sizeof(*primes));
    if (primes == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t index = 0; index < k; ++index) {
        uintmax_t prime;

        if (!read_uintmax_bounded(stdin, (uintmax_t)UINT64_MAX, &prime) ||
            prime < 2) {
            fputs("Invalid prime list\n", stderr);
            free(primes);
            return EXIT_FAILURE;
        }

        primes[index] = (uint64_t)prime;
    }

    if (!input_finished(stdin)) {
        fputs("Invalid input\n", stderr);
        free(primes);
        return EXIT_FAILURE;
    }

    if (!nth_super_ugly_number(n, primes, k, &result)) {
        fputs("Unable to compute the requested value\n", stderr);
        free(primes);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    free(primes);
    return EXIT_SUCCESS;
}