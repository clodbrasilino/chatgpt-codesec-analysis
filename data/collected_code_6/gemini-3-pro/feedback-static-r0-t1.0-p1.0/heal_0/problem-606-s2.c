#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

double degrees_to_radians(double degrees);

double degrees_to_radians(double degrees) {
    return degrees * (PI / 180.0);
}

int main(void) {
    double degrees = 0.0;
    double radians = 0.0;
    int input_status = 0;

    input_status = scanf("%lf", &degrees);

    if (input_status != 1) {
        return EXIT_FAILURE;
    }

    radians = degrees_to_radians(degrees);

    if (printf("%f\n", radians) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}