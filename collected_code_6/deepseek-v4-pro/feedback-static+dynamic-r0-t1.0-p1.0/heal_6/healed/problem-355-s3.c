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
    char *input = NULL;
    size_t input_size = 0;
    ssize_t line_length;
    
    printf("Enter circle radius: ");
    line_length = getline(&input, &input_size, stdin);
    
    if (line_length == -1) {
        free(input);
        return EXIT_FAILURE;
    }
    
    if (line_length > 0 && input[line_length - 1] == '\n') {
        input[line_length - 1] = '\0';
        line_length--;
    }
    
    if (line_length == 0) {
        free(input);
        return EXIT_FAILURE;
    }
    
    char *endptr = NULL;
    
    errno = 0;
    double radius = strtod(input, &endptr);
    
    if (endptr == NULL || endptr == input || errno == ERANGE) {
        free(input);
        return EXIT_FAILURE;
    }
    
    if (radius < 0 || radius > DBL_MAX / 2.0) {
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
    if (rectangles < 0) {
        printf("Error: result overflow\n");
        return EXIT_FAILURE;
    }
    
    printf("Number of rectangles: %d\n", rectangles);
    
    return EXIT_SUCCESS;
}