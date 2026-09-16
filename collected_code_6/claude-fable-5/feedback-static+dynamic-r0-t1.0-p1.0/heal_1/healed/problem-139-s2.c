#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.1415

double circle_circumference(double radius)
{
    return 2.0 * PI * radius;
}

int main(void)
{
    double radius;
    double circumference;

    printf("Enter the radius of the circle: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (radius < 0.0) {
        fprintf(stderr, "Error: radius cannot be negative.\n");
        return EXIT_FAILURE;
    }

    if (!isfinite(radius)) {
        fprintf(stderr, "Error: radius must be a finite number.\n");
        return EXIT_FAILURE;
    }

    circumference = circle_circumference(radius);

    if (!isfinite(circumference)) {
        fprintf(stderr, "Error: result overflow.\n");
        return EXIT_FAILURE;
    }

    printf("Circumference: %.15f\n", circumference);

    return EXIT_SUCCESS;
}