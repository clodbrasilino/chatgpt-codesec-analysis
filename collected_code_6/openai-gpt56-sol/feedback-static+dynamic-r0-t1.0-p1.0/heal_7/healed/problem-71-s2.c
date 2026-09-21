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
        gap = (gap * 10U) / 13U;

        if (gap < 1U) {
            gap = 1U;
        }

        swapped = 0;

        for (size_t i = 0U; i < length - gap; ++i) {
            if (array[i] > array[i + gap]) {
                const int temporary = array[i];
                array[i] = array[i + gap];
                array[i + gap] = temporary;
                swapped = 1;
            }
        }
    }
}

int main(int argc, char *const argv[])
{
    const char *const *const arguments = (const char *const *)argv;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s integer [integer ...]\n", arguments[0]);
        return EXIT_FAILURE;
    }

    const size_t count = (size_t)argc - 1U;

    if (count > SIZE_MAX / sizeof(int)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    int *values = malloc(count * sizeof(*values));

    if (values == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        const char *const argument = arguments[i + 1U];
        char *end = NULL;

        errno = 0;
        const long parsed = strtol(argument, &end, 10);

        if (errno == ERANGE || end == argument || *end != '\0' ||
            parsed < INT_MIN || parsed > INT_MAX) {
            fprintf(stderr, "Invalid integer: %s\n", argument);
            free(values);
            return EXIT_FAILURE;
        }

        values[i] = (int)parsed;
    }

    comb_sort(values, count);

    for (size_t i = 0U; i < count; ++i) {
        if (i != 0U && fputc(' ', stdout) == EOF) {
            free(values);
            return EXIT_FAILURE;
        }

        if (printf("%d", values[i]) < 0) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (fputc('\n', stdout) == EOF) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}