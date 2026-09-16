#include <stdio.h>
#include <stdlib.h>

double find_trapezium_median(double a, double b) {
    return (a + b) / 2.0;
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <base1> <base2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr1;
    double a = strtod(argv[1], &endptr1);
    if (*endptr1 != '\0') {
        return EXIT_FAILURE;
    }

    char *endptr2;
    double b = strtod(argv[2], &endptr2);
    if (*endptr2 != '\0') {
        return EXIT_FAILURE;
    }

    double median = find_trapezium_median(a, b);
    printf("%.6f\n", median);

    return EXIT_SUCCESS;
}