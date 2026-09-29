#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double largest_triangle_area(double semi_major, double semi_minor);

double largest_triangle_area(double semi_major, double semi_minor)
{
    if (semi_major <= 0.0 || semi_minor <= 0.0)
    {
        return -1.0;
    }

    if (!isfinite(semi_major) || !isfinite(semi_minor))
    {
        return -1.0;
    }

    return (3.0 * sqrt(3.0) / 4.0) * semi_major * semi_minor;
}

int main(void)
{
    double a = 0.0;
    double b = 0.0;
    double area = 0.0;

    printf("Enter semi-major axis (a): ");
    if (scanf("%lf", &a) != 1)
    {
        fprintf(stderr, "Error: invalid input for semi-major axis.\n");
        return EXIT_FAILURE;
    }

    printf("Enter semi-minor axis (b): ");
    if (scanf("%lf", &b) != 1)
    {
        fprintf(stderr, "Error: invalid input for semi-minor axis.\n");
        return EXIT_FAILURE;
    }

    area = largest_triangle_area(a, b);

    if (area < 0.0)
    {
        fprintf(stderr, "Error: axes must be positive finite values.\n");
        return EXIT_FAILURE;
    }

    printf("Largest inscribed triangle area: %.6f\n", area);

    return EXIT_SUCCESS;
}