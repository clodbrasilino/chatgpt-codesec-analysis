#include <errno.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int round_and_print(const double *numbers, size_t length)
{
    long double sum = 0.0L;

    if (numbers == NULL || length == 0) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!isfinite(numbers[i])) {
            return EXIT_FAILURE;
        }
        sum += roundl((long double)numbers[i]);
    }

    long double result = sum * (long double)length;

    if (!isfinite(result) || printf("%.0Lf\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int main(void)
{
    size_t length;

    errno = 0;
    if (scanf("%zu", &length) != 1 || errno != 0 || length == 0 ||
        length > SIZE_MAX / sizeof(double)) {
        return EXIT_FAILURE;
    }

    double *numbers = malloc(length * sizeof(*numbers));
    if (numbers == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%lf", &numbers[i]) != 1) {
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    int status = round_and_print(numbers, length);
    free(numbers);

    return status;
}