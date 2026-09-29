#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    int valid;
    double slope;
} SlopeResult;

SlopeResult calc_slope(Point p1, Point p2) {
    SlopeResult result;
    
    if (fabs(p2.x - p1.x) < 1e-10) {
        result.valid = 0;
        result.slope = 0.0;
        return result;
    }
    
    result.valid = 1;
    result.slope = (p2.y - p1.y) / (p2.x - p1.x);
    return result;
}

int main(void) {
    Point point1 = {1.0, 2.0};
    Point point2 = {3.0, 6.0};
    SlopeResult result = calc_slope(point1, point2);
    
    if (result.valid) {
        printf("The slope is: %.2f\n", result.slope);
    } else {
        fprintf(stderr, "Error: Division by zero or vertical line\n");
        return EXIT_FAILURE;
    }
    
    Point point3 = {2.0, 1.0};
    Point point4 = {2.0, 5.0};
    SlopeResult result2 = calc_slope(point3, point4);
    
    if (result2.valid) {
        printf("The slope is: %.2f\n", result2.slope);
    } else {
        fprintf(stderr, "Error: Division by zero or vertical line\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}