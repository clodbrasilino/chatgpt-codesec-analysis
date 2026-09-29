#include <stdio.h>
#include <stdlib.h>

double calculate_triangular_prism_volume(double base_length, double height, double prism_length) {
    if (base_length < 0.0 || height < 0.0 || prism_length < 0.0) {
        return -1.0;
    }
    return 0.5 * base_length * height * prism_length;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <base_length> <height> <prism_length>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr_base, *endptr_height, *endptr_length;

    double base_length = strtod(argv[1], &endptr_base);
    double height = strtod(argv[2], &endptr_height);
    double prism_length = strtod(argv[3], &endptr_length);

    if (*endptr_base != '\0' || *endptr_height != '\0' || *endptr_length != '\0') {
        fprintf(stderr, "Invalid numeric input provided.\n");
        return EXIT_FAILURE;
    }

    double volume = calculate_triangular_prism_volume(base_length, height, prism_length);

    if (volume < 0.0) {
        fprintf(stderr, "Invalid dimensions: dimensions must be non-negative.\n");
        return EXIT_FAILURE;
    }

    printf("Volume: %.4f\n", volume);

    return EXIT_SUCCESS;
}