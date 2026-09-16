#include <stdio.h>
#include <stdlib.h>

double largest_triangle_area(double radius);

double largest_triangle_area(double radius)
{
    if (radius < 0.0)
    {
        return -1.0;
    }
    return radius * radius;
}

int main(void)
{
    double radius = 0.0;
    double area = 0.0;
    int result = 0;

    printf("Enter the radius of the semicircle: ");
    result = scanf("%lf", &radius);

    if (result != 1)
    {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    area = largest_triangle_area(radius);

    if (area < 0.0)
    {
        fprintf(stderr, "Error: radius cannot be negative.\n");
        return EXIT_FAILURE;
    }

    printf("The largest triangle area inscribed in the semicircle is: %f\n", area);

    return EXIT_SUCCESS;
}