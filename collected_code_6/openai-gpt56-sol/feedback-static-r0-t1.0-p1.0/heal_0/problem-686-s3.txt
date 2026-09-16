#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *a, const void *b)
{
    const int left = *(const int *)a;
    const int right = *(const int *)b;

    return (left > right) - (left < right);
}

static void print_frequencies(int *values, size_t count)
{
    if (values == NULL || count == 0U) {
        return;
    }

    qsort(values, count, sizeof(*values), compare_ints);

    size_t frequency = 1U;

    for (size_t i = 1U; i <= count; ++i) {
        if (i < count && values[i] == values[i - 1U]) {
            ++frequency;
        } else {
            printf("%d: %zu\n", values[i - 1U], frequency);
            frequency = 1U;
        }
    }
}

int main(void)
{
    size_t count = 0U;

    if (scanf("%zu", &count) != 1 || count == 0U ||
        count > SIZE_MAX / sizeof(int)) {
        fputs("Invalid element count.\n", stderr);
        return EXIT_FAILURE;
    }

    int *values = malloc(count * sizeof(*values));

    if (values == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (scanf("%d", &values[i]) != 1) {
            fputs("Invalid element.\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    print_frequencies(values, count);
    free(values);

    return EXIT_SUCCESS;
}