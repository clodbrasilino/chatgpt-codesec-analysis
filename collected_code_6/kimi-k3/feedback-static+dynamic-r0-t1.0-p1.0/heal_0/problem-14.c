#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>

double calculate_triangular_prism_volume(double base, double height, double length) {
    if (base <= 0.0 || height <= 0.0 || length <= 0.0) {
        return -1.0;
    }
    return 0.5 * base * height * length;
}

int main(void) {
    double base, height, length, volume;
    int result;

    printf("Enter the base of the triangle: ");
    result = scanf("%lf", &base);
    if (result != 1) {
        fprintf(stderr, "Invalid input for base\n");
        return EXIT_FAILURE;
    }

    printf("Enter the height of the triangle: ");
    result = scanf("%lf", &height);
    if (result != 1) {
        fprintf(stderr, "Invalid input for height\n");
        return EXIT_FAILURE;
    }

    printf("Enter the length of the prism: ");
    result = scanf("%lf", &length);
    if (result != 1) {
        fprintf(stderr, "Invalid input for length\n");
        return EXIT_FAILURE;
    }

    volume = calculate_triangular_prism_volume(base, height, length);
    if (volume < 0.0) {
        fprintf(stderr, "Invalid dimensions: all values must be positive\n");
        return EXIT_FAILURE;
    }

    printf("Volume of the triangular prism: %.2f\n", volume);

    return EXIT_SUCCESS;
}