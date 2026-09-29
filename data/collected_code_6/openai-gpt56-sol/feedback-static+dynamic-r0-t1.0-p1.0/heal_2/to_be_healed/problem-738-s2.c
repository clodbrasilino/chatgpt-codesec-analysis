#include <errno.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int geometric_sum(double first_term, double ratio, size_t term_count,
                         double *result)
{
    if (result == NULL || !isfinite(first_term) || !isfinite(ratio)) {
        return -1;
    }

    if (term_count == 0U) {
        *result = 0.0;
        return 0;
    }

    double sum = first_term;

    for (size_t i = 1U; i < term_count; ++i) {
        sum = sum * ratio + first_term;

        if (!isfinite(sum)) {
            return -1;
        }
    }

    *result = sum;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <first_term> <ratio> <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    const double first_term = strtod(argv[1], &end);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        !isfinite(first_term)) {
        fprintf(stderr, "Invalid first term\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    const double ratio = strtod(argv[2], &end);

    if (errno == ERANGE || end == argv[2] || *end != '\0' ||
        !isfinite(ratio)) {
        fprintf(stderr, "Invalid ratio\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    const unsigned long long n = strtoull(argv[3], &end, 10);

    if (errno == ERANGE || end == argv[3] || *end != '\0' || n == 0ULL ||
        n - 1ULL > (unsigned long long)SIZE_MAX) {
        fprintf(stderr, "Invalid n\n");
        return EXIT_FAILURE;
    }

    double result;

    if (geometric_sum(first_term, ratio, (size_t)(n - 1ULL), &result) != 0) {
        fprintf(stderr, "Unable to calculate the geometric sum\n");
        return EXIT_FAILURE;
    }

    if (printf("%.17g\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}