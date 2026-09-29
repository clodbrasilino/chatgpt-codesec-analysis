#include <stdio.h>
#include <stdlib.h>

double triangular_prism_volume(double base, double height, double length) {
    if (base <= 0.0 || height <= 0.0 || length <= 0.0) {
        return -1.0;
    }
    return 0.5 * base * height * length;
}

int main(void) {
    double base = 3.0;
    double height = 4.0;
    double length = 5.0;
    double volume = triangular_prism_volume(base, height, length);

    if (volume < 0.0) {
        return EXIT_FAILURE;
    }

    printf("%f\n", volume);
    return EXIT_SUCCESS;
}