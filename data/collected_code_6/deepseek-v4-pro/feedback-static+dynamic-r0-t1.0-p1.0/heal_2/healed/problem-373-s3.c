#include <stdio.h>
#include <stdlib.h>

double calculate_cuboid_volume(double length, double width, double height) {
    return length * width * height;
}

int main(void) {
    double length, width, height, volume;
    char *input_buffer = NULL;
    size_t buffer_size = 0;
    ssize_t read_length;

    printf("Enter length: ");
    read_length = getline(&input_buffer, &buffer_size, stdin);
    if (read_length == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input_buffer);
        return EXIT_FAILURE;
    }
    if (sscanf(input_buffer, "%lf", &length) != 1 || length <= 0) {
        fprintf(stderr, "Invalid input for length\n");
        free(input_buffer);
        return EXIT_FAILURE;
    }

    printf("Enter width: ");
    read_length = getline(&input_buffer, &buffer_size, stdin);
    if (read_length == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input_buffer);
        return EXIT_FAILURE;
    }
    if (sscanf(input_buffer, "%lf", &width) != 1 || width <= 0) {
        fprintf(stderr, "Invalid input for width\n");
        free(input_buffer);
        return EXIT_FAILURE;
    }

    printf("Enter height: ");
    read_length = getline(&input_buffer, &buffer_size, stdin);
    if (read_length == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input_buffer);
        return EXIT_FAILURE;
    }
    if (sscanf(input_buffer, "%lf", &height) != 1 || height <= 0) {
        fprintf(stderr, "Invalid input for height\n");
        free(input_buffer);
        return EXIT_FAILURE;
    }

    volume = calculate_cuboid_volume(length, width, height);
    printf("Volume of cuboid: %.2f\n", volume);

    free(input_buffer);
    return EXIT_SUCCESS;
}