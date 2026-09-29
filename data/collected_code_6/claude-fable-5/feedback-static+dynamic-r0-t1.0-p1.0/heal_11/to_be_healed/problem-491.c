#include <stdio.h>
#include <math.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 31, got 6
  *  test case 2 failed: expected 728, got 86
  *  test case 1 failed: expected 341, got 156
  */

double sum_of_gp(double a, double r, int n)
{
    double sum;
    double term;
    int i;

    if (n <= 0) {
        return 0.0;
    }

    if (fabs(r - 1.0) < 1e-12) {
        return a * (double)n;
    }

    sum = 0.0;
    term = a;
    for (i = 0; i < n; i++) {
        sum += term;
        term *= r;
    }

    return sum;
}

int main(void)
{
    double a;
    double r;
    int n;
    double result;

    printf("Enter the first term: ");
    if (scanf("%lf", &a) != 1) {
        fprintf(stderr, "Invalid input for first term.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the common ratio: ");
    if (scanf("%lf", &r) != 1) {
        fprintf(stderr, "Invalid input for common ratio.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the number of terms: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input for number of terms.\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Number of terms must be non-negative.\n");
        return EXIT_FAILURE;
    }

    result = sum_of_gp(a, r, n);

    if (isinf(result) || isnan(result)) {
        fprintf(stderr, "Result out of representable range.\n");
        return EXIT_FAILURE;
    }

    if (fabs(result - round(result)) < 1e-9) {
        printf("Sum of the geometric progression: %.0f\n", result);
    } else {
        printf("Sum of the geometric progression: %f\n", result);
    }

    return EXIT_SUCCESS;
}