#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

typedef struct {
    uint64_t value;
    uint64_t prime;
    size_t index;
} HeapNode;

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
    for (size_t i = size / 2; i > 0; --i) {
        heap_sift_down(heap, size, i - 1);
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

    for (size_t i = 0; i < k; ++i) {
        if (primes[i] < 2) {
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

    for (size_t i = 0; i < k; ++i) {
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

            if (node.index == SIZE_MAX) {
                goto cleanup;
            }

            ++node.index;

            if (node.index > i ||
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
    uintmax_t n_input;
    uintmax_t k_input;
    uint64_t *primes = NULL;
    uint64_t result;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNuMAX " %" SCNuMAX, &n_input, &k_input) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (n_input == 0 || k_input == 0 ||
        n_input > SIZE_MAX || k_input > SIZE_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    size_t n = (size_t)n_input;
    size_t k = (size_t)k_input;

    if (k > SIZE_MAX / sizeof(*primes)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    primes = malloc(k * sizeof(*primes));
    if (primes == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < k; ++i) {
        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (scanf("%" SCNu64, &primes[i]) != 1) {
            fputs("Invalid prime list\n", stderr);
            free(primes);
            return EXIT_FAILURE;
        }
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