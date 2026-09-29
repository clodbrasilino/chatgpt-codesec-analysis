#include <stdio.h>
#include <stdlib.h>

double find_diameter(double radius)
{
    return 2.0 * radius;
}

int main(void)
{
    double radius;
    double diameter;
    int result;

    printf("Enter the radius of the circle: ");
    result = scanf("%lf", &radius);

    if (result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (radius < 0.0) {
        fprintf(stderr, "Error: radius cannot be negative.\n");
        return EXIT_FAILURE;
    }

    diameter = find_diameter(radius);
    printf("The diameter of the circle is: %.2f\n", diameter);

    return EXIT_SUCCESS;
}