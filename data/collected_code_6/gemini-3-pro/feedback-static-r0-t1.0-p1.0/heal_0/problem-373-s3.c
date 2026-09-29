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

    if (scanf("%lf %lf %lf", &length, &width, &height) != 3) {
        fprintf(stderr, "Error: Invalid input format.\n");
        return EXIT_FAILURE;
    }

    volume = calculate_cuboid_volume(length, width, height);

    if (volume < 0.0) {
        fprintf(stderr, "Error: Dimensions must be non-negative.\n");
        return EXIT_FAILURE;
    }

    printf("%f\n", volume);

    return EXIT_SUCCESS;
}