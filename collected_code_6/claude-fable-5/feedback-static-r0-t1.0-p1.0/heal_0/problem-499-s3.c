#include <stdio.h>
#include <stdlib.h>

double circle_diameter(double radius)
{
    return 2.0 * radius;
}

int main(void)
{
    double radius = 0.0;

    printf("Enter the radius of the circle: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (radius < 0.0) {
        fprintf(stderr, "Error: radius cannot be negative.\n");
        return EXIT_FAILURE;
    }

    printf("Diameter of the circle: %.6f\n", circle_diameter(radius));

    return EXIT_SUCCESS;
}