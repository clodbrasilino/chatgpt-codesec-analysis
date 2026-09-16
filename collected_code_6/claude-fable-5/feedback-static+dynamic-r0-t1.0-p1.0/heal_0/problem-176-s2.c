#include <stdio.h>
#include <stdlib.h>

double triangle_perimeter(double a, double b, double c);
int is_valid_triangle(double a, double b, double c);

double triangle_perimeter(double a, double b, double c)
{
    return a + b + c;
}

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

int main(void)
{
    double a;
    double b;
    double c;
    double perimeter;

    printf("Enter the three sides of the triangle: ");

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (!is_valid_triangle(a, b, c)) {
        fprintf(stderr, "Error: the given sides do not form a valid triangle.\n");
        return EXIT_FAILURE;
    }

    perimeter = triangle_perimeter(a, b, c);

    printf("Perimeter of the triangle: %.2f\n", perimeter);

    return EXIT_SUCCESS;
}