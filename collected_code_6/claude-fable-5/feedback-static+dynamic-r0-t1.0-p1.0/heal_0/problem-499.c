#include <stdio.h>
#include <stdlib.h>

double calculate_diameter(double radius);

double calculate_diameter(double radius)
{
    return 2.0 * radius;
}

int main(void)
{
    double radius = 0.0;
    double diameter = 0.0;
    int result = 0;

    printf("Enter the radius of the circle: ");
    result = scanf("%lf", &radius);

    if (result != 1)
    {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (radius < 0.0)
    {
        fprintf(stderr, "Error: radius cannot be negative.\n");
        return EXIT_FAILURE;
    }

    diameter = calculate_diameter(radius);
    printf("The diameter of the circle is: %.2f\n", diameter);

    return EXIT_SUCCESS;
}