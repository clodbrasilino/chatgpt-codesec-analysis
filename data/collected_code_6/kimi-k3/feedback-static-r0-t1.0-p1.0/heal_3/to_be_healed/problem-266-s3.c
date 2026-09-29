#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 256

double lateral_surface_area_cube(double side)
{
    if (side < 0.0 || !isfinite(side)) {
        errno = EDOM;
        return -1.0;
    }
    
    if (side > 0.0 && side > sqrt(DBL_MAX / 4.0)) {
        errno = ERANGE;
        return -1.0;
    }
    
    return 4.0 * side * side;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    char *endptr;
    double side;
    double result;
    size_t len;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] != '\n' && !feof(stdin)) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    side = strtod(buffer, &endptr);
    
    if (errno != 0 || endptr == buffer) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    while (*endptr != '\0' && isspace((unsigned char)*endptr)) {
        endptr++;
    }
    
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    result = lateral_surface_area_cube(side);
    
    if (errno != 0 || result < 0.0) {
        fprintf(stderr, "Error calculating lateral surface area\n");
        return EXIT_FAILURE;
    }
    
    printf("%.6f\n", result);
    
    return EXIT_SUCCESS;
}