#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

double cylinder_volume(double radius, double height) {
    if (radius < 0 || height < 0) {
        return -1.0;
    }
    return PI * radius * radius * height;
}

int main(void) {
    double radius, height, volume;
    char input[100];
    char *endptr;

    printf("Enter radius: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    radius = strtod(input, &endptr);
    if (endptr == input || *endptr != '\n') {
        fprintf(stderr, "Invalid radius input\n");
        return EXIT_FAILURE;
    }

    printf("Enter height: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    height = strtod(input, &endptr);
    if (endptr == input || *endptr != '\n') {
        fprintf(stderr, "Invalid height input\n");
        return EXIT_FAILURE;
    }

    volume = cylinder_volume(radius, height);
    if (volume < 0) {
        fprintf(stderr, "Radius and height must be non-negative\n");
        return EXIT_FAILURE;
    }

    printf("Volume: %.6f\n", volume);
    return EXIT_SUCCESS;
}