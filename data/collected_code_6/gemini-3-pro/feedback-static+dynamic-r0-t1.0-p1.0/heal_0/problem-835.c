#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-9

typedef struct {
    double x;
    double y;
} Point;

int calculate_slope(Point p1, Point p2, double *slope) {
    if (slope == NULL) {
        return -1;
    }

    if (fabs(p2.x - p1.x) < EPSILON) {
        return 0;
    }

    *slope = (p2.y - p1.y) / (p2.x - p1.x);
    return 1;
}

int main(void) {
    Point p1 = {1.0, 2.0};
    Point p2 = {3.0, 4.0};
    double slope = 0.0;
    int result = 0;

    result = calculate_slope(p1, p2, &slope);

    if (result == 1) {
        printf("Slope: %f\n", slope);
    } else if (result == 0) {
        printf("Vertical line, slope is undefined.\n");
    } else {
        printf("Invalid arguments.\n");
    }

    p2.x = 1.0;
    
    result = calculate_slope(p1, p2, &slope);
    
    if (result == 1) {
        printf("Slope: %f\n", slope);
    } else if (result == 0) {
        printf("Vertical line, slope is undefined.\n");
    } else {
        printf("Invalid arguments.\n");
    }

    return EXIT_SUCCESS;
}