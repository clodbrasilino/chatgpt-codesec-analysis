#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <stdlib.h>

double geometric_series_sum(double first_term, double common_ratio, int num_terms) {
    double sum = 0.0;
    double term = first_term;
    int i;

    if (num_terms <= 0) {
        return 0.0;
    }

    if (common_ratio == 1.0) {
        return first_term * num_terms;
    }

    for (i = 0; i < num_terms; i++) {
        sum += term;
        term *= common_ratio;
    }

    return sum;
}

int main(void) {
    double first_term;
    double common_ratio;
    int num_terms;
    double result;

    printf("Enter the first term: ");
    if (scanf("%lf", &first_term) != 1) {
        fprintf(stderr, "Invalid input for first term\n");
        return EXIT_FAILURE;
    }

    printf("Enter the common ratio: ");
    if (scanf("%lf", &common_ratio) != 1) {
        fprintf(stderr, "Invalid input for common ratio\n");
        return EXIT_FAILURE;
    }

    printf("Enter the number of terms: ");
    if (scanf("%d", &num_terms) != 1) {
        fprintf(stderr, "Invalid input for number of terms\n");
        return EXIT_FAILURE;
    }

    if (num_terms < 0) {
        fprintf(stderr, "Number of terms cannot be negative\n");
        return EXIT_FAILURE;
    }

    result = geometric_series_sum(first_term, common_ratio, num_terms);
    printf("Sum of geometric progression: %.6f\n", result);

    return EXIT_SUCCESS;
}