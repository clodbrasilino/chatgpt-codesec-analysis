#include <stdio.h>
#include <stdlib.h>

static int is_valid_triangle(double a, double b, double c)
{
    return a > 0.0 && b > 0.0 && c > 0.0 &&
           a + b > c && a + c > b && b + c > a;
}

static int is_isosceles(double a, double b, double c)
{
    return a == b || a == c || b == c;
}

int main(void)
{
    double a;
    double b;
    double c;

    if (printf("Enter three side lengths: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (!is_valid_triangle(a, b, c)) {
        fprintf(stderr, "The side lengths do not form a valid triangle.\n");
        return EXIT_FAILURE;
    }

    if (is_isosceles(a, b, c)) {
        printf("The triangle is isosceles.\n");
    } else {
        printf("The triangle is not isosceles.\n");
    }

    return EXIT_SUCCESS;
}