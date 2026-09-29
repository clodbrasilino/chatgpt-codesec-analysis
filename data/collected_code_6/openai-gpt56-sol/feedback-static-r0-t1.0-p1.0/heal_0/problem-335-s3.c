#include <stdio.h>
#include <stdlib.h>

static int arithmetic_progression_sum(long double first_term,
                                      long double common_difference,
                                      size_t term_count,
                                      long double *sum)
{
    if (sum == NULL) {
        return 0;
    }

    if (term_count == 0U) {
        *sum = 0.0L;
        return 1;
    }

    *sum = ((long double)term_count / 2.0L) *
           (2.0L * first_term +
            ((long double)term_count - 1.0L) * common_difference);

    return 1;
}

int main(void)
{
    long double first_term = 0.0L;
    long double common_difference = 0.0L;
    size_t term_count = 0U;
    long double sum = 0.0L;

    if (scanf("%Lf %Lf %zu",
              &first_term,
              &common_difference,
              &term_count) != 3) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!arithmetic_progression_sum(first_term,
                                    common_difference,
                                    term_count,
                                    &sum)) {
        fputs("Unable to calculate sum\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%.10Lg\n", sum);
    return EXIT_SUCCESS;
}