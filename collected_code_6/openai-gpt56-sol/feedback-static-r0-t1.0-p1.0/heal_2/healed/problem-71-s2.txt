#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void comb_sort(int *array, size_t length)
{
    size_t gap = length;
    int swapped = 1;

    while (gap > 1U || swapped != 0) {
        size_t i;

        gap = (gap * 10U) / 13U;
        if (gap < 1U) {
            gap = 1U;
        }

        swapped = 0;

        for (i = 0U; gap < length && i < length - gap; ++i) {
            if (array[i] > array[i + gap]) {
                const int temporary = array[i];

                array[i] = array[i + gap];
                array[i + gap] = temporary;
                swapped = 1;
            }
        }
    }
}

int main(int argc, const char *const argv[])
{
    int *values;
    size_t count;
    size_t i;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s integer [integer ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    count = (size_t)(argc - 1);

    if (count > SIZE_MAX / sizeof(*values)) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; ++i) {
        char *end;
        long parsed;

        errno = 0;
        parsed = strtol(argv[i + 1U], &end, 10);

        if (errno == ERANGE ||
            end == argv[i + 1U] ||
            *end != '\0' ||
            parsed < INT_MIN ||
            parsed > INT_MAX) {
            fprintf(stderr, "Invalid integer: %s\n", argv[i + 1U]);
            free(values);
            return EXIT_FAILURE;
        }

        values[i] = (int)parsed;
    }

    comb_sort(values, count);

    for (i = 0U; i < count; ++i) {
        if (printf("%s%d", i == 0U ? "" : " ", values[i]) < 0) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}