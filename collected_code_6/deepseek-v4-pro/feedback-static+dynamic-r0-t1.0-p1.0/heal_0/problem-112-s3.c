#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

double cylinder_perimeter(double radius, double height) {
    if (radius < 0 || height < 0) {
        return -1.0;
    }
    return 2.0 * PI * radius + 2.0 * height;
}

int main(void) {
    double radius;
    double height;
    double perimeter;

    printf("Enter radius: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Invalid input for radius\n");
        return EXIT_FAILURE;
    }

    printf("Enter height: ");
    if (scanf("%lf", &height) != 1) {
        fprintf(stderr, "Invalid input for height\n");
        return EXIT_FAILURE;
    }

    perimeter = cylinder_perimeter(radius, height);
    if (perimeter < 0) {
        fprintf(stderr, "Dimensions cannot be negative\n");
        return EXIT_FAILURE;
    }

    printf("Perimeter of cylinder: %.2f\n", perimeter);

    return EXIT_SUCCESS;
}