#include <stdio.h>
#include <stdlib.h>

double calculate_parallelogram_area(double base, double height) {
    if (base < 0.0 || height < 0.0) {
        return -1.0;
    }
    return base * height;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <base> <height>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr_base;
    char *endptr_height;

    double base = strtod(argv[1], &endptr_base);
    double height = strtod(argv[2], &endptr_height);

    if (*endptr_base != '\0' || *endptr_height != '\0') {
        fprintf(stderr, "Invalid input: Parameters must be numeric.\n");
        return EXIT_FAILURE;
    }

    double area = calculate_parallelogram_area(base, height);

    if (area < 0.0) {
        fprintf(stderr, "Invalid input: Base and height must be non-negative.\n");
        return EXIT_FAILURE;
    }

    printf("%f\n", area);

    return EXIT_SUCCESS;
}