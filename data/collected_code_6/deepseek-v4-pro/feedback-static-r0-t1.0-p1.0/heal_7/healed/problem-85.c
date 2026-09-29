#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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
    char *input_line;
    size_t len;

    if (argc > 1) {
        errno = 0;
        radius = strtod(argv[1], &endptr);
        if (*endptr != '\0' || errno == ERANGE) {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
    } else {
        input_line = NULL;
        len = 0;

        printf("Enter radius: ");
        ssize_t read = getline(&input_line, &len, stdin);
        if (read == -1) {
            free(input_line);
            fprintf(stderr, "Error reading input\n");
            return EXIT_FAILURE;
        }

        if (read > 0 && read <= (ssize_t)len && input_line[read - 1] == '\n') {
            input_line[read - 1] = '\0';
            read--;
        }

        if (read == 0 || input_line[0] == '\0') {
            free(input_line);
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }

        errno = 0;
        radius = strtod(input_line, &endptr);
        if (*endptr != '\0' || errno == ERANGE) {
            free(input_line);
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
        free(input_line);
    }

    if (radius < 0.0) {
        fprintf(stderr, "Radius cannot be negative\n");
        return EXIT_FAILURE;
    }

    double area = sphere_surface_area(radius);
    printf("Surface area: %.10f\n", area);

    return EXIT_SUCCESS;
}