#include <stdio.h>
#include <stdlib.h>

int is_valid_triangle(double a, double b, double c);
int is_scalene(double a, double b, double c);

int is_valid_triangle(double a, double b, double c)
{
    if (a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return 0;
    }
    if ((a + b <= c) || (a + c <= b) || (b + c <= a)) {
        return 0;
    }
    return 1;
}

int is_scalene(double a, double b, double c)
{
    if (a != b && b != c && a != c) {
        return 1;
    }
    return 0;
}

int main(void)
{
    double a = 0.0;
    double b = 0.0;
    double c = 0.0;
    int result = 0;

    printf("Enter the three sides of the triangle: ");
    result = scanf("%lf %lf %lf", &a, &b, &c);

    if (result != 3) {
        fprintf(stderr, "Error: invalid input. Please enter three numbers.\n");
        return EXIT_FAILURE;
    }

    if (!is_valid_triangle(a, b, c)) {
        fprintf(stderr, "Error: the given sides do not form a valid triangle.\n");
        return EXIT_FAILURE;
    }

    if (is_scalene(a, b, c)) {
        printf("The triangle is scalene.\n");
    } else {
        printf("The triangle is not scalene.\n");
    }

    return EXIT_SUCCESS;
}