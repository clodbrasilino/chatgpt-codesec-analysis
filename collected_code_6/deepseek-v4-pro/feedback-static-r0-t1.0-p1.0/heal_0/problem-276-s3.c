#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double cylinder_volume(double radius, double height) {
    if (radius < 0.0 || height < 0.0) {
        fprintf(stderr, "Error: radius and height must be non-negative\n");
        exit(EXIT_FAILURE);
    }
    return M_PI * radius * radius * height;
}

int main(void) {
    double radius = 0.0;
    double height = 0.0;
    double volume = 0.0;
    int result = 0;

    printf("Enter radius: ");
    result = scanf("%lf", &radius);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input for radius\n");
        return EXIT_FAILURE;
    }

    printf("Enter height: ");
    result = scanf("%lf", &height);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input for height\n");
        return EXIT_FAILURE;
    }

    volume = cylinder_volume(radius, height);
    printf("Volume: %.6f\n", volume);

    return EXIT_SUCCESS;
}