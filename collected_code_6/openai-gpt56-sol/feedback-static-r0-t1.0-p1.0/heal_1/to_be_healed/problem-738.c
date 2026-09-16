#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int geometric_sum(double ratio, size_t terms, double *result)
{
    if (result == NULL || !isfinite(ratio)) {
        return -1;
    }

    if (terms == 0U) {
        *result = 0.0;
        return 0;
    }

    if (ratio == 1.0) {
        *result = (double)terms;
        return isfinite(*result) ? 0 : -1;
    }

    *result = (1.0 - pow(ratio, (double)terms)) / (1.0 - ratio);
    return isfinite(*result) ? 0 : -1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long long input = 0ULL;
    double result = 0.0;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoull(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' || input == 0ULL) {
        fprintf(stderr, "Invalid n\n");
        return EXIT_FAILURE;
    }

    if (geometric_sum((double)input, (size_t)(input - 1ULL), &result) != 0) {
        fprintf(stderr, "Unable to calculate the geometric sum\n");
        return EXIT_FAILURE;
    }

    printf("%.17g\n", result);
    return EXIT_SUCCESS;
}