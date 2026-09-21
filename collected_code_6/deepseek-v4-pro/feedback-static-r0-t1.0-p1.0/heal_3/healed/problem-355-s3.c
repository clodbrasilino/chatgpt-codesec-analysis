#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

int count_rectangles_in_circle(double radius) {
    if (radius <= 0) {
        return 0;
    }
    
    int count = 0;
    int r_int = (int)floor(radius);
    
    for (int x = 1; x <= r_int; x++) {
        int max_y = (int)floor(sqrt(radius * radius - x * x));
        for (int y = 1; y <= max_y; y++) {
            count++;
        }
    }
    
    return count * 4;
}

int main(void) {
    double radius;
    char *line = NULL;
    size_t line_size = 0;
    ssize_t read_len;
    
    printf("Enter circle radius: ");
    read_len = getline(&line, &line_size, stdin);
    
    if (read_len == -1) {
        free(line);
        return EXIT_FAILURE;
    }
    
    if (read_len > 0 && line[read_len - 1] == '\n') {
        line[read_len - 1] = '\0';
        read_len--;
    }
    
    if (read_len == 0) {
        free(line);
        return EXIT_FAILURE;
    }
    
    char *endptr;
    errno = 0;
    radius = strtod(line, &endptr);
    
    if (errno == ERANGE) {
        free(line);
        return EXIT_FAILURE;
    }
    
    if (endptr == line || *endptr != '\0') {
        free(line);
        return EXIT_FAILURE;
    }
    
    free(line);
    
    int rectangles = count_rectangles_in_circle(radius);
    printf("Number of rectangles: %d\n", rectangles);
    
    return EXIT_SUCCESS;
}