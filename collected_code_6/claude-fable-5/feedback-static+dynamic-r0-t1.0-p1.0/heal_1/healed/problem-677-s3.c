#include <stdio.h>
#include <stdlib.h>
#include <float.h>

int is_valid_triangle(double a, double b, double c)
{
    double eps;

    if (a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return 0;
    }

    eps = DBL_EPSILON * (a + b + c);

    if ((a + b - c > eps) && (a + c - b > eps) && (b + c - a > eps)) {
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