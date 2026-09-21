#include <stdio.h>
#include <stdlib.h>

double cube_surface_area(double side_length) {
    if (side_length <= 0) {
        return -1.0;
    }
    return 6.0 * side_length * side_length;
}

int main(void) {
    double input;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *endptr;

    printf("Enter cube side length: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    input = strtod(buffer, &endptr);

    if (endptr == buffer || *endptr != '\n') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    double area = cube_surface_area(input);

    if (area < 0) {
        fprintf(stderr, "Side length must be positive\n");
        return EXIT_FAILURE;
    }

    printf("Surface area: %.2f\n", area);
    return EXIT_SUCCESS;
}