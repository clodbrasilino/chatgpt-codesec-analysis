#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

double calculate_trapezium_area(double a, double b, double h) {
    if (h < 0.0) {
        return -1.0;
    }
    return ((a + b) / 2.0) * h;
}

int main(int argc, char * const * const argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <base1> <base2> <height>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr1, *endptr2, *endptr3;
    errno = 0;
    double a = strtod(argv[1], &endptr1);
    if (errno == ERANGE || endptr1 == argv[1] || *endptr1 != '\0') {
        fprintf(stderr, "Invalid input: base1 must be a valid number.\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    double b = strtod(argv[2], &endptr2);
    if (errno == ERANGE || endptr2 == argv[2] || *endptr2 != '\0') {
        fprintf(stderr, "Invalid input: base2 must be a valid number.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    double h = strtod(argv[3], &endptr3);
    if (errno == ERANGE || endptr3 == argv[3] || *endptr3 != '\0') {
        fprintf(stderr, "Invalid input: height must be a valid number.\n");
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