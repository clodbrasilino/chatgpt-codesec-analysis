#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    uint64_t value;
    uint64_t prime;
    size_t index;
} HeapNode;

typedef enum {
    UGLY_SUCCESS,
    UGLY_INVALID_ARGUMENT,
    UGLY_ALLOCATION_FAILURE,
    UGLY_OUT_OF_RANGE
} UglyStatus;

static bool heap_push(HeapNode *heap, size_t *size, size_t capacity, HeapNode node)
{
    size_t index;

    if (heap == NULL || size == NULL || *size >= capacity) {
        return false;
    }

    index = (*size)++;
    while (index > 0) {
        size_t parent = (index - 1) / 2;

        if (heap[parent].value <= node.value) {
            break;
        }

        heap[index] = heap[parent];
        index = parent;
    }

    heap[index] = node;
    return true;
}

static bool heap_pop(HeapNode *heap, size_t *size, HeapNode *result)
{
    HeapNode last;
    size_t index;

    if (heap == NULL || size == NULL || result == NULL || *size == 0) {
        return false;
    }

    *result = heap[0];
    --(*size);

    if (*size == 0) {
        return true;
    }

    last = heap[*size];
    index = 0;

    for (;;) {
        size_t left = index * 2 + 1;
        size_t right = left + 1;
        size_t smallest;

        if (left >= *size) {
            break;
        }

        smallest = left;
        if (right < *size && heap[right].value < heap[left].value) {
            smallest = right;
        }

        if (last.value <= heap[smallest].value) {
            break;
        }

        heap[index] = heap[smallest];
        index = smallest;
    }

    heap[index] = last;
    return true;
}

UglyStatus nth_super_ugly_number(size_t n, const uint64_t *primes,
                                  size_t k, uint64_t *result)
{
    uint64_t *ugly;
    HeapNode *heap;
    size_t heap_size = 0;
    size_t count = 1;
    size_t i;
    UglyStatus status = UGLY_SUCCESS;

    if (n == 0 || primes == NULL || k == 0 || result == NULL) {
        return UGLY_INVALID_ARGUMENT;
    }

    for (i = 0; i < k; ++i) {
        if (primes[i] < 2) {
            return UGLY_INVALID_ARGUMENT;
        }
    }

    if (n == 1) {
        *result = 1;
        return UGLY_SUCCESS;
    }

    if (n > SIZE_MAX / sizeof(*ugly) ||
        k > SIZE_MAX / sizeof(*heap)) {
        return UGLY_ALLOCATION_FAILURE;
    }

    ugly = malloc(n * sizeof(*ugly));
    heap = malloc(k * sizeof(*heap));

    if (ugly == NULL || heap == NULL) {
        free(ugly);
        free(heap);
        return UGLY_ALLOCATION_FAILURE;
    }

    ugly[0] = 1;

    for (i = 0; i < k; ++i) {
        HeapNode node = {primes[i], primes[i], 0};

        if (!heap_push(heap, &heap_size, k, node)) {
            status = UGLY_INVALID_ARGUMENT;
            goto cleanup;
        }
    }

    while (count < n && heap_size > 0) {
        HeapNode node;

        if (!heap_pop(heap, &heap_size, &node)) {
            status = UGLY_INVALID_ARGUMENT;
            goto cleanup;
        }

        if (node.value != ugly[count - 1]) {
            ugly[count++] = node.value;
        }

        if (count == n) {
            break;
        }

        if (node.index == SIZE_MAX) {
            continue;
        }

        ++node.index;

        if (node.index >= count) {
            status = UGLY_INVALID_ARGUMENT;
            goto cleanup;
        }

        if (ugly[node.index] > UINT64_MAX / node.prime) {
            continue;
        }

        node.value = ugly[node.index] * node.prime;

        if (!heap_push(heap, &heap_size, k, node)) {
            status = UGLY_INVALID_ARGUMENT;
            goto cleanup;
        }
    }

    if (count < n) {
        status = UGLY_OUT_OF_RANGE;
        goto cleanup;
    }

    *result = ugly[n - 1];

cleanup:
    free(heap);
    free(ugly);
    return status;
}

static bool parse_uint64(const char *text, uint64_t *value)
{
    uint64_t parsed = 0;
    const unsigned char *current;

    if (text == NULL || value == NULL || *text == '\0') {
        return false;
    }

    current = (const unsigned char *)text;

    while (*current != '\0') {
        uint64_t digit;

        if (*current < '0' || *current > '9') {
            return false;
        }

        digit = (uint64_t)(*current - '0');

        if (parsed > (UINT64_MAX - digit) / 10) {
            return false;
        }

        parsed = parsed * 10 + digit;
        ++current;
    }

    *value = parsed;
    return true;
}

int main(int argc, char **argv)
{
    uint64_t parsed_n;
    uint64_t result;
    uint64_t *primes;
    size_t n;
    size_t k;
    size_t i;
    UglyStatus status;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s n prime1 [prime2 ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_uint64(argv[1], &parsed_n) ||
        parsed_n == 0 ||
        parsed_n > SIZE_MAX) {
        fprintf(stderr, "Invalid value for n\n");
        return EXIT_FAILURE;
    }

    n = (size_t)parsed_n;
    k = (size_t)(argc - 2);

    if (k > SIZE_MAX / sizeof(*primes)) {
        fprintf(stderr, "Prime list is too large\n");
        return EXIT_FAILURE;
    }

    primes = malloc(k * sizeof(*primes));
    if (primes == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < k; ++i) {
        if (!parse_uint64(argv[i + 2], &primes[i]) || primes[i] < 2) {
            fprintf(stderr, "Invalid prime value: %s\n", argv[i + 2]);
            free(primes);
            return EXIT_FAILURE;
        }
    }

    status = nth_super_ugly_number(n, primes, k, &result);
    free(primes);

    if (status == UGLY_ALLOCATION_FAILURE) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (status == UGLY_OUT_OF_RANGE) {
        fprintf(stderr, "The result exceeds the supported range\n");
        return EXIT_FAILURE;
    }

    if (status != UGLY_SUCCESS) {
        fprintf(stderr, "Unable to calculate the result\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}