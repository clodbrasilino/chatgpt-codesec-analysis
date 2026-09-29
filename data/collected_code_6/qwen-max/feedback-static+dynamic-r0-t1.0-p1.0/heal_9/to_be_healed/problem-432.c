#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 7.5, got 7
  */

double find_median_trapezium(double a, double b, double h) {
    if (a <= 0 || b <= 0 || h <= 0) {
        return -1.0;
    }
    return 0.5 * (a + b);
}

int main() {
    double base1, base2, height, median;
    printf("Enter the lengths of the two bases and the height: ");
    if (scanf("%lf %lf %lf", &base1, &base2, &height) != 3) {
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }

    median = find_median_trapezium(base1, base2, height);
    if (median >= 0) {
        printf("The median of the trapezium is: %.2f\n", median);
    } else {
        printf("Invalid dimensions for trapezium.\n");
    }

    return EXIT_SUCCESS;
}