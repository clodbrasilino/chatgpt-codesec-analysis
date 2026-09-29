#include <stdio.h>
#include <stdlib.h>

static int is_valid_triangle(double a, double b, double c)
{
    if (a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return 0;
    }
    if ((a + b) <= c || (b + c) <= a || (a + c) <= b) {
        return 0;
    }
    return 1;
}

static int is_isosceles(double a, double b, double c)
{
    if (a == b || b == c || a == c) {
        return 1;
    }
    return 0;
}

int main(void)
{
    double a;
    double b;
    double c;
    int result;

    printf("Enter the three sides of the triangle: ");

    result = scanf("%lf %lf %lf", &a, &b, &c);
    if (result != 3) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (!is_valid_triangle(a, b, c)) {
        fprintf(stderr, "Error: the given sides do not form a valid triangle.\n");
        return EXIT_FAILURE;
    }

    if (is_isosceles(a, b, c)) {
        printf("The triangle is isosceles.\n");
    } else {
        printf("The triangle is not isosceles.\n");
    }

    return EXIT_SUCCESS;
}