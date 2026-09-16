#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

int calculate_slope(Point p1, Point p2, double *slope) {
    if (slope == NULL) {
        return EXIT_FAILURE;
    }

    if (p1.x == p2.x) {
        return EXIT_FAILURE;
    }

    *slope = (p2.y - p1.y) / (p2.x - p1.x);

    return EXIT_SUCCESS;
}

int main(void) {
    Point a = {2.0, 3.0};
    Point b = {4.0, 7.0};
    double slope;

    if (calculate_slope(a, b, &slope) == EXIT_SUCCESS) {
        printf("%f\n", slope);
    } else {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}