#include <stdio.h>
#include <stdlib.h>

double find_slope(double x1, double y1, double x2, double y2) {
    if (x1 == x2) {
        printf("Undefined slope (vertical line)\n");
        return 0;
    }
    return (y2 - y1) / (x2 - x1);
}

int main() {
    double x1, y1, x2, y2;

    printf("Enter the first point (x1,y1): ");
    if (scanf("%lf %lf", &x1, &y1) != 2) {
        fprintf(stderr, "Invalid input for the first point.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the second point (x2,y2): ");
    if (scanf("%lf %lf", &x2, &y2) != 2) {
        fprintf(stderr, "Invalid input for the second point.\n");
        return EXIT_FAILURE;
    }

    double slope = find_slope(x1, y1, x2, y2);
    if (slope != 0) {
        printf("Slope of the line: %f\n", slope);
    }

    return 0;
}