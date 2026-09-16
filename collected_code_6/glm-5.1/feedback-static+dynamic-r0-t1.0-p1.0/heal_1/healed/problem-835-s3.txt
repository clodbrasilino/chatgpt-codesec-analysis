#include <stdio.h>
#include <stdlib.h>

double calculate_slope(double x1, double y1, double x2, double y2) {
    if (x1 == x2) {
        fprintf(stderr, "Vertical line: slope is undefined.\n");
        exit(EXIT_FAILURE);
    }
    return (y2 - y1) / (x2 - x1);
}

int main(int argc, char * const argv[]) {
    double x1, y1, x2, y2, slope;

    if (argc != 5) {
        fprintf(stderr, "Usage: %s x1 y1 x2 y2\n", argv[0]);
        return EXIT_FAILURE;
    }

    x1 = strtod(argv[1], NULL);
    y1 = strtod(argv[2], NULL);
    x2 = strtod(argv[3], NULL);
    y2 = strtod(argv[4], NULL);

    slope = calculate_slope(x1, y1, x2, y2);
    printf("%f\n", slope);

    return EXIT_SUCCESS;
}