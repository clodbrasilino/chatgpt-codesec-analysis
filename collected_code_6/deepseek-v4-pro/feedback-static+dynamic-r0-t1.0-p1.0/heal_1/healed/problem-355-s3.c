#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <errno.h>

int count_rectangles_in_circle(double radius) {
    if (radius <= 0) {
        return 0;
    }
    
    if (radius > sqrt((double)INT_MAX)) {
        radius = sqrt((double)INT_MAX);
    }
    
    int count = 0;
    int r_int = (int)floor(radius);
    
    for (int x = 1; x <= r_int; x++) {
        double x_squared = (double)x * x;
        double y_max = sqrt(radius * radius - x_squared);
        int max_y = (int)floor(y_max);
        for (int y = 1; y <= max_y; y++) {
            count++;
        }
    }
    
    return count * 4;
}

int main(void) {
    double radius;
    char input[256];
    
    printf("Enter circle radius: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    char *endptr;
    errno = 0;
    radius = strtod(input, &endptr);
    
    if (endptr == input || errno == ERANGE) {
        return EXIT_FAILURE;
    }
    
    while (*endptr != '\0') {
        if (*endptr != ' ' && *endptr != '\t' && *endptr != '\n' && *endptr != '\r') {
            return EXIT_FAILURE;
        }
        endptr++;
    }
    
    int rectangles = count_rectangles_in_circle(radius);
    printf("Number of rectangles: %d\n", rectangles);
    
    return EXIT_SUCCESS;
}