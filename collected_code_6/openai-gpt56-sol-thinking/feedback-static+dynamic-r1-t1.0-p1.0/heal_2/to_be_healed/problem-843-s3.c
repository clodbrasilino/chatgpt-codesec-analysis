#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    uint64_t value;
    uint64_t prime;
    size_t index;
} HeapNode;

static bool read_uint64(FILE *stream, uint64_t *result)
{
    uint64_t value = 0;
    bool overflow = false;
    int character;

    if (stream == NULL || result == NULL) {
        return false;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stream);
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

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stream);
    } while (character >= '0' && character <= '9');

    if (character == EOF) {
        if (ferror(stream)) {
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

static void swap_nodes(HeapNode *left, HeapNode *right)
{
    HeapNode temporary = *left;
    *left = *right;
    *right = temporary;
}

static void sift_down(HeapNode *heap, size_t heap_size, size_t index)
{
    for (;;) {
        size_t smallest;
        size_t left;
        size_t right;

        if (heap_size < 2 || index > (heap_size - 2) / 2) {
            break;
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
            break;
        }

        swap_nodes(&heap[index], &heap[smallest]);
        index = smallest;
    }
}

static void sift_up(HeapNode *heap, size_t index)
{
    while (index > 0) {
        size_t parent = (index - 1) / 2;

        if (heap[parent].value <= heap[index].value) {
            break;
        }

        swap_nodes(&heap[parent], &heap[index]);
        index = parent;
    }
}

static void build_heap(HeapNode *heap, size_t heap_size)
{
    size_t index;

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
    heap = malloc(prime_count * sizeof(*heap));

    if (ugly == NULL || heap == NULL) {
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
    uint64_t n_input;
    uint64_t prime_count_input;
    uint64_t *primes = NULL;
    uint64_t result;
    size_t n;
    size_t prime_count;
    size_t index;

    if (!read_uint64(stdin, &n_input) ||
        !read_uint64(stdin, &prime_count_input)) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n_input == 0 || prime_count_input == 0 ||
        n_input > SIZE_MAX || prime_count_input > SIZE_MAX) {
        fprintf(stderr, "Input values are out of range\n");
        return EXIT_FAILURE;
    }

    n = (size_t)n_input;
    prime_count = (size_t)prime_count_input;

    if (prime_count > SIZE_MAX / sizeof(*primes)) {
        fprintf(stderr, "Prime list is too large\n");
        return EXIT_FAILURE;
    }

    primes = malloc(prime_count * sizeof(*primes));

    if (primes == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (index = 0; index < prime_count; ++index) {
        if (!read_uint64(stdin, &primes[index])) {
            fprintf(stderr, "Invalid prime list\n");
            free(primes);
            return EXIT_FAILURE;
        }
    }

    if (!nth_super_ugly_number(n, primes, prime_count, &result)) {
        fprintf(stderr, "Unable to compute the requested value\n");
        free(primes);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);

    free(primes);
    return EXIT_SUCCESS;
}