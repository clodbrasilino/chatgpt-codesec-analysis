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
int main(int argc, char * const argv[]) {
    double base = 0.0;
    double height = 0.0;
    double area = 0.0;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <base> <height>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (sscanf(argv[1], "%lf", &base) != 1) {
        fprintf(stderr, "Invalid base value\n");
        return EXIT_FAILURE;
    }

    if (sscanf(argv[2], "%lf", &height) != 1) {
        fprintf(stderr, "Invalid height value\n");
        return EXIT_FAILURE;
    }

    area = calculate_parallelogram_area(base, height);

    if (area < 0.0) {
        fprintf(stderr, "Base and height must be non-negative\n");
        return EXIT_FAILURE;
    }

    printf("%f\n", area);

    return EXIT_SUCCESS;
}