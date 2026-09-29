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

    double dx = p2.x - p1.x;
    
    if (fabs(dx) < EPSILON) {
        return 0;
    }

    *slope = (p2.y - p1.y) / dx;
    return 1;
}

int main(void) {
    Point p1 = {1.0, 2.0};
    Point p2 = {3.0, 6.0};
    double slope = 0.0;
    int result;

    result = calculate_slope(p1, p2, &slope);

    if (result == 1) {
        printf("The slope of the line is: %f\n", slope);
    } else if (result == 0) {
        printf("The line is vertical. Slope is undefined.\n");
    } else {
        printf("Invalid arguments provided.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}