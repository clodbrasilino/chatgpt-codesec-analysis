#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 128

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
    char buffer[BUFFER_SIZE];
    char *endptr;
    double side;
    double result;
    size_t len;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    len = strnlen(buffer, sizeof(buffer));
    if (len == sizeof(buffer) - 1 && buffer[len - 1] != '\n') {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    side = strtod(buffer, &endptr);
    
    if (errno != 0 || endptr == buffer) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    while (isspace((unsigned char)*endptr)) {
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
    
    printf("%.0f\n", result);
    
    return EXIT_SUCCESS;
}