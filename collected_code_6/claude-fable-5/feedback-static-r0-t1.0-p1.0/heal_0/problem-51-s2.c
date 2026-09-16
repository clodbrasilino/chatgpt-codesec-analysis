#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool is_valid_triangle(double a, double b, double c)
{
    if (a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return false;
    }
    if ((a + b <= c) || (a + c <= b) || (b + c <= a)) {
        return false;
    }
    return true;
}

static bool is_equilateral(double a, double b, double c)
{
    return (a == b) && (b == c);
}

int main(void)
{
    double a = 0.0;
    double b = 0.0;
    double c = 0.0;

    printf("Enter the three sides of the triangle: ");

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (!is_valid_triangle(a, b, c)) {
        fprintf(stderr, "Error: the given sides do not form a valid triangle.\n");
        return EXIT_FAILURE;
    }

    if (is_equilateral(a, b, c)) {
        printf("The triangle is equilateral.\n");
    } else {
        printf("The triangle is not equilateral.\n");
    }

    return EXIT_SUCCESS;
}