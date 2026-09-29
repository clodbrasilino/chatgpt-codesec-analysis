#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static void swap_int(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void min_heapify(int heap[], size_t size, size_t index)
{
    for (;;) {
        size_t smallest = index;
        size_t left;
        size_t right;

        if (index > (SIZE_MAX - 2U) / 2U) {
            return;
        }

        left = 2U * index + 1U;
        right = left + 1U;

        if (left < size && heap[left] < heap[smallest]) {
            smallest = left;
        }

        if (right < size && heap[right] < heap[smallest]) {
            smallest = right;
        }

        if (smallest == index) {
            return;
        }

        swap_int(&heap[index], &heap[smallest]);
        index = smallest;
    }
}

static void build_min_heap(int heap[], size_t size)
{
    size_t index = size / 2U;

    while (index > 0U) {
        --index;
        min_heapify(heap, size, index);
    }
}

static int compare_descending(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a < b) - (a > b);
}

static int find_largest(const int values[], size_t count, size_t k, int **result)
{
    int *heap;
    size_t i;

    if (values == NULL || result == NULL || k == 0U || k > count ||
        k > SIZE_MAX / sizeof(*heap)) {
        return -1;
    }

    *result = NULL;
    heap = malloc(k * sizeof(*heap));
    if (heap == NULL) {
        return -1;
    }

    for (i = 0U; i < k; ++i) {
        heap[i] = values[i];
    }

    build_min_heap(heap, k);

    for (i = k; i < count; ++i) {
        if (values[i] > heap[0]) {
            heap[0] = values[i];
            min_heapify(heap, k, 0U);
        }
    }

    qsort(heap, k, sizeof(*heap), compare_descending);
    *result = heap;
    return 0;
}

static int read_size(const char *prompt, size_t *value)
{
    unsigned long long input;

    if (prompt == NULL || value == NULL) {
        return -1;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return -1;
    }

    errno = 0;
    if (scanf("%llu", &input) != 1 || errno == ERANGE ||
        input > (unsigned long long)SIZE_MAX) {
        return -1;
    }

    *value = (size_t)input;
    return 0;
}

int main(void)
{
    int *values = NULL;
    int *largest = NULL;
    size_t count;
    size_t k;
    size_t i;
    int status = EXIT_FAILURE;

    if (read_size("Number of integers: ", &count) != 0 ||
        count == 0U || count > SIZE_MAX / sizeof(*values)) {
        fputs("Invalid number of integers.\n", stderr);
        goto cleanup;
    }

    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        goto cleanup;
    }

    if (fputs("Enter the integers: ", stdout) == EOF || fflush(stdout) == EOF) {
        fputs("Output error.\n", stderr);
        goto cleanup;
    }

    for (i = 0U; i < count; ++i) {
        if (scanf("%d", &values[i]) != 1) {
            fputs("Invalid integer input.\n", stderr);
            goto cleanup;
        }
    }

    if (read_size("How many largest integers: ", &k) != 0 ||
        k == 0U || k > count) {
        fputs("Invalid requested count.\n", stderr);
        goto cleanup;
    }

    if (find_largest(values, count, k, &largest) != 0) {
        fputs("Unable to find the largest integers.\n", stderr);
        goto cleanup;
    }

    if (fputs("Largest integers:", stdout) == EOF) {
        fputs("Output error.\n", stderr);
        goto cleanup;
    }

    for (i = 0U; i < k; ++i) {
        if (printf(" %d", largest[i]) < 0) {
            fputs("Output error.\n", stderr);
            goto cleanup;
        }
    }

    if (putchar('\n') == EOF) {
        fputs("Output error.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(largest);
    free(values);
    return status;
}