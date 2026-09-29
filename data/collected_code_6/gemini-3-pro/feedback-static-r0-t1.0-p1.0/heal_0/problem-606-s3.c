#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

double degrees_to_radians(double degrees);

int main(void) {
    double degrees = 0.0;
    double radians = 0.0;

    if (scanf("%lf", &degrees) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    radians = degrees_to_radians(degrees);
    printf("%f\n", radians);

    return EXIT_SUCCESS;
}

double degrees_to_radians(double degrees) {
    return degrees * (PI / 180.0);
}