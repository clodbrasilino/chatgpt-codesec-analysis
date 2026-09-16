#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

static void sort_sides(double *a, double *b, double *c)
{
    double tmp;

    if (*a > *b) {
        tmp = *a;
        *a = *b;
        *b = tmp;
    }
    if (*b > *c) {
        tmp = *b;
        *b = *c;
        *c = tmp;
    }
    if (*a > *b) {
        tmp = *a;
        *a = *b;
        *b = tmp;
    }
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected True, got 0
  *  test case 0 failed: expected False, got 1
  */

int is_valid_triangle(double a, double b, double c)
{
    double diff;
    double tolerance;

    if (!isfinite(a) || !isfinite(b) || !isfinite(c)) {
        return 0;
    }

    if (a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return 0;
    }

    sort_sides(&a, &b, &c);

    diff = (a + b) - c;
    tolerance = DBL_EPSILON * fmax(fmax(a, b), c) * 4.0;

    if (diff > tolerance) {
        return 1;
    }

    return 0;
}

int main(void)
{
    double a;
    double b;
    double c;

    printf("Enter the three sides of the triangle: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (is_valid_triangle(a, b, c)) {
        printf("The triangle is valid.\n");
    } else {
        printf("The triangle is not valid.\n");
    }

    return EXIT_SUCCESS;
}