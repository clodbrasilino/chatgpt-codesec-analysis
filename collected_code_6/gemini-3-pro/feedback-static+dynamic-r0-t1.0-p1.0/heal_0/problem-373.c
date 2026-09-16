#include <stdio.h>
#include <stdlib.h>

double calculate_cuboid_volume(double length, double width, double height) {
    if (length < 0.0 || width < 0.0 || height < 0.0) {
        return -1.0;
    }
    return length * width * height;
}

int main(void) {
    double length = 0.0;
    double width = 0.0;
    double height = 0.0;
    double volume = 0.0;

    if (printf("Enter length, width, and height: ") < 0) {
        return EXIT_FAILURE;
    }
    
    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (scanf("%lf %lf %lf", &length, &width, &height) != 3) {
        fprintf(stderr, "Invalid input. Please enter three numeric values.\n");
        return EXIT_FAILURE;
    }

    volume = calculate_cuboid_volume(length, width, height);

    if (volume < 0.0) {
        fprintf(stderr, "Invalid dimensions. Values cannot be negative.\n");
        return EXIT_FAILURE;
    }

    if (printf("Volume of the cuboid: %f\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}