#include <stdio.h>
#include <stdlib.h>

double lateral_surface_area_cuboid(double length, double width, double height) {
    if (length < 0 || width < 0 || height < 0) {
        fprintf(stderr, "Error: Dimensions cannot be negative.\n");
        return -1.0;
    }
    return 2.0 * height * (length + width);
}

int main(void) {
    double length, width, height;
    char input_buffer[256];
    char *endptr;

    printf("Enter length: ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error: Failed to read input.\n");
        return EXIT_FAILURE;
    }
    length = strtod(input_buffer, &endptr);
    if (endptr == input_buffer || *endptr != '\n') {
        fprintf(stderr, "Error: Invalid input for length.\n");
        return EXIT_FAILURE;
    }

    printf("Enter width: ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error: Failed to read input.\n");
        return EXIT_FAILURE;
    }
    width = strtod(input_buffer, &endptr);
    if (endptr == input_buffer || *endptr != '\n') {
        fprintf(stderr, "Error: Invalid input for width.\n");
        return EXIT_FAILURE;
    }

    printf("Enter height: ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error: Failed to read input.\n");
        return EXIT_FAILURE;
    }
    height = strtod(input_buffer, &endptr);
    if (endptr == input_buffer || *endptr != '\n') {
        fprintf(stderr, "Error: Invalid input for height.\n");
        return EXIT_FAILURE;
    }

    double area = lateral_surface_area_cuboid(length, width, height);
    if (area < 0) {
        return EXIT_FAILURE;
    }

    printf("Lateral surface area: %.2f\n", area);
    return EXIT_SUCCESS;
}