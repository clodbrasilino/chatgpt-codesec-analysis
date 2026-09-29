#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>

double degrees_to_radians(double degrees) {
    return degrees * (M_PI / 180.0);
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[128];
    char *end_ptr;
    double degrees;
    double radians;

    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    degrees = strtod(input_buffer, &end_ptr);

    if (end_ptr == input_buffer) {
        fprintf(stderr, "No digits were found\n");
        return EXIT_FAILURE;
    }

    if (errno == ERANGE) {
        fprintf(stderr, "Input value out of range\n");
        return EXIT_FAILURE;
    }

    radians = degrees_to_radians(degrees);

    printf("%f degrees is %f radians\n", degrees, radians);

    return EXIT_SUCCESS;
}