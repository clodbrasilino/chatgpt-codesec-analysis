#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double radians_to_degrees(double radians);

double radians_to_degrees(double radians) {
    return radians * (180.0 / M_PI);
}

int main(int argc, const char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <radians>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr = NULL;
    double radians = strtod(argv[1], &endptr);

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    if (endptr == (char *)argv[1] || *endptr != '\0') {
        fprintf(stderr, "Error: Invalid numeric input.\n");
        return EXIT_FAILURE;
    }

    double degrees = radians_to_degrees(radians);
    
    if (printf("%.6f\n", degrees) < 0) {
        fprintf(stderr, "Error: Output failed.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}