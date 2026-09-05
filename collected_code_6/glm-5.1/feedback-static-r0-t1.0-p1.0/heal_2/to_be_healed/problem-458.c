#include <stdio.h>
#include <stdlib.h>

double area_rectangle(double width, double height) {
    if (width < 0.0 || height < 0.0) {
        return -1.0;
    }
    return width * height;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <width> <height>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    double width = strtod(argv[1], &endptr);
    if (*endptr != '\0' || width < 0.0) {
        fprintf(stderr, "Invalid width\n");
        return EXIT_FAILURE;
    }

    double height = strtod(argv[2], &endptr);
    if (*endptr != '\0' || height < 0.0) {
        fprintf(stderr, "Invalid height\n");
        return EXIT_FAILURE;
    }

    double area = area_rectangle(width, height);
    if (area < 0.0) {
        fprintf(stderr, "Invalid area calculation\n");
        return EXIT_FAILURE;
    }

    printf("%f\n", area);
    return EXIT_SUCCESS;
}