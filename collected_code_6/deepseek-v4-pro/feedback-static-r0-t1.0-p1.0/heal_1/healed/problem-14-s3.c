#include <stdio.h>
#include <stdlib.h>

double triangular_prism_volume(double base_triangle_base, double base_triangle_height, double prism_length) {
    if (base_triangle_base <= 0.0 || base_triangle_height <= 0.0 || prism_length <= 0.0) {
        return -1.0;
    }
    double base_area = 0.5 * base_triangle_base * base_triangle_height;
    return base_area * prism_length;
}

int main(void) {
    double base, height, length;
    char *input_buffer = NULL;
    size_t buffer_size = 0;
    ssize_t chars_read;

    printf("Enter base of triangular face: ");
    chars_read = getline(&input_buffer, &buffer_size, stdin);
    if (chars_read == -1) {
        fprintf(stderr, "Error reading input.\n");
        free(input_buffer);
        return EXIT_FAILURE;
    }
    if (sscanf(input_buffer, "%lf", &base) != 1) {
        fprintf(stderr, "Invalid input for base.\n");
        free(input_buffer);
        return EXIT_FAILURE;
    }

    printf("Enter height of triangular face: ");
    chars_read = getline(&input_buffer, &buffer_size, stdin);
    if (chars_read == -1) {
        fprintf(stderr, "Error reading input.\n");
        free(input_buffer);
        return EXIT_FAILURE;
    }
    if (sscanf(input_buffer, "%lf", &height) != 1) {
        fprintf(stderr, "Invalid input for height.\n");
        free(input_buffer);
        return EXIT_FAILURE;
    }

    printf("Enter length of prism: ");
    chars_read = getline(&input_buffer, &buffer_size, stdin);
    if (chars_read == -1) {
        fprintf(stderr, "Error reading input.\n");
        free(input_buffer);
        return EXIT_FAILURE;
    }
    if (sscanf(input_buffer, "%lf", &length) != 1) {
        fprintf(stderr, "Invalid input for length.\n");
        free(input_buffer);
        return EXIT_FAILURE;
    }

    free(input_buffer);
    input_buffer = NULL;

    double volume = triangular_prism_volume(base, height, length);
    if (volume < 0.0) {
        fprintf(stderr, "Dimensions must be positive numbers.\n");
        return EXIT_FAILURE;
    }

    printf("Volume of triangular prism: %.6f\n", volume);
    return EXIT_SUCCESS;
}