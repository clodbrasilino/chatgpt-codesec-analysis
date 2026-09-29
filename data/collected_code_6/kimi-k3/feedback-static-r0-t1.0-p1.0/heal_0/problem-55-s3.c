#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static double geometric_nth_term(double first_term, double common_ratio, unsigned int n)
{
    double result = first_term;
    unsigned int i;

    if (n == 0U) {
        return 0.0;
    }

    for (i = 1U; i < n; ++i) {
        result *= common_ratio;
    }

    return result;
}

int main(void)
{
    double first_term = 0.0;
    double common_ratio = 0.0;
    unsigned int n = 0U;
    double term = 0.0;

    printf("Enter the first term: ");
    if (scanf("%lf", &first_term) != 1) {
        fprintf(stderr, "Invalid input for first term.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the common ratio: ");
    if (scanf("%lf", &common_ratio) != 1) {
        fprintf(stderr, "Invalid input for common ratio.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the term number (n): ");
    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Invalid input for term number.\n");
        return EXIT_FAILURE;
    }

    if (n == 0U) {
        fprintf(stderr, "Term number must be at least 1.\n");
        return EXIT_FAILURE;
    }

    term = geometric_nth_term(first_term, common_ratio, n);
    printf("The %uth term of the geometric series is: %lf\n", n, term);

    return EXIT_SUCCESS;
}