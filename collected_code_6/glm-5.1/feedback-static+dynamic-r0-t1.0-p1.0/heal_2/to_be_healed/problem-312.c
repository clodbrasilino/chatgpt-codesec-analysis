#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_cone_volume(double radius, double height) {
    if (radius < 0.0 || height < 0.0) {
        return -1.0;
    }
    return (1.0 / 3.0) * M_PI * radius * radius * height;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    double radius = 0.0;
    double height = 0.0;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <radius> <height>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    radius = strtod(argv[1], &endptr);
    if (*endptr != '\0') {
        return EXIT_FAILURE;
    }

    height = strtod(argv[2], &endptr);
    if (*endptr != '\0') {
        return EXIT_FAILURE;
    }

    double volume = calculate_cone_volume(radius, height);
    if (volume < 0.0) {
        return EXIT_FAILURE;
    }

    printf("%.6f\n", volume);

    return EXIT_SUCCESS;
}