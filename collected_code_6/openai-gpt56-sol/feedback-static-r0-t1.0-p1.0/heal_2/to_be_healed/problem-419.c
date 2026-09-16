#include <errno.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_and_print(const double *numbers, size_t length)
{
    long double sum = 0.0L;

    if (numbers == NULL || length == 0U) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (!isfinite(numbers[i])) {
            return EXIT_FAILURE;
        }

        sum += roundl((long double)numbers[i]);
    }

    const long double result = sum * (long double)length;

    if (!isfinite(result) || printf("%.0Lf\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s number [number ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const size_t length = (size_t)(argc - 1);
    double *numbers = calloc(length, sizeof(*numbers));

    if (numbers == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i) {
        char *end = NULL;

        errno = 0;
        numbers[i] = strtod(argv[i + 1U], &end);

        if (errno == ERANGE || end == argv[i + 1U] || *end != '\0' ||
            !isfinite(numbers[i])) {
            fprintf(stderr, "Invalid number: %s\n", argv[i + 1U]);
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    const int status = calculate_and_print(numbers, length);
    free(numbers);

    if (status != EXIT_SUCCESS) {
        fputs("Calculation or output failed\n", stderr);
    }

    return status;
}