#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

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
    char *input = NULL;
    size_t len = 0;
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    ssize_t read;
    
    printf("Enter circle radius: ");
    read = getline(&input, &len, stdin);
    if (read == -1) {
        free(input);
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    if (read > 0 && input[read - 1] == '\n') {
        input[read - 1] = '\0';
    }
    
    char *endptr;
    errno = 0;
    radius = strtod(input, &endptr);
    
    if (endptr == input || errno == ERANGE) {
        free(input);
        return EXIT_FAILURE;
    }
    
    while (*endptr != '\0') {
        if (*endptr != ' ' && *endptr != '\t') {
            free(input);
            return EXIT_FAILURE;
        }
        endptr++;
    }
    
    free(input);
    
    int rectangles = count_rectangles_in_circle(radius);
    printf("Number of rectangles: %d\n", rectangles);
    
    return EXIT_SUCCESS;
}