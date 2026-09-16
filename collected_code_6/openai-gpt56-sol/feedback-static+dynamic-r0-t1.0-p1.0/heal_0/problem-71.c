#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void comb_sort(int *values, size_t count)
{
    size_t gap = count;
    int swapped;

    if (values == NULL || count < 2U) {
        return;
    }

    do {
        gap = (gap / 13U) * 10U + ((gap % 13U) * 10U) / 13U;
        if (gap < 1U) {
            gap = 1U;
        }

        swapped = 0;

        for (size_t i = 0U; i < count - gap; ++i) {
            if (values[i] > values[i + gap]) {
                const int temporary = values[i];
                values[i] = values[i + gap];
                values[i + gap] = temporary;
                swapped = 1;
            }
        }
    } while (gap > 1U || swapped != 0);
}

int main(void)
{
    size_t count;

    if (scanf("%zu", &count) != 1) {
        fputs("Failed to read the element count.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(int)) {
        fputs("Element count is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    int *values = NULL;

    if (count > 0U) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0U; i < count; ++i) {
        if (scanf("%d", &values[i]) != 1) {
            fputs("Failed to read an element.\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    comb_sort(values, count);

    for (size_t i = 0U; i < count; ++i) {
        if (printf("%d%c", values[i], i + 1U == count ? '\n' : ' ') < 0) {
            fputs("Failed to write output.\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    free(values);
    return EXIT_SUCCESS;
}