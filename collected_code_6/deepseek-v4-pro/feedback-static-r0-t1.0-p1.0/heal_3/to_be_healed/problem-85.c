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

    if (argc > 1) {
        errno = 0;
        radius = strtod(argv[1], &endptr);
        if (*endptr != '\0' || errno == ERANGE) {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
    } else {
        char *input_line = NULL;
        size_t len = 0;
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ssize_t read;

        printf("Enter radius: ");
        read = getline(&input_line, &len, stdin);
        if (read == -1) {
            free(input_line);
            fprintf(stderr, "Error reading input\n");
            return EXIT_FAILURE;
        }

        input_line[strcspn(input_line, "\n")] = '\0';

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