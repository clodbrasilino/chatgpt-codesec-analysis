#include <stdio.h>
#include <stdlib.h>

#define PI 3.1415

double circle_circumference(double radius)
{
    return 2.0 * PI * radius;
}

int main(void)
{
    double radius;
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

    printf("Circumference: %.6f\n", circle_circumference(radius));

    return EXIT_SUCCESS;
}