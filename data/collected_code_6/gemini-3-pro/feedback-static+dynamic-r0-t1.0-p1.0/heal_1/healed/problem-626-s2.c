#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>

double largest_triangle_area(double radius);

double largest_triangle_area(double radius) {
    if (radius < 0.0) {
        return -1.0;
    }
    return radius * radius;
}

int main(void) {
    char *input = NULL;
    size_t len = 0;
    ssize_t read_bytes;
    double radius;
    double area;
    char *endptr;

    read_bytes = getline(&input, &len, stdin);
    if (read_bytes == -1) {
        free(input);
        return EXIT_FAILURE;
    }

    radius = strtod(input, &endptr);
    if (endptr == input) {
        free(input);
        return EXIT_FAILURE;
    }

    area = largest_triangle_area(radius);
    if (area < 0.0) {
        free(input);
        return EXIT_FAILURE;
    }

    printf("%f\n", area);

    free(input);
    return EXIT_SUCCESS;
}