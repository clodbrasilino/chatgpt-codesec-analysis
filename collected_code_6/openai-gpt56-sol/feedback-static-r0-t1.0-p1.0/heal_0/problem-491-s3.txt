#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int geometric_sum(double first_term, double ratio, size_t term_count,
                         double *result)
{
    if (result == NULL || !isfinite(first_term) || !isfinite(ratio)) {
        return 0;
    }

    if (term_count == 0U) {
        *result = 0.0;
        return 1;
    }

    if (ratio == 1.0) {
        *result = first_term * (double)term_count;
    } else {
        *result = first_term *
                  (1.0 - pow(ratio, (double)term_count)) /
                  (1.0 - ratio);
    }

    return isfinite(*result);
}

int main(void)
{
    double first_term;
    double ratio;
    unsigned long long input_count;
    size_t term_count;
    double sum;

    if (scanf("%lf %lf %llu", &first_term, &ratio, &input_count) != 3) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    term_count = (size_t)input_count;
    if ((unsigned long long)term_count != input_count) {
        fputs("Term count is too large\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    if (!geometric_sum(first_term, ratio, term_count, &sum) ||
        errno == EDOM || errno == ERANGE) {
        fputs("Unable to calculate a finite sum\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.17g\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}