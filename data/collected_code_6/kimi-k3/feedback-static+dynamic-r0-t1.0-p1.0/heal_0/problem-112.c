#include <stdio.h>
#include <math.h>

double cylinder_perimeter(double radius, double height) {
    return 2 * M_PI * radius + 2 * height;
}

int main(void) {
    double radius = 0.0;
    double height = 0.0;
    double perimeter = 0.0;

    printf("Enter the radius of the cylinder: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Error: Invalid input for radius.\n");
        return 1;
    }

    printf("Enter the height of the cylinder: ");
    if (scanf("%lf", &height) != 1) {
        fprintf(stderr, "Error: Invalid input for height.\n");
        return 1;
    }

    if (radius < 0.0 || height < 0.0) {
        fprintf(stderr, "Error: Radius and height must be non-negative.\n");
        return 1;
    }

    perimeter = cylinder_perimeter(radius, height);
    printf("The perimeter of the cylinder is: %.2f\n", perimeter);

    return 0;
}