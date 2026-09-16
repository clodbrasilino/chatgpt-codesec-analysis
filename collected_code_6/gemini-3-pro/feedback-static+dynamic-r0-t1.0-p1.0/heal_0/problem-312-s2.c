#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double calculate_cone_volume(double radius, double height) {
    if (radius < 0.0 || height < 0.0) {
        return -1.0;
    }
    return (M_PI * radius * radius * height) / 3.0;
}

int main(void) {
    double radius = 0.0;
    double height = 0.0;
    double volume = 0.0;
    int result = 0;

    printf("Enter radius of the cone: ");
    result = scanf("%lf", &radius);
    if (result != 1) {
        fprintf(stderr, "Invalid input for radius.\n");
        return EXIT_FAILURE;
    }

    printf("Enter height of the cone: ");
    result = scanf("%lf", &height);
    if (result != 1) {
        fprintf(stderr, "Invalid input for height.\n");
        return EXIT_FAILURE;
    }

    volume = calculate_cone_volume(radius, height);
    
    if (volume < 0.0) {
        fprintf(stderr, "Radius and height must be non-negative.\n");
        return EXIT_FAILURE;
    }

    printf("The volume of the cone is: %.4f\n", volume);

    return EXIT_SUCCESS;
}