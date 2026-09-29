#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <float.h>

int validate_dimension(double value, const char *name) {
    if (errno == ERANGE || value <= 0.0 || value > DBL_MAX || isnan(value) || isinf(value)) {
        fprintf(stderr, "Error: %s must be a positive finite number.\n", name);
        return 0;
    }
    return 1;
}

double triangular_prism_volume(double base, double height, double length) {
    double volume;

    if (!validate_dimension(base, "base") ||
        !validate_dimension(height, "height") ||
        !validate_dimension(length, "length")) {
        return -1.0;
    }

    if (base > DBL_MAX / height) {
        fprintf(stderr, "Error: base * height overflows.\n");
        return -1.0;
    }

    volume = (base * height * length) / 2.0;

    if (isinf(volume) || isnan(volume)) {
        fprintf(stderr, "Error: Volume calculation overflow.\n");
        return -1.0;
    }

    return volume;
}

int main(void) {
    double base, height, length, volume;
    char input_buffer[256];
    char *endptr;

    printf("Enter base of triangular prism: ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }
    errno = 0;
    base = strtod(input_buffer, &endptr);
    if (endptr == input_buffer || *endptr != '\n') {
        fprintf(stderr, "Error: Invalid input for base.\n");
        return EXIT_FAILURE;
    }

    printf("Enter height of triangular prism: ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }
    errno = 0;
    height = strtod(input_buffer, &endptr);
    if (endptr == input_buffer || *endptr != '\n') {
        fprintf(stderr, "Error: Invalid input for height.\n");
        return EXIT_FAILURE;
    }

    printf("Enter length of triangular prism: ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }
    errno = 0;
    length = strtod(input_buffer, &endptr);
    if (endptr == input_buffer || *endptr != '\n') {
        fprintf(stderr, "Error: Invalid input for length.\n");
        return EXIT_FAILURE;
    }

    volume = triangular_prism_volume(base, height, length);
    if (volume < 0.0) {
        return EXIT_FAILURE;
    }

    printf("Volume of triangular prism: %.6f\n", volume);

    return EXIT_SUCCESS;
}