#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

double complex_angle(double real, double imag) {
    if (real == 0.0 && imag == 0.0) {
        errno = EDOM;
        return 0.0;
    }
    return atan2(imag, real);
}

int main(void) {
    double real, imag, angle;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *endptr;

    printf("Enter real part: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }
    errno = 0;
    real = strtod(input, &endptr);
    if (errno == ERANGE || endptr == input) {
        fprintf(stderr, "Invalid real part.\n");
        return EXIT_FAILURE;
    }

    printf("Enter imaginary part: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }
    errno = 0;
    imag = strtod(input, &endptr);
    if (errno == ERANGE || endptr == input) {
        fprintf(stderr, "Invalid imaginary part.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    angle = complex_angle(real, imag);
    if (errno == EDOM) {
        fprintf(stderr, "Angle undefined for zero complex number.\n");
        return EXIT_FAILURE;
    }

    printf("Angle: %f radians\n", angle);
    return EXIT_SUCCESS;
}