#include <stdio.h>
#include <stdlib.h>

double calculate_diameter(double radius) {
    if (radius < 0.0) {
        return -1.0;
    }
    return 2.0 * radius;
}

int main(void) {
    double radius = 0.0;
    double diameter = 0.0;
    
    if (scanf("%lf", &radius) != 1) {
        return EXIT_FAILURE;
    }

    diameter = calculate_diameter(radius);
    if (diameter < 0.0) {
        return EXIT_FAILURE;
    }

    printf("%f\n", diameter);

    return EXIT_SUCCESS;
}