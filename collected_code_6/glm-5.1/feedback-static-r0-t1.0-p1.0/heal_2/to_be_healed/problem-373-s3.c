#include <stdio.h>
#include <stdlib.h>

double calculate_cuboid_volume(double length, double width, double height) {
    return length * width * height;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <length> <width> <height>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    double length = strtod(argv[1], &endptr);
    if (*endptr != '\0' || length <= 0.0) {
        fprintf(stderr, "Invalid length\n");
        return EXIT_FAILURE;
    }

    double width = strtod(argv[2], &endptr);
    if (*endptr != '\0' || width <= 0.0) {
        fprintf(stderr, "Invalid width\n");
        return EXIT_FAILURE;
    }

    double height = strtod(argv[3], &endptr);
    if (*endptr != '\0' || height <= 0.0) {
        fprintf(stderr, "Invalid height\n");
        return EXIT_FAILURE;
    }

    double volume = calculate_cuboid_volume(length, width, height);
    printf("%.6f\n", volume);

    return EXIT_SUCCESS;
}