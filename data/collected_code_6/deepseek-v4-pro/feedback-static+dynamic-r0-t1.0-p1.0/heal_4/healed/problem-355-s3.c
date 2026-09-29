#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <float.h>

int count_rectangles_in_circle(double radius) {
    if (radius <= 0) {
        return 0;
    }
    
    double max_radius = sqrt((double)INT_MAX);
    if (radius > max_radius) {
        radius = max_radius;
    }
    
    int count = 0;
    int r_int = (int)floor(radius);
    double r_squared = radius * radius;
    
    for (int x = 1; x <= r_int; x++) {
        double x_squared = (double)x * x;
        double y_max = sqrt(r_squared - x_squared);
        int max_y = (int)floor(y_max);
        if (max_y < 0) {
            continue;
        }
        for (int y = 1; y <= max_y; y++) {
            if ((long long)count + 1 > INT_MAX / 4) {
                return -1;
            }
            count++;
        }
    }
    
    return count * 4;
}

int main(void) {
    char input[128];
    size_t input_size = sizeof(input);
    
    printf("Enter circle radius: ");
    if (fgets(input, (int)input_size, stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    size_t len = 0;
    while (len < input_size && input[len] != '\0') {
        len++;
    }
    
    if (len == 0 || len >= input_size) {
        return EXIT_FAILURE;
    }
    
    if (input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }
    
    if (len == 0) {
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < len; i++) {
        if (input[i] == '\0') {
            break;
        }
    }
    
    char *endptr = NULL;
    char input_copy[128];
    size_t copy_size = len < sizeof(input_copy) - 1 ? len : sizeof(input_copy) - 1;
    memcpy(input_copy, input, copy_size);
    input_copy[copy_size] = '\0';
    
    errno = 0;
    double radius = strtod(input_copy, &endptr);
    
    if (endptr == NULL || endptr == input_copy || errno == ERANGE) {
        return EXIT_FAILURE;
    }
    
    if (radius < 0 || radius > DBL_MAX / 2.0) {
        return EXIT_FAILURE;
    }
    
    while (endptr != NULL && *endptr != '\0') {
        if (*endptr != ' ' && *endptr != '\t') {
            return EXIT_FAILURE;
        }
        endptr++;
    }
    
    int rectangles = count_rectangles_in_circle(radius);
    if (rectangles < 0) {
        printf("Error: result overflow\n");
        return EXIT_FAILURE;
    }
    
    printf("Number of rectangles: %d\n", rectangles);
    
    return EXIT_SUCCESS;
}