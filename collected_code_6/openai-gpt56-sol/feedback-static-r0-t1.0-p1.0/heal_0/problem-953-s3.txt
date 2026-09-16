#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static size_t minimum_distinct_subsets(int *values, size_t count)
{
    size_t maximum_frequency = 0;
    size_t current_frequency = 0;
    size_t i;

    if (values == NULL || count == 0) {
        return 0;
    }

    qsort(values, count, sizeof(*values), compare_ints);

    for (i = 0; i < count; ++i) {
        if (i > 0 && values[i] == values[i - 1]) {
            ++current_frequency;
        } else {
            current_frequency = 1;
        }

        if (current_frequency > maximum_frequency) {
            maximum_frequency = current_frequency;
        }
    }

    return maximum_frequency;
}

int main(void)
{
    size_t count;
    size_t i;
    int *values;
    size_t result;

    if (scanf("%zu", &count) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (count == 0) {
        puts("0");
        return EXIT_SUCCESS;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        fputs("Input size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        if (scanf("%d", &values[i]) != 1) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    result = minimum_distinct_subsets(values, count);
    printf("%zu\n", result);

    free(values);
    return EXIT_SUCCESS;
}