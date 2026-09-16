#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool inversion_counts_are_equal(const int *values, size_t count)
{
    size_t regular_inversions = 0;
    size_t reverse_inversions = 0;

    for (size_t i = 0; i < count; ++i) {
        for (size_t j = i + 1; j < count; ++j) {
            if (values[i] > values[j]) {
                ++regular_inversions;
            } else if (values[i] < values[j]) {
                ++reverse_inversions;
            }
        }
    }

    return regular_inversions == reverse_inversions;
}

int main(void)
{
    size_t count;

    if (scanf("%zu", &count) != 1) {
        fprintf(stderr, "Failed to read the element count.\n");
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(int)) {
        fprintf(stderr, "Element count is too large.\n");
        return EXIT_FAILURE;
    }

    int *values = NULL;

    if (count > 0) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%d", &values[i]) != 1) {
            fprintf(stderr, "Failed to read element %zu.\n", i);
            free(values);
            return EXIT_FAILURE;
        }
    }

    puts(inversion_counts_are_equal(values, count) ? "Same" : "Not same");

    free(values);
    return EXIT_SUCCESS;
}