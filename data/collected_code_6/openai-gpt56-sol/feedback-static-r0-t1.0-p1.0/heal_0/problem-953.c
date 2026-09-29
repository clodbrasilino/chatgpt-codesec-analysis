#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static int minimum_distinct_subsets(const int *values, size_t count, size_t *result)
{
    int *copy;
    size_t current_frequency = 1;
    size_t maximum_frequency = 1;
    size_t i;

    if (result == NULL || (values == NULL && count != 0)) {
        return -1;
    }

    if (count == 0) {
        *result = 0;
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*copy)) {
        return -1;
    }

    copy = malloc(count * sizeof(*copy));
    if (copy == NULL) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        copy[i] = values[i];
    }

    qsort(copy, count, sizeof(*copy), compare_ints);

    for (i = 1; i < count; ++i) {
        if (copy[i] == copy[i - 1]) {
            ++current_frequency;
            if (current_frequency > maximum_frequency) {
                maximum_frequency = current_frequency;
            }
        } else {
            current_frequency = 1;
        }
    }

    free(copy);
    *result = maximum_frequency;
    return 0;
}

int main(void)
{
    size_t count;
    size_t result;
    int *values = NULL;
    size_t i;

    if (scanf("%zu", &count) != 1) {
        fprintf(stderr, "Failed to read the element count.\n");
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        fprintf(stderr, "Input is too large.\n");
        return EXIT_FAILURE;
    }

    if (count != 0) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < count; ++i) {
        if (scanf("%d", &values[i]) != 1) {
            fprintf(stderr, "Failed to read an element.\n");
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (minimum_distinct_subsets(values, count, &result) != 0) {
        fprintf(stderr, "Failed to compute the result.\n");
        free(values);
        return EXIT_FAILURE;
    }

    printf("%zu\n", result);
    free(values);
    return EXIT_SUCCESS;
}