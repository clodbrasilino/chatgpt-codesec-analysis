#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

double calculate_circumference(double radius) {
    if (radius < 0.0) {
        return -1.0;
    }
    return 2.0 * PI * radius;
}

int main(void) {
    double radius = 5.0;
    double circumference = calculate_circumference(radius);

    if (circumference < 0.0) {
        fprintf(stderr, "Error: Invalid negative radius.\n");
        return EXIT_FAILURE;
    }

    printf("Circumference: %f\n", circumference);

    return EXIT_SUCCESS;
}