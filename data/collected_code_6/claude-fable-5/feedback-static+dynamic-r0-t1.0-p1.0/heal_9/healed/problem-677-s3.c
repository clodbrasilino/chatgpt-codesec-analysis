#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

int is_valid_triangle(double a, double b, double c)
{
    if (!isfinite(a) || !isfinite(b) || !isfinite(c)) {
        return 0;
    }

    if (a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return 0;
    }

    sort_sides(&a, &b, &c);

    return (a + b > c) ? 1 : 0;
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