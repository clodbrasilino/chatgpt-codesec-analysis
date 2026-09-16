#include <stdio.h>
#include <stdlib.h>

double calculate_rombus_area(double diagonal1, double diagonal2) {
    if (diagonal1 <= 0.0 || diagonal2 <= 0.0) {
        return 0.0;
    }
    return 0.5 * diagonal1 * diagonal2;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <diagonal1> <diagonal2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr1 = NULL;
    char *endptr2 = NULL;
    double d1 = strtod(argv[1], &endptr1);
    double d2 = strtod(argv[2], &endptr2);

    if (endptr1 == argv[1] || *endptr1 != '\0' || endptr2 == argv[2] || *endptr2 != '\0') {
        fprintf(stderr, "Invalid input: Arguments must be valid numerical values.\n");
        return EXIT_FAILURE;
    }

    double area = calculate_rombus_area(d1, d2);

    if (area == 0.0) {
        fprintf(stderr, "Invalid input: Diagonals must be strictly positive.\n");
        return EXIT_FAILURE;
    }

    printf("%f\n", area);

    return EXIT_SUCCESS;
}