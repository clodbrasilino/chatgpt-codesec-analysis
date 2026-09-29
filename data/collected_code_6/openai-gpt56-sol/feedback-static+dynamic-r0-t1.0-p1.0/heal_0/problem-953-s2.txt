#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *a, const void *b)
{
    const int x = *(const int *)a;
    const int y = *(const int *)b;

    return (x > y) - (x < y);
}

static size_t minimum_distinct_subsets(int *values, size_t count)
{
    size_t maximum_frequency = 0;
    size_t current_frequency = 0;

    if (values == NULL || count == 0) {
        return 0;
    }

    qsort(values, count, sizeof(*values), compare_ints);

    for (size_t i = 0; i < count; ++i) {
        if (i == 0 || values[i] == values[i - 1]) {
            ++current_frequency;
        } else {
            if (current_frequency > maximum_frequency) {
                maximum_frequency = current_frequency;
            }
            current_frequency = 1;
        }
    }

    if (current_frequency > maximum_frequency) {
        maximum_frequency = current_frequency;
    }

    return maximum_frequency;
}

int main(void)
{
    size_t count;

    if (scanf("%zu", &count) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (count == 0) {
        puts("0");
        return EXIT_SUCCESS;
    }

    if (count > SIZE_MAX / sizeof(int)) {
        fputs("Input size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    int *values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%d", &values[i]) != 1) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    printf("%zu\n", minimum_distinct_subsets(values, count));

    free(values);
    return EXIT_SUCCESS;
}