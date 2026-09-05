#include <stdio.h>
#include <stdlib.h>

double calculate_trapezium_area(double a, double b, double h) {
    if (h < 0.0) {
        return -1.0;
    }
    return ((a + b) / 2.0) * h;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <base1> <base2> <height>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr1, *endptr2, *endptr3;
    double a = strtod(argv[1], &endptr1);
    double b = strtod(argv[2], &endptr2);
    double h = strtod(argv[3], &endptr3);

    if (*endptr1 != '\0' || *endptr2 != '\0' || *endptr3 != '\0') {
        fprintf(stderr, "Invalid input: all arguments must be valid numbers.\n");
        return EXIT_FAILURE;
    }

    double area = calculate_trapezium_area(a, b, h);
    if (area < 0.0) {
        fprintf(stderr, "Invalid input: height cannot be negative.\n");
        return EXIT_FAILURE;
    }

    printf("%.4f\n", area);

    return EXIT_SUCCESS;
}