#include <stdio.h>
#include <stdlib.h>

static double largest_triangle_area(double radius)
{
    return radius * radius;
}

int main(void)
{
    double radius = 0.0;

    printf("Enter the radius of the semicircle: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Error: invalid input, expected a number.\n");
        return EXIT_FAILURE;
    }

    if (radius < 0.0) {
        fprintf(stderr, "Error: radius cannot be negative.\n");
        return EXIT_FAILURE;
    }

    printf("The largest inscribed triangle area is: %.6f\n",
           largest_triangle_area(radius));

    return EXIT_SUCCESS;
}