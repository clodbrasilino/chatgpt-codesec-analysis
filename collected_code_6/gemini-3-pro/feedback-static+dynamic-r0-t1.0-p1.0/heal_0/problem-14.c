#include <stdio.h>
#include <stdlib.h>

double calculateTriangularPrismVolume(double base, double height, double length) {
    if (base < 0.0 || height < 0.0 || length < 0.0) {
        return -1.0;
    }
    return 0.5 * base * height * length;
}

int main(void) {
    double base = 5.0;
    double height = 4.0;
    double length = 10.0;
    double volume;

    volume = calculateTriangularPrismVolume(base, height, length);

    if (volume < 0.0) {
        fprintf(stderr, "Invalid input dimensions.\n");
        return EXIT_FAILURE;
    }

    printf("The volume of the triangular prism is: %.2f\n", volume);

    return EXIT_SUCCESS;
}