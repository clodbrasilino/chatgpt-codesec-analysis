#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int geometric_sum(double first, double ratio, size_t terms, double *result)
{
    if (result == NULL || !isfinite(first) || !isfinite(ratio)) {
        return -1;
    }

    double sum = 0.0;
    double term = first;

    for (size_t i = 0; i < terms; ++i) {
        sum += term;
        if (!isfinite(sum)) {
            return -1;
        }

        if (i + 1U < terms) {
            term *= ratio;
            if (!isfinite(term)) {
                return -1;
            }
        }
    }

    *result = sum;
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <first-term> <ratio> <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *end = NULL;

    errno = 0;
    double first = strtod(argv[1], &end);
    if (errno == ERANGE || end == argv[1] || *end != '\0' || !isfinite(first)) {
        fprintf(stderr, "Invalid first term\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    double ratio = strtod(argv[2], &end);
    if (errno == ERANGE || end == argv[2] || *end != '\0' || !isfinite(ratio)) {
        fprintf(stderr, "Invalid ratio\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    unsigned long long n = strtoull(argv[3], &end, 10);
    if (errno == ERANGE || end == argv[3] || *end != '\0' || argv[3][0] == '-' || n < 1U) {
        fprintf(stderr, "Invalid n\n");
        return EXIT_FAILURE;
    }

    if (n - 1U > (unsigned long long)SIZE_MAX) {
        fprintf(stderr, "n is too large\n");
        return EXIT_FAILURE;
    }

    double result = 0.0;
    if (geometric_sum(first, ratio, (size_t)(n - 1U), &result) != 0) {
        fprintf(stderr, "Unable to calculate the sum\n");
        return EXIT_FAILURE;
    }

    printf("%.17g\n", result);
    return EXIT_SUCCESS;
}