#include <stdio.h>
#include <stdlib.h>

double trapezium_median(double a, double b) {
    if (a < 0 || b < 0) {
        fprintf(stderr, "Error: Base lengths must be non-negative.\n");
        exit(EXIT_FAILURE);
    }
    return (a + b) / 2.0;
}

int main(void) {
    double base1, base2, median;
    int result;

    printf("Enter the lengths of the two parallel sides: ");
    result = scanf("%lf %lf", &base1, &base2);

    if (result != 2) {
        fprintf(stderr, "Error: Invalid input. Please enter two numeric values.\n");
        return EXIT_FAILURE;
    }

    median = trapezium_median(base1, base2);
    printf("Median length: %.2f\n", median);

    return EXIT_SUCCESS;
}