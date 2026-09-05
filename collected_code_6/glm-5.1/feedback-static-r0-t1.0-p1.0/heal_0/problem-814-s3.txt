#include <stdio.h>
#include <stdlib.h>

double calculate_rombus_area(double diagonal1, double diagonal2) {
    if (diagonal1 <= 0.0 || diagonal2 <= 0.0) {
        return -1.0;
    }
    return (diagonal1 * diagonal2) / 2.0;
}

int main(int argc, char *argv[]) {
    double d1, d2, area;

    if (argc != 3) {
        printf("Usage: %s <diagonal1> <diagonal2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (sscanf(argv[1], "%lf", &d1) != 1 || sscanf(argv[2], "%lf", &d2) != 1) {
        return EXIT_FAILURE;
    }

    area = calculate_rombus_area(d1, d2);

    if (area < 0.0) {
        return EXIT_FAILURE;
    }

    printf("%f\n", area);

    return EXIT_SUCCESS;
}