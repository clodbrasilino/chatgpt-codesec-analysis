#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define PI 3.14159265358979323846

double sphere_surface_area(double radius) {
    if (radius < 0.0) {
        return -1.0;
    }
    return 4.0 * PI * radius * radius;
}

int main(int argc, const char *argv[]) {
    double radius;
    char *endptr;

    if (argc > 1) {
        radius = strtod(argv[1], &endptr);
        if (*endptr != '\0') {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
    } else {
        char *input_buffer = NULL;
        size_t buffer_size = 0;
        ssize_t line_length;
        printf("Enter radius: ");
        line_length = getline(&input_buffer, &buffer_size, stdin);
        if (line_length == -1) {
            free(input_buffer);
            fprintf(stderr, "Error reading input\n");
            return EXIT_FAILURE;
        }
        if (line_length > 0 && input_buffer[line_length - 1] == '\n') {
            input_buffer[line_length - 1] = '\0';
        }
        radius = strtod(input_buffer, &endptr);
        if (*endptr != '\0') {
            free(input_buffer);
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
        free(input_buffer);
    }

    if (radius < 0.0) {
        fprintf(stderr, "Radius cannot be negative\n");
        return EXIT_FAILURE;
    }

    double area = sphere_surface_area(radius);
    printf("Surface area: %.10f\n", area);

    return EXIT_SUCCESS;
}