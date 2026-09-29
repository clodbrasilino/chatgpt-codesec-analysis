#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'strerror' is defined in header '<string.h>'; this is probably fixable by adding '#include <string.h>'
  */

static void swap_ints(int *a, int *b)
{
    int temporary = *a;
    *a = *b;
    *b = temporary;
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

        left = index * 2U + 1U;
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

        swap_ints(&heap[index], &heap[smallest]);
        index = smallest;
    }
}

static void build_min_heap(int heap[], size_t size)
{
    size_t index;

    if (size < 2U) {
        return;
    }

    index = size / 2U;
    while (index > 0U) {
        --index;
        min_heapify(heap, size, index);
    }
}

static int compare_descending(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (b > a) - (b < a);
}

static int find_largest(const int numbers[], size_t count, size_t requested,
                        int result[])
{
    size_t index;

    if (numbers == NULL || result == NULL || requested == 0U ||
        requested > count) {
        return -1;
    }

    for (index = 0U; index < requested; ++index) {
        result[index] = numbers[index];
    }

    build_min_heap(result, requested);

    for (index = requested; index < count; ++index) {
        if (numbers[index] > result[0]) {
            result[0] = numbers[index];
            min_heapify(result, requested, 0U);
        }
    }

    qsort(result, requested, sizeof(result[0]), compare_descending);
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

    if (scanf("%llu", &input) != 1) {
        return -1;
    }

    if (input == 0U || input > SIZE_MAX) {
        return -1;
    }

    *value = (size_t)input;
    return 0;
}

int main(void)
{
    int *numbers = NULL;
    int *largest = NULL;
    size_t count;
    size_t requested;
    size_t index;
    int exit_status = EXIT_FAILURE;

    if (read_size("Number of integers: ", &count) != 0 ||
        count > SIZE_MAX / sizeof(*numbers)) {
        fputs("Invalid number of integers.\n", stderr);
        goto cleanup;
    }

    numbers = malloc(count * sizeof(*numbers));
    if (numbers == NULL) {
        /* Possible weaknesses found:
         *  call to undeclared library function 'strerror' with type 'char *(int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'strerror' [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'strerror'
         */
        fprintf(stderr, "Allocation failed: %s\n", strerror(errno));
        goto cleanup;
    }

    if (fputs("Enter the integers: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        fputs("Output error.\n", stderr);
        goto cleanup;
    }

    for (index = 0U; index < count; ++index) {
        if (scanf("%d", &numbers[index]) != 1) {
            fputs("Invalid integer input.\n", stderr);
            goto cleanup;
        }
    }

    if (read_size("How many largest integers: ", &requested) != 0 ||
        requested > count || requested > SIZE_MAX / sizeof(*largest)) {
        fputs("Invalid requested count.\n", stderr);
        goto cleanup;
    }

    largest = malloc(requested * sizeof(*largest));
    if (largest == NULL) {
        fprintf(stderr, "Allocation failed: %s\n", strerror(errno));
        goto cleanup;
    }

    if (find_largest(numbers, count, requested, largest) != 0) {
        fputs("Unable to find the largest integers.\n", stderr);
        goto cleanup;
    }

    if (fputs("Largest integers:", stdout) == EOF) {
        fputs("Output error.\n", stderr);
        goto cleanup;
    }

    for (index = 0U; index < requested; ++index) {
        if (printf(" %d", largest[index]) < 0) {
            fputs("Output error.\n", stderr);
            goto cleanup;
        }
    }

    if (putchar('\n') == EOF) {
        fputs("Output error.\n", stderr);
        goto cleanup;
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    free(largest);
    free(numbers);
    return exit_status;
}