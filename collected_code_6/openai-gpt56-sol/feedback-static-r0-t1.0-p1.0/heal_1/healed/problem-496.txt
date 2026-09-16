#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void swap_ints(int *a, int *b)
{
    int temporary = *a;
    *a = *b;
    *b = temporary;
}

static void sift_down(int heap[], size_t size, size_t root)
{
    for (;;) {
        size_t largest = root;
        size_t left = root <= (SIZE_MAX - 1U) / 2U
                          ? root * 2U + 1U
                          : size;
        size_t right = left < size && left < SIZE_MAX
                           ? left + 1U
                           : size;

        if (left < size && heap[left] > heap[largest]) {
            largest = left;
        }

        if (right < size && heap[right] > heap[largest]) {
            largest = right;
        }

        if (largest == root) {
            return;
        }

        swap_ints(&heap[root], &heap[largest]);
        root = largest;
    }
}

static void build_max_heap(int heap[], size_t size)
{
    for (size_t i = size / 2U; i > 0U; --i) {
        sift_down(heap, size, i - 1U);
    }
}

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static int find_smallest(const int numbers[], size_t count, size_t amount,
                         int result[])
{
    if (numbers == NULL || result == NULL || amount == 0U || amount > count) {
        return -1;
    }

    for (size_t i = 0U; i < amount; ++i) {
        result[i] = numbers[i];
    }

    build_max_heap(result, amount);

    for (size_t i = amount; i < count; ++i) {
        if (numbers[i] < result[0]) {
            result[0] = numbers[i];
            sift_down(result, amount, 0U);
        }
    }

    qsort(result, amount, sizeof(*result), compare_ints);
    return 0;
}

static int parse_size(const char *text, size_t *value)
{
    char *end = NULL;
    unsigned long long parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return -1;
    }

    errno = 0;
    parsed = strtoull(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed == 0ULL || parsed > SIZE_MAX) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int parse_int(const char *text, int *value)
{
    char *end = NULL;
    long parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return -1;
    }

    errno = 0;
    parsed = strtol(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT_MIN || parsed > INT_MAX) {
        return -1;
    }

    *value = (int)parsed;
    return 0;
}

int main(int argc, char *const argv[])
{
    size_t amount;
    size_t count;
    int *numbers = NULL;
    int *result = NULL;
    int status = EXIT_FAILURE;

    if (argc < 3 || parse_size(argv[1], &amount) != 0) {
        fprintf(stderr, "Usage: %s <amount> <integer> [integer ...]\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    count = (size_t)argc - 2U;

    if (amount > count ||
        count > SIZE_MAX / sizeof(*numbers) ||
        amount > SIZE_MAX / sizeof(*result)) {
        fprintf(stderr, "Invalid amount or input size.\n");
        return EXIT_FAILURE;
    }

    numbers = malloc(count * sizeof(*numbers));
    result = malloc(amount * sizeof(*result));

    if (numbers == NULL || result == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        goto cleanup;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (parse_int(argv[i + 2U], &numbers[i]) != 0) {
            fprintf(stderr, "Invalid integer: %s\n", argv[i + 2U]);
            goto cleanup;
        }
    }

    if (find_smallest(numbers, count, amount, result) != 0) {
        fprintf(stderr, "Unable to find the smallest integers.\n");
        goto cleanup;
    }

    for (size_t i = 0U; i < amount; ++i) {
        printf("%d%c", result[i], i + 1U == amount ? '\n' : ' ');
    }

    status = EXIT_SUCCESS;

cleanup:
    free(result);
    free(numbers);
    return status;
}