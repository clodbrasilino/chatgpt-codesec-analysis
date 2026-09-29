#include <stdio.h>
#include <stdlib.h>

int is_valid_triangle(double a, double b, double c)
{
    if (a <= 0.0 || b <= 0.0 || c <= 0.0)
    {
        return 0;
    }
    if ((a + b) <= c || (b + c) <= a || (a + c) <= b)
    {
        return 0;
    }
    return 1;
}

int is_equilateral(double a, double b, double c)
{
    return (a == b) && (b == c);
}

int main(void)
{
    double a;
    double b;
    double c;

    printf("Enter the three sides of the triangle: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3)
    {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (!is_valid_triangle(a, b, c))
    {
        fprintf(stderr, "Error: the given sides do not form a valid triangle.\n");
        return EXIT_FAILURE;
    }

    if (is_equilateral(a, b, c))
    {
        printf("The triangle is equilateral.\n");
    }
    else
    {
        printf("The triangle is not equilateral.\n");
    }

    return EXIT_SUCCESS;
}