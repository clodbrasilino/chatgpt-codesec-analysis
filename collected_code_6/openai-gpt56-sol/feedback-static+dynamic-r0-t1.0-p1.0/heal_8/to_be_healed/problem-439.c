#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int concatenate_integers(const int *values, size_t count,
                                uintmax_t *result)
{
    uintmax_t combined = 0;

    if (values == NULL || result == NULL || count == 0) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        uintmax_t value;
        uintmax_t multiplier = 10;

        if (values[i] < 0) {
            return -1;
        }

        value = (uintmax_t)values[i];

        for (uintmax_t remaining = value; remaining >= 10;
             remaining /= 10) {
            if (multiplier > UINTMAX_MAX / 10) {
                return -1;
            }

            multiplier *= 10;
        }

        if (combined > (UINTMAX_MAX - value) / multiplier) {
            return -1;
        }

        combined = combined * multiplier + value;
    }

    *result = combined;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    int *values;
    uintmax_t result;
    size_t count;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s integer [integer ...]\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    count = (size_t)(argc - 1);

    if (count > SIZE_MAX / sizeof(*values)) {
        fputs("Input count is too large\n", stderr);
        return EXIT_FAILURE;
    }

    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        const char *input = argv[i + 1];
        char *end = NULL;
        intmax_t parsed;

        if (input == NULL) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }

        errno = 0;
        parsed = strtoimax(input, &end, 10);

        if (errno == ERANGE || end == input || *end != '\0' ||
            parsed < 0 || parsed > INT_MAX) {
            fprintf(stderr, "Invalid nonnegative integer: %s\n", input);
            free(values);
            return EXIT_FAILURE;
        }

        values[i] = (int)parsed;
    }

    if (concatenate_integers(values, count, &result) != 0) {
        fputs("Unable to concatenate integers without overflow\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    printf("%" PRIuMAX "\n", result);
    free(values);

    return EXIT_SUCCESS;
}