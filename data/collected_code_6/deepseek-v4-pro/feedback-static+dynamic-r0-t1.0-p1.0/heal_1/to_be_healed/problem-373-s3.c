#include <stdio.h>
#include <stdlib.h>

double calculate_cuboid_volume(double length, double width, double height) {
    return length * width * height;
}

int main(void) {
    double length, width, height, volume;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[128];

    printf("Enter length: ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    if (sscanf(input_buffer, "%lf", &length) != 1 || length <= 0) {
        fprintf(stderr, "Invalid input for length\n");
        return EXIT_FAILURE;
    }

    printf("Enter width: ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    if (sscanf(input_buffer, "%lf", &width) != 1 || width <= 0) {
        fprintf(stderr, "Invalid input for width\n");
        return EXIT_FAILURE;
    }

    printf("Enter height: ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    if (sscanf(input_buffer, "%lf", &height) != 1 || height <= 0) {
        fprintf(stderr, "Invalid input for height\n");
        return EXIT_FAILURE;
    }

    volume = calculate_cuboid_volume(length, width, height);
    printf("Volume of cuboid: %.2f\n", volume);

    return EXIT_SUCCESS;
}