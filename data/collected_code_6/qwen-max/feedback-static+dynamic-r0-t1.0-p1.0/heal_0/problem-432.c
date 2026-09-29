#include <stdio.h>
#include <stdlib.h>

double find_median_trapezium(double a, double b, double h) {
    if (a <= 0 || b <= 0 || h <= 0) {
        return -1.0;
    }
    return (a + b) / 2.0;
}

int main() {
    double base1, base2, height, median;

    printf("Enter the lengths of the two bases and the height: ");
    if (scanf("%lf %lf %lf", &base1, &base2, &height) != 3) {
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }

    median = find_median_trapezium(base1, base2, height);
    if (median < 0) {
        printf("Invalid dimensions for trapezium.\n");
    } else {
        printf("The median of the trapezium is: %.2f\n", median);
    }

    return EXIT_SUCCESS;
}