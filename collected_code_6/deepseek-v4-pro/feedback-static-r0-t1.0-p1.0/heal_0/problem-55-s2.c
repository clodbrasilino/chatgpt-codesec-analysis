#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double geometric_nth_term(double first_term, double common_ratio, int n) {
    if (n <= 0) {
        fprintf(stderr, "Error: Term index must be positive\n");
        exit(EXIT_FAILURE);
    }
    return first_term * pow(common_ratio, n - 1);
}

int main(void) {
    double first_term;
    double common_ratio;
    int n;
    double result;

    printf("Enter first term: ");
    if (scanf("%lf", &first_term) != 1) {
        fprintf(stderr, "Error: Invalid input for first term\n");
        return EXIT_FAILURE;
    }

    printf("Enter common ratio: ");
    if (scanf("%lf", &common_ratio) != 1) {
        fprintf(stderr, "Error: Invalid input for common ratio\n");
        return EXIT_FAILURE;
    }

    printf("Enter term index (n): ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: Invalid input for term index\n");
        return EXIT_FAILURE;
    }

    result = geometric_nth_term(first_term, common_ratio, n);
    printf("The %d-th term of the geometric series is: %.10f\n", n, result);

    return EXIT_SUCCESS;
}