#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double degrees_to_radians(double degrees);

double degrees_to_radians(double degrees) {
    return degrees * (M_PI / 180.0);
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    double degrees;
    double radians;
    char *endptr;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    degrees = strtod(buffer, &endptr);

    if (endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        return EXIT_FAILURE;
    }

    radians = degrees_to_radians(degrees);

    if (printf("%f\n", radians) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}